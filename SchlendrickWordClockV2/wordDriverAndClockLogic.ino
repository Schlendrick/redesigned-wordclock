/*
  void matrixReloaded() {
  int matrix [10] [11] = {
  //[10]Zeilen [11]Spalten
  {99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109},
  {98,  97,  96,  95,  94,  93,  92,  91,  90,  89,  88},
  {77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87},
  {76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66},
  {55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65},
  {54,  53,  52,  51,  50,  49,  48,  47,  46,  45,  44},
  {33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43},
  {32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22},
  {11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21},
  {10,   9,   8,   7,   6,   5,   4,   3,   2,   1,   0}
  };
  }
*/

//sk6812:
uint8_t ledBrightnessRGBWhite = 0;
uint8_t ledBrightnessLEDWhite = ledBrightness;

//ws2812b
//uint8_t ledBrightnessRGBWhite = ledBrightness;
//uint8_t ledBrightnessLEDWhite = 0;

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

