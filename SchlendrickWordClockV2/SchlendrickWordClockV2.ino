#include <Wire.h> //https://www.arduino.cc/en/Reference/Wire
#include <LiquidCrystal_I2C.h> //https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
#include <DS3232RTC.h> //https://github.com/JChristensen/DS3232RTC
#include <Bounce2.h> //https://github.com/thomasfredericks/Bounce2
#include <SimpleTimer.h> //https://github.com/jfturcot/SimpleTimer
#include <FAB_LED.h> //https://github.com/sonyhome/FAB_LED
#include <DHT.h> //https://github.com/adafruit/DHT-sensor-library
#include <Adafruit_Sensor.h> //https://github.com/adafruit/Adafruit_Sensor
//#include <DCF77.h>
//#include <TimeLib.h>

//define adresses
#define DS3231_ADDRESS 0x68
#define BUTTON_HOUR 8
#define BUTTON_MIN 9
#define BUTTON_MODE 10
#define LEDPIN 6
#define DHTPIN 7
#define LDRPIN A1
//#define DCF_PIN 2           // Connection pin to DCF 77 device
//#define DCF_INTERRUPT 0    // Interrupt number associated with pin

//define wordclock modes
#define CLOCK_LDR 0
#define CLOCK_100_PER_MODE 1
#define TEMPERATUR_MODE 2
#define HEART_MODE 3
#define OFF_MODE 4

// Declare the LED protocol and the port
sk6812<D, LEDPIN>  strip;
//ws2812b<D, 6>  strip;

/* ************** DCF BLOCK ************** */
//time_t time;
//DCF77 DCF = DCF77(DCF_PIN, 0);

/* ************** LED BLOCK ************** */
// How many pixels to control
const uint8_t numPixels = 115;
// The pixel array to display
rgbw pixels[numPixels] = {};
// define brightness var
uint8_t ledBrightness = 255;

/* ************** TEMP BLOCK ************** */
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
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

  //intialize DCF
  //DCF.Start();

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
  if (isnan(roomTemperature)) {
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
    case CLOCK_LDR: //25 so dass sicher im positiven Bereich
      ledBrightness = 25 + ((1000 - analogRead(LDRPIN)) / 4);
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
      /*
        case ALL_ON_MODE:
        for (int i = 0; i < numPixels; i++) {
        //pre define every led as "off"
        updateLED(i, 0, 0 , 0, 111);
        }
      */
      break;
  }

  //activate matrix on hardware
  strip.sendPixels(numPixels, pixels);
}

