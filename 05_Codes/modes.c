#include "modes.h"
#include "testLED.h"
#include "tim.h"

// ============================================================
// Conversion coordonnées (col, ligne) → index LED
// Serpentin : colonnes paires montent, impaires descendent
// ============================================================
static int get_led_index(int col, int ligne) {
    if (col % 2 == 0) {
        return col * 8 + ligne;        // Monte
    } else {
        return col * 8 + (7 - ligne);  // Descend
    }
}

// ============================================================
// Mode 0 : Blanc réglable
// ============================================================
void mode_blanc(uint8_t brightness) {
    for (int i = 0; i < NUM_LEDS; i++)
        set_led_rgb(i, brightness, brightness, brightness);
    send_leds();
}

// ============================================================
// Hola : transition entre deux couleurs ligne par ligne
// ============================================================
static void hola_transition(
    uint8_t r1, uint8_t g1, uint8_t b1,
    uint8_t r2, uint8_t g2, uint8_t b2
) {
    for (int ligne = 0; ligne < NUM_LIGNES; ligne++) {
        for (int l = 0; l < ligne; l++)
            for (int j = 0; j < LEDS_PAR_LIGNE; j++)
                set_led_rgb(l * LEDS_PAR_LIGNE + j, r2, g2, b2);

        for (int j = 0; j < LEDS_PAR_LIGNE; j++)
            set_led_rgb(ligne * LEDS_PAR_LIGNE + j, r2, g2, b2);

        for (int l = ligne + 1; l < NUM_LIGNES; l++)
            for (int j = 0; j < LEDS_PAR_LIGNE; j++)
                set_led_rgb(l * LEDS_PAR_LIGNE + j, r1, g1, b1);

        send_leds();
        HAL_Delay(150);
    }
}

// ============================================================
// Mode 1 : Hola Bleu → Vert → Violet → Orange → Bleu
// ============================================================
void mode_hola(void) {
    // Tout en bleu au départ
    for (int i = 0; i < NUM_LEDS; i++)
        set_led_rgb(i, 0, 0, 150);
    send_leds();
    HAL_Delay(500);

    // Hola 1 : Bleu → Vert
    hola_transition(0, 0, 150, 0, 150, 0);
    HAL_Delay(300);

    // Hola 2 : Vert → Violet
    hola_transition(0, 150, 0, 100, 0, 150);
    HAL_Delay(300);

    // Hola 3 : Violet → Orange
    hola_transition(100, 0, 150, 200, 80, 0);
    HAL_Delay(300);

    // Hola 4 : Orange → Bleu
    hola_transition(200, 80, 0, 0, 0, 150);
    HAL_Delay(500);
}

// ============================================================
// Mode 2 : Défilement texte MAXIME
// ============================================================
static const uint8_t font_M[5][6] = {
    {1,1,0,0,1,1},
    {1,1,1,0,0,1},
    {1,0,1,0,0,1},
    {1,1,1,0,0,1},
    {1,1,0,0,1,1}
};
static const uint8_t font_A[5][6] = {
    {0,1,1,1,1,0},
    {1,0,0,0,0,1},
    {1,1,1,1,1,1},
    {1,0,0,0,0,1},
    {1,0,0,0,0,1}
};
static const uint8_t font_X[5][6] = {
    {1,0,0,0,0,1},
    {0,1,0,0,1,0},
    {0,0,1,1,0,0},
    {0,1,0,0,1,0},
    {1,0,0,0,0,1}
};
static const uint8_t font_I[5][6] = {
    {1,1,1,1,1,1},
    {0,0,1,1,0,0},
    {0,0,1,1,0,0},
    {0,0,1,1,0,0},
    {1,1,1,1,1,1}
};
static const uint8_t font_E[5][6] = {
    {1,1,1,1,1,1},
    {1,0,0,0,0,0},
    {1,1,1,1,0,0},
    {1,0,0,0,0,0},
    {1,1,1,1,1,1}
};
static const uint8_t font_space[2][6] = {
    {0,0,0,0,0,0},
    {0,0,0,0,0,0}
};

