/*******************************************************************************
* File Name          : USB_HANDLER.c
* Project            : K870T Keyboard Firmware (CH555 MCU)
* Description        : X? lý ng?t USB
*******************************************************************************/
#include "USB_HANDLER.h"

UINT8C DevDesc[] = {
    0x12, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00, THIS_ENDP0_SIZE,
    0x86, 0x1A, 0xE1, 0xE6, 0x00, 0x01, 0x01, 0x02, 0x00, 0x01
};

UINT8C KeyRepDesc[] = {
    0x05, 0x01, 0x09, 0x06, 0xA1, 0x01, 0x05, 0x07, 0x19, 0xE0,
    0x29, 0xE7, 0x15, 0x00, 0x25, 0x01, 0x75, 0x01, 0x95, 0x08,
    0x81, 0x02, 0x95, 0x01, 0x75, 0x08, 0x81, 0x01, 0x95, 0x03,
    0x75, 0x01, 0x05, 0x08, 0x19, 0x01, 0x29, 0x03, 0x91, 0x02,
    0x95, 0x05, 0x75, 0x01, 0x91, 0x01, 0x95, 0x06, 0x75, 0x08,
    0x26, 0xFF, 0x00, 0x05, 0x07, 0x19, 0x00, 0x29, 0x91, 0x81,
    0x00, 0xC0
};

UINT8C CfgDesc[] = {
    0x09, 0x02, 0x22, 0x00, 0x01, 0x01, 0x00, 0xA0, 0x32,
    0x09, 0x04, 0x00, 0x00, 0x01, 0x03, 0x01, 0x01, 0x00,
    0x09, 0x21, 0x11, 0x01, 0x00, 0x01, 0x22, sizeof(KeyRepDesc) & 0xFF, sizeof(KeyRepDesc) >> 8,
    0x07, 0x05, 0x81, 0x03, ENDP1_IN_SIZE, 0x00, 0x0A
};

UINT8C MyLangDescr[] = { 0x04, 0x03, 0x09, 0x04 };
UINT8C MyManuInfo[]  = { 0x0E, 0x03, 'w',0, 'c',0, 'h',0, '.',0, 'c',0, 'n',0 };
UINT8C MyProdInfo[]  = { 0x0C, 0x03, 'k',0, '8',0, '7',0, '0',0, 't',0 };

volatile UINT8 Endp1Busy = 0;
UINT8 UsbConfig = 0;
UINT8 Ready = 0;

volatile UINT8  D0SetupReqCode = 0xFF;
volatile UINT16 D0SetupLen = 0x00;
volatile PUINT8 pD0Descr;

#define FAST_COPY(dst, src, len) do { \
    UINT8 _i; \
    for (_i = 0; _i < (UINT8)(len); _i++) { \
        ((PUINT8)(dst))[_i] = ((PUINT8)(src))[_i]; \
    } \
} while(0)

void Send_Keyboard_Report(UINT8 *buf, UINT8 len)
{
    FAST_COPY(pUSB_BUF_DEV0 + UX_EP1_ADDR, buf, len);
    D0_EP1T_L = len;
    D0_EP1RES = (D0_EP1RES & ~MASK_UEP_X_RES) | UEP_X_RES_ACK;
}

