/*
 * Copyright 2013 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * C29XPCIE board configuration file
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef CONFIG_SPIFLASH
#define CONFIG_RAMBOOT_SPIFLASH
#define CONFIG_RESET_VECTOR_ADDRESS	0x110bfffc
#endif

#ifdef CONFIG_NAND
#ifdef CONFIG_TPL_BUILD
#define CONFIG_SPL_NAND_BOOT
#define CONFIG_SPL_FLUSH_IMAGE
#define CONFIG_SPL_NAND_INIT
#define CONFIG_TPL_DRIVERS_MISC_SUPPORT
#define CONFIG_SPL_COMMON_INIT_DDR
#define CONFIG_SPL_MAX_SIZE		(128 << 10)
#define CONFIG_SPL_TEXT_BASE		0xf8f81000
#define CONFIG_SYS_MPC85XX_NO_RESETVEC
#define CONFIG_SYS_NAND_U_BOOT_SIZE	(832 << 10)
#define CONFIG_SYS_NAND_U_BOOT_DST	(0x11000000)
#define CONFIG_SYS_NAND_U_BOOT_START	(0x11000000)
#define CONFIG_SYS_NAND_U_BOOT_OFFS	((128 + 128) << 10)
#elif defined(CONFIG_SPL_BUILD)
#define CONFIG_SPL_INIT_MINIMAL
#define CONFIG_SPL_NAND_MINIMAL
#define CONFIG_SPL_FLUSH_IMAGE
#define CONFIG_SPL_TEXT_BASE		0xff800000
#define CONFIG_SPL_MAX_SIZE		8192
#define CONFIG_SYS_NAND_U_BOOT_SIZE	(128 << 10)
#define CONFIG_SYS_NAND_U_BOOT_DST	0xf8f80000
#define CONFIG_SYS_NAND_U_BOOT_START	0xf8f80000
#define CONFIG_SYS_NAND_U_BOOT_OFFS	(128 << 10)
#endif
#define CONFIG_SPL_PAD_TO		0x20000
#define CONFIG_TPL_PAD_TO		0x20000
#define CONFIG_SPL_TARGET		"u-boot-with-spl.bin"
#define CONFIG_SYS_LDSCRIPT	"arch/powerpc/cpu/mpc85xx/u-boot-nand.lds"
#endif

#ifndef CONFIG_RESET_VECTOR_ADDRESS
#define CONFIG_RESET_VECTOR_ADDRESS	0xeffffffc
#endif

#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SPL_TEXT_BASE
#else
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_TEXT_BASE	/* start of monitor */
#endif

#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_CCSR_DO_NOT_RELOCATE
#endif

/* High Level Configuration Options */
#define CONFIG_SYS_HAS_SERDES		/* common SERDES init code */

#ifdef CONFIG_PCI
#define CONFIG_PCIE1			/* PCIE controller 1 (slot 1) */
#define CONFIG_FSL_PCI_INIT		/* Use common FSL init code */
#define CONFIG_PCI_INDIRECT_BRIDGE
#define CONFIG_FSL_PCIE_RESET		/* need PCIe reset errata */
#define CONFIG_SYS_PCI_64BIT		/* enable 64-bit PCI resources */

/*
 * PCI Windows
 * Memory space is mapped 1-1, but I/O space must start from 0.
 */
/* controller 1, Slot 1, tgtid 1, Base address a000 */
#define CONFIG_SYS_PCIE1_NAME		"Slot 1"
#define CONFIG_SYS_PCIE1_MEM_VIRT	0x80000000
#define CONFIG_SYS_PCIE1_MEM_BUS	0x80000000
#define CONFIG_SYS_PCIE1_MEM_PHYS	0xc00000000ull
#define CONFIG_SYS_PCIE1_MEM_SIZE	0x10000000	/* 256M */
#define CONFIG_SYS_PCIE1_IO_VIRT	0xffc00000
#define CONFIG_SYS_PCIE1_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE1_IO_SIZE	0x00010000	/* 64k */
#define CONFIG_SYS_PCIE1_IO_PHYS	0xfffc00000ull

