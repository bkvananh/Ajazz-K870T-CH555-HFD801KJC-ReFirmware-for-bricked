/*******************************************************************************
* File Name          : USB_DESC.h
* Project            : K870T Keyboard Firmware (CH555 MCU)
* Description        : Khai báo USB Descriptors (Header)
*******************************************************************************/
#ifndef __USB_DESC_H__
#define __USB_DESC_H__

#include "CH555.H"

#define THIS_ENDP0_SIZE         8     
#define ENDP1_IN_SIZE           8     

extern UINT8C DevDesc[];
extern UINT8C KeyRepDesc[];
extern UINT8C CfgDesc[];
extern UINT8C MyLangDescr[];
extern UINT8C MyManuInfo[];
extern UINT8C MyProdInfo[];

#endif