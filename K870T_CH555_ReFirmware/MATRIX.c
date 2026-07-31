#include "MATRIX.h"

UINT8C BitMask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

UINT8C KeyMap[MATRIX_ROWS][MATRIX_COLS] = {
    { KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_NO   },
    { KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_NO   },
    { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_NO   },
    { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NO,   KC_ENT,  KC_PGUP, KC_PGDN, KC_NO   },
    { MOD_LSFT,KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MOD_RSFT,KC_NO,   KC_UP,   KC_NO,   KC_NO   },
    { MOD_LCTL,MOD_LGUI,MOD_LALT,KC_NO,   KC_SPC,  KC_LED_TOG, KC_NO,   MOD_RALT,KC_NO,   KC_APP,  MOD_RCTL,KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO   }
};

/* B?ng 16 bu?c màu chu?n xác d?i Hex (Ti?t ki?m 48 bytes ROM):
 * 0..2: #884499 | 3..5: #BB6688 | 6..11: #8888CC | 12..15: #DDAACC
 */
UINT8C Palette_R[16] = {2,2,2, 2,2,2, 1,1,1,1,1,1, 2,2,2,2};
UINT8C Palette_G[16] = {0,0,0, 1,1,1, 1,1,1,1,1,1, 1,1,1,1};
UINT8C Palette_B[16] = {2,2,2, 1,1,1, 2,2,2,2,2,2, 2,2,2,2};

UINT8X KeyboardReport[ENDP1_IN_SIZE];
UINT8 ReportChanged = 0;
static UINT8X PrevReport[ENDP1_IN_SIZE];

UINT8 LedOn = 1;
static UINT8 LedKeyDebounce = 0;
static UINT8 HueShift = 0;
static UINT8 HueTick = 0;
static UINT8 FrameCnt = 0;

void Matrix_Init(void)
{
    UINT8 i;

    P0_MOD_OC &= ~0xFF; P0_DIR_PU |= 0xFF; P0 = 0xFF;
    P7 |= (bP7_0_DIR | bP7_1_DIR | bP7_0_OUT_PU | bP7_1_OUT_PU);
    P3_MOD_OC &= ~0xFE; P3_DIR_PU |= 0xFE; P3 = 0xFF;

    P2_MOD_OC &= ~0x3F; P2_DIR_PU |= 0x3F; P2 |= 0x3F;
    P1_MOD_OC &= ~0x3F; P1_DIR_PU |= 0x3F;

    P1_MOD_OC |= 0xC0; P1_DIR_PU |= 0xC0; P1_7 = 1; P1_6 = 1;
    P4_MOD_OC |= 0xFF; P4_DIR_PU |= 0xFF; P4 = 0xFF;

    for (i = 0; i < ENDP1_IN_SIZE; i++) {
        KeyboardReport[i] = 0;
        PrevReport[i] = 0;
    }
}

void Matrix_Scan(void)
{
    UINT8 r, c, keycode, key_count = 0, i;
    UINT8 led_key_pressed = 0;
    UINT8 col_r, col_g, col_b, idx, toggle;
    static UINT8 last_a = 1;
    UINT8 curr_a;

    for (i = 0; i < ENDP1_IN_SIZE; i++) KeyboardReport[i] = 0;

    FrameCnt++;
    toggle = FrameCnt & 0x01;

    /* Nhích 1 n?c màu sau m?i 35 lu?t quét */
    if (++HueTick >= 35) {
        HueTick = 0;
        HueShift = (HueShift + 1) & 0x0F; // Ép d?i 16 steps (& 0x0F)
    }

    for (c = 0; c < MATRIX_COLS; c++) {
        /* ---- Pha 1: Quét màu LED ---- */
        if (LedOn) {
#if RAINBOW_REVERSE
            idx = (HueShift - c) & 0x0F;
#else
            idx = (HueShift + c) & 0x0F;
#endif
            col_r = Palette_R[idx];
            col_g = Palette_G[idx];
            col_b = Palette_B[idx];
        } else {
            col_r = col_g = col_b = 0;
        }

        P2 = (col_g > toggle) ? 0x00 : 0xFF;
        P1 = 0xC0 | ((col_b > toggle) ? 0x00 : 0x3F);

        P4_MOD_OC &= ~0xFF;
        P4 = (col_r > toggle) ? 0x00 : 0xFF;

        P0 = 0xFF; P7 |= (bP7_0_OUT_PU | bP7_1_OUT_PU); P3 = 0xFF;
        if (c < 8) P0 = ~BitMask[c];
        else if (c == 8) P7 &= ~bP7_1_OUT_PU;
        else if (c == 9) P7 &= ~bP7_0_OUT_PU;
        else if (c == 16) P3 &= ~0x02;
        else P3 &= ~BitMask[c - 8];

        mDelayuS(5);

        /* ---- Pha 2: Quét ma tr?n phím ---- */
        P4_MOD_OC |= 0xFF;
        P4 = 0xFF;
        mDelayuS(5);

        for (r = 0; r < MATRIX_ROWS; r++) {
            if ((P4 & BitMask[r]) == 0) {
                keycode = KeyMap[r][c];

                if (keycode == KC_LED_TOG) {
                    led_key_pressed = 1;
                }
                else if (keycode != KC_NO) {
                    if (keycode >= 0xE0 && keycode <= 0xE7) {
                        KeyboardReport[0] |= BitMask[keycode - 0xE0];
                    }
                    else if (key_count < 6) {
                        KeyboardReport[2 + key_count] = keycode;
                        key_count++;
                    }
                }
            }
        }
    }

    if (led_key_pressed) {
        if (!LedKeyDebounce) {
            LedOn = !LedOn;
            LedKeyDebounce = 1;
        }
    } else {
        LedKeyDebounce = 0;
    }

    P0 = 0xFF; P7 |= (bP7_0_OUT_PU | bP7_1_OUT_PU); P3 = 0xFF;
    P2 = 0xFF; P1 = 0xFF; P4 = 0xFF;

    /* ---- X? lý con lan P1.7 / P1.6 ---- */
    curr_a = ENCODER_PAD_A;
    if (last_a == 1 && curr_a == 0) {
        KeyboardReport[2] = (ENCODER_PAD_B == 1) ? KC_VOLU : KC_VOLD;
    }
    last_a = curr_a;

    ReportChanged = 0;
    for (i = 0; i < ENDP1_IN_SIZE; i++) {
        if (KeyboardReport[i] != PrevReport[i]) {
            ReportChanged = 1;
            PrevReport[i] = KeyboardReport[i];
        }
    }
}