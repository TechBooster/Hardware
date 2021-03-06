#ifndef XBM_HAND_LEFT_1_H
#define XBM_HAND_LEFT_1_H

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#else
#define PROGMEM
#endif

#define XBM_HAND_LEFT_1_WIDTH 36
#define XBM_HAND_LEFT_1_HEIGHT 25
#define XBM_HAND_LEFT_1_X 16
#define XBM_HAND_LEFT_1_Y 73

static const uint8_t xbm_hand_left_1[] PROGMEM = {
  0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0E, 0x0F, 
  0x00, 0x00, 0x00, 0x0F, 0x0E, 0x00, 0x00, 0x00, 0x0F, 0x0E, 0x00, 0x00, 
  0x00, 0x07, 0x1F, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0x00, 0x00, 0x00, 0x7F, 
  0x0F, 0x00, 0x00, 0x00, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xFE, 0x0F, 0x00, 
  0x00, 0x00, 0xFC, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x1F, 0x00, 0x00, 0x00, 
  0x20, 0x3E, 0x00, 0x00, 0x00, 0x00, 0xBC, 0x00, 0x00, 0x00, 0x00, 0xFC, 
  0x00, 0x00, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x00, 
  0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0xE0, 0x1F, 0x00, 0x06, 0x00, 
  0x80, 0x3F, 0x40, 0x07, 0x00, 0x00, 0xFF, 0xFB, 0x0F, 0x00, 0x00, 0xFD, 
  0xFF, 0x07, 0x00, 0x00, 0xFC, 0xFF, 0x03, 0x00, 0x00, 0xF0, 0xFF, 0x01, 
  0x00, 0x00, 0x80, 0x17, 0x00, };
#endif
