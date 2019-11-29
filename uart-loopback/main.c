#include <libopencm3/nrf51/gpio.h>
#include <libopencm3/nrf51/uart.h>

enum
{
	/* pad1, banana connector number 0 on the microbit */
	PAD1_GPIO_NUMBER	= 3,
	/* pad2, banana connector number 1 on the microbit */
	PAD2_GPIO_NUMBER	= 2,
	UART_TX_PIN		= PAD1_GPIO_NUMBER,
	UART_RX_PIN		= PAD2_GPIO_NUMBER,
};

int main(void)
{
	/* configure uart tx pin */
	gpio_configure(UART_TX_PIN, PIN_CNF_DIR_OUTPUT, PIN_CNF_INPUT_DISCONNECT, PIN_CNF_PULL_DISABLED, PIN_CNF_DRIVE_S0S1, PIN_CNF_SENSE_DISABLED);
	/* configure uart rx pin */
	gpio_configure(UART_RX_PIN, PIN_CNF_DIR_INPUT, PIN_CNF_INPUT_CONNECT, PIN_CNF_PULL_DISABLED, PIN_CNF_DRIVE_S0S1, PIN_CNF_SENSE_DISABLED);
	/* configure uart */
	UART_BAUDRATE = BAUD_9600;
	UART_PSELTXD = UART_TX_PIN;
	UART_PSELRXD = UART_RX_PIN;
	UART_ENABLE = UART_PERIPHERAL_ENABLE;

	UART_STARTTX_TASK = 1;
	UART_STARTRX_TASK = 1;

	UART_TXD = 's';
	while (!UART_TXDRDY_EVENT);
	UART_TXDRDY_EVENT = 0;

	while (1)
	{

		while (!UART_RXDRDY_EVENT);
		UART_TXD = UART_RXD + 1;
		UART_RXDRDY_EVENT = 0;
		while (!UART_TXDRDY_EVENT);
		UART_TXDRDY_EVENT = 0;
	}
}
