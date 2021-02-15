#include <avr/io.h>
#include <avr/interrupt.h>

extern void clock_init(void);

uint16_t sinewaveVect[256] =
{0x800,0x832,0x864,0x896,0x8c8,0x8fa,0x92c,0x95e,
	0x98f,0x9c0,0x9f1,0xa22,0xa52,0xa82,0xab1,0xae0,
	0xb0f,0xb3d,0xb6b,0xb98,0xbc5,0xbf1,0xc1c,0xc47,
	0xc71,0xc9a,0xcc3,0xceb,0xd12,0xd39,0xd5f,0xd83,
	0xda7,0xdca,0xded,0xe0e,0xe2e,0xe4e,0xe6c,0xe8a,
	0xea6,0xec1,0xedc,0xef5,0xf0d,0xf24,0xf3a,0xf4f,
	0xf63,0xf76,0xf87,0xf98,0xfa7,0xfb5,0xfc2,0xfcd,
	0xfd8,0xfe1,0xfe9,0xff0,0xff5,0xff9,0xffd,0xffe,
	0xfff,0xffe,0xffd,0xff9,0xff5,0xff0,0xfe9,0xfe1,
	0xfd8,0xfcd,0xfc2,0xfb5,0xfa7,0xf98,0xf87,0xf76,
	0xf63,0xf4f,0xf3a,0xf24,0xf0d,0xef5,0xedc,0xec1,
	0xea6,0xe8a,0xe6c,0xe4e,0xe2e,0xe0e,0xded,0xdca,
	0xda7,0xd83,0xd5f,0xd39,0xd12,0xceb,0xcc3,0xc9a,
	0xc71,0xc47,0xc1c,0xbf1,0xbc5,0xb98,0xb6b,0xb3d,
	0xb0f,0xae0,0xab1,0xa82,0xa52,0xa22,0x9f1,0x9c0,
	0x98f,0x95e,0x92c,0x8fa,0x8c8,0x896,0x864,0x832,
	0x800,0x7cd,0x79b,0x769,0x737,0x705,0x6d3,0x6a1,
	0x670,0x63f,0x60e,0x5dd,0x5ad,0x57d,0x54e,0x51f,
	0x4f0,0x4c2,0x494,0x467,0x43a,0x40e,0x3e3,0x3b8,
	0x38e,0x365,0x33c,0x314,0x2ed,0x2c6,0x2a0,0x27c,
	0x258,0x235,0x212,0x1f1,0x1d1,0x1b1,0x193,0x175,
	0x159,0x13e,0x123,0x10a,0xf2,0xdb,0xc5,0xb0,
	0x9c,0x89,0x78,0x67,0x58,0x4a,0x3d,0x32,
	0x27,0x1e,0x16,0xf,0xa,0x6,0x2,0x1,
	0x0,0x1,0x2,0x6,0xa,0xf,0x16,0x1e,
	0x27,0x32,0x3d,0x4a,0x58,0x67,0x78,0x89,
	0x9c,0xb0,0xc5,0xdb,0xf2,0x10a,0x123,0x13e,
	0x159,0x175,0x193,0x1b1,0x1d1,0x1f1,0x212,0x235,
	0x258,0x27c,0x2a0,0x2c6,0x2ed,0x314,0x33c,0x365,
	0x38e,0x3b8,0x3e3,0x40e,0x43a,0x467,0x494,0x4c2,
	0x4f0,0x51f,0x54e,0x57d,0x5ad,0x5dd,0x60e,0x63f,
0x670,0x6a1,0x6d3,0x705,0x737,0x769,0x79b,0x7cd};

uint16_t sinewaveVectHalf[256]=
{0x400,0x419,0x432,0x44b,0x464,0x47d,0x496,0x4af,
	0x4c8,0x4e0,0x4f9,0x511,0x529,0x541,0x559,0x571,
	0x588,0x59f,0x5b6,0x5cc,0x5e3,0x5f9,0x60e,0x624,
	0x639,0x64e,0x662,0x676,0x68a,0x69d,0x6b0,0x6c2,
	0x6d4,0x6e6,0x6f7,0x707,0x718,0x727,0x736,0x745,
	0x753,0x761,0x76e,0x77b,0x787,0x793,0x79e,0x7a8,
	0x7b2,0x7bb,0x7c4,0x7cc,0x7d4,0x7db,0x7e1,0x7e7,
	0x7ec,0x7f1,0x7f5,0x7f8,0x7fb,0x7fd,0x7ff,0x800,
	0x800,0x800,0x7ff,0x7fd,0x7fb,0x7f8,0x7f5,0x7f1,
	0x7ec,0x7e7,0x7e1,0x7db,0x7d4,0x7cc,0x7c4,0x7bb,
	0x7b2,0x7a8,0x79e,0x793,0x787,0x77b,0x76e,0x761,
	0x753,0x745,0x736,0x727,0x718,0x707,0x6f7,0x6e6,
	0x6d4,0x6c2,0x6b0,0x69d,0x68a,0x676,0x662,0x64e,
	0x639,0x624,0x60e,0x5f9,0x5e3,0x5cc,0x5b6,0x59f,
	0x588,0x571,0x559,0x541,0x529,0x511,0x4f9,0x4e0,
	0x4c8,0x4af,0x496,0x47d,0x464,0x44b,0x432,0x419,
	0x400,0x3e7,0x3ce,0x3b5,0x39c,0x383,0x36a,0x351,
	0x338,0x320,0x307,0x2ef,0x2d7,0x2bf,0x2a7,0x28f,
	0x278,0x261,0x24a,0x234,0x21d,0x207,0x1f2,0x1dc,
	0x1c7,0x1b2,0x19e,0x18a,0x176,0x163,0x150,0x13e,
	0x12c,0x11a,0x109,0xf9,0xe8,0xd9,0xca,0xbb,
	0xad,0x9f,0x92,0x85,0x79,0x6d,0x62,0x58,
	0x4e,0x45,0x3c,0x34,0x2c,0x25,0x1f,0x19,
	0x14,0xf,0xb,0x8,0x5,0x3,0x1,0x0,
	0x0,0x0,0x1,0x3,0x5,0x8,0xb,0xf,
	0x14,0x19,0x1f,0x25,0x2c,0x34,0x3c,0x45,
	0x4e,0x58,0x62,0x6d,0x79,0x85,0x92,0x9f,
	0xad,0xbb,0xca,0xd9,0xe8,0xf9,0x109,0x11a,
	0x12c,0x13e,0x150,0x163,0x176,0x18a,0x19e,0x1b2,
	0x1c7,0x1dc,0x1f2,0x207,0x21d,0x234,0x24a,0x261,
	0x278,0x28f,0x2a7,0x2bf,0x2d7,0x2ef,0x307,0x320,
0x338,0x351,0x36a,0x383,0x39c,0x3b5,0x3ce,0x3e7};

