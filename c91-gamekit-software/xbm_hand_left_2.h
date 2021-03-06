#ifndef XBM_HAND_LEFT_2_H
#define XBM_HAND_LEFT_2_H

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#else
#define PROGMEM
#endif

#define XBM_HAND_LEFT_2_WIDTH 22
#define XBM_HAND_LEFT_2_HEIGHT 25
#define XBM_HAND_LEFT_2_X 30
#define XBM_HAND_LEFT_2_Y 75

static const uint8_t xbm_hand_left_2[] PROGMEM = {
  0x1C, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x07, 0x0C, 0x00, 
  0x07, 0x0C, 0x00, 0x07, 0x0E, 0x00, 0x0F, 0x0F, 0x00, 0x1E, 0x07, 0x00, 
  0xFE, 0x07, 0x00, 0xFC, 0x03, 0x00, 0xF0, 0x00, 0x00, 0xE0, 0x00, 0x00, 
  0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 
  0xE0, 0x00, 0x00, 0xE0, 0x01, 0x00, 0xC0, 0x01, 0x30, 0xC0, 0x03, 0x38, 
  0x80, 0x07, 0x3E, 0x00, 0x1F, 0x1F, 0x00, 0xFE, 0x0F, 0x00, 0xFC, 0x03, 
  0x00, 0xF0, 0x00, };
#endif