////////////////////////////////////////////////////////////////////////////////
// Generate Clock Matrix
////////////////////////////////////////////////////////////////////////////////
void generateClockMatrix() {
  //Update LED (ID, R, G, B, White)
  pushES_IST();

  //prepair time
  int myMin = minute();
  int myHour = hour();

  if (myMin >= 25) // USE CASE "VOR"/"HALB"
    myHour += 1;
  if (myHour >= 12) // 24h auf 12h brechen
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
      pushUHR(); break;
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
// Output the time to different media
////////////////////////////////////////////////////////////////////////////////
void processTimesOutput() {
  calculateAndPushLED();
  String rowOne = String(hour()) + ":" + String(minute()) + ":" + String(second()) + " | Mode" + modeSelector;
  String rowTwo = String(roomTemperature) + "\xDF" + "C " + String((1000 - analogRead(LDRPIN)) / 10) + "%LDR";
  printDebugOnLCD(rowOne, rowTwo);
  printDebugOnConsole(rowOne, rowTwo);
}

////////////////////////////////////////////////////////////////////////////////
// Write current Debug on LCD
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
// Write current Debug on console
////////////////////////////////////////////////////////////////////////////////
void printDebugOnConsole(String rowOne, String rowTwo) {
  getDCFTime();
  //cycle 0-9 for output to slow serial down
  serialOutputCounter++; if (serialOutputCounter > 9) serialOutputCounter = 0;
  if (serialOutputCounter == 0) {
    Serial.println( "******************" );
    Serial.println( rowOne );
    Serial.println( rowTwo );
  }
}

////////////////////////////////////////////////////////////////////////////////
// Get DCF Time
////////////////////////////////////////////////////////////////////////////////
void getDCFTime()  {
  /*
    time_t DCFtime = DCF.getTime(); // Check if new DCF77 time is available
    if (DCFtime != 0)
    {
      Serial.println("=================================================");
      Serial.println("Time is updated");
      Serial.println("=================================================");
      //setTime(DCFtime);
      printDebugOnLCD("Time is updated", "Time is updated");
    }
  */
}

////////////////////////////////////////////////////////////////////////////////
// Reads temperature sensor of DS3231&DHT11 and write to variable
////////////////////////////////////////////////////////////////////////////////
void getTemperatures() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  roomTemperature = dht.readTemperature();
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
  updateLED(99, 0, 0, 0, ledBrightness);
  updateLED(100, 0, 0, 0, ledBrightness);
  updateLED(102, 0, 0, 0, ledBrightness);
  updateLED(103, 0, 0, 0, ledBrightness);
  updateLED(104, 0, 0, 0, ledBrightness);
}
void pushFUENF1() {
  updateLED(106, 0, 0, 0, ledBrightness);
  updateLED(107, 0, 0, 0, ledBrightness);
  updateLED(108, 0, 0, 0, ledBrightness);
  updateLED(109, 0, 0, 0, ledBrightness);
}
void pushFUENF2() {
  updateLED(62, 0, 0, 0, ledBrightness);
  updateLED(63, 0, 0, 0, ledBrightness);
  updateLED(64, 0, 0, 0, ledBrightness);
  updateLED(65, 0, 0, 0, ledBrightness);
}
void pushNACH() {
  updateLED(69, 0, 0, 0, ledBrightness);
  updateLED(68, 0, 0, 0, ledBrightness);
  updateLED(67, 0, 0, 0, ledBrightness);
  updateLED(66, 0, 0, 0, ledBrightness);
}
void pushZEHN1() {
  updateLED(98, 0, 0, 0, ledBrightness);
  updateLED(97, 0, 0, 0, ledBrightness);
  updateLED(96, 0, 0, 0, ledBrightness);
  updateLED(95, 0, 0, 0, ledBrightness);
}
void pushVIERTEL() {
  updateLED(81, 0, 0, 0, ledBrightness);
  updateLED(82, 0, 0, 0, ledBrightness);
  updateLED(83, 0, 0, 0, ledBrightness);
  updateLED(84, 0, 0, 0, ledBrightness);
  updateLED(85, 0, 0, 0, ledBrightness);
  updateLED(86, 0, 0, 0, ledBrightness);
  updateLED(87, 0, 0, 0, ledBrightness);
}
void pushVOR() {
  updateLED(76, 0, 0, 0, ledBrightness);
  updateLED(75, 0, 0, 0, ledBrightness);
  updateLED(74, 0, 0, 0, ledBrightness);
}
void pushHALB() {
  updateLED(55, 0, 0, 0, ledBrightness);
  updateLED(56, 0, 0, 0, ledBrightness);
  updateLED(57, 0, 0, 0, ledBrightness);
  updateLED(58, 0, 0, 0, ledBrightness);
}
void pushONE() {
  updateLED(111, 0, 0, 0, ledBrightness);
}
void pushTWO() {
  updateLED(110, 0, 0, 0, ledBrightness);
}
void pushTHREE() {
  updateLED(113, 0, 0, 0, ledBrightness);
}
void pushFOUR() {
  updateLED(112, 0, 0, 0, ledBrightness);
}
void pushZWANZIG() {
  updateLED(94, 0, 0, 0, ledBrightness);
  updateLED(93, 0, 0, 0, ledBrightness);
  updateLED(92, 0, 0, 0, ledBrightness);
  updateLED(91, 0, 0, 0, ledBrightness);
  updateLED(90, 0, 0, 0, ledBrightness);
  updateLED(89, 0, 0, 0, ledBrightness);
  updateLED(88, 0, 0, 0, ledBrightness);
}
void pushZWOELF() {
  updateLED(17, 0, 0, 0, ledBrightness);
  updateLED(18, 0, 0, 0, ledBrightness);
  updateLED(19, 0, 0, 0, ledBrightness);
  updateLED(20, 0, 0, 0, ledBrightness);
  updateLED(21, 0, 0, 0, ledBrightness);
}
void pushEINS() {
  updateLED(54, 0, 0, 0, ledBrightness);
  updateLED(53, 0, 0, 0, ledBrightness);
  updateLED(52, 0, 0, 0, ledBrightness);
  updateLED(51, 0, 0, 0, ledBrightness);
}
void pushEIN() {
  updateLED(54, 0, 0, 0, ledBrightness);
  updateLED(53, 0, 0, 0, ledBrightness);
  updateLED(52, 0, 0, 0, ledBrightness);
}
void pushZWEI() {
  updateLED(47, 0, 0, 0, ledBrightness);
  updateLED(46, 0, 0, 0, ledBrightness);
  updateLED(45, 0, 0, 0, ledBrightness);
  updateLED(44, 0, 0, 0, ledBrightness);
}
void pushDREI() {
  updateLED(33, 0, 0, 0, ledBrightness);
  updateLED(34, 0, 0, 0, ledBrightness);
  updateLED(35, 0, 0, 0, ledBrightness);
  updateLED(36, 0, 0, 0, ledBrightness);
}
void pushVIER() {
  updateLED(40, 0, 0, 0, ledBrightness);
  updateLED(41, 0, 0, 0, ledBrightness);
  updateLED(42, 0, 0, 0, ledBrightness);
  updateLED(43, 0, 0, 0, ledBrightness);
}
void pushSECHS() {
  updateLED(32, 0, 0, 0, ledBrightness);
  updateLED(31, 0, 0, 0, ledBrightness);
  updateLED(30, 0, 0, 0, ledBrightness);
  updateLED(29, 0, 0, 0, ledBrightness);
  updateLED(28, 0, 0, 0, ledBrightness);
}
void pushSIEBEN() {
  updateLED(11, 0, 0, 0, ledBrightness);
  updateLED(12, 0, 0, 0, ledBrightness);
  updateLED(13, 0, 0, 0, ledBrightness);
  updateLED(14, 0, 0, 0, ledBrightness);
  updateLED(15, 0, 0, 0, ledBrightness);
  updateLED(16, 0, 0, 0, ledBrightness);
}
void pushACHT() {
  updateLED(25, 0, 0, 0, ledBrightness);
  updateLED(24, 0, 0, 0, ledBrightness);
  updateLED(23, 0, 0, 0, ledBrightness);
  updateLED(22, 0, 0, 0, ledBrightness);
}
void pushNEUN() {
  updateLED(7, 0, 0, 0, ledBrightness);
  updateLED(6, 0, 0, 0, ledBrightness);
  updateLED(5, 0, 0, 0, ledBrightness);
  updateLED(4, 0, 0, 0, ledBrightness);
}
void pushZEHN() {
  updateLED(10, 0, 0, 0, ledBrightness);
  updateLED(9, 0, 0, 0, ledBrightness);
  updateLED(8, 0, 0, 0, ledBrightness);
  updateLED(7, 0, 0, 0, ledBrightness);
}
void pushELF() {
  updateLED(60, 0, 0, 0, ledBrightness);
  updateLED(61, 0, 0, 0, ledBrightness);
  updateLED(62, 0, 0, 0, ledBrightness);
}
void pushUHR() {
  updateLED(2, 0, 0, 0, ledBrightness);
  updateLED(1, 0, 0, 0, ledBrightness);
  updateLED(0, 0, 0, 0, ledBrightness);
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
  updateLED(108, 0, 0, 0, ledBrightness);
  updateLED(90, 0, 0, 0, ledBrightness);
  updateLED(88, 0, 0, 0, ledBrightness);
  updateLED(86, 0, 0, 0, ledBrightness);
}
void pushTempLOne() {
  updateLED( 73 , 0, 0, 0, ledBrightness);
  updateLED( 57 , 0, 0, 0, ledBrightness);
  updateLED( 58 , 0, 0, 0, ledBrightness);
  updateLED( 53 , 0, 0, 0, ledBrightness);
  updateLED( 51 , 0, 0, 0, ledBrightness);
  updateLED( 36 , 0, 0, 0, ledBrightness);
  updateLED( 29 , 0, 0, 0, ledBrightness);
  updateLED( 14 , 0, 0, 0, ledBrightness);
}
void pushTempLTwo() {
  updateLED( 75 , 0, 0, 0, ledBrightness);
  updateLED( 74 , 0, 0, 0, ledBrightness);
  updateLED( 73 , 0, 0, 0, ledBrightness);
  updateLED( 58 , 0, 0, 0, ledBrightness);
  updateLED( 53 , 0, 0, 0, ledBrightness);
  updateLED( 52 , 0, 0, 0, ledBrightness);
  updateLED( 51 , 0, 0, 0, ledBrightness);
  updateLED( 34 , 0, 0, 0, ledBrightness);
  updateLED( 31 , 0, 0, 0, ledBrightness);
  updateLED( 12 , 0, 0, 0, ledBrightness);
  updateLED( 13 , 0, 0, 0, ledBrightness);
  updateLED( 14 , 0, 0, 0, ledBrightness);
}
void pushTempLThree() {
  updateLED( 75 , 0, 0, 0, ledBrightness);
  updateLED( 74 , 0, 0, 0, ledBrightness);
  updateLED( 73 , 0, 0, 0, ledBrightness);
  updateLED( 58 , 0, 0, 0, ledBrightness);
  updateLED( 53 , 0, 0, 0, ledBrightness);
  updateLED( 52 , 0, 0, 0, ledBrightness);
  updateLED( 51 , 0, 0, 0, ledBrightness);
  updateLED( 36 , 0, 0, 0, ledBrightness);
  updateLED( 29 , 0, 0, 0, ledBrightness);
  updateLED( 12 , 0, 0, 0, ledBrightness);
  updateLED( 13 , 0, 0, 0, ledBrightness);
  updateLED( 14 , 0, 0, 0, ledBrightness);
}
void pushTempLFour() {
  updateLED( 75 , 0, 0, 0, ledBrightness);
  updateLED( 73 , 0, 0, 0, ledBrightness);
  updateLED( 56 , 0, 0, 0, ledBrightness);
  updateLED( 58 , 0, 0, 0, ledBrightness);
  updateLED( 53 , 0, 0, 0, ledBrightness);
  updateLED( 52 , 0, 0, 0, ledBrightness);
  updateLED( 51 , 0, 0, 0, ledBrightness);
  updateLED( 36 , 0, 0, 0, ledBrightness);
  updateLED( 29 , 0, 0, 0, ledBrightness);
  updateLED( 14 , 0, 0, 0, ledBrightness);
}
void pushTempRZero() {
  updateLED( 71 , 0, 0, 0, ledBrightness);
  updateLED( 70 , 0, 0, 0, ledBrightness);
  updateLED( 69 , 0, 0, 0, ledBrightness);
  updateLED( 60 , 0, 0, 0, ledBrightness);
  updateLED( 62 , 0, 0, 0, ledBrightness);
  updateLED( 49 , 0, 0, 0, ledBrightness);
  updateLED( 47 , 0, 0, 0, ledBrightness);
  updateLED( 38 , 0, 0, 0, ledBrightness);
  updateLED( 40 , 0, 0, 0, ledBrightness);
  updateLED( 27 , 0, 0, 0, ledBrightness);
  updateLED( 25 , 0, 0, 0, ledBrightness);
  updateLED( 16 , 0, 0, 0, ledBrightness);
  updateLED( 17 , 0, 0, 0, ledBrightness);
  updateLED( 18 , 0, 0, 0, ledBrightness);
}
void pushTempROne() {
  updateLED( 69 , 0, 0, 0, ledBrightness);
  updateLED( 61 , 0, 0, 0, ledBrightness);
  updateLED( 62 , 0, 0, 0, ledBrightness);
  updateLED( 49 , 0, 0, 0, ledBrightness);
  updateLED( 47 , 0, 0, 0, ledBrightness);
  updateLED( 40 , 0, 0, 0, ledBrightness);
  updateLED( 25 , 0, 0, 0, ledBrightness);
  updateLED( 18 , 0, 0, 0, ledBrightness);
}
void pushTempRTwo() {
  updateLED( 71 , 0, 0, 0, ledBrightness);
  updateLED( 70 , 0, 0, 0, ledBrightness);
  updateLED( 69 , 0, 0, 0, ledBrightness);
  updateLED( 62 , 0, 0, 0, ledBrightness);
  updateLED( 49 , 0, 0, 0, ledBrightness);
  updateLED( 48 , 0, 0, 0, ledBrightness);
  updateLED( 47 , 0, 0, 0, ledBrightness);
  updateLED( 38 , 0, 0, 0, ledBrightness);
  updateLED( 27 , 0, 0, 0, ledBrightness);
  updateLED( 16 , 0, 0, 0, ledBrightness);
  updateLED( 17 , 0, 0, 0, ledBrightness);
  updateLED( 18 , 0, 0, 0, ledBrightness);
}
void pushTempRThree() {
  updateLED( 71 , 0, 0, 0, ledBrightness);
  updateLED( 70 , 0, 0, 0, ledBrightness);
  updateLED( 69 , 0, 0, 0, ledBrightness);
  updateLED( 62 , 0, 0, 0, ledBrightness);
  updateLED( 49 , 0, 0, 0, ledBrightness);
  updateLED( 48 , 0, 0, 0, ledBrightness);
  updateLED( 47 , 0, 0, 0, ledBrightness);
  updateLED( 40 , 0, 0, 0, ledBrightness);
  updateLED( 25 , 0, 0, 0, ledBrightness);
  updateLED( 16 , 0, 0, 0, ledBrightness);
  updateLED( 17 , 0, 0, 0, ledBrightness);
  updateLED( 18 , 0, 0, 0, ledBrightness);
}
void pushTempRFour() {
  updateLED( 71 , 0, 0, 0, ledBrightness);
  updateLED( 69 , 0, 0, 0, ledBrightness);
  updateLED( 60 , 0, 0, 0, ledBrightness);
  updateLED( 62 , 0, 0, 0, ledBrightness);
  updateLED( 49 , 0, 0, 0, ledBrightness);
  updateLED( 48 , 0, 0, 0, ledBrightness);
  updateLED( 47 , 0, 0, 0, ledBrightness);
  updateLED( 40 , 0, 0, 0, ledBrightness);
  updateLED( 25 , 0, 0, 0, ledBrightness);
  updateLED( 18 , 0, 0, 0, ledBrightness);
}
void pushTempRFive() {
  updateLED( 71 , 0, 0, 0, ledBrightness);
  updateLED( 70 , 0, 0, 0, ledBrightness);
  updateLED( 69 , 0, 0, 0, ledBrightness);
  updateLED( 60 , 0, 0, 0, ledBrightness);
  updateLED( 49 , 0, 0, 0, ledBrightness);
  updateLED( 48 , 0, 0, 0, ledBrightness);
  updateLED( 47 , 0, 0, 0, ledBrightness);
  updateLED( 40 , 0, 0, 0, ledBrightness);
  updateLED( 25 , 0, 0, 0, ledBrightness);
  updateLED( 16 , 0, 0, 0, ledBrightness);
  updateLED( 17 , 0, 0, 0, ledBrightness);
  updateLED( 18 , 0, 0, 0, ledBrightness);
}
void pushTempRSix() {
  updateLED( 71 , 0, 0, 0, ledBrightness);
  updateLED( 70 , 0, 0, 0, ledBrightness);
  updateLED( 69 , 0, 0, 0, ledBrightness);
  updateLED( 60 , 0, 0, 0, ledBrightness);
  updateLED( 49 , 0, 0, 0, ledBrightness);
  updateLED( 48 , 0, 0, 0, ledBrightness);
  updateLED( 47 , 0, 0, 0, ledBrightness);
  updateLED( 38 , 0, 0, 0, ledBrightness);
  updateLED( 40 , 0, 0, 0, ledBrightness);
  updateLED( 27 , 0, 0, 0, ledBrightness);
  updateLED( 25 , 0, 0, 0, ledBrightness);
  updateLED( 16 , 0, 0, 0, ledBrightness);
  updateLED( 17 , 0, 0, 0, ledBrightness);
  updateLED( 18 , 0, 0, 0, ledBrightness);
}
void pushTempRSeven() {
  updateLED( 71 , 0, 0, 0, ledBrightness);
  updateLED( 70 , 0, 0, 0, ledBrightness);
  updateLED( 69 , 0, 0, 0, ledBrightness);
  updateLED( 62 , 0, 0, 0, ledBrightness);
  updateLED( 47 , 0, 0, 0, ledBrightness);
  updateLED( 40 , 0, 0, 0, ledBrightness);
  updateLED( 25 , 0, 0, 0, ledBrightness);
  updateLED( 18 , 0, 0, 0, ledBrightness);
}
void pushTempREight() {
  updateLED( 71 , 0, 0, 0, ledBrightness);
  updateLED( 70 , 0, 0, 0, ledBrightness);
  updateLED( 69 , 0, 0, 0, ledBrightness);
  updateLED( 60 , 0, 0, 0, ledBrightness);
  updateLED( 62 , 0, 0, 0, ledBrightness);
  updateLED( 49 , 0, 0, 0, ledBrightness);
  updateLED( 48 , 0, 0, 0, ledBrightness);
  updateLED( 47 , 0, 0, 0, ledBrightness);
  updateLED( 38 , 0, 0, 0, ledBrightness);
  updateLED( 40 , 0, 0, 0, ledBrightness);
  updateLED( 27 , 0, 0, 0, ledBrightness);
  updateLED( 25 , 0, 0, 0, ledBrightness);
  updateLED( 16 , 0, 0, 0, ledBrightness);
  updateLED( 17 , 0, 0, 0, ledBrightness);
  updateLED( 18 , 0, 0, 0, ledBrightness);
}
void pushTempRNine() {
  updateLED( 71 , 0, 0, 0, ledBrightness);
  updateLED( 70 , 0, 0, 0, ledBrightness);
  updateLED( 69 , 0, 0, 0, ledBrightness);
  updateLED( 60 , 0, 0, 0, ledBrightness);
  updateLED( 62 , 0, 0, 0, ledBrightness);
  updateLED( 49 , 0, 0, 0, ledBrightness);
  updateLED( 48 , 0, 0, 0, ledBrightness);
  updateLED( 47 , 0, 0, 0, ledBrightness);
  updateLED( 40 , 0, 0, 0, ledBrightness);
  updateLED( 25 , 0, 0, 0, ledBrightness);
  updateLED( 16 , 0, 0, 0, ledBrightness);
  updateLED( 17 , 0, 0, 0, ledBrightness);
  updateLED( 18 , 0, 0, 0, ledBrightness);
}

