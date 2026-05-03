#include "testLED.h"
#include "modes.h"
#include "tim.h"

// ============================================================
// Projet : LumaDome
// MCU    : STM32 Nucleo-L476RG
// LEDs   : 48x WS2812B (6 colonnes x 8 lignes, serpentin)
// Timer  : TIM3 Channel 1 PWM + DMA
// ============================================================

#define RESET_PULSES  60
#define BUFFER_SIZE   (NUM_LEDS * 24) + RESET_PULSES

// Boutons PCB — Active Low, pull-up sur PCB
#define BTN_MODE_PORT   GPIOC
#define BTN_MODE_PIN    GPIO_PIN_7   // D9

#define BTN_LUMIN_PORT  GPIOB
#define BTN_LUMIN_PIN   GPIO_PIN_6   // D10

#define BTN_RESET_PORT  GPIOB
#define BTN_RESET_PIN   GPIO_PIN_5   // D11

// Bouton bleu Nucleo
#define BTN_BLEU_PORT   GPIOC
#define BTN_BLEU_PIN    GPIO_PIN_13

// Buffer partagé avec modes.c
uint16_t led_buffer[BUFFER_SIZE];

static uint8_t leds_on    = 0;
static uint8_t brightness = 80;
static uint8_t mode_actif = 0; // 0=blanc, 1=hola, 2=texte, 3=koro

// ============================================================
// Callback DMA — stoppe proprement après envoi
// ============================================================
volatile uint8_t dma_done = 0;

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);
        dma_done = 1;
    }
}

// ============================================================
void set_led_rgb(int led_idx, uint8_t r, uint8_t g, uint8_t b) {
    if (led_idx >= NUM_LEDS) return;
    uint32_t color = ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;
    for (int i = 0; i < 24; i++) {
        led_buffer[led_idx * 24 + i] = (color & (1UL << (23 - i))) ? WS2812_1 : WS2812_0;
    }
}

void send_leds(void) {
    dma_done = 0;
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)led_buffer, BUFFER_SIZE);
    while (!dma_done);
}

static void eteindre_leds(void) {
    for (int i = 0; i < BUFFER_SIZE; i++) led_buffer[i] = 0;
    send_leds();
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
    leds_on    = 0;
    mode_actif = 0;
}

static uint8_t bouton_appuye(GPIO_TypeDef* port, uint16_t pin) {
    if (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET) {
        HAL_Delay(50);
        if (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET) {
            while (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET);
            HAL_Delay(50);
            return 1;
        }
    }
    return 0;
}

// ============================================================
void setup(void) {
    for (int i = 0; i < BUFFER_SIZE; i++) led_buffer[i] = 0;
    eteindre_leds();
}

void loop(void) {
    // Bouton bleu → Toggle ON/OFF
    if (bouton_appuye(BTN_BLEU_PORT, BTN_BLEU_PIN)) {
        if (leds_on) eteindre_leds();
        else {
            leds_on = 1;
            mode_actif = 0;
            mode_blanc(brightness);
        }
    }

    // Mode → cycle entre les modes
    if (bouton_appuye(BTN_MODE_PORT, BTN_MODE_PIN) && leds_on) {
        mode_actif++;
        if (mode_actif > 3) mode_actif = 0;
    }

    // Luminosité → cycle
    if (bouton_appuye(BTN_LUMIN_PORT, BTN_LUMIN_PIN) && leds_on) {
        brightness += 40;
        if (brightness > 200) brightness = 40;
        if (mode_actif == 0) mode_blanc(brightness);
    }

    // Reset → éteint tout
    if (bouton_appuye(BTN_RESET_PORT, BTN_RESET_PIN)) {
        eteindre_leds();
    }

    // Exécution du mode actif
    if (leds_on) {
        switch (mode_actif) {
            case 0: mode_blanc(brightness); HAL_Delay(100); break;
            case 1: mode_hola();            break;
            case 2: mode_texte();           break;
            case 3: mode_koro_sensei();     break;
        }
    }
}