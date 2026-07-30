#include "CH555.H"
#include "Debug.H"
#include "MATRIX.h"
#include "USB_HANDLER.h"

void main(void)
{
    CfgFsys();
    mDelaymS(20);

    Matrix_Init();      // da bao gom cau hinh LED + ma tran phim
    InitUSB_Device();
    EA = 1;

    while (1)
    {
        if (Ready)
        {
            Matrix_Scan();   // vua quet phim, vua sang LED, gop lam 1

            if (ReportChanged)
            {
                while (Endp1Busy);
                Endp1Busy = 1;
                Send_Keyboard_Report(KeyboardReport, ENDP1_IN_SIZE);
            }
        }

        mDelaymS(DEBOUNCE_MS);
    }
}
