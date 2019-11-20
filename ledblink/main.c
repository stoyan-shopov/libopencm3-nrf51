/* code copied and tweaked from https://github.com/andenore/NordicSnippets/blob/master/examples/gpio_toggle/main.c */
#include <libopencm3/nrf51/gpio.h>

enum
{
	LED_ROW1	= 13,
	LED_ROW2	= 14,
	LED_COL1	= 4,
	BUTTON_A	= 17,
};

int main(void)
{

	gpio_configure(LED_ROW1, PIN_CNF_DIR_OUTPUT, PIN_CNF_INPUT_DISCONNECT, PIN_CNF_PULL_DISABLED, PIN_CNF_DRIVE_S0S1, PIN_CNF_SENSE_DISABLED);
	gpio_configure(LED_ROW2, PIN_CNF_DIR_OUTPUT, PIN_CNF_INPUT_DISCONNECT, PIN_CNF_PULL_DISABLED, PIN_CNF_DRIVE_S0S1, PIN_CNF_SENSE_DISABLED);
	gpio_configure(LED_COL1, PIN_CNF_DIR_OUTPUT, PIN_CNF_INPUT_DISCONNECT, PIN_CNF_PULL_DISABLED, PIN_CNF_DRIVE_S0S1, PIN_CNF_SENSE_DISABLED);

	gpio_configure(BUTTON_A, PIN_CNF_DIR_INPUT, PIN_CNF_INPUT_CONNECT, PIN_CNF_PULL_DISABLED, PIN_CNF_DRIVE_S0S1, PIN_CNF_SENSE_DISABLED);

	gpio_clear(LED_COL1);

	// Toggle GPIO ON/OFF.
	while (1)
	{
		uint32_t volatile tmo;

		gpio_set(LED_ROW1);
		tmo = 1000000;
		while (tmo--);

		gpio_clear(LED_ROW1);
		tmo = 1000000;
		while (tmo--);
		(gpio_read(BUTTON_A) ? gpio_clear : gpio_set)(LED_ROW2);
	}
}
