APP =		stm32u3

CROSS_COMPILE ?= arm-none-eabi-
export CROSS_COMPILE

CC =		${CROSS_COMPILE}gcc
LD =		${CROSS_COMPILE}ld
OBJCOPY =	${CROSS_COMPILE}objcopy

OSDIR =		mdepx

ADAPTER_SERIAL ?=	003D003C3234510133353533

all:
	python3 -B ${OSDIR}/tools/emitter.py -j mdepx.conf
	@${OBJCOPY} -O binary obj/${APP}.elf obj/${APP}.bin

readelf:
	${CROSS_COMPILE}readelf -a obj/${APP}.elf | less

objdump:
	${CROSS_COMPILE}objdump -d obj/${APP}.elf | less

clean:
	@rm -rf obj/*

flash:
	sudo /home/br/dev/openocd-stm32u3/src/openocd -s /home/br/dev/openocd-stm32u3/tcl -f interface/stlink.cfg -f target/stm32u3x.cfg -c 'adapter serial ${ADAPTER_SERIAL}' -c 'reset_config srst_only connect_assert_srst; program obj/${APP}.bin reset 0x08000000 exit'

openocd:
	sudo /home/br/dev/openocd-stm32u3/src/openocd -s /home/br/dev/openocd-stm32u3/tcl -f interface/stlink.cfg -f target/stm32u3x.cfg -c 'adapter serial ${ADAPTER_SERIAL}' -c 'reset_config srst_only connect_assert_srst'

include ${OSDIR}/mk/user.mk
