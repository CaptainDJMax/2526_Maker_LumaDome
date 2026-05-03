#ifndef INC_MODES_H_
#define INC_MODES_H_

#include "main.h"

#define NUM_LEDS        48
#define NUM_LIGNES      6
#define LEDS_PAR_LIGNE  8

#define WS2812_0  32
#define WS2812_1  64

extern uint16_t led_buffer[];

void set_led_rgb(int led_idx, uint8_t r, uint8_t g, uint8_t b);
void send_leds(void);

void mode_blanc(uint8_t brightness);
void mode_hola(void);
void mode_texte(void);
void mode_koro_sensei(void);

#endif /* INC_MODES_H_ */