#define TEXTE_COLS 41
static uint8_t texte[TEXTE_COLS][6];

static void build_texte(void) {
    for (int c=0;c<5;c++) for (int l=0;l<6;l++) texte[c][l]    = font_M[c][l];
    for (int c=0;c<2;c++) for (int l=0;l<6;l++) texte[5+c][l]  = font_space[c][l];
    for (int c=0;c<5;c++) for (int l=0;l<6;l++) texte[7+c][l]  = font_A[c][l];
    for (int c=0;c<2;c++) for (int l=0;l<6;l++) texte[12+c][l] = font_space[c][l];
    for (int c=0;c<5;c++) for (int l=0;l<6;l++) texte[14+c][l] = font_X[c][l];
    for (int c=0;c<2;c++) for (int l=0;l<6;l++) texte[19+c][l] = font_space[c][l];
    for (int c=0;c<5;c++) for (int l=0;l<6;l++) texte[21+c][l] = font_I[c][l];
    for (int c=0;c<2;c++) for (int l=0;l<6;l++) texte[26+c][l] = font_space[c][l];
    for (int c=0;c<5;c++) for (int l=0;l<6;l++) texte[28+c][l] = font_M[c][l];
    for (int c=0;c<2;c++) for (int l=0;l<6;l++) texte[33+c][l] = font_space[c][l];
    for (int c=0;c<5;c++) for (int l=0;l<6;l++) texte[35+c][l] = font_E[c][l];
}

void mode_texte(void) {
    build_texte();

    for (int offset = -8; offset < TEXTE_COLS; offset++) {
        for (int i = 0; i < NUM_LEDS; i++)
            set_led_rgb(i, 0, 0, 0);

        for (int ligne_phys = 0; ligne_phys < 8; ligne_phys++) {
            int col_texte = offset + ligne_phys;
            if (col_texte >= 0 && col_texte < TEXTE_COLS) {
                for (int col_phys = 0; col_phys < 6; col_phys++) {
                    if (texte[col_texte][col_phys]) {
                        int idx = get_led_index(col_phys, ligne_phys);
                        set_led_rgb(idx, 150, 150, 150);
                    }
                }
            }
        }

        send_leds();
        HAL_Delay(200);
    }
}

// ============================================================
// Mode 3 : Koro Sensei
// 0=noir, 1=jaune, 2=blanc
// ============================================================
void mode_koro_sensei(void) {
    uint8_t J_r=200, J_g=180, J_b=0;    // Jaune
    uint8_t B_r=255, B_g=255, B_b=255;  // Blanc
    uint8_t N_r=0,   N_g=0,   N_b=0;    // Noir

    //             L0  L1  L2  L3  L4  L5  L6  L7
    uint8_t grille[6][8] = {
        /* Col 0 */ {0, 1, 1, 1, 1, 1, 1, 0},
        /* Col 1 */ {1, 1, 2, 1, 0, 1, 1, 1},
        /* Col 2 */ {1, 2, 1, 1, 1, 1, 1, 1},
        /* Col 3 */ {1, 2, 1, 1, 1, 1, 1, 1},
        /* Col 4 */ {1, 1, 2, 1, 0, 1, 1, 1},
        /* Col 5 */ {0, 1, 1, 1, 1, 1, 1, 0},
    };

    for (int i = 0; i < NUM_LEDS; i++)
        set_led_rgb(i, 0, 0, 0);

    for (int col = 0; col < 6; col++) {
        for (int ligne = 0; ligne < 8; ligne++) {
            int idx = get_led_index(col, ligne);
            switch (grille[col][ligne]) {
                case 0: set_led_rgb(idx, N_r, N_g, N_b); break;
                case 1: set_led_rgb(idx, J_r, J_g, J_b); break;
                case 2: set_led_rgb(idx, B_r, B_g, B_b); break;
            }
        }
    }

    send_leds();
    HAL_Delay(100);
}