#define CONFIG_PCI_SCAN_SHOW		/* show pci devices on startup */
#endif

#define CONFIG_TSEC_ENET
#define CONFIG_ENV_OVERWRITE

#define CONFIG_DDR_CLK_FREQ	100000000
#define CONFIG_SYS_CLK_FREQ	66666666

#define CONFIG_HWCONFIG

/*
 * These can be toggled for performance analysis, otherwise use default.
 */
#define CONFIG_L2_CACHE			/* toggle L2 cache */
#define CONFIG_BTB			/* toggle branch predition */


#define CONFIG_ENABLE_36BIT_PHYS

#define CONFIG_ADDR_MAP			1
#define CONFIG_SYS_NUM_ADDR_MAP		16	/* number of TLB1 entries */

#define CONFIG_SYS_MEMTEST_START	0x00200000
#define CONFIG_SYS_MEMTEST_END		0x00400000

/* DDR Setup */
#define CONFIG_DDR_SPD
#define CONFIG_SYS_SPD_BUS_NUM		0
#define SPD_EEPROM_ADDRESS		0x50
#define CONFIG_SYS_DDR_RAW_TIMING

/* DDR ECC Setup*/
#define CONFIG_DDR_ECC
#define CONFIG_MEM_INIT_VALUE		0xDeadBeef
#define CONFIG_ECC_INIT_VIA_DDRCONTROLLER

#define CONFIG_SYS_SDRAM_SIZE		512
#define CONFIG_SYS_DDR_SDRAM_BASE	0x00000000
#define CONFIG_SYS_SDRAM_BASE		CONFIG_SYS_DDR_SDRAM_BASE

#define CONFIG_DIMM_SLOTS_PER_CTLR	1
#define CONFIG_CHIP_SELECTS_PER_CTRL	1

#define CONFIG_SYS_CCSRBAR		0xffe00000
#define CONFIG_SYS_CCSRBAR_PHYS_LOW	CONFIG_SYS_CCSRBAR

/* Platform SRAM setting  */
#define CONFIG_SYS_PLATFORM_SRAM_BASE	0xffb00000
#define CONFIG_SYS_PLATFORM_SRAM_BASE_PHYS \
			(0xf00000000ull | CONFIG_SYS_PLATFORM_SRAM_BASE)
#define CONFIG_SYS_PLATFORM_SRAM_SIZE	(512 << 10)

/*
 * IFC Definitions
 */
/* NOR Flash on IFC */
#define CONFIG_SYS_FLASH_BASE		0xec000000
#define CONFIG_SYS_MAX_FLASH_SECT	512	/* 64M */

#define CONFIG_SYS_FLASH_BASE_PHYS	(0xf00000000ull | CONFIG_SYS_FLASH_BASE)

#define CONFIG_SYS_FLASH_BANKS_LIST	{ CONFIG_SYS_FLASH_BASE_PHYS }
#define CONFIG_SYS_MAX_FLASH_BANKS	1

#define CONFIG_SYS_FLASH_QUIET_TEST
#define CONFIG_FLASH_SHOW_PROGRESS	45
#define CONFIG_SYS_FLASH_ERASE_TOUT	60000	/* in ms */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* in ms */

/* 16Bit NOR Flash - S29GL512S10TFI01 */
#define CONFIG_SYS_NOR_CSPR	(CSPR_PHYS_ADDR(CONFIG_SYS_FLASH_BASE_PHYS) | \
				CSPR_PORT_SIZE_16 | \
				CSPR_MSEL_NOR | \
				CSPR_V)
#define CONFIG_SYS_NOR_AMASK	IFC_AMASK(64*1024*1024)
#define CONFIG_SYS_NOR_CSOR	CSOR_NOR_ADM_SHIFT(4)

#define CONFIG_SYS_NOR_FTIM0	(FTIM0_NOR_TACSE(0x4) | \
				FTIM0_NOR_TEADC(0x5) | \
				FTIM0_NOR_TEAHC(0x5))
#define CONFIG_SYS_NOR_FTIM1	(FTIM1_NOR_TACO(0x35) | \
				FTIM1_NOR_TRAD_NOR(0x1A) |\
				FTIM1_NOR_TSEQRAD_NOR(0x13))
