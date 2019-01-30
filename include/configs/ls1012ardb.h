/*
 * Copyright 2016 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __LS1012ARDB_H__
#define __LS1012ARDB_H__

#include "ls1012a_common.h"

/* DDR */
#define CONFIG_DIMM_SLOTS_PER_CTLR	1
#define CONFIG_CHIP_SELECTS_PER_CTRL	1
#define CONFIG_NR_DRAM_BANKS		2
#define CONFIG_SYS_SDRAM_SIZE		0x40000000
#define CONFIG_CMD_MEMINFO
#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		0x9fffffff


/*
 * I2C IO expander
 */

#define I2C_MUX_IO_ADDR		0x24
#define I2C_MUX_IO2_ADDR	0x25
#define I2C_MUX_IO_0		0
#define I2C_MUX_IO_1		1
#define SW_BOOT_MASK		0x03
#define SW_BOOT_EMU		0x02
#define SW_BOOT_BANK1		0x00
#define SW_BOOT_BANK2		0x01
#define SW_REV_MASK		0xF8
#define SW_REV_A		0xF8
#define SW_REV_B		0xF0
#define SW_REV_C		0xE8
#define SW_REV_C1		0xE0
#define SW_REV_C2		0xD8
#define SW_REV_D		0xD0
#define SW_REV_E		0xC8
#define __PHY_MASK		0xF9
#define __PHY_ETH2_MASK		0xFB
#define __PHY_ETH1_MASK		0xFD

/*  MMC  */
#ifdef CONFIG_MMC
#define CONFIG_FSL_ESDHC
#define CONFIG_SYS_FSL_MMC_HAS_CAPBLT_VS33
#endif


#define CONFIG_PCIE1		/* PCIE controller 1 */

#define CONFIG_PCI_SCAN_SHOW

#define CONFIG_CMD_MEMINFO
#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		0x9fffffff

#undef CONFIG_BOOTDELAY
#define CONFIG_BOOTDELAY                2
#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS		\
	"verify=no\0"                           \
        "fdt_high=0xffffffffffffffff\0"         \
        "initrd_high=0xffffffffffffffff\0"      \
        "kernel_addr_r=0x80000000\0"            \
        "fdt_addr_r=0x8ef00000\0"               \
        "env_addr_r=0x8ff00000\0"               \
        "load_addr_r=0x90000000\0"              \
        "mmcdev=0\0"                            \
        "mmcpart=1\0"                           \
        "console=ttyS0,115200\0"                \
        "image=Image\0"                         \
        "initrd=uInitrd\0"                      \
        "fdt_file=NOVAsom_N1.dtb\0"             \
        "bootenv_file=NOVAsomParams\0"               \
        "ramroot=/dev/ram rw\0"                 \
        "mmcloadimage=fatload mmc ${mmcdev}:${mmcpart} ${kernel_addr_r} ${image}\0"                             \
        "mmcloadinitrd=fatload mmc ${mmcdev}:${mmcpart} ${load_addr_r} ${initrd}\0"                             \
        "mmcloadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr_r} ${fdt_file}\0"                               \
        "mmcloadbootenv=fatload mmc ${mmcdev}:${mmcpart}  ${env_addr_r} ${bootenv_file}\0"                      \
        "importbootenv=echo Importing environment ...; env import -t ${env_addr_r} ${filesize}\0"                 \
        "boardargs=setenv bootargs console=${console} root=${ramroot} ramdisk_size=64000 earlycon=uart8250,mmio,0x21c0500 lpj=250000;\0"          \
        "board_boot=run boardargs; booti ${kernel_addr_r} ${load_addr_r} ${fdt_addr_r} \0"


#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev}; "                           \
        "if run mmcloadbootenv; then "                  \
                "echo Loaded environment ${bootenv};"   \
                "run importbootenv;"                    \
                "run uenvcmd;"                          \
        "fi;"                                           \
        "if run mmcloadimage; then "                    \
                "if run mmcloadfdt; then "              \
                        "if run mmcloadinitrd; then "   \
                                "run board_boot; "      \
                        "fi; "                          \
                "fi; "                                  \
        "fi; "


#include <asm/fsl_secure_boot.h>

#endif /* __LS1012ARDB_H__ */
