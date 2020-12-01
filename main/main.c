#include <stdio.h>

void xmu_init(void);
void xmu_task(void);

void usbd_isr(void)
{
    // tud_int_handler(0);
}


    //USB Device Interface Init
    // USB1_USBCMD |= USB_USBCMD_RST;
    // while (USB1_USBCMD & USB_USBCMD_RST);

void app_main()

{
    xmu_init();
    tusb_init();
    printf("USB Device Stack Initialised\r\n");
    while (1) {
        tud_task();
        xmu_task();
    }
}