#define CONFIG_SYS_NOR_FTIM2	(FTIM2_NOR_TCS(0x4) | \
				FTIM2_NOR_TCH(0x4) | \
				FTIM2_NOR_TWPH(0x0E) | \
				FTIM2_NOR_TWP(0x1c))
#define CONFIG_SYS_NOR_FTIM3	0x0

/* CFI for NOR Flash */
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE

/* NAND Flash on IFC */
#define CONFIG_NAND_FSL_IFC
#define CONFIG_SYS_NAND_BASE		0xff800000
#define CONFIG_SYS_NAND_BASE_PHYS	0xfff800000ull

#define CONFIG_SYS_NAND_BASE_LIST	{ CONFIG_SYS_NAND_BASE }

#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BLOCK_SIZE	(1024 * 1024)

/* 8Bit NAND Flash - K9F1G08U0B */
#define CONFIG_SYS_NAND_CSPR	(CSPR_PHYS_ADDR(CONFIG_SYS_NAND_BASE_PHYS) \
				| CSPR_PORT_SIZE_8 \
				| CSPR_MSEL_NAND \
				| CSPR_V)
#define CONFIG_SYS_NAND_AMASK	IFC_AMASK(64*1024)
#define CONFIG_SYS_NAND_OOBSIZE	0x00000280	/* 640b */
#define CONFIG_SYS_NAND_CSOR	(CSOR_NAND_ECC_ENC_EN	/* ECC on encode */ \
				| CSOR_NAND_ECC_DEC_EN	/* ECC on decode */ \
				| CSOR_NAND_ECC_MODE_4	/* 4-bit ECC */ \
				| CSOR_NAND_RAL_3	/* RAL = 3 Bytes */ \
				| CSOR_NAND_PGS_8K	/* Page Size = 8K */ \
				| CSOR_NAND_SPRZ_CSOR_EXT /*oob in csor_ext*/\
				| CSOR_NAND_PB(128))	/*128 Pages Per Block*/
#define CONFIG_SYS_NAND_FTIM0	(FTIM0_NAND_TCCST(0x01) | \
				FTIM0_NAND_TWP(0x0c)   | \
				FTIM0_NAND_TWCHT(0x08) | \
				FTIM0_NAND_TWH(0x06))
#define CONFIG_SYS_NAND_FTIM1	(FTIM1_NAND_TADLE(0x28) | \
				FTIM1_NAND_TWBE(0x1d)  | \
				FTIM1_NAND_TRR(0x08)   | \
				FTIM1_NAND_TRP(0x0c))
#define CONFIG_SYS_NAND_FTIM2	(FTIM2_NAND_TRAD(0x0c) | \
				FTIM2_NAND_TREH(0x0a) | \
				FTIM2_NAND_TWHRE(0x18))
#define CONFIG_SYS_NAND_FTIM3	(FTIM3_NAND_TWW(0x04))

#define CONFIG_SYS_NAND_DDR_LAW		11

