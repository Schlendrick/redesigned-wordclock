#include <Wire.h> //https://www.arduino.cc/en/Reference/Wire
#include <LiquidCrystal_I2C.h> //https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
#include <DS3232RTC.h> //https://github.com/JChristensen/DS3232RTC
#include <Bounce2.h> //https://github.com/thomasfredericks/Bounce2
#include <SimpleTimer.h> //https://github.com/jfturcot/SimpleTimer
#include <FAB_LED.h> //https://github.com/sonyhome/FAB_LED
#include <DHT.h> //https://github.com/adafruit/DHT-sensor-library
#include <Adafruit_Sensor.h> //https://github.com/adafruit/Adafruit_Sensor

//define adresses
#define DS3231_ADDRESS 0x68
#define BUTTON_HOUR 8
#define BUTTON_MIN 9
#define BUTTON_MODE 10
#define LEDPIN 6
#define DHTPIN 7
#define LDRPIN A1

//define wordclock modes
#define CLOCK_LDR 0
#define CLOCK_100_PER_MODE 1
#define TEMPERATUR_MODE 2
#define HEART_MODE 3
#define OFF_MODE 4

// Declare the LED protocol and the port
sk6812<D, LEDPIN>  strip;
//ws2812b<D, 6>  strip;

/* ************** LED BLOCK ************** */
// How many pixels to control
const uint8_t numPixels = 115;
// The pixel array to display
rgbw pixels[numPixels] = {};
// define brightness var
uint8_t ledBrightness = 255;
uint8_t ledBrightnessRGBWhite = 0;
uint8_t ledBrightnessLEDWhite = 0;

/* ************** TEMP BLOCK ************** */
//correct temp
const int tempOffset = 0;
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
float tempDHT11;
float tempDS3231;
float roomTemperature;

/* ************** LCD BLOCK ************** */
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ************** BUTTON BLOCK ************** */
//define Bouncer & delay variables
Bounce debouncerHour = Bounce();
Bounce debouncerMin = Bounce();
Bounce debouncerMode = Bounce();
bool bolMinSet = false;
bool bolHourSet = false;
bool bolModeSet = false;
int modeSelector = 0;

/* ************** SERIAL BLOCK ************** */
int serialOutputCounter = 0;

/* ************** TIMER BLOCK ************** */
//define Timer
SimpleTimer timerClock;
SimpleTimer timerTemp;

