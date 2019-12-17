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

	/* The buffer sizes must be a power of two each. */
	UART_TX_BUFFER_SIZE	= 16,
	UART_RX_BUFFER_SIZE	= 16,
};

/* The convention is that the receiver (rx) task is started on uart initialization,
 * and never stopped.
 *
 * The transmission (tx) task is stopped on uart initialization. It is started
 * when a first byte needs to be sent, and is stopped again when all of the
 * bytes in the transmit queue have been sent. 
 */
static struct
{
	volatile uint8_t	rxbuf[UART_RX_BUFFER_SIZE];
	unsigned		rxhead, rxtail;
       	volatile unsigned	rxlevel;

	volatile uint8_t	txbuf[UART_RX_BUFFER_SIZE];
	unsigned		txhead, txtail;
	volatile unsigned	txlevel;
}
uart_comm;


/* uart rx/tx interrupt handler */
void uart0_isr(void)
{
	/* determine source of interrupt */
	if (UART_RXDRDY_EVENT)
	{
		/* data received */
		unsigned data = UART_RXD;
		/* clear reception event */
		UART_RXDRDY_EVENT = 0;
		if (uart_comm.rxlevel == UART_RX_BUFFER_SIZE)
			/* reception buffer overflow - hang program */
			while (1);
		uart_comm.rxbuf[uart_comm.rxtail ++] = data;
		uart_comm.rxtail &=~ UART_RX_BUFFER_SIZE - 1;
	}

	if (UART_TXDRDY_EVENT)
	{
		/* Data trasmitted. If more data needs to be sent - send the next
		 * byte; otherwise - stop the transmission task. */
		/* clear transmission event */
		UART_TXDRDY_EVENT = 0;
		uart_comm.txhead ++;
		uart_comm.txhead &=~ UART_TX_BUFFER_SIZE - 1;
		uart_comm.level --;
		if (!uart_comm.txlevel)
			/* no more data to send - halt transmitter */
			UART_STARTTX_TASK = 0;
		else
			/* more data needs to be sent - transmit next byte */
			UART_TXD = uart_comm[uart_comm.txhead];
	}
}

void uart_transmit_char(uint8_t data)
{
}

unsigned uart_receive_char(void)
{
}

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

	/* enable the uart interrupt in the nvic */
	nvic_enable_irq(NVIC_UART0_IRQ);
	/* enable uart rx/tx interrupts in the uart peripheral */
	UART_INTENSET = UART_RXDRDY_INTERRUPT_BIT | UART_TXDRDY_INTERRUPT_BIT;
	UART_ENABLE = UART_PERIPHERAL_ENABLE;

	/* only start the reception task */
	UART_STARTRX_TASK = 1;

	while (1)
	{

		while (!UART_RXDRDY_EVENT);
		UART_TXD = UART_RXD + 1;
		UART_RXDRDY_EVENT = 0;
		while (!UART_TXDRDY_EVENT);
		UART_TXDRDY_EVENT = 0;
	}
}