/* Set up IFC registers for boot location NOR/NAND */
#ifdef CONFIG_NAND
#define CONFIG_SYS_CSPR0		CONFIG_SYS_NAND_CSPR
#define CONFIG_SYS_AMASK0		CONFIG_SYS_NAND_AMASK
#define CONFIG_SYS_CSOR0		CONFIG_SYS_NAND_CSOR
#define CONFIG_SYS_CSOR0_EXT		CONFIG_SYS_NAND_OOBSIZE
#define CONFIG_SYS_CS0_FTIM0		CONFIG_SYS_NAND_FTIM0
#define CONFIG_SYS_CS0_FTIM1		CONFIG_SYS_NAND_FTIM1
#define CONFIG_SYS_CS0_FTIM2		CONFIG_SYS_NAND_FTIM2
#define CONFIG_SYS_CS0_FTIM3		CONFIG_SYS_NAND_FTIM3
#define CONFIG_SYS_CSPR1		CONFIG_SYS_NOR_CSPR
#define CONFIG_SYS_AMASK1		CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR1		CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS1_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS1_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS1_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS1_FTIM3		CONFIG_SYS_NOR_FTIM3
#else
#define CONFIG_SYS_CSPR0		CONFIG_SYS_NOR_CSPR
#define CONFIG_SYS_AMASK0		CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR0		CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS0_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS0_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS0_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS0_FTIM3		CONFIG_SYS_NOR_FTIM3
#define CONFIG_SYS_CSPR1		CONFIG_SYS_NAND_CSPR
#define CONFIG_SYS_AMASK1		CONFIG_SYS_NAND_AMASK
#define CONFIG_SYS_CSOR1		CONFIG_SYS_NAND_CSOR
#define CONFIG_SYS_CSOR1_EXT		CONFIG_SYS_NAND_OOBSIZE
#define CONFIG_SYS_CS1_FTIM0		CONFIG_SYS_NAND_FTIM0
#define CONFIG_SYS_CS1_FTIM1		CONFIG_SYS_NAND_FTIM1
#define CONFIG_SYS_CS1_FTIM2		CONFIG_SYS_NAND_FTIM2
#define CONFIG_SYS_CS1_FTIM3		CONFIG_SYS_NAND_FTIM3
#endif

/* CPLD on IFC, selected by CS2 */
#define CONFIG_SYS_CPLD_BASE		0xffdf0000
#define CONFIG_SYS_CPLD_BASE_PHYS	(0xf00000000ull \
					| CONFIG_SYS_CPLD_BASE)

#define CONFIG_SYS_CSPR2	(CSPR_PHYS_ADDR(CONFIG_SYS_CPLD_BASE_PHYS) \
				| CSPR_PORT_SIZE_8 \
				| CSPR_MSEL_GPCM \
				| CSPR_V)
#define CONFIG_SYS_AMASK2	IFC_AMASK(64*1024)
#define CONFIG_SYS_CSOR2	0x0
/* CPLD Timing parameters for IFC CS2 */
#define CONFIG_SYS_CS2_FTIM0	(FTIM0_GPCM_TACSE(0x0e) | \
				FTIM0_GPCM_TEADC(0x0e) | \
				FTIM0_GPCM_TEAHC(0x0e))
#define CONFIG_SYS_CS2_FTIM1	(FTIM1_GPCM_TACO(0x0e) | \
				FTIM1_GPCM_TRAD(0x1f))
#define CONFIG_SYS_CS2_FTIM2	(FTIM2_GPCM_TCS(0x0e) | \
				FTIM2_GPCM_TCH(0x8) | \
				FTIM2_GPCM_TWP(0x1f))
#define CONFIG_SYS_CS2_FTIM3	0x0

#if defined(CONFIG_RAMBOOT_SPIFLASH)
#define CONFIG_SYS_RAMBOOT
#define CONFIG_SYS_EXTRA_ENV_RELOC
#endif

#define CONFIG_BOARD_EARLY_INIT_R

#define CONFIG_SYS_INIT_RAM_LOCK
#define CONFIG_SYS_INIT_RAM_ADDR	0xffd00000
#define CONFIG_SYS_INIT_RAM_SIZE	0x00004000