void USB_DeviceInterrupt(void) interrupt INT_NO_USB using 1
{
    UINT8 us;
    UINT16 len;

    us = USB_IF;
    if (us & bUX_IF_D0_TRANS) {
USB_DevIntNext:
        switch (D0_STATUS & (bUXS_SETUP_ACT | MASK_UXS_TOKEN | MASK_UXS_ENDP)) {
            case UXS_TOKEN_IN | 1:
            case bUXS_SETUP_ACT | UXS_TOKEN_IN | 1:
                D0_EP1T_L = 0;
                D0_EP1RES ^= bUEP_X_TOG;
                Endp1Busy = 0;
                D0_EP1RES = (D0_EP1RES & ~MASK_UEP_X_RES) | UEP_X_RES_NAK;
                break;

            case UXS_TOKEN_IN | 0:
            case bUXS_SETUP_ACT | UXS_TOKEN_IN | 0:
                switch(D0SetupReqCode) {
                    case USB_GET_DESCRIPTOR:
                        len = D0SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : D0SetupLen;
                        FAST_COPY(pD0_EP0_BUF, pD0Descr, len);
                        D0SetupLen -= len;
                        pD0Descr += len;
                        D0_EP0T_L = len;
                        D0_EP0RES ^= bUEP_T_TOG;
                        break;
                    case USB_SET_ADDRESS:
                        D0_ADDR = D0SetupLen;
                        D0_EP0RES = UEP_R_RES_ACK | UEP_T_RES_NAK;
                        break;
                    default:
                        D0_EP0T_L = 0;
                        D0_EP0RES = UEP_R_RES_ACK | UEP_T_RES_NAK;
                        break;
                }
                break;

            case UXS_TOKEN_OUT | 0:
            case bUXS_SETUP_ACT | UXS_TOKEN_OUT | 0:
                D0_EP0RES ^= bUEP_R_TOG;
                break;

            default:
                if ((D0_STATUS & (bUXS_SETUP_ACT | MASK_UXS_TOKEN)) == (bUXS_SETUP_ACT | UXS_TOKEN_FREE)) {
                    D0_EP0RES = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;
                    D0SetupLen = ((UINT16)pD0_SETUP_REQ->wLengthH << 8) + pD0_SETUP_REQ->wLengthL;
                    D0SetupReqCode = pD0_SETUP_REQ->bRequest;
                    if (pD0_SETUP_REQ->wLengthH || D0SetupLen > 0x7F) D0SetupLen = 0x7F;
                    len = 0;

                    if ((pD0_SETUP_REQ->bRequestType & USB_REQ_TYP_MASK) == USB_REQ_TYP_STANDARD) {
                        switch(D0SetupReqCode) {
                            case USB_GET_DESCRIPTOR:
                                switch(pD0_SETUP_REQ->wValueH) {
                                    case 1: pD0Descr = (PUINT8)&DevDesc[0]; len = sizeof(DevDesc); break;
                                    case 2: pD0Descr = (PUINT8)&CfgDesc[0]; len = sizeof(CfgDesc); break;
                                    case 3:
                                        switch(pD0_SETUP_REQ->wValueL) {
                                            case 1: pD0Descr = (PUINT8)&MyManuInfo[0]; len = sizeof(MyManuInfo); break;
                                            case 2: pD0Descr = (PUINT8)&MyProdInfo[0]; len = sizeof(MyProdInfo); break;
                                            case 0: pD0Descr = (PUINT8)&MyLangDescr[0]; len = sizeof(MyLangDescr); break;
                                            default: len = 0xFF; break;
                                        }
                                        break;
                                    case 0x22:
                                        pD0Descr = (PUINT8)&KeyRepDesc[0];
                                        len = sizeof(KeyRepDesc);
                                        break;
                                    default: len = 0xFF; break;
                                }
                                if (D0SetupLen > len) D0SetupLen = len;
                                len = D0SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : D0SetupLen;
                                FAST_COPY(pD0_EP0_BUF, pD0Descr, len);
                                D0SetupLen -= len;
                                pD0Descr += len;
                                break;

                            case USB_SET_ADDRESS: D0SetupLen = pD0_SETUP_REQ->wValueL; break;
                            case USB_SET_CONFIGURATION:
                                UsbConfig = pD0_SETUP_REQ->wValueL;
                                if (UsbConfig) Ready = 1;
                                break;
                            default: len = 0xFF; break;
                        }
                    }

                    if (len == 0xFF) {
                        D0_EP0RES = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL;
                    } else {
                        D0_EP0T_L = len;
                        D0_EP0RES = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;
                    }
                }
                break;
        }
        D0_STATUS = 0;
    }
    else if (us & bUX_IF_BUS_RST) {
        D0_EP0RES = UEP_R_RES_ACK | UEP_T_RES_NAK;
        D0_EP1RES = UEP_X_RES_NAK;
        D0_EP_MOD = bUX_DEV_EN;
        D0_ADDR = 0;
        HB_ADDR = 0x7F;
        USB_IF = 0xFF;
        Endp1Busy = 0;
        Ready = 0;
        USB_IE = bUX_IE_SUSPEND | bUX_IE_TRANSFER | bUX_IE_BUS_RST;
        USB_IF |= bUX_IF_BUS_RST;
    }
    else if (us & bUX_IF_SUSPEND) {
        USB_IF |= bUX_IF_SUSPEND;
        D0_STATUS = 0;
    }

    if (USB_IF & bUX_IF_D0_TRANS) goto USB_DevIntNext;
}

void InitUSB_Device(void)
{
    IE_USB = 0;
    USB_CTRL = 0;
    D0_EP_MOD = bUX_DEV_EN;
    D0_EP1T_L = 0;
    D0_ADDR = 0;
    HB_ADDR = 0x7F;
    USB_IF = 0xFF;
    USB_IE = bUX_IE_SUSPEND | bUX_IE_TRANSFER | bUX_IE_BUS_RST;
    USB_CTRL = bUX_DP_PU_EN;
    IE_USB = 1;
}