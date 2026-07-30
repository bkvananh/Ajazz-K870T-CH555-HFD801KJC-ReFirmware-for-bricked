/*******************************************************************************
* File Name          : MATRIX.h
* Project            : K870T Keyboard Firmware (CH555 MCU)
* Description        : Khai báo hàm quét ma tr?n phím và núm xoay
*******************************************************************************/
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "CH555.H"
#include "Debug.H"
#include "KEYBOARD_CONFIG.h"

/* Gói tin USB HID Report 8 bytes g?i lên PC */
/* [0]: Modifier | [1]: Reserved | [2..7]: T?i da 6 phím nh?n d?ng th?i */
extern UINT8X KeyboardReport[ENDP1_IN_SIZE];

/* C? báo tr?ng thái d? li?u phím có s? thay d?i */
extern UINT8 ReportChanged;

/* Các hàm x? lý ph?n c?ng */
void Matrix_Init(void);
void Matrix_Scan(void);
void Encoder_Scan(void);

#endif