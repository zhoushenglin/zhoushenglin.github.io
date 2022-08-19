///gpio初始化
#define XX_GPIO_PIN 1
//1,2,3,.....A0,A1,A2...

void xx_gpio_init(void)
{
    pinMode(XX_GPIO_PIN,OUTPUT);
}
bool xx_gpio_read(void)
{
    pinMode(XX_GPIO_PIN,INPUT);
    return digitalRead(XX_GPIO_PIN);
}

void xx_gpio_write(bool b)
{
    pinMode(XX_GPIO_PIN,OUTPUT);
    if(b)
        digitalWrite(XX_GPIO_PIN, HIGH);
    else
        digitalWrite(XX_GPIO_PIN, LOW);
}
////interrupt
void xx_enable_irq(void)
{
    pinMode(XX_GPIO_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(XX_GPIO_PIN), pwm_in_irqhandle, RISING);//LOW,CHANGE ,RISING ,FALLING ,HIGH
}
void xx_disable_irq(void)
{
    detachInterrupt(digitalPinToInterrupt(XX_GPIO_PIN));
}
void xx_irqhandler(enum HAL_GPIO_PIN_T pin)
{

    Serial.println(" hal irq");
    /*
    APP_MESSAGE_BLOCK msg;
    msg.mod_id          = APP_MODUAL_XX;
    msg.msg_body.message_id = XX_EINT_EVT;
    msg.msg_body.message_ptr = (uint32_t) NULL;
    app_mailbox_put(&msg);
    */

}
//pwm
// Set pin 9's PWM frequency to 3906 Hz (31250/8 = 3906)
// Note that the base frequency for pins 3, 9, 10, and 11 is 31250 Hz
//pwm_freq_set(9, 8);
// Set pin 6's PWM frequency to 62500 Hz (62500/1 = 62500)
// Note that the base frequency for pins 5 and 6 is 62500 Hz
//pwm_freq_set(6, 1);
// Set pin 10's PWM frequency to 31 Hz (31250/1024 = 31)
//pwm_freq_set(10, 1024);
void pwm_freq_set(int pin, int divisor)
{
    byte mode;
    if(pin == 5 || pin == 6 || pin == 9 || pin == 10)
    {
        switch(divisor)
        {
            case 1:
                mode = 0x01;
                break;
            case 8:
                mode = 0x02;
                break;
            case 64:
                mode = 0x03;
                break;
            case 256:
                mode = 0x04;
                break;
            case 1024:
                mode = 0x05;
                break;
            default:
                return;
        }
        if(pin == 5 || pin == 6)
        {
            TCCR0B = TCCR0B & 0b11111000 | mode;
        }
        else
        {
            TCCR1B = TCCR1B & 0b11111000 | mode;
        }
    }
    else if(pin == 3 || pin == 11)
    {
        switch(divisor)
        {
            case 1:
                mode = 0x01;
                break;
            case 8:
                mode = 0x02;
                break;
            case 32:
                mode = 0x03;
                break;
            case 64:
                mode = 0x04;
                break;
            case 128:
                mode = 0x05;
                break;
            case 256:
                mode = 0x06;
                break;
            case 1024:
                mode = 0x7;
                break;
            default:
                return;
        }
        TCCR2B = TCCR2B & 0b11111000 | mode;
    }
}
void pwm_gpio_init(void)
{
    pinMode(XX_GPIO_PIN,OUTPUT);
}
void pwm_dutecycle_set(int pin,int persent)
{
    int val=0;
    val=map(persent,0,100,0,255);
    analogWrite(pin,val);
}
//
//install mstimer2 lib
#include <MsTimer2.h>

#define XX_TIME_MS 1000

void xx_timerhandler(void const * param)
{
    Serial.println("xx_timehandler");
//your code
}

void xx_timer_start(unsigned int ms)
{
    Serial.println("xx_timer_start");
    MsTimer2::set(ms, xx_timerhandler);
    MsTimer2::start();
}
void xx_timer_stop(void)
{
    Serial.println("xx_timer_stop");
    MsTimer2::stop();
}
//时间操作函数
delay(ms);
delayMicroseconds(us);
ms=millis();
us=micros();

//i2c
      todo
//spi
	todo
	
//ble
