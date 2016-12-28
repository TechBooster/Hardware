/***************************************************
This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
----> http://www.adafruit.com/products/358
The 1.8" TFT shield
----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
----> http://www.adafruit.com/products/618

Check out the links above for our tutorials and wiring diagrams
These displays use SPI to communicate, 4 or 5 pins are required to
interface (RST is optional)
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
MIT license, all text above must be included in any redistribution
****************************************************/

#include "Adafruit_GFX_tiny.h"    // Core graphics library
#include "Adafruit_ST7735_mod.h"  // Hardware-specific library
#include <SPI.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
// in which case, set this #define pin to 0!
#define TFT_DC     8

#define PIN_SWITCH_LEFT 6
#define PIN_SWITCH_RIGHT 7

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

#define SCORE_NUM_DIGITS 5
#define USE_ZEROFILL // define this to suppress rendering preceding zeros
#define SCORE_X 60
#define SCORE_Y 10
#define DIGIT_WIDTH 6

// comment out DEBUG to save 2KB~ ROM size
#define DEBUG

#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
#define DIRECTION_NOP 2

#define HAND_START 0
#define HAND_MIDDLE 1
#define HAND_END 2

#include "xbm_title.h"
#include "xbm_gameover.h"
#include "xbm_body.h"
#include "xbm_hand_left_1.h"
#include "xbm_hand_left_2.h"
#include "xbm_hand_left_3.h"
#include "xbm_hand_right_1.h"
#include "xbm_hand_right_2.h"
#include "xbm_hand_right_3.h"
#include "xbm_book_1.h"
#include "xbm_book_2.h"
#include "xbm_book_3.h"
#include "xbm_book_4.h"
#include "xbm_book_5.h"

struct PICTURE{
	const uint8_t* raw;
	int width;
	int height;
	int x;
	int y;
};

struct OBJECT{
	struct PICTURE* pictures;
	int index;
	int current;
};

struct BOOK{
	struct OBJECT object;
	int direction;
	int nextIndex;
	boolean isDrop;
};

struct PLAYER{
	struct OBJECT leftHand;
	struct OBJECT rightHand;
	int status;
};

/************************************************
 * Draw Screen - Util function
 ************************************************/
inline void clearScreen() {
	tft.fillScreen(ST7735_WHITE);
}

inline void drawPicture(struct PICTURE* picture) {
	tft.drawXBitmap(picture->x, picture->y, picture->raw, picture->width, picture->height, 0x00);
}

inline void clearPicture(struct PICTURE* picture) {
	tft.fillRect(picture->x, picture->y, picture->width, picture->height, ST7735_WHITE);
}


/************************************************
 * Setup - Hardware Initialize
 ************************************************/
void setup(void) {
	Serial.begin(9600);

	// initialize a ST7735S chip, black tab
	tft.initR(INITR_144GREENTAB);

	// setup input button
	pinMode(PIN_SWITCH_LEFT, INPUT_PULLUP);
	pinMode(PIN_SWITCH_RIGHT, INPUT_PULLUP);

	return;
}

/************************************************
 * Title Loop
 ************************************************/
void title(){
	clearScreen();
	tft.drawXBitmap2x2(0, 0, xbm_title, XBM_TITLE_WIDTH, XBM_TITLE_HEIGHT, 0x00);
	while(1){
		int nLeft = digitalRead(PIN_SWITCH_LEFT);
		int nRight = digitalRead(PIN_SWITCH_RIGHT);
		if (nLeft == LOW || nRight == LOW) {
			break;
		}
		if (serialEventRun) serialEventRun();
	}
	
	return;
}

/************************************************
* Create Objects
************************************************/
struct PICTURE createPicture(int x, int y, int width, int height, const uint8_t *raw) {
	struct PICTURE pic;

	pic.x = x;
	pic.y = y;
	pic.width = width;
	pic.height = height;
	pic.raw = raw;
	return pic;
}


struct OBJECT createObjest(int index, int currentStatus, struct PICTURE* pictures) {
	struct OBJECT object;
	object.index = index;
	object.current = currentStatus;
	object.pictures = pictures;

	return object;
}

struct BOOK book;
struct PICTURE bookPictures[6];
struct PLAYER player;
struct PICTURE leftHandPictures[3];
struct PICTURE rightHandPictures[3];

