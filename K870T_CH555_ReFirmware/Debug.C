/*******************************************************************************
* File Name          : Debug.C
* Project            : K870T Keyboard Firmware (CH555 MCU)
* Description        : C?u hình xung nh?p chu?n WCH cho USB Full-Speed
*******************************************************************************/
#include "Debug.H"

void CfgFsys(void)  
{
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;
    // Khóa xung nh?p Fsys = 24MHz (Fusb4x = 48MHz dành riêng cho b? SIE USB)
    CLOCK_CFG = (CLOCK_CFG & ~MASK_SYS_CK_SEL) | 0x05; 
    SAFE_MOD = 0x00;
}

void mDelayuS(UINT16 n)  
{
    while(n) {
        ++SAFE_MOD;
        ++SAFE_MOD;
        --n;
    }
}

void mDelaymS(UINT16 n)                                                    
{
    while(n) {
        mDelayuS(1000);
        --n;
    }
}