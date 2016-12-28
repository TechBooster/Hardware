#ifndef XBM_BOOK_4_H
#define XBM_BOOK_4_H

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#else
#define PROGMEM
#endif

#define XBM_BOOK_4_WIDTH 15
#define XBM_BOOK_4_HEIGHT 21
#define XBM_BOOK_4_X 55
#define XBM_BOOK_4_Y 32

static const uint8_t xbm_book_4[] PROGMEM = {
  0x7C, 0x00, 0xFC, 0x0F, 0xFE, 0x3F, 0xFE, 0x7F, 0xFF, 0x7F, 0xFD, 0x7F, 
  0xFD, 0x7F, 0xFD, 0x7F, 0xFD, 0x7F, 0xFD, 0x7F, 0xFD, 0x7F, 0xFD, 0x7F, 
  0xFD, 0x7F, 0xFD, 0x7F, 0xFD, 0x7F, 0xFD, 0x7F, 0xFD, 0x7F, 0x1F, 0x78, 
  0xE2, 0x37, 0x9C, 0x1F, 0x78, 0x00, };
#endif