#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE \
						- GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_MONITOR_LEN		(768 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(2 * 1024 * 1024)

/*
 * Config the L2 Cache as L2 SRAM
 */
#if defined(CONFIG_SPL_BUILD)
#if defined(CONFIG_SDCARD) || defined(CONFIG_SPIFLASH)
#define CONFIG_SYS_INIT_L2_ADDR		0xf8f80000
#define CONFIG_SYS_INIT_L2_ADDR_PHYS	CONFIG_SYS_INIT_L2_ADDR
#define CONFIG_SYS_L2_SIZE		(256 << 10)
#define CONFIG_SYS_INIT_L2_END	(CONFIG_SYS_INIT_L2_ADDR + CONFIG_SYS_L2_SIZE)
#define CONFIG_SPL_RELOC_TEXT_BASE	0xf8f81000
#define CONFIG_SPL_RELOC_STACK		(CONFIG_SYS_INIT_L2_ADDR + 128 * 1024)
#define CONFIG_SPL_RELOC_STACK_SIZE	(32 << 10)
#define CONFIG_SPL_RELOC_MALLOC_ADDR	(CONFIG_SYS_INIT_L2_ADDR + 160 * 1024)
#define CONFIG_SPL_RELOC_MALLOC_SIZE	(96 << 10)
#define CONFIG_SPL_GD_ADDR		(CONFIG_SYS_INIT_L2_ADDR + 112 * 1024)
#elif defined(CONFIG_NAND)
#ifdef CONFIG_TPL_BUILD
#define CONFIG_SYS_INIT_L2_ADDR		0xf8f80000
#define CONFIG_SYS_INIT_L2_ADDR_PHYS	CONFIG_SYS_INIT_L2_ADDR
#define CONFIG_SYS_L2_SIZE		(256 << 10)
#define CONFIG_SYS_INIT_L2_END	(CONFIG_SYS_INIT_L2_ADDR + CONFIG_SYS_L2_SIZE)
#define CONFIG_SPL_RELOC_TEXT_BASE	0xf8f81000
#define CONFIG_SPL_RELOC_STACK		(CONFIG_SYS_INIT_L2_ADDR + 192 * 1024)
#define CONFIG_SPL_RELOC_MALLOC_ADDR	(CONFIG_SYS_INIT_L2_ADDR + 208 * 1024)
#define CONFIG_SPL_RELOC_MALLOC_SIZE	(48 << 10)
#define CONFIG_SPL_GD_ADDR		(CONFIG_SYS_INIT_L2_ADDR + 176 * 1024)
#else
#define CONFIG_SYS_INIT_L2_ADDR		0xf8f80000
#define CONFIG_SYS_INIT_L2_ADDR_PHYS	CONFIG_SYS_INIT_L2_ADDR
#define CONFIG_SYS_L2_SIZE		(256 << 10)
#define CONFIG_SYS_INIT_L2_END	(CONFIG_SYS_INIT_L2_ADDR + CONFIG_SYS_L2_SIZE)
#define CONFIG_SPL_RELOC_TEXT_BASE	(CONFIG_SYS_INIT_L2_END - 0x3000)
#define CONFIG_SPL_RELOC_STACK		((CONFIG_SYS_INIT_L2_END - 1) & ~0xF)
#endif
#endif
#endif

/* Serial Port */
#define CONFIG_CONS_INDEX	1
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	1
#define CONFIG_SYS_NS16550_CLK		get_bus_freq(0)

#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_INIT_MINIMAL)
#define CONFIG_NS16550_MIN_FUNCTIONS
#endif

#define CONFIG_SYS_BAUDRATE_TABLE	\
	{300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200}

#define CONFIG_SYS_NS16550_COM1	(CONFIG_SYS_CCSRBAR+0x4500)
#define CONFIG_SYS_NS16550_COM2	(CONFIG_SYS_CCSRBAR+0x4600)

#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_FSL
#define CONFIG_SYS_FSL_I2C_SPEED	400000
#define CONFIG_SYS_FSL_I2C2_SPEED	400000
#define CONFIG_SYS_FSL_I2C_SLAVE	0x7F
#define CONFIG_SYS_FSL_I2C2_SLAVE	0x7F
#define CONFIG_SYS_FSL_I2C_OFFSET	0x3000
#define CONFIG_SYS_FSL_I2C2_OFFSET	0x3100

/* I2C EEPROM */
/* enable read and write access to EEPROM */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 2
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS 3
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS 5

/* eSPI - Enhanced SPI */
#define CONFIG_SF_DEFAULT_SPEED		10000000
#define CONFIG_SF_DEFAULT_MODE		SPI_MODE_0

#ifdef CONFIG_TSEC_ENET
#define CONFIG_MII			/* MII PHY management */
#define CONFIG_MII_DEFAULT_TSEC	1	/* Allow unregistered phys */
#define CONFIG_TSEC1		1
#define CONFIG_TSEC1_NAME	"eTSEC1"
#define CONFIG_TSEC2		1
#define CONFIG_TSEC2_NAME	"eTSEC2"

/* Default mode is RGMII mode */
#define TSEC1_PHY_ADDR		0
#define TSEC2_PHY_ADDR		2

#define TSEC1_FLAGS		(TSEC_GIGABIT | TSEC_REDUCED)
#define TSEC2_FLAGS		(TSEC_GIGABIT | TSEC_REDUCED)

#define CONFIG_ETHPRIME		"eTSEC1"
#endif	/* CONFIG_TSEC_ENET */

/*
 * Environment
 */
#if defined(CONFIG_SYS_RAMBOOT)
#if defined(CONFIG_RAMBOOT_SPIFLASH)
#define CONFIG_ENV_SPI_BUS	0
#define CONFIG_ENV_SPI_CS	0
#define CONFIG_ENV_SPI_MAX_HZ	10000000
#define CONFIG_ENV_SPI_MODE	0
#define CONFIG_ENV_OFFSET	0x100000	/* 1MB */
#define CONFIG_ENV_SECT_SIZE	0x10000
#define CONFIG_ENV_SIZE		0x2000
#endif
#elif defined(CONFIG_NAND)
#ifdef CONFIG_TPL_BUILD
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_ENV_ADDR		(CONFIG_SYS_INIT_L2_ADDR + (160 << 10))
#else
#define CONFIG_ENV_SIZE		CONFIG_SYS_NAND_BLOCK_SIZE
#define CONFIG_ENV_RANGE	CONFIG_ENV_SIZE
#endif
#define CONFIG_ENV_OFFSET	CONFIG_SYS_NAND_BLOCK_SIZE
#else
#define CONFIG_ENV_ADDR	(CONFIG_SYS_MONITOR_BASE - CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_ENV_SECT_SIZE	0x20000
#endif

#define CONFIG_LOADS_ECHO
#define CONFIG_SYS_LOADS_BAUD_CHANGE

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LOAD_ADDR	0x2000000	/* default load address */

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 64 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CONFIG_SYS_BOOTMAPSZ	(64 << 20) /* Initial Memory map for Linux */
#define CONFIG_SYS_BOOTM_LEN	(64 << 20) /* Increase max gunzip size */

/*
 * Environment Configuration
 */

#ifdef CONFIG_TSEC_ENET
#define CONFIG_HAS_ETH0
#define CONFIG_HAS_ETH1
#endif

#define CONFIG_ROOTPATH		"/opt/nfsroot"
#define CONFIG_BOOTFILE		"uImage"
#define CONFIG_UBOOTPATH	u-boot.bin/* U-Boot image on TFTP server */

/* default location for tftp and bootm */
#define CONFIG_LOADADDR		1000000

#define CONFIG_DEF_HWCONFIG	fsl_ddr:ecc=on

#define	CONFIG_EXTRA_ENV_SETTINGS				\
	"initrd_high=0xffffffff\0"				\
	"hwconfig=" __stringify(CONFIG_DEF_HWCONFIG)  "\0"	\
	"netdev=eth0\0"						\
	"uboot=" __stringify(CONFIG_UBOOTPATH) "\0"		\
	"loadaddr=1000000\0"				\
	"consoledev=ttyS0\0"				\
	"ramdiskaddr=2000000\0"				\
	"ramdiskfile=rootfs.ext2.gz.uboot\0"		\
	"fdtaddr=1e00000\0"				\
	"fdtfile=name/of/device-tree.dtb\0"			\
	"othbootargs=ramdisk_size=600000\0"		\

#define CONFIG_RAMBOOTCOMMAND			\
	"setenv bootargs root=/dev/ram rw "	\
	"console=$consoledev,$baudrate $othbootargs; "	\
	"tftp $ramdiskaddr $ramdiskfile;"	\
	"tftp $loadaddr $bootfile;"		\
	"tftp $fdtaddr $fdtfile;"		\
	"bootm $loadaddr $ramdiskaddr $fdtaddr"

#define CONFIG_BOOTCOMMAND CONFIG_RAMBOOTCOMMAND

#include <asm/fsl_secure_boot.h>

#endif	/* __CONFIG_H */