struct BOOK createBook() {
	book.direction = DIRECTION_RIGHT;
	book.isDrop = false;
	bookPictures[0] = createPicture(XBM_BOOK_1_X, XBM_BOOK_1_Y, XBM_BOOK_1_WIDTH, XBM_BOOK_1_HEIGHT, xbm_book_1);
	bookPictures[1] = createPicture(XBM_BOOK_2_X, XBM_BOOK_2_Y, XBM_BOOK_2_WIDTH, XBM_BOOK_2_HEIGHT, xbm_book_2);
	bookPictures[2] = createPicture(XBM_BOOK_3_X, XBM_BOOK_3_Y, XBM_BOOK_3_WIDTH, XBM_BOOK_3_HEIGHT, xbm_book_3);
	bookPictures[3] = createPicture(XBM_BOOK_4_X, XBM_BOOK_4_Y, XBM_BOOK_4_WIDTH, XBM_BOOK_4_HEIGHT, xbm_book_4);
	bookPictures[4] = createPicture(XBM_BOOK_5_X, XBM_BOOK_5_Y, XBM_BOOK_5_WIDTH, XBM_BOOK_5_HEIGHT, xbm_book_5);
	book.object = createObjest(5, 0, bookPictures);
	book.nextIndex = 0;

	return book;
}

void drawBook(struct BOOK *book) {
	struct PICTURE cPict = book->object.pictures[book->object.current];
	clearPicture(&cPict);
	drawPicture(&(book->object.pictures[book->nextIndex]));

	book->object.current = book->nextIndex;
}

void updateBook(struct BOOK *book) {

	int nextIndex;

	if (book->object.current == book->object.index - 1) {
		book->direction = DIRECTION_LEFT;
	}
	if (book->object.current == 0) {
		book->direction = DIRECTION_RIGHT;
	}

	if (book->direction == DIRECTION_LEFT) {
		nextIndex = book->object.current - 1;
	}
	else {
		nextIndex = book->object.current + 1;
	}

	book->nextIndex = nextIndex;
}

void setDrop(struct BOOK *book, struct PLAYER *player) {
	
	if (book->object.current == book->object.index - 1  && player->status != HAND_MIDDLE) {
		book->isDrop = true;
		return;
	}

	if (book->object.current == 0 && player->status != HAND_START) {
		book->isDrop = true;
		return;
	}
	return;
}

void createPlayer() {

	leftHandPictures[0] = createPicture(XBM_HAND_LEFT_1_X, XBM_HAND_LEFT_1_Y, XBM_HAND_LEFT_1_WIDTH, XBM_HAND_LEFT_1_HEIGHT, xbm_hand_left_1);
	leftHandPictures[1] = createPicture(XBM_HAND_LEFT_2_X, XBM_HAND_LEFT_2_Y, XBM_HAND_LEFT_2_WIDTH, XBM_HAND_LEFT_2_HEIGHT, xbm_hand_left_2);
	leftHandPictures[2] = createPicture(XBM_HAND_LEFT_3_X, XBM_HAND_LEFT_3_Y, XBM_HAND_LEFT_3_WIDTH, XBM_HAND_LEFT_3_HEIGHT, xbm_hand_left_3);
	player.leftHand = createObjest(3, 0, leftHandPictures);

	rightHandPictures[0] = createPicture(XBM_HAND_RIGHT_1_X, XBM_HAND_RIGHT_1_Y, XBM_HAND_RIGHT_1_WIDTH, XBM_HAND_RIGHT_1_HEIGHT, xbm_hand_right_1);
	rightHandPictures[1] = createPicture(XBM_HAND_RIGHT_2_X, XBM_HAND_RIGHT_2_Y, XBM_HAND_RIGHT_2_WIDTH, XBM_HAND_RIGHT_2_HEIGHT, xbm_hand_right_2);
	rightHandPictures[2] = createPicture(XBM_HAND_RIGHT_3_X, XBM_HAND_RIGHT_3_Y, XBM_HAND_RIGHT_3_WIDTH, XBM_HAND_RIGHT_3_HEIGHT, xbm_hand_right_3);
	player.rightHand = createObjest(3, 0, rightHandPictures);

	player.status = HAND_START;
}

void updatePlayerStatus(int direction) {

	int next = player.status;

	if (direction == DIRECTION_NOP) {
		return;
	}

	if (direction == DIRECTION_LEFT) {
		next--;
	}

	if (direction == DIRECTION_RIGHT) {
		next++;
	}

	if (next < HAND_START) {
		next = HAND_START;
	}
	if (next > HAND_END) {
		next = HAND_END;
	}
	player.status = next;
}

void drawPlayer() {
	struct PICTURE currentLeftPict = player.leftHand.pictures[player.leftHand.current];
	struct PICTURE nextLeftPict = player.leftHand.pictures[player.status];

	struct PICTURE currentRightPict = player.rightHand.pictures[player.rightHand.current];
	struct PICTURE nextRightPict = player.rightHand.pictures[player.status];

	clearPicture(&currentLeftPict);
	clearPicture(&currentRightPict);
	drawPicture(&nextLeftPict);
	drawPicture(&nextRightPict);

	player.leftHand.current = player.status;
	player.rightHand.current = player.status;
}

/************************************************
 * Game Loop
 ************************************************/
