
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xgpiops.h"

#define GPIO_DEVICE_ID      XPAR_XGPIOPS_0_DEVICE_ID
#define PS_KEY_MIO      26
#define PS_LED_MIO      40
#define GPIO_INPUT      0
#define GPIO_OUTPUT     1

XGpioPs xx_ps_Gpio;

void xx_ps_gpio_init()
{
    XGpioPs_Config *ConfigPtr;
    ConfigPtr = XGpioPs_LookupConfig(GPIO_DEVICE_ID);
    XGpioPs_CfgInitialize(&xx_ps_Gpio, ConfigPtr,ConfigPtr->BaseAddr);
    XGpioPs_SetDirectionPin(&xx_ps_Gpio, PS_LED_MIO, 1);//set dir
    XGpioPs_SetOutputEnablePin(&xx_ps_Gpio, PS_LED_MIO, 1);//enable output

}
void xx_ps_gpio_write(int val)
{

    XGpioPs_SetDirectionPin(&xx_ps_Gpio, PS_LED_MIO, 1);//set dir
    XGpioPs_SetOutputEnablePin(&xx_ps_Gpio, PS_LED_MIO, 1);//enable output
    if(val)
    {
        XGpioPs_WritePin(&xx_ps_Gpio, PS_LED_MIO, 0x0);
    }
    else
    {
        XGpioPs_WritePin(&xx_ps_Gpio, PS_LED_MIO, 0x1);
    }

}
int xx_ps_gpio_read()
{
    XGpioPs_SetDirectionPin(&xx_ps_Gpio, PS_KEY_MIO, GPIO_INPUT);//set dir
    return XGpioPs_ReadPin(&xx_ps_Gpio, PS_KEY_MIO);

}
int main()
{
    init_platform();


    print("Hello World\n\r");
    print("Successfully ran Hello World application");
    xx_ps_gpio_init();
    while(1)
    {
        xx_ps_gpio_write(1);
        sleep(1);
        xx_ps_gpio_write(0);
        sleep(1);
        //print("Hello World\n\r");
        if(xx_ps_gpio_read())
            print("read==1\n\r");
        else
            print("read==0\n\r");
    }
    cleanup_platform();
    return 0;
}


