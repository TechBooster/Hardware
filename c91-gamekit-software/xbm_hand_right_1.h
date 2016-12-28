#ifndef XBM_HAND_RIGHT_1_H
#define XBM_HAND_RIGHT_1_H

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#else
#define PROGMEM
#endif

#define XBM_HAND_RIGHT_1_WIDTH 17
#define XBM_HAND_RIGHT_1_HEIGHT 23
#define XBM_HAND_RIGHT_1_X 71
#define XBM_HAND_RIGHT_1_Y 76

static const uint8_t xbm_hand_right_1[] PROGMEM = {
  0x00, 0x70, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xE0, 0x00, 0x60, 0xC0, 0x01, 
  0x60, 0xC0, 0x01, 0xE0, 0xC0, 0x01, 0xE0, 0xE1, 0x01, 0xC0, 0xF1, 0x00, 
  0xC0, 0xFF, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x0E, 0x00, 
  0x00, 0x0E, 0x00, 0x07, 0x0E, 0x00, 0x0F, 0x0E, 0x00, 0x1F, 0x0E, 0x00, 
  0x3E, 0x0E, 0x00, 0x7C, 0x0F, 0x00, 0xF8, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 
  0xE0, 0x07, 0x00, 0xC0, 0x07, 0x00, 0x80, 0x07, 0x00, };
#endif