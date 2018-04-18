#include <TimeLib.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "ws2812.h"

const char ssid[] = "UPCAA87BFD";  //  your network SSID (name)
const char pass[] = "czkx78pjMCvj";       // your network password

// NTP Servers:
static const char ntpServerName[] = "us.pool.ntp.org";
//static const char ntpServerName[] = "time.nist.gov";
//static const char ntpServerName[] = "time-a.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-b.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-c.timefreq.bldrdoc.gov";

const int timeZone = 1;     // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)


WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);

//LED Settings
const int DATA_PIN = 18;
const uint16_t NUM_PIXELS = 114;
rgbVal *pixels;

uint8_t selectedLanguageMode = 0;
const uint8_t RHEIN_RUHR_MODE = 0; //Define?
const uint8_t WESSI_MODE = 1;

int testHours = 200;
int testMinutes = 500;

const long oneSecondDelay = 1000;
const long halfSecondDelay = 500;

long waitUntilFastTest = 0;
long waitUntilRtc = 0;


void setup()
{
  //Setup Wifi
  Serial.begin(9600);
  Serial.println("TimeNTP Example");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("IP number assigned by DHCP is ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  setSyncInterval(300); //Get time from Server every 5 min

  //Setup LED_WS2812B
  ws2812_init(DATA_PIN, LED_WS2812B);
  pixels = (rgbVal*)malloc(sizeof(rgbVal) * NUM_PIXELS);
  displayOff();
}

//time_t prevDisplay = 0; // when the digital clock was displayed

void loop() {

  if (timeStatus() != timeNotSet) {
      clockLogic();
    //if (now() != prevDisplay) { //update the display only if time has changed
    //  prevDisplay = now();
       //digitalClockDisplay(); for debugging in Serial monitor
    //}
  }

  
}

void clockLogic() {
  if(millis() >= waitUntilRtc) {
    waitUntilRtc = millis();
    if(testMinutes != minute() || testHours != hour()) {
      testMinutes = minute();
      testHours = hour();
      displayOff();
      timeToStrip(testHours, testMinutes);
    }
    waitUntilRtc += oneSecondDelay;
  }
}

void timeToStrip(uint8_t hours,uint8_t minutes)
{
  pushES_IST();

  //show minutes
  if(minutes >= 5 && minutes < 10) {
    pushFUENF1();
    pushNACH();
  } else if(minutes >= 10 && minutes < 15) {
    pushZEHN1();
    pushNACH();
  } else if(minutes >= 15 && minutes < 20) {
    pushVIERTEL();
    pushNACH();
  } else if(minutes >= 20 && minutes < 25) {
    if(selectedLanguageMode == RHEIN_RUHR_MODE) {
      pushZWANZIG();
      pushNACH();
    } else if(selectedLanguageMode == WESSI_MODE) {
      pushZEHN1();
      pushVOR();
      pushHALB();
    }
  } else if(minutes >= 25 && minutes < 30) {
    pushFUENF1();
    pushVOR();
    pushHALB();
  } else if(minutes >= 30 && minutes < 35) {
    pushHALB();
  } else if(minutes >= 35 && minutes < 40) {
    pushFUENF1();
    pushNACH();
    pushHALB();
  } else if(minutes >= 40 && minutes < 45) {
    if(selectedLanguageMode == RHEIN_RUHR_MODE) {
      pushZWANZIG();
      pushVOR();
    } else if(selectedLanguageMode == WESSI_MODE) {
      pushZEHN1();
      pushNACH();
      pushHALB();
    }
  } else if(minutes >= 45 && minutes < 50) {
    pushVIERTEL();
    pushVOR();
  } else if(minutes >= 50 && minutes < 55) {
    pushZEHN1();
    pushVOR();
  } else if(minutes >= 55 && minutes < 60) {
    pushFUENF1();
    pushVOR();
  }

  int singleMinutes = minutes % 5;
  switch(singleMinutes) {
    case 1:
      pushONE();
      break;
    case 2:
      pushONE();
      pushTWO();
      break;
    case 3:
      pushONE();
      pushTWO();
      pushTHREE();
      break;
    case 4:
      pushONE();
      pushTWO();
      pushTHREE();
      pushFOUR();
    break;
  }

  if(hours >= 12) {
    hours -= 12;
  }

  if(selectedLanguageMode == RHEIN_RUHR_MODE) {
    if(minutes >= 25) {
      hours++;
    }
  } else if(selectedLanguageMode == WESSI_MODE) {
    if(minutes >= 20) {
      hours++;
    }
  }

  if(hours == 12) {
    hours = 0;
  }

  //show hours
  switch(hours) {
    case 0:
      pushZWOELF();
      break;
    case 1:
      if(minutes > 4) {
        pushEINS(true);
      } else {
        pushEINS(false);
      }
      break;
    case 2:
      pushZWEI();
      break;
    case 3:
      pushDREI();
      break;
    case 4:
      pushVIER();
      break;
    case 5:
      pushFUENF2();
      break;
    case 6:
      pushSECHS();
      break;
    case 7:
      pushSIEBEN();
      break;
    case 8:
      pushACHT();
      break;
    case 9:
      pushNEUN();
      break;
    case 10:
      pushZEHN();
      break;
    case 11:
      pushELF();
      break;
  }

  //show uhr
  if(minutes < 5) {
    pushUHR();
  }
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

/*-------- debugging code for clock ----------*/
void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(".");
  Serial.print(month());
  Serial.print(".");
  Serial.print(year());
  Serial.println();
}

void printDigits(int digits)
{
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void fastTest(){
  if(millis() >= waitUntilFastTest) {
    if(testMinutes >= 60){
      testMinutes =0;
      testHours++;
    }
    if(testHours >=24){
      testHours = 0;
    }
    displayOff();
    timeToStrip(testHours,testMinutes);
    testMinutes++;
    waitUntilFastTest += oneSecondDelay;
  }
}
