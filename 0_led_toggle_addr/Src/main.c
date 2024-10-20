// Where is the led connected?
// PORT: A
// PIN: 5

#define PERIPH_BASE			(0x40000000UL)
#define AHB1PERIPH_OFFSET	(0x00020000UL)
#define AHB2PERIPH_OFFSET	(0x08000000UL)
#define AHB2PERIPH_BASE		(PERIPH_BASE + AHB2PERIPH_OFFSET)
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET		(0x0000U)

#define GPIOA_BASE			(AHB2PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET			(0x00001000UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET 	(0X14UL)
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET		(0x00UL)
#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET			(0x14UL)
#define GPIOA_OD_R			(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN				(1U<<17)

#define PIN5				(1U<<5)
#define LED_PIN				PIN5
#define GPIO_MODER_OUTPUT (1 << (5 * 2))  // Set PA5 as output


int main(void) {
	// 1. Enable clock access to GPIOA
	RCC_AHB1EN_R |= GPIOAEN;
	// 2. Set PA5 as output pin
	GPIOA_MODE_R &= ~(0x3 << (5 * 2));
	GPIOA_MODE_R |= GPIO_MODER_OUTPUT;

	while(1) {
		// 3. Set PA5 high
		GPIOA_OD_R ^= LED_PIN;
		for(int i=0; i<100000;i++){}
	}
	return 0;
}