void game(){

	clearScreen();
	createBook();
	createPlayer();

	resetScore();
	tft.drawXBitmap(XBM_BODY_X, XBM_BODY_Y, xbm_body, XBM_BODY_WIDTH, XBM_BODY_HEIGHT, 0x00);
	drawPlayer();

	int speed = 500;
	int interval = 5;
	drawPlayer();

	while(1){
		int loop = 0;
		int direction = DIRECTION_NOP;

		drawBook(&book);
		drawPlayer();

		while (speed > interval*loop) {
			int nLeft = digitalRead(PIN_SWITCH_LEFT);
			int nRight = digitalRead(PIN_SWITCH_RIGHT);
			// Serial.println("left: " + String(nLeft, HEX) + ", right: " + String(nRight, HEX));
			if (nLeft == LOW) {
				direction = DIRECTION_LEFT;
			}
			else if (nRight == LOW) {
				direction = DIRECTION_RIGHT;
			}
			delay(interval);
			loop++;
			if (serialEventRun) serialEventRun();
		}

		setDrop(&book, &player);
		
		if (book.isDrop) {
			return;
		}
		else {
			addScore(1);
		}
		updatePlayerStatus(direction);
		updateBook(&book);
		if (serialEventRun) serialEventRun();
	}
	return;
}

/************************************************
 * Game is over
 ************************************************/
void finish(){
	clearScreen();
	tft.drawXBitmap2x2(0, 0, xbm_gameover, XBM_GAMEOVER_WIDTH, XBM_GAMEOVER_HEIGHT, 0x00);
	while(1){
		int nLeft = digitalRead(PIN_SWITCH_LEFT);
		int nRight = digitalRead(PIN_SWITCH_RIGHT);
		if (nLeft == LOW || nRight == LOW) {
			break;
		}
		if (serialEventRun) serialEventRun();
	}

	return;
}

void loop() {
	title();
	game();
	finish();
}

static int16_t currentScore = -1;

void addScore(int16_t ptsToAdd) {
	if (currentScore != -1) {
		updateScore(currentScore + ptsToAdd);
	}
	else {
		updateScore(ptsToAdd);
	}
}

inline void resetScore() {
	updateScore(0);
}

void updateScore(int16_t score_in) {
	int16_t score = score_in;
	if (score == currentScore) {
		return;
	}
	for (char pos = SCORE_NUM_DIGITS - 1; pos != -1; pos--) {
		char n = score % 10;
		char n_prev = currentScore % 10;
		// omit update when not needed
		if (n == n_prev) {
			continue;
		}
#ifdef USE_ZEROFILL
		if (n == 0 && score < 10) {
			continue;
		}
#endif
		int16_t posX = SCORE_X + (DIGIT_WIDTH * pos);
		tft.drawChar(posX, SCORE_Y, n + '0', ST7735_BLACK, ST7735_WHITE, 1);
		score /= 10;
	}
	currentScore = score_in;
}


// TEST CODE 

void testlines(uint16_t color) {
	tft.fillScreen(ST7735_BLACK);
	for (int16_t x = 0; x < tft.width(); x += 6) {
		tft.drawLine(0, 0, x, tft.height() - 1, color);
	}
	for (int16_t y = 0; y < tft.height(); y += 6) {
		tft.drawLine(0, 0, tft.width() - 1, y, color);
	}

	tft.fillScreen(ST7735_BLACK);
	for (int16_t x = 0; x < tft.width(); x += 6) {
		tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
	}
	for (int16_t y = 0; y < tft.height(); y += 6) {
		tft.drawLine(tft.width() - 1, 0, 0, y, color);
	}

	tft.fillScreen(ST7735_BLACK);
	for (int16_t x = 0; x < tft.width(); x += 6) {
		tft.drawLine(0, tft.height() - 1, x, 0, color);
	}
	for (int16_t y = 0; y < tft.height(); y += 6) {
		tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
	}

	tft.fillScreen(ST7735_BLACK);
	for (int16_t x = 0; x < tft.width(); x += 6) {
		tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
	}
	for (int16_t y = 0; y < tft.height(); y += 6) {
		tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
	}
}

void testdrawtext(const char *text, uint16_t color) {
	tft.setCursor(100, 10);
	tft.setTextColor(color);
	tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
	tft.fillScreen(ST7735_BLACK);
	for (int16_t y = 0; y < tft.height(); y += 5) {
		tft.drawFastHLine(0, y, tft.width(), color1);
	}
	for (int16_t x = 0; x < tft.width(); x += 5) {
		tft.drawFastVLine(x, 0, tft.height(), color2);
	}
}

void testdrawrects(uint16_t color) {
	tft.fillScreen(ST7735_BLACK);
	for (int16_t x = 0; x < tft.width(); x += 6) {
		tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color);
	}
}

void testfillrects(uint16_t color1, uint16_t color2) {
	tft.fillScreen(ST7735_BLACK);
	for (int16_t x = tft.width() - 1; x > 6; x -= 6) {
		tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color1);
		tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color2);
	}
}
