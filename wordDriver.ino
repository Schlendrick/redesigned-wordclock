#include "default_layout.h"

void pushToStrip(int ledId);

void pushToStrip(int ledId) {
  
    pixels[ledId] = makeRGBVal (255, 255, 255);
    ws2812_setColors(NUM_PIXELS, pixels);
}

void displayOff() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels[i] = makeRGBVal(0, 0, 0);
  }
  ws2812_setColors(NUM_PIXELS, pixels);
}

void matrixReloaded(){
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

for(int y = 0; y< 11; y++){
  for (int i = 0; i < 10; i++) {
    pixels[ matrix[i][y] ] = makeRGBVal(0, 100, 0);
    ws2812_setColors(NUM_PIXELS, pixels);
    pixels[ matrix[i][y-1] ] = makeRGBVal(0, 0, 0);
  }
  
}

}


void displayStars(){
  int  i = random(NUM_PIXELS);
  pixels[i] = makeRGBVal (255, 0, 0);
  ws2812_setColors(NUM_PIXELS, pixels);
  delay(1);
  displayOff();
}

void pushES_IST()  {
	pushToStrip(L99);
	pushToStrip(L100);
	pushToStrip(L102);
	pushToStrip(L103);
	pushToStrip(L104);
}

void pushFUENF1() {
	pushToStrip(L106);
	pushToStrip(L107);
	pushToStrip(L108);
	pushToStrip(L109);
}

void pushFUENF2() {
	pushToStrip(L62);
	pushToStrip(L63);
	pushToStrip(L64);
	pushToStrip(L65);
}

void pushNACH() {
	pushToStrip(L69);
	pushToStrip(L68);
	pushToStrip(L67);
	pushToStrip(L66);
}

void pushZEHN1() {
	pushToStrip(L98);
	pushToStrip(L97);
	pushToStrip(L96);
	pushToStrip(L95);
}

void pushVIERTEL() {
	pushToStrip(L81);
	pushToStrip(L82);
	pushToStrip(L83);
	pushToStrip(L84);
	pushToStrip(L85);
	pushToStrip(L86);
	pushToStrip(L87);
}

void pushVOR() {
	pushToStrip(L76);
	pushToStrip(L75);
	pushToStrip(L74);
}

void pushHALB() {
	pushToStrip(L55);
	pushToStrip(L56);
	pushToStrip(L57);
	pushToStrip(L58);
}

void pushONE() {
	pushToStrip(L111);
}

void pushTWO() {
	pushToStrip(L110);
}

void pushTHREE() {
	pushToStrip(L113);
}

void pushFOUR() {
	pushToStrip(L112);
}

void pushZWANZIG() {
	pushToStrip(L94);
	pushToStrip(L93);
	pushToStrip(L92);
	pushToStrip(L91);
	pushToStrip(L90);
	pushToStrip(L89);
	pushToStrip(L88);
}

void pushZWOELF() {
	pushToStrip(L17);
	pushToStrip(L18);
	pushToStrip(L19);
	pushToStrip(L20);
	pushToStrip(L21);
}

void pushEINS(bool s) {
	pushToStrip(L54);
	pushToStrip(L53);
	pushToStrip(L52);
	if(s) {
		pushToStrip(L51);
	}
}

void pushZWEI() {
	pushToStrip(L47);
	pushToStrip(L46);
	pushToStrip(L45);
	pushToStrip(L44);
}

void pushDREI() {
	pushToStrip(L33);
	pushToStrip(L34);
	pushToStrip(L35);
	pushToStrip(L36);
}

void pushVIER() {
	pushToStrip(L40);
	pushToStrip(L41);
	pushToStrip(L42);
	pushToStrip(L43);
}

void pushSECHS() {
	pushToStrip(L32);
	pushToStrip(L31);
	pushToStrip(L30);
	pushToStrip(L29);
	pushToStrip(L28);
}

void pushSIEBEN() {
	pushToStrip(L11);
	pushToStrip(L12);
	pushToStrip(L13);
	pushToStrip(L14);
	pushToStrip(L15);
	pushToStrip(L16);
}

void pushACHT() {
	pushToStrip(L25);
	pushToStrip(L24);
	pushToStrip(L23);
	pushToStrip(L22);
}

void pushNEUN() {
	pushToStrip(L7);
	pushToStrip(L6);
  pushToStrip(L5);
	pushToStrip(L4);
}

void pushZEHN() {
	pushToStrip(L10);
	pushToStrip(L9);
	pushToStrip(L8);
	pushToStrip(L7);
}

void pushELF() {
	pushToStrip(L60);
	pushToStrip(L61);
	pushToStrip(L62);
}

void pushUHR() {
	pushToStrip(L2);
	pushToStrip(L1);
	pushToStrip(L0);
}

void pushHeart() {
	pushToStrip(L101); pushToStrip(L102); pushToStrip(L106); pushToStrip(L107);
	pushToStrip(L97); pushToStrip(L94); pushToStrip(L92); pushToStrip(L89);
  pushToStrip(L77); pushToStrip(L82); pushToStrip(L87);
	pushToStrip(L76); pushToStrip(L66);
	pushToStrip(L55); pushToStrip(L65);
	pushToStrip(L53); pushToStrip(L45);
	pushToStrip(L35); pushToStrip(L41);
	pushToStrip(L29); pushToStrip(L25);
	pushToStrip(L15); pushToStrip(L17);
	pushToStrip(L5);
}
///////////////////////
