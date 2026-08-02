#include "CH555.H"
#include "Debug.H"
#include "MATRIX.h"
#include "USB_HANDLER.h"

void main(void)
{
    CfgFsys();
    mDelaymS(20);

    Matrix_Init();      // khoi tao ma tran, LED va P4_LED_KEY
    InitUSB_Device();
    EA = 1;

    while (1)
    {
        if (Ready)
        {
            /* Quet va quat LED xuyen suot continuous, khong bi hoan boidelay */
            Matrix_Scan();

            if (ReportChanged)
            {
                while (Endp1Busy);
                Endp1Busy = 1;
                Send_Keyboard_Report(KeyboardReport, ENDP1_IN_SIZE);
            }
        }

        /* DA XOA mDelaymS(DEBOUNCE_MS) AT DAY DE TRIET TIEU HOAN TOAN L?I CH?P NHÁY LED */
    }
}