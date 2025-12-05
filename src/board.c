/*-
 * Copyright (c) 2025 Ruslan Bukin <br@bsdpad.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#include <sys/console.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/thread.h>

#include <machine/cpufunc.h>
#include <machine/cpuregs.h>

#include <dev/intc/intc.h>
#include <dev/uart/uart.h>

#include <arm/stm/stm32u3.h>
#include <arm/arm/nvic.h>

static struct stm32u3_rcc_softc rcc_sc;
static struct stm32l4_usart_softc usart_sc;
static struct stm32f4_timer_softc timer_sc;

struct stm32f4_gpio_softc gpio_sc;

static struct arm_nvic_softc nvic_sc;
static struct mdx_device dev_nvic = { .sc = &nvic_sc };

void
udelay(uint32_t usec)
{
	int i;

	/* TODO: implement me */

	for (i = 0; i < usec * 100; i++)
		;
}

static void
uart_putchar(int c, void *arg)
{
	struct stm32l4_usart_softc *sc;

	sc = arg;

	if (c == '\n')
		stm32l4_usart_putc(sc, '\r');

	stm32l4_usart_putc(sc, c);
}

static const struct stm32_gpio_pin uart_pins[] = {
	{ PORT_A,  9, MODE_ALT, 7, OT_PP, OS_H, FLOAT }, /* USART1_TX */
	{ PORT_A, 10, MODE_ALT, 7, OT_PP, OS_H, FLOAT }, /* USART1_RX */
	PINS_END
};

void
board_init(void)
{
	struct rcc_config cfg;

	bzero(&cfg, sizeof(struct rcc_config));
	cfg.ahb1enr1 = AHB1ENR1_SRAM1EN | AHB1ENR1_FLASHEN;
	cfg.ahb2enr1 = AHB2ENR1_SRAM2EN | AHB2ENR1_GPIOAEN;
	cfg.apb2enr = APB2ENR_USART1EN | APB2ENR_TIM1EN;

	/* RCC */
	stm32u3_rcc_init(&rcc_sc, RCC_BASE);
	stm32u3_rcc_setup(&rcc_sc, &cfg);

	/* GPIO */
	stm32f4_gpio_init(&gpio_sc, GPIO_BASE);
	pin_configure(&gpio_sc, uart_pins);

	/* UART */
	stm32l4_usart_init(&usart_sc, USART1_BASE, 12000000, 115200);
	mdx_console_register(uart_putchar, (void *)&usart_sc);

	/* TIMER */
	stm32f4_timer_init(&timer_sc, TIM1_BASE, 12000000);
	arm_nvic_init(&dev_nvic, NVIC_BASE);
	mdx_intc_setup(&dev_nvic, 44, stm32f4_timer_intr, &timer_sc);
	mdx_intc_enable(&dev_nvic, 44);

#if 0
	malloc_init();
	malloc_add_region((void *)0x20020000, 0x20000);
#endif
}
