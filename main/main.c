#include <stdio.h>
#include "tusb.h"

void xmu_init(void);
void xmu_task(void);

void usbd_isr(void)
{
    tud_int_handler(0);
}

xmu_init();
    //USB Device Interface Init
    // USB1_USBCMD |= USB_USBCMD_RST;
    // while (USB1_USBCMD & USB_USBCMD_RST);

tusb_init();
printf("USB Device Stack Initialised\r\n");

}

void app_main()
{
    tud_task();

    xmu_task();
}