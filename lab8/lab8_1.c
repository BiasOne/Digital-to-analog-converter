#include <avr/io.h>

extern void clock_init(void);

float vDAC = 1.5;
float vREF = 2.5;
int staticVar = 0xFFF;
uint16_t chXData;

int main(void)
{
   clock_init();
 
   DACA.CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;
   DACA.CTRLC = DAC_REFSEL_AREFB_gc;
   PORTA.DIRCLR = PIN2_bm;
 
   chXData = ((vDAC*staticVar)/vREF);   
   
    while (1) 
    {
		DACA_CH0DATA = chXData;
		while(!(DACA.STATUS & DAC_CH0DRE_bm));
		
    }
}

