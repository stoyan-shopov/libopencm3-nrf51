/* code copied and tweaked from https://github.com/andenore/NordicSnippets/blob/master/examples/gpio_toggle/main.c */
#include <libopencm3/nrf51/nrf51.h>

#define PIN_ROW1	13
#define PIN_COL1	4

int main(void)
{
#if 0
	NRF_GPIO->PIN_CNF[PIN_ROW1] = (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos) |
		(GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos) |
		(GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
		(GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) |
		(GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);

	struct {
		__IOM uint32_t DIR        : 1;            /*!< [0..0] Pin direction.                                                     */
		__IOM uint32_t INPUT      : 1;            /*!< [1..1] Connect or disconnect input path.                                  */
		__IOM uint32_t PULL       : 2;            /*!< [3..2] Pull-up or -down configuration.                                    */
		__IM  uint32_t            : 4;
		__IOM uint32_t DRIVE      : 3;            /*!< [10..8] Drive configuration.                                              */
		__IM  uint32_t            : 5;
		__IOM uint32_t SENSE      : 2;            /*!< [17..16] Pin sensing mechanism.                                           */
	} PIN_CN
#endif

	/*! \todo - this is evil, the port configuration should be all
	 *	set at once, but the generated headers do not conveniently export
	 *	port offset bitfield definitions as of today... must be fixed */
	NRF_GPIO->PIN_CNF_b[PIN_ROW1].DIR = GPIO_PIN_CNF_DIR_Output;
	NRF_GPIO->PIN_CNF_b[PIN_ROW1].DRIVE = GPIO_PIN_CNF_DRIVE_S0S1;
	NRF_GPIO->PIN_CNF_b[PIN_ROW1].INPUT = GPIO_PIN_CNF_INPUT_Connect;
	NRF_GPIO->PIN_CNF_b[PIN_ROW1].PULL = GPIO_PIN_CNF_PULL_Disabled;
	NRF_GPIO->PIN_CNF_b[PIN_ROW1].SENSE = GPIO_PIN_CNF_SENSE_Disabled;

	/*
	   NRF_GPIO->PIN_CNF[PIN_COL1] = (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos) |
	   (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos) |
	   (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
	   (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) |
	   (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);
	 */
	NRF_GPIO->PIN_CNF_b[PIN_COL1].DIR = GPIO_PIN_CNF_DIR_Output;
	NRF_GPIO->PIN_CNF_b[PIN_COL1].DRIVE = GPIO_PIN_CNF_DRIVE_S0S1;
	NRF_GPIO->PIN_CNF_b[PIN_COL1].INPUT = GPIO_PIN_CNF_INPUT_Connect;
	NRF_GPIO->PIN_CNF_b[PIN_COL1].PULL = GPIO_PIN_CNF_PULL_Disabled;
	NRF_GPIO->PIN_CNF_b[PIN_COL1].SENSE = GPIO_PIN_CNF_SENSE_Disabled;

	NRF_GPIO->OUTCLR = (1UL << PIN_COL1);    

	// Toggle GPIO ON/OFF.
	while (1)
	{
		uint32_t volatile tmo;

		NRF_GPIO->OUTSET = (1UL << PIN_ROW1);    
		tmo = 100000;
		while (tmo--);

		NRF_GPIO->OUTCLR = (1UL << PIN_ROW1);  
		tmo = 1000000;
		while (tmo--);
	}
}
