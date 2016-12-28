#ifndef XBM_BOOK_5_H
#define XBM_BOOK_5_H

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#else
#define PROGMEM
#endif

#define XBM_BOOK_5_WIDTH 20
#define XBM_BOOK_5_HEIGHT 23
#define XBM_BOOK_5_X 74
#define XBM_BOOK_5_Y 50

static const uint8_t xbm_book_5[] PROGMEM = {
  0x40, 0x03, 0x00, 0xC0, 0x0E, 0x00, 0xA0, 0x3E, 0x00, 0x60, 0x7F, 0x00, 
  0x50, 0xFF, 0x01, 0x50, 0xFF, 0x07, 0xB0, 0xFF, 0x0F, 0xA8, 0xFF, 0x0F, 
  0xA8, 0xFF, 0x07, 0xD4, 0xFF, 0x07, 0xD4, 0xFF, 0x07, 0xEC, 0xFF, 0x03, 
  0xEA, 0xFF, 0x03, 0xEA, 0xFF, 0x03, 0xF5, 0xFF, 0x01, 0xF5, 0xFF, 0x01, 
  0xFF, 0xFF, 0x01, 0xE5, 0xFF, 0x00, 0x8E, 0xFF, 0x00, 0x78, 0xFF, 0x00, 
  0xE0, 0x7D, 0x00, 0x80, 0x77, 0x00, 0x00, 0x1E, 0x00, };
#endif