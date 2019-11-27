#include <libopencm3/nrf51/gpio.h>
#include <libopencm3/nrf51/uart.h>

enum
{
	/* pad1, banana connector number 0 on the microbit */
	PAD1_GPIO_NUMBER	= 3,
	UART_TX_PIN		= PAD1_GPIO_NUMBER,
};

int main(void)
{
uint32_t volatile tmo;

	/* configure uart tx pin */
	gpio_configure(UART_TX_PIN, PIN_CNF_DIR_OUTPUT, PIN_CNF_INPUT_DISCONNECT, PIN_CNF_PULL_DISABLED, PIN_CNF_DRIVE_S0S1, PIN_CNF_SENSE_DISABLED);
	/* configure uart */
	UART_BAUDRATE = BAUD_9600;
	UART_PSELTXD = UART_TX_PIN;
	UART_ENABLE = UART_PERIPHERAL_ENABLE;

	UART_STARTTX_TASK = 1;

	while (1)
	{
		tmo = 1000000;
		while (tmo--);

		UART_TXD = 's';
	}

	while (1);
}
