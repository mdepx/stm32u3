#ifndef _SRC_TUSB_CONFIG_H_
#define _SRC_TUSB_CONFIG_H_

#define	CFG_TUSB_MCU		OPT_MCU_STM32U3
#define	CFG_TUSB_OS		OPT_OS_CUSTOM
#define	CFG_TUSB_DEBUG		10

/* Device stack. */
#define CFG_TUD_ENABLED		1
#define CFG_TUD_CDC		0
#define CFG_TUD_MSC		0
#define CFG_TUD_HID		1
#define CFG_TUD_MIDI		0
#define CFG_TUD_VENDOR		0

#define	BOARD_TUD_RHPORT	0

#endif /* _SRC_TUSB_CONFIG_H_ */
