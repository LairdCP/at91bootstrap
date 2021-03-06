#include "arch/at91_pio.h"
#include "gpio.h"

/* notes on default configuration:
 * Outputs have both pull up and pull downs cleared
 * Inputs on PIO_DEFAULT get both PU and PD cleared
 * Valid values for ATTRIBUTES, used for inputs unless specified:
 * PIO_DEFAULT  (will clear PU and PD)
 * PIO_PULLUP
 * PIO_DEGLITCH
 * PIO_OPENDRAIN (OUTPUT)
 * PIO_PULLDOWN
 */
void hw_init_hook(void)
{
#if defined (CONFIG_SAMA5D3XEK)
	/* Setup WB50NBT custom GPIOs to match BB40 */
	const struct pio_desc gpios[] = {
		/*  {"NAME",        PIN NUMBER,     VALUE, ATTRIBUTES, TYPE },*/

		/* GPIOs
		 * The LED GPIO pins go to a header && through a buffer to LEDs,
		 *     active low to light LED
		 * BOOT1/BOOT2 are odd, go to header to short a PU to gnd
		 * GPIO_4, connects to CON37 and also direct-drives D10 through
		 *     a 1k to GND
		 * IRQ needs to NOT have a PU on it. There is an error on the
		 *     BB40 where it's pulled up to 1.8v.
		 */
		{"GPIO_5",	AT91C_PIN_PA(0),	0, PIO_DEFAULT, PIO_INPUT},  /* BOOT1, has pullup on BB40 */
		{"GPIO_6",	AT91C_PIN_PA(3),	0, PIO_DEFAULT, PIO_INPUT},  /* BOOT2, has pullup on BB40 */
		{"GPIO_3",	AT91C_PIN_PA(10),	0, PIO_PULLUP, PIO_INPUT},  /* GPIO2 */
		{"LED0",	AT91C_PIN_PA(12),	0, PIO_DEFAULT, PIO_OUTPUT},
		{"GPIO_4",	AT91C_PIN_PA(14),	0, PIO_DEFAULT, PIO_OUTPUT},  /* GPIO3 */
		{"STAT0",	AT91C_PIN_PA(22),	0, PIO_DEFAULT, PIO_OUTPUT},
		{"LED1",	AT91C_PIN_PA(24),	0, PIO_DEFAULT, PIO_OUTPUT},
		{"LED2",	AT91C_PIN_PA(26),	0, PIO_DEFAULT, PIO_OUTPUT},
		{"STAT1",	AT91C_PIN_PA(28),	0, PIO_DEFAULT, PIO_OUTPUT},
		{"IRQ",	        AT91C_PIN_PE(31),	0, PIO_DEFAULT,  PIO_INPUT},

		/* USB */
		{"VBUS_EN",	AT91C_PIN_PA(2),	0, PIO_DEFAULT, PIO_OUTPUT},
		{"OVER_CUR",	AT91C_PIN_PA(4),	0, PIO_DEFAULT, PIO_INPUT},  /* pullup on BB40 */
		{"VBUS_SENSE",	AT91C_PIN_PB(13),	0, PIO_PULLUP, PIO_INPUT},

		/* UART0 pins */
		{"UART0_DCD",	AT91C_PIN_PD(7),	0, PIO_DEFAULT, PIO_INPUT}, /* BB40 with a PU */
		{"UART0_RI",	AT91C_PIN_PD(8),	0, PIO_DEFAULT, PIO_INPUT}, /* BB40 with a PU */
		{"UART0_DSR",	AT91C_PIN_PD(11),	0, PIO_DEFAULT, PIO_INPUT}, /* BB40 with a PU */
		{"UART0_DTR",	AT91C_PIN_PD(13),	0, PIO_DEFAULT, PIO_OUTPUT},

		/* WiFi and BT SIP */
		{"WAKE_ON_WLAN",AT91C_PIN_PC(31),	0, PIO_DEFAULT, PIO_INPUT}, /* WB50 has a PU on this line */
		{"WLAN_PWD_L",	AT91C_PIN_PE(3),	0, PIO_DEFAULT, PIO_OUTPUT}, /* WB50 has a PU on this line, set in reset by default */
		{"BT_PWD_L",	AT91C_PIN_PE(5),	0, PIO_DEFAULT, PIO_OUTPUT}, /* Leave in reset by default */
		{"BT_WAKEUP_HOST",AT91C_PIN_PE(10),	0, PIO_DEFAULT, PIO_OUTPUT}, /* WB50 schematic in error. This is an output, and it should always stay low */
		{"WIFI_GPIO10",	AT91C_PIN_PE(13),	0, PIO_DEFAULT, PIO_INPUT}, /* WB50 has PU on this */

		{(char *)0,	0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#elif defined (CONFIG_AT91SAM9X5EK)
	/* Setup WB45NBT custom GPIOs */
	const struct pio_desc gpios[] = {
	/*  {"NAME",        PIN NUMBER,     VALUE, ATTRIBUTES, TYPE },*/
		{"CHIP_PWD_L",	AT91C_PIN_PA(28),	0, PIO_DEFAULT, PIO_OUTPUT},
		{"VBUS_SENSE",	AT91C_PIN_PB(11),	0, PIO_DEFAULT, PIO_INPUT},
		{"VBUS_EN",	    AT91C_PIN_PB(12),	0, PIO_DEFAULT, PIO_OUTPUT},
		{"IRQ",	        AT91C_PIN_PB(18),	0, PIO_PULLUP,  PIO_INPUT},
		{(char *)0,	0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#else
#error CONFIG_USER_HW_INIT needs to be defined for your board.
#endif

	pio_configure(gpios);
}
