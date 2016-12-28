#ifndef XBM_BOOK_3_H
#define XBM_BOOK_3_H

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#else
#define PROGMEM
#endif

#define XBM_BOOK_3_WIDTH 17
#define XBM_BOOK_3_HEIGHT 19
#define XBM_BOOK_3_X 32
#define XBM_BOOK_3_Y 23

static const uint8_t xbm_book_3[] PROGMEM = {
  0x80, 0x1F, 0x00, 0xFE, 0x1F, 0x00, 0xFF, 0x3F, 0x00, 0xFF, 0x3F, 0x00, 
  0xFD, 0x3F, 0x00, 0xFD, 0x7F, 0x00, 0xFF, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 
  0xFA, 0xFF, 0x00, 0xFA, 0xFF, 0x00, 0xFA, 0xFF, 0x00, 0xFC, 0xFF, 0x00, 
  0xF4, 0xFF, 0x01, 0xF4, 0xFF, 0x01, 0xE8, 0xFF, 0x01, 0xE8, 0xFF, 0x01, 
  0xE8, 0x23, 0x01, 0x10, 0xFC, 0x00, 0xE0, 0x03, 0x00, };
#endif
