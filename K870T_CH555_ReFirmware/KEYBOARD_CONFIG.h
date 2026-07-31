#ifndef __KEYBOARD_CONFIG_H__
#define __KEYBOARD_CONFIG_H__

#include "CH555.H"

#define ENDP1_IN_SIZE       8  
#define RAINBOW_REVERSE     0   /* 0: Cuon tu Trai sang Phai */
#define MATRIX_ROWS         6       
#define MATRIX_COLS         17      
#define DEBOUNCE_MS         5       

#define KC_NO               0x00
#define KC_A                0x04
#define KC_B                0x05
#define KC_C                0x06
#define KC_D                0x07
#define KC_E                0x08
#define KC_F                0x09
#define KC_G                0x0A
#define KC_H                0x0B
#define KC_I                0x0C
#define KC_J                0x0D
#define KC_K                0x0E
#define KC_L                0x0F
#define KC_M                0x10
#define KC_N                0x11
#define KC_O                0x12
#define KC_P                0x13
#define KC_Q                0x14
#define KC_R                0x15
#define KC_S                0x16
#define KC_T                0x17
#define KC_U                0x18
#define KC_V                0x19
#define KC_W                0x1A
#define KC_X                0x1B
#define KC_Y                0x1C
#define KC_Z                0x1D

#define KC_1                0x1E
#define KC_2                0x1F
#define KC_3                0x20
#define KC_4                0x21
#define KC_5                0x22
#define KC_6                0x23
#define KC_7                0x24
#define KC_8                0x25
#define KC_9                0x26
#define KC_0                0x27

#define KC_ENT              0x28    
#define KC_ESC              0x29    
#define KC_BSPC             0x2A    
#define KC_TAB              0x2B    
#define KC_SPC              0x2C    
#define KC_MINS             0x2D    
#define KC_EQL              0x2E    
#define KC_LBRC             0x2F    
#define KC_RBRC             0x30    
#define KC_BSLS             0x31    
#define KC_SCLN             0x33    
#define KC_QUOT             0x34    
#define KC_GRV              0x35    
#define KC_COMM             0x36    
#define KC_DOT              0x37    
#define KC_SLSH             0x38    
#define KC_CAPS             0x39    

#define KC_F1               0x3A
#define KC_F2               0x3B
#define KC_F3               0x3C
#define KC_F4               0x3D
#define KC_F5               0x3E
#define KC_F6               0x3F
#define KC_F7               0x40
#define KC_F8               0x41
#define KC_F9               0x42
#define KC_F10              0x43
#define KC_F11              0x44
#define KC_F12              0x45

#define KC_PSCR             0x46    
#define KC_SLCK             0x47    
#define KC_PAUS             0x48    
#define KC_INS              0x49    
#define KC_HOME             0x4A    
#define KC_PGUP             0x4B    
#define KC_DEL              0x4C    
#define KC_END              0x4D    
#define KC_PGDN             0x4E    

#define KC_RGHT             0x4F    
#define KC_LEFT             0x50    
#define KC_DOWN             0x51    
#define KC_UP               0x52    
#define KC_APP              0x65    

#define KC_MUTE             0x7F    
#define KC_VOLU             0x80    
#define KC_VOLD             0x81    

#define KC_LED_TOG          0xF0    

#define MOD_LCTL            0xE0
#define MOD_LSFT            0xE1
#define MOD_LALT            0xE2
#define MOD_LGUI            0xE3
#define MOD_RCTL            0xE4
#define MOD_RSFT            0xE5
#define MOD_RALT            0xE6
#define MOD_RGUI            0xE7

/* === DANH SÁCH CH? Ð? LED === */
#define LED_MODE_SPECIFIED_ROLLING  0   /* Che do 1: 5 mau Hex chi dinh, cuon ngang tu trai sang phai */
#define LED_MODE_PASTEL_RAINBOW     1   /* Che do 2: Cau vong 7 sac pastel, cuon sang phai muot ma */
#define LED_MODE_ZONE_ROTATE_4X4    2   /* Che do 3: Cau vong 7 sac pastel, chia ma tran 4x4 xoay kim dong ho */
#define LED_MODE_VERTICAL_DUAL      3   /* Che do 4: Cuon tu tren xuong duoi 2 mau #CCAA88 va #8888CC */
#define LED_MODE_OFF                4   /* Tat LED */
#define LED_MODE_COUNT              5

extern UINT8C KeyMap[MATRIX_ROWS][MATRIX_COLS];
extern UINT8 LedMode;

sbit ENCODER_PAD_A = P1^7;          
sbit ENCODER_PAD_B = P1^6;          

#endif