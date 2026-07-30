/*******************************************************************************
* File Name          : USB_HANDLER.h
* Project            : K870T Keyboard Firmware (CH555 MCU)
* Description        : Khai báo hàm di?u khi?n giao th?c USB HID
*******************************************************************************/
#ifndef __USB_HANDLER_H__
#define __USB_HANDLER_H__

#include "CH555.H"
#include "Debug.H"
#include "USB_DESC.h"

extern volatile UINT8 Endp1Busy;
extern UINT8 Ready;

void InitUSB_Device(void);
void Send_Keyboard_Report(UINT8 *buf, UINT8 len);

#endif