void setup()
{
  // Turn off the LEDs
  strip.clear(2 * numPixels);

  //intialize RTC
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");

  //start output Timer
  timerClock.setInterval(100, processTimesOutput);
  timerTemp.setInterval(5000, getTemperatures);

  //intialize wire
  Wire.begin();

  //intialize serial
  Serial.begin(9600);

  // Setup the button with an internal pull-up, attach bouncer , set bounceinterval
  pinMode(BUTTON_HOUR, INPUT_PULLUP);
  debouncerHour.attach(BUTTON_HOUR);
  debouncerHour.interval(5); // interval in ms
  pinMode(BUTTON_MIN, INPUT_PULLUP);
  debouncerMin.attach(BUTTON_MIN);
  debouncerMin.interval(5); // interval in ms
  pinMode(BUTTON_MODE, INPUT_PULLUP);
  debouncerMode.attach(BUTTON_MODE);
  debouncerMode.interval(5); // interval in ms

  //initialize temps
  dht.begin();
  getTemperatures();
  if (isnan(tempDHT11)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // initialize the LCD
  lcd.begin();
  lcd.backlight();
}

void loop()
{
  //run timer (check)
  timerClock.run();
  timerTemp.run();
  checkButtons();
}

////////////////////////////////////////////////////////////////////////////////
// Calculate LED
////////////////////////////////////////////////////////////////////////////////
void calculateAndPushLED () {
  //reset all leds to "dark"
  for (int i = 0; i < numPixels; i++) {
    //pre define every led as "off"
    updateLED(i, 0, 0 , 0, 0);
  }

  switch (modeSelector) {
    case CLOCK_100_PER_MODE:
      ledBrightness = 255;
      generateClockMatrix();
      break;
    case CLOCK_LDR:
      ledBrightness = 5 + ((1000 - analogRead(LDRPIN)) / 4);
      generateClockMatrix();
      break;
    case TEMPERATUR_MODE:
      ledBrightness = 255;
      generateTempMatrix();
      break;
    case HEART_MODE:
      ledBrightness = 255;
      pushHeart();
      break;
    case OFF_MODE:
      //Nothing
      break;
  }

  //sk6812:
  ledBrightnessRGBWhite = 0;
  ledBrightnessLEDWhite = ledBrightness;

  //ws2812b
  //ledBrightnessRGBWhite = ledBrightness;
  //ledBrightnessLEDWhite = 0;

  //activate matrix on hardware
  strip.sendPixels(numPixels, pixels);
}

////////////////////////////////////////////////////////////////////////////////
// Generate Clock Matrix
////////////////////////////////////////////////////////////////////////////////
void generateClockMatrix() {
  //Update LED (ID, R, G, B, White)
  pushES_IST();
  pushUHR;

  //prepair time
  int myMin = minute();
  int myHour = hour();
  //remove 12hours if afternoon
  if (myHour >= 12)
    myHour -= 12;

  //calculate hours
  switch (myHour) {
    case 0: pushZWOELF(); break;
    case 1: if (myMin > 4) {
        pushEINS();
      } else {
        pushEIN();
      } break;
    case 2: pushZWEI(); break;
    case 3: pushDREI(); break;
    case 4: pushVIER(); break;
    case 5: pushFUENF2(); break;
    case 6: pushSECHS(); break;
    case 7: pushSIEBEN(); break;
    case 8: pushACHT(); break;
    case 9: pushNEUN(); break;
    case 10: pushZEHN(); break;
    case 11: pushELF(); break;
  }

  //calculate minutes
  switch (myMin) {
    case 0: case 1: case 2: case 3: case 4:
      /* NICHTS */ break;
    case 5: case 6: case 7: case 8: case 9:
      pushFUENF1(); pushNACH(); break;
    case 10: case 11: case 12: case 13: case 14:
      pushZEHN1(); pushNACH(); break;
    case 15: case 16: case 17: case 18: case 19:
      pushVIERTEL(); pushNACH(); break;
    case 20: case 21: case 22: case 23: case 24:
      pushZWANZIG(); pushNACH(); break;
    case 25: case 26: case 27: case 28: case 29:
      pushFUENF1(); pushVOR(); pushHALB(); break;
    case 30: case 31: case 32: case 33: case 34:
      pushHALB(); break;
    case 35: case 36: case 37: case 38: case 39:
      pushFUENF1(); pushNACH(); pushHALB(); break;
    case 40: case 41: case 42: case 43: case 44:
      pushZWANZIG(); pushVOR(); break;
    case 45: case 46: case 47: case 48: case 49:
      pushVIERTEL(); pushVOR(); break;
    case 50: case 51: case 52: case 53: case 54:
      pushZEHN1(); pushVOR(); break;
    case 55: case 56: case 57: case 58: case 59:
      pushFUENF1(); pushVOR(); break;
  }

  //calculate sinlge dots (corner-minutes)
  int singleMinutes = myMin % 5;
  switch (singleMinutes) {
    case 1: pushONE(); break;
    case 2: pushONE(); pushTWO(); break;
    case 3: pushONE(); pushTWO(); pushTHREE(); break;
    case 4: pushONE(); pushTWO(); pushTHREE(); pushFOUR(); break;
  }
}

////////////////////////////////////////////////////////////////////////////////
// Generate Temprature Matrix
////////////////////////////////////////////////////////////////////////////////
void generateTempMatrix() {
  int secondDigit = (int)roomTemperature % 10;
  int firstDigit = ((int)roomTemperature - secondDigit) / 10;

  pushTempDegree();

  switch (firstDigit) {
    case 1: pushTempLOne(); break;
    case 2: pushTempLTwo(); break;
    case 3: pushTempLThree(); break;
    case 4: pushTempLFour(); break;
  }
  switch (secondDigit) {
    case 0: pushTempRZero(); break;
    case 1: pushTempROne(); break;
    case 2: pushTempRTwo(); break;
    case 3: pushTempRThree(); break;
    case 4: pushTempRFour(); break;
    case 5: pushTempRFive(); break;
    case 6: pushTempRSix(); break;
    case 7: pushTempRSeven(); break;
    case 8: pushTempREight(); break;
    case 9: pushTempRNine(); break;
  }
}

////////////////////////////////////////////////////////////////////////////////
// Output the time to different media
////////////////////////////////////////////////////////////////////////////////
void processTimesOutput() {
  //cycle 0-9 for output to slow serial down
  serialOutputCounter++; if (serialOutputCounter > 9) serialOutputCounter = 0;

  calculateAndPushLED();
  String rowOne = String(hour()) + ":" + String(minute()) + ":" + String(second()) + " | Mode" + modeSelector;
  String rowTwo = String(tempDS3231) + "\xDF" + "C " + String((1000 - analogRead(LDRPIN)) / 10) + "%LDR";
  printDebugOnLCD(rowOne, rowTwo);
  printDebugOnConsole(rowOne, rowTwo);
}

////////////////////////////////////////////////////////////////////////////////
// Check if Buttons are pushed
////////////////////////////////////////////////////////////////////////////////
void checkButtons() {
  //Update Bouncer & gather button status
  debouncerHour.update();
  debouncerMin.update();
  debouncerMode.update();
  int buttonHour = debouncerHour.read();
  int buttonMin = debouncerMin.read();
  int buttonMode = debouncerMode.read();

  if (buttonHour == LOW && bolHourSet == false) {
    bolHourSet = true;
    setTime(hour() + 1, minute(), 0, 17, 7, 2017);
    RTC.set(now());
  } else if (buttonHour == HIGH) {
    bolHourSet = false;
  }

  if (buttonMin == LOW && bolMinSet == false) {
    bolMinSet = true;
    //check if time change would result in adding an hour
    if (minute() == 59)
      setTime(hour() - 1, minute() + 1, 0, 17, 7, 2017);
    else
      setTime(hour(), minute() + 1, 0, 17, 7, 2017);
    RTC.set(now());
  } else if (buttonMin == HIGH) {
    bolMinSet = false;
  }

  if (buttonMode == LOW && bolModeSet == false) {
    bolModeSet = true;

    //increment mode and reset if too high
    modeSelector++;
    if (modeSelector == 5)
      modeSelector = 0;
    Serial.println("MODE Selected: " + String(modeSelector));
  } else if (buttonMode == HIGH) {
    bolModeSet = false;
  }

}

////////////////////////////////////////////////////////////////////////////////
// Write current time and temp ond LCD
////////////////////////////////////////////////////////////////////////////////
void printDebugOnLCD(String rowOne, String rowTwo) {
  for (int i = 0; i < (16 - rowTwo.length()); i++)
    rowOne += ' ';
  for (int i = 0; i < (16 - rowTwo.length()); i++)
    rowTwo += ' ';
  lcd.setCursor( 0, 0);
  lcd.print( rowOne );
  lcd.setCursor( 0, 1);
  lcd.print( rowTwo );
}

////////////////////////////////////////////////////////////////////////////////
// Write current time and temp ond LCD
////////////////////////////////////////////////////////////////////////////////
void printDebugOnConsole(String rowOne, String rowTwo) {
  if (serialOutputCounter == 0) {
    Serial.println( "******************" );
    Serial.println( rowOne );
    Serial.println( rowTwo );
  }
}

////////////////////////////////////////////////////////////////////////////////
// Reads temperature sensor of DS3231&DHT11 and write to variable
////////////////////////////////////////////////////////////////////////////////
void getTemperatures() {
  tempDS3231 = getDS3231Temprature();
  tempDHT11 = getDHT11Temprature();
  roomTemperature = tempDHT11;
}

////////////////////////////////////////////////////////////////////////////////
// Reads temperature sensor of DS3231
////////////////////////////////////////////////////////////////////////////////
float getDS3231Temprature() {
  // Read temperature of DS3231
  float temp;
  int msb, lsb;
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0x11); // DS3231 Register in 11h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS, 2); // Get 2 Byte Data from DS3231
  msb = Wire.read();
  lsb = Wire.read();
  temp = ((msb << 2) + (lsb >> 6) ) / 4.0;
  return temp + tempOffset;
}

