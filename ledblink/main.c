/* code copied and tweaked from https://github.com/andenore/NordicSnippets/blob/master/examples/gpio_toggle/main.c */
#include <libopencm3/nrf51/gpio.h>

#define PIN_ROW1	13
#define PIN_COL1	4

int main(void)
{

	gpio_configure(PIN_ROW1, PIN_CNF_DIR_OUTPUT, PIN_CNF_INPUT_DISCONNECT, PIN_CNF_PULL_DISABLED, PIN_CNF_DRIVE_S0S1, PIN_CNF_SENSE_DISABLED);
	gpio_configure(PIN_COL1, PIN_CNF_DIR_OUTPUT, PIN_CNF_INPUT_DISCONNECT, PIN_CNF_PULL_DISABLED, PIN_CNF_DRIVE_S0S1, PIN_CNF_SENSE_DISABLED);

	gpio_clear(PIN_COL1);

	// Toggle GPIO ON/OFF.
	while (1)
	{
		uint32_t volatile tmo;

		gpio_set(PIN_ROW1);
		tmo = 1000000;
		while (tmo--);

		gpio_clear(PIN_ROW1);
		tmo = 1000000;
		while (tmo--);
	}
}
