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

/* ================= B?NG MÀU DÙNG CHO CÁC CH? Ð? ================= */

/* --- B?ng màu Ch? d? 1: 5 màu Hex ch? d?nh (#884499, #BB6688, #8888CC, #8888CC, #DDAACC) --- */
#define SPECIFIED_TABLE_SIZE 25
UINT8C SpecTable_R[SPECIFIED_TABLE_SIZE] = {
    8, 9, 9, 10, 10,  11, 10, 10, 9, 9,  8, 8, 8, 8, 8,  8, 9, 10, 11, 12,  13, 12, 11, 10, 9
};
UINT8C SpecTable_G[SPECIFIED_TABLE_SIZE] = {
    4, 4, 5, 5, 6,   6, 6, 7, 7, 8,    8, 8, 8, 8, 8,  8, 8, 9, 9, 10,   10, 9, 8, 6, 5
};
UINT8C SpecTable_B[SPECIFIED_TABLE_SIZE] = {
    9, 9, 9, 8, 8,   8, 9, 10, 11, 11,  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 11, 10, 10
};

/* --- B?ng màu Ch? d? 2 & 3: C?u v?ng 7 s?c tông Pastel --- */
#define PASTEL_TABLE_SIZE 35
UINT8C PastelWheel_R[PASTEL_TABLE_SIZE] = {
    10, 9, 7, 6, 5,  5, 5, 5, 5, 5,  7, 9, 11, 13, 14,  15, 15, 15, 15, 15,  15, 15, 15, 14, 14,  13, 12, 11, 10, 10,  10, 10, 10, 10, 10
};
UINT8C PastelWheel_G[PASTEL_TABLE_SIZE] = {
    6, 7, 8, 9, 10,  11, 12, 13, 14, 14,  14, 13, 12, 11, 10,  9, 8, 7, 6, 5,  5, 5, 6, 7, 8,  9, 8, 7, 6, 6,  6, 6, 6, 6, 6
};
UINT8C PastelWheel_B[PASTEL_TABLE_SIZE] = {
    14, 14, 15, 15, 15,  13, 11, 9, 8, 7,  6, 5, 5, 5, 5,  5, 5, 6, 6, 7,  8, 10, 12, 13, 14,  14, 14, 14, 14, 14,  14, 14, 14, 14, 14
};

/* --- B?ng màu Ch? d? 4: 2 màu Hex (#CCAA88 & #8888CC) --- */
#define DUAL_TABLE_SIZE 20
UINT8C DualTable_R[DUAL_TABLE_SIZE] = {
    12, 12, 11, 11, 10,  10, 9, 9, 8, 8,  8, 8, 9, 9, 10,  10, 11, 11, 12, 12
};
UINT8C DualTable_G[DUAL_TABLE_SIZE] = {
    10, 10, 10, 9, 9,  9, 8, 8, 8, 8,  8, 8, 8, 8, 9,  9, 9, 10, 10, 10
};
UINT8C DualTable_B[DUAL_TABLE_SIZE] = {
    8, 8, 9, 9, 10,  10, 11, 11, 12, 12,  12, 12, 11, 11, 10,  10, 9, 9, 8, 8
};

/* --- Ch? d? 3: B?ng ánh x? ma tr?n 4x4 xoay theo kim d?ng h? --- */
UINT8C Zone4x4_Map[4][4] = {
    { 0,  1,  2,  3 },
    { 11, 12, 13, 4 },
    { 10, 15, 14, 5 },
    { 9,  8,  7,  6 }
};

UINT8X KeyboardReport[ENDP1_IN_SIZE];
UINT8 ReportChanged = 0;
static UINT8X PrevReport[ENDP1_IN_SIZE];

UINT8 LedMode = LED_MODE_SPECIFIED_ROLLING;
static UINT8 LedKeyDebounce = 0;

/* B? d?m th?i gian hi?u ?ng chung */
static UINT8 AnimPhase = 0;
static UINT8 AnimTick = 0;

