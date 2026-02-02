/*-
 * Copyright (c) 2025-2026 Ruslan Bukin <br@bsdpad.com>
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
#include <sys/systm.h>
#include <sys/thread.h>
#include <sys/spinlock.h>

#include <arm/stm/stm32u3.h>

#include <dev/i2c/i2c.h>

#include <lib/tinyusb/src/tusb.h>
#include <lib/tinyusb/src/class/hid/hid_device.h>
#include <lib/tinyusb/src/common/tusb_fifo.h>

extern struct stm32f4_gpio_softc gpio_sc;

mdx_sem_t buffer_count;

#define	dprintf(fmt, ...)

void
tud_hid_set_report_cb(uint8_t itf, uint8_t report_id,
    hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{

	dprintf("%s\n", __func__);

	/* echo back anything we received from host */
	tud_hid_report(0, buffer, bufsize);
}

uint16_t
tud_hid_get_report_cb(uint8_t itf, uint8_t report_id,
    hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{

	dprintf("%s\n", __func__);

	return (0);
}

static void
tud_thread(void *arg)
{

	while (1)
		tud_task(); /* tinyusb device task */
}

int
main(void)
{
	struct thread *td;
	tusb_rhport_init_t dev_init = {
		.role = TUSB_ROLE_DEVICE,
		.speed = TUSB_SPEED_AUTO
	};

	tusb_init(BOARD_TUD_RHPORT, &dev_init);

	mdx_sem_init(&buffer_count, 0);

	td = mdx_thread_create("tud", 1, 10000, 8192, tud_thread, NULL);
	if (td == NULL)
		panic("cant create thread");
	mdx_sched_add(td);

	while (1) {
		printf("%s: Hello World from u3\n", __func__);
		mdx_usleep(500000);
		mdx_usleep(500000);
	}

	return (0);
}
