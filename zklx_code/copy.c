
static gpio_t xx_gpio;

void xx_gpio_init(u8 io_num,u8 is_out)// None: 0, PA3: 4, PA4: 5, PA5: 6, PA6: 7, PA7: 8, PB0: 9, PB1: 10, PB2: 11, PB3: 12, PB4: 13, PB5/WKO: 26, PE0: 14, PE4: 18, PE5: 19, PE6: 20, PE7: 21, PF0: 22, PF1: 23, PF2: 24, PF3: 25
{
  
	gpio_t *p = &xx_gpio;
    bsp_gpio_cfg_init(p, io_num);//用io num初始化xx_gpio结构体
    if (p->sfr == NULL) {
        return;
    }
	if(is_out)
		{
    p->sfr[GPIOxDE] |= BIT(p->num);
    p->sfr[GPIOxDIR] &= ~BIT(p->num);
		}
	else
		{
		p->sfr[GPIOxDE] |= BIT(p->num);
		p->sfr[GPIOxPU] |= BIT(p->num);//上拉
		p->sfr[GPIOxDIR] |= BIT(p->num);

	}
}



AT(.com_text.mute)
bool xx_gpio_read(void)
{
	gpio_t *p = &xx_gpio;
    return (p->sfr[GPIOx] & BIT(p->num));
}


AT(.com_text.mute)
void xx_gpio_write(bool val)
{
  
    gpio_t *p = &mute_gpio;
	
    if (p->sfr == NULL) {
        return;
    }
    if (val) {
        p->sfr[GPIOxSET] = BIT(p->num);
    } else {
        p->sfr[GPIOxCLR] = BIT(p->num);
    }
}	


