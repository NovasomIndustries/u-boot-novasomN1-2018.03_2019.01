/*
 * Board init file for Dragonboard 410C
 *
 * (C) Copyright 2015 Mateusz Kulikowski <mateusz.kulikowski@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <usb.h>
#include <asm/gpio.h>
#include <fdt_support.h>

DECLARE_GLOBAL_DATA_PTR;

/* pointer to the device tree ammended by the firmware */
extern void *fw_dtb;

void *board_fdt_blob_setup(void)
{
	if (fdt_magic(fw_dtb) != FDT_MAGIC) {
		printf("Firmware provided invalid dtb!\n");
		return NULL;
	}

	return fw_dtb;
}

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_1_SIZE;

	return 0;
}

int dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return 0;
}

int board_prepare_usb(enum usb_init_type type)
{
	static struct udevice *pmic_gpio;
	static struct gpio_desc hub_reset, usb_sel;
	int ret = 0, node;

	if (!pmic_gpio) {
		ret = uclass_get_device_by_name(UCLASS_GPIO,
						"pm8916_gpios@c000",
						&pmic_gpio);
		if (ret < 0) {
			printf("Failed to find pm8916_gpios@c000 node.\n");
			return ret;
		}
	}

	/* Try to request gpios needed to start usb host on dragonboard */
	if (!dm_gpio_is_valid(&hub_reset)) {
		node = fdt_subnode_offset(gd->fdt_blob,
					  dev_of_offset(pmic_gpio),
					  "usb_hub_reset_pm");
		if (node < 0) {
			printf("Failed to find usb_hub_reset_pm dt node.\n");
			return node;
		}
		ret = gpio_request_by_name_nodev(offset_to_ofnode(node),
						 "gpios", 0, &hub_reset, 0);
		if (ret < 0) {
			printf("Failed to request usb_hub_reset_pm gpio.\n");
			return ret;
		}
	}

	if (!dm_gpio_is_valid(&usb_sel)) {
		node = fdt_subnode_offset(gd->fdt_blob,
					  dev_of_offset(pmic_gpio),
					  "usb_sw_sel_pm");
		if (node < 0) {
			printf("Failed to find usb_sw_sel_pm dt node.\n");
			return 0;
		}
		ret = gpio_request_by_name_nodev(offset_to_ofnode(node),
						 "gpios", 0, &usb_sel, 0);
		if (ret < 0) {
			printf("Failed to request usb_sw_sel_pm gpio.\n");
			return ret;
		}
	}

	if (type == USB_INIT_HOST) {
		/* Start USB Hub */
		dm_gpio_set_dir_flags(&hub_reset,
				      GPIOD_IS_OUT | GPIOD_IS_OUT_ACTIVE);
		mdelay(100);
		/* Switch usb to host connectors */
		dm_gpio_set_dir_flags(&usb_sel,
				      GPIOD_IS_OUT | GPIOD_IS_OUT_ACTIVE);
		mdelay(100);
	} else { /* Device */
		/* Disable hub */
		dm_gpio_set_dir_flags(&hub_reset, GPIOD_IS_OUT);
		/* Switch back to device connector */
		dm_gpio_set_dir_flags(&usb_sel, GPIOD_IS_OUT);
	}

	return 0;
}

/* Check for vol- button - if pressed - stop autoboot */
int misc_init_r(void)
{
	struct udevice *pon;
	struct gpio_desc resin;
	int node, ret;

	ret = uclass_get_device_by_name(UCLASS_GPIO, "pm8916_pon@800", &pon);
	if (ret < 0) {
		printf("Failed to find PMIC pon node. Check device tree\n");
		return 0;
	}

	node = fdt_subnode_offset(gd->fdt_blob, dev_of_offset(pon),
				  "key_vol_down");
	if (node < 0) {
		printf("Failed to find key_vol_down node. Check device tree\n");
		return 0;
	}

	if (gpio_request_by_name_nodev(offset_to_ofnode(node), "gpios", 0,
				       &resin, 0)) {
		printf("Failed to request key_vol_down button.\n");
		return 0;
	}

	if (dm_gpio_get_value(&resin)) {
		env_set("bootdelay", "-1");
		printf("Power button pressed - dropping to console.\n");
	}

	return 0;
}

int board_init(void)
{
	return 0;
}

int ft_board_setup(void *blob, bd_t *bd)
{
	int offset, len, i;
	const char *mac;
	struct {
		const char *compatible;
		const char *property;
	} fix[] = {
		[0] = {
			/* update the kernel's dtb with wlan mac */
			.compatible = "qcom,wcnss-wlan",
			.property = "local-mac-address",
		},
		[1] = {
			/* update the kernel's dtb with bt mac */
			.compatible = "qcom,wcnss-bt",
			.property = "local-bd-address",
		},
	};

	for (i = 0; i < sizeof(fix) / sizeof(fix[0]); i++) {
		offset = fdt_node_offset_by_compatible(gd->fdt_blob, -1,
						       fix[i].compatible);
		if (offset < 0)
			continue;

		mac = fdt_getprop(gd->fdt_blob, offset, fix[i].property, &len);
		if (mac)
			do_fixup_by_compat(blob, fix[i].compatible,
					   fix[i].property, mac, ARP_HLEN, 1);
	}

	return 0;
}

void reset_cpu(ulong addr)
{
	psci_system_reset();
}