#define PWM_LEVELS 16

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
    UINT8 sub, rz, cz, pos, tblIdx, idx;
    UINT8 cell_r[MATRIX_ROWS], cell_g[MATRIX_ROWS], cell_b[MATRIX_ROWS];
    UINT8 mask_r, mask_g, mask_b;
    static UINT8 last_a = 1;
    UINT8 curr_a;

    for (i = 0; i < ENDP1_IN_SIZE; i++) KeyboardReport[i] = 0;

    /* --- C?p nh?t nh?p chuy?n d?ng (Tang t?c d? lên ~20% v?i threshold 10) --- */
    if (++AnimTick >= 10) {
        AnimTick = 0;
        AnimPhase++;
    }

    for (c = 0; c < MATRIX_COLS; c++) {
        
        /* 1. Tính toán màu s?c (S? d?ng bu?c nh?y nhân dôi/ba d? thu h?p di?n tích màu) */
        for (r = 0; r < MATRIX_ROWS; r++) {
            switch (LedMode)
            {
                case LED_MODE_SPECIFIED_ROLLING:
                    /* Ch? d? 1: Bu?c nh?y (c * 2) d?m b?o xu?t hi?n ít nh?t 3-4 màu cùng lúc */
                    idx = (SPECIFIED_TABLE_SIZE * 100 + AnimPhase - c * 2) % SPECIFIED_TABLE_SIZE;
                    cell_r[r] = SpecTable_R[idx];
                    cell_g[r] = SpecTable_G[idx];
                    cell_b[r] = SpecTable_B[idx];
                    break;

                case LED_MODE_PASTEL_RAINBOW:
                    /* Ch? d? 2: Bu?c nh?y (c * 2) cho phép d?i c?u v?ng xu?t hi?n tr?n v?n 7 màu */
                    idx = (PASTEL_TABLE_SIZE * 100 + AnimPhase - c * 2) % PASTEL_TABLE_SIZE;
                    cell_r[r] = PastelWheel_R[idx];
                    cell_g[r] = PastelWheel_G[idx];
                    cell_b[r] = PastelWheel_B[idx];
                    break;

                case LED_MODE_ZONE_ROTATE_4X4:
                    /* Ch? d? 3: Ma tr?n 4x4 th? hi?n d?ng th?i nhi?u tông màu pastel xoay quanh */
                    rz = (r == 0) ? 0 : ((r <= 2) ? 1 : ((r <= 4) ? 2 : 3));
                    cz = (c < 4) ? 0 : ((c < 8) ? 1 : ((c < 12) ? 2 : 3));
                    pos = Zone4x4_Map[rz][cz];
                    tblIdx = (pos * 2 + AnimPhase) % PASTEL_TABLE_SIZE;
                    cell_r[r] = PastelWheel_R[tblIdx];
                    cell_g[r] = PastelWheel_G[tblIdx];
                    cell_b[r] = PastelWheel_B[tblIdx];
                    break;

                case LED_MODE_VERTICAL_DUAL:
                    /* Ch? d? 4: Bu?c nh?y d?c (r * 3) t?o d?i màu bi?n d?i rõ r?t trên 6 hàng */
                    idx = (DUAL_TABLE_SIZE * 100 + AnimPhase - r * 3) % DUAL_TABLE_SIZE;
                    cell_r[r] = DualTable_R[idx];
                    cell_g[r] = DualTable_G[idx];
                    cell_b[r] = DualTable_B[idx];
                    break;

                case LED_MODE_OFF:
                default:
                    cell_r[r] = cell_g[r] = cell_b[r] = 0;
                    break;
            }
        }

        /* 2. Ch?n c?t hi?n t?i */
        P0 = 0xFF; P7 |= (bP7_0_OUT_PU | bP7_1_OUT_PU); P3 = 0xFF;
        if (c < 8) P0 = ~BitMask[c];
        else if (c == 8) P7 &= ~bP7_1_OUT_PU;
        else if (c == 9) P7 &= ~bP7_0_OUT_PU;
        else if (c == 16) P3 &= ~0x02;
        else P3 &= ~BitMask[c - 8];

        /* 3. Phát xung PWM 16 c?p d? */
        for (sub = 0; sub < PWM_LEVELS; sub++) {
            mask_r = 0; mask_g = 0; mask_b = 0;
            for (r = 0; r < MATRIX_ROWS; r++) {
                if (cell_g[r] <= sub) mask_g |= BitMask[r];
                if (cell_b[r] <= sub) mask_b |= BitMask[r];
                if (cell_r[r] <= sub) mask_r |= BitMask[r];
            }

            P2 = mask_g;
            P1 = 0xC0 | (mask_b & 0x3F);
            P4_MOD_OC &= ~0xFF;
            P4 = mask_r;

            mDelayuS(1);
        }

        /* 4. Quét ma tr?n phím b?m */
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

    /* X? lý chuy?n d?i ch? d? LED */
    if (led_key_pressed) {
        if (!LedKeyDebounce) {
            LedMode++;
            if (LedMode >= LED_MODE_COUNT) LedMode = LED_MODE_SPECIFIED_ROLLING;
            LedKeyDebounce = 1;
        }
    } else {
        LedKeyDebounce = 0;
    }

    P0 = 0xFF; P7 |= (bP7_0_OUT_PU | bP7_1_OUT_PU); P3 = 0xFF;
    P2 = 0xFF; P1 = 0xFF; P4 = 0xFF;

    /* --- X? LÝ NÚM XOAY: TANG / GI?M ÂM LU?NG (Volume Up / Down) --- */
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