int main(void)
{
	clock_init();
	tcc0_init();
	daca_init();
	usartd0_init();
	
	DMA.CTRL = DMA_RESET_bm;
	DMA.CH0.CTRLA = DMA_RESET_bm;
	
	DMA.CH0.TRFCNT= (uint16_t)(sizeof(sinewaveVect));

	DMA.CH0.REPCNT = 0;
	DMA.CH0.CTRLA |= DMA_CH_REPEAT_bm | DMA_CH_SINGLE_bm | DMA_CH_BURSTLEN_2BYTE_gc;
	DMA.CH0.ADDRCTRL |= DMA_CH_SRCRELOAD_BLOCK_gc | DMA_CH_SRCDIR_INC_gc |DMA_CH_DESTRELOAD_BURST_gc|DMA_CH_DESTDIR_INC_gc;
	DMA.CH0.TRIGSRC = DMA_CH_TRIGSRC_DACA_CH0_gc;
	
	DMA.CH0.SRCADDR0= (uint8_t)((uintptr_t)sinewaveVect);
	DMA.CH0.SRCADDR1= (uint8_t)((uintptr_t)sinewaveVect >> 8);
	DMA.CH0.SRCADDR2= (uint8_t)(((uint32_t)((uintptr_t)sinewaveVect)) >> 16);
	
	DMA.CH0.DESTADDR0 = (uint8_t)((uintptr_t)&DACA.CH0DATA);
	DMA.CH0.DESTADDR1 = (uint8_t)((uintptr_t)&DACA.CH0DATA >> 8);
	DMA.CH0.DESTADDR2 = (uint8_t)(((uint32_t)((uintptr_t)&DACA.CH0DATA)) >> 16);
	
	DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
	DMA.CTRL = DMA_ENABLE_bm;
	
	PMIC.CTRL |=PMIC_LOLVLEN_bm;
	sei();
	
	TCC0.CTRLA = TC_CLKSEL_DIV2_gc;

	
	while(1)
	{
		char input = usartd0_in_char();
		usartd0_out_char(input);
		
		if (input == 'h')
		{
			DMA.CH0.CTRLA = 0;			
			DMA.CH0.TRFCNT= (uint16_t)(sizeof(sinewaveVectHalf));
			
			DMA.CH0.SRCADDR0= (uint8_t)((uintptr_t)sinewaveVectHalf);
			DMA.CH0.SRCADDR1= (uint8_t)((uintptr_t)sinewaveVectHalf >> 8);
			DMA.CH0.SRCADDR2= (uint8_t)(((uint32_t)((uintptr_t)sinewaveVectHalf)) >> 16);
		
			DMA.CH0.CTRLA |= DMA_CH_REPEAT_bm | DMA_CH_SINGLE_bm | DMA_CH_BURSTLEN_2BYTE_gc;
			DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
		}
		else if(input == 'o')
		{
			DMA.CH0.CTRLA = 0;			
			DMA.CH0.TRFCNT= (uint16_t)(sizeof(sinewaveVect));
			
			DMA.CH0.SRCADDR0= (uint8_t)((uintptr_t)sinewaveVect);
			DMA.CH0.SRCADDR1= (uint8_t)((uintptr_t)sinewaveVect >> 8);
			DMA.CH0.SRCADDR2= (uint8_t)(((uint32_t)((uintptr_t)sinewaveVect)) >> 16);
					
			DMA.CH0.CTRLA |= DMA_CH_REPEAT_bm | DMA_CH_SINGLE_bm | DMA_CH_BURSTLEN_2BYTE_gc;
			DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
		}
	}
}

void tcc0_init(void)
{
	TCC0.PER=60;
	EVSYS.CH0MUX = EVSYS_CHMUX_TCC0_OVF_gc;
}


void daca_init(void)
{
	DACA.CTRLB = DAC_CHSEL_SINGLE_gc | DAC_CH0TRIG_bm;
	DACA.CTRLC = DAC_REFSEL_AREFB_gc;
	DACA.EVCTRL = DAC_EVSEL_0_gc;
	DACA.CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;
}