////////////////////////////////////////////////////////////////////////////////
// Reads temperature sensor of DHT11
////////////////////////////////////////////////////////////////////////////////
float getDHT11Temprature() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temp = dht.readTemperature();
  return temp + tempOffset;
}

////////////////////////////////////////////////////////////////////////////////
// Sets the led to specified color (ledID/R/G/B/White)
////////////////////////////////////////////////////////////////////////////////
void updateLED(int i, char r, char g, char b, char w)
{
  pixels[i].r = g; //fix some errors with strip?
  pixels[i].g = r; //fix some errors with strip?
  pixels[i].b = b;
  pixels[i].w = w;
}

////////////////////////////////////////////////////////////////////////////////
// PUSHES FOR STRIP
////////////////////////////////////////////////////////////////////////////////
void pushES_IST()  {
  updateLED(99, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(100, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(102, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(103, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(104, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushFUENF1() {
  updateLED(106, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(107, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(108, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(109, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushFUENF2() {
  updateLED(62, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(63, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(64, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(65, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushNACH() {
  updateLED(69, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(68, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(67, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(66, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushZEHN1() {
  updateLED(98, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(97, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(96, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(95, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushVIERTEL() {
  updateLED(81, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(82, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(83, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(84, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(85, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(86, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(87, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushVOR() {
  updateLED(76, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(75, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(74, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushHALB() {
  updateLED(55, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(56, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(57, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(58, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushONE() {
  updateLED(111, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTWO() {
  updateLED(110, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTHREE() {
  updateLED(113, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushFOUR() {
  updateLED(112, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushZWANZIG() {
  updateLED(94, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(93, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(92, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(91, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(90, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(89, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(88, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushZWOELF() {
  updateLED(17, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(18, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(19, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(20, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(21, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushEINS() {
  updateLED(54, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(53, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(52, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(51, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushEIN() {
  updateLED(54, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(53, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(52, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushZWEI() {
  updateLED(47, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(46, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(45, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(44, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushDREI() {
  updateLED(33, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(34, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(35, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(36, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushVIER() {
  updateLED(40, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(41, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(42, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(43, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushSECHS() {
  updateLED(32, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(31, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(30, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(29, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(28, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushSIEBEN() {
  updateLED(11, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(12, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(13, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(14, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(15, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(16, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushACHT() {
  updateLED(25, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(24, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(23, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(22, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushNEUN() {
  updateLED(7, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(6, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(5, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(4, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushZEHN() {
  updateLED(10, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(9, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(8, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(7, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushELF() {
  updateLED(60, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(61, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(62, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushUHR() {
  updateLED(2, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(1, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(0, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushHeart() {
  updateLED(101, ledBrightness, 0, 0, 0);
  updateLED(102, ledBrightness, 0, 0, 0);
  updateLED(106, ledBrightness, 0, 0, 0);
  updateLED(107, ledBrightness, 0, 0, 0);
  updateLED(97, ledBrightness, 0, 0, 0);
  updateLED(94, ledBrightness, 0, 0, 0);
  updateLED(92, ledBrightness, 0, 0, 0);
  updateLED(89, ledBrightness, 0, 0, 0);
  updateLED(77, ledBrightness, 0, 0, 0);
  updateLED(82, ledBrightness, 0, 0, 0);
  updateLED(87, ledBrightness, 0, 0, 0);
  updateLED(76, ledBrightness, 0, 0, 0);
  updateLED(66, ledBrightness, 0, 0, 0);
  updateLED(55, ledBrightness, 0, 0, 0);
  updateLED(65, ledBrightness, 0, 0, 0);
  updateLED(53, ledBrightness, 0, 0, 0);
  updateLED(45, ledBrightness, 0, 0, 0);
  updateLED(35, ledBrightness, 0, 0, 0);
  updateLED(41, ledBrightness, 0, 0, 0);
  updateLED(29, ledBrightness, 0, 0, 0);
  updateLED(25, ledBrightness, 0, 0, 0);
  updateLED(17, ledBrightness, 0, 0, 0);
  updateLED(15, ledBrightness, 0, 0, 0);
  updateLED(5, ledBrightness, 0, 0, 0);
}
void pushTempDegree() {
  updateLED(108, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(90, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(88, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED(86, ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempLOne() {
  updateLED( 73 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 57 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 58 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 53 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 51 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 36 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 29 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 14 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempLTwo() {
  updateLED( 75 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 74 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 73 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 58 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 53 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 52 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 51 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 34 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 31 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 12 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 13 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 14 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempLThree() {
  updateLED( 75 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 74 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 73 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 58 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 53 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 52 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 51 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 36 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 29 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 12 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 13 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 14 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempLFour() {
  updateLED( 75 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 73 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 56 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 58 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 53 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 52 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 51 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 36 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 29 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 14 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempRZero() {
  updateLED( 71 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 70 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 69 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 60 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 62 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 49 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 47 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 38 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 40 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 27 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 25 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 16 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 17 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 18 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempROne() {
  updateLED( 69 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 61 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 62 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 49 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 47 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 40 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 25 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 18 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempRTwo() {
  updateLED( 71 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 70 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 69 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 62 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 49 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 48 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 47 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 38 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 27 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 16 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 17 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 18 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempRThree() {
  updateLED( 71 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 70 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 69 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 62 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 49 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 48 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 47 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 40 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 25 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 16 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 17 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 18 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempRFour() {
  updateLED( 71 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 69 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 60 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 62 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 49 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 48 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 47 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 40 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 25 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 18 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempRFive() {
  updateLED( 71 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 70 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 69 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 60 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 49 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 48 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 47 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 40 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 25 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 16 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 17 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 18 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempRSix() {
  updateLED( 71 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 70 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 69 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 60 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 49 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 48 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 47 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 38 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 40 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 27 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 25 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 16 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 17 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 18 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempRSeven() {
  updateLED( 71 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 70 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 69 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 62 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 47 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 40 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 25 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 18 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempREight() {
  updateLED( 71 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 70 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 69 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 60 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 62 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 49 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 48 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 47 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 38 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 40 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 27 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 25 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 16 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 17 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 18 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}
void pushTempRNine() {
  updateLED( 71 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 70 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 69 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 60 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 62 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 49 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 48 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 47 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 40 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 25 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 16 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 17 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
  updateLED( 18 , ledBrightnessRGBWhite, ledBrightnessRGBWhite, ledBrightnessRGBWhite , ledBrightnessLEDWhite);
}

