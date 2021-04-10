#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include "../../../drivers/video/sprdfb/sprdfb.h"
#include "../../../drivers/video/sprdfb/sprdfb_panel.h"

extern struct sprdfb_device *dev_cabc_bl;

void set_backlight(uint32_t brightness)
{
	if((NULL !=  dev_cabc_bl) && (NULL != dev_cabc_bl->panel->ops->panel_set_brightness)){
		dev_cabc_bl->panel->ops->panel_set_brightness(dev_cabc_bl->panel,brightness);
	}
	printk("lcd cabc backlight brightness==%d\n",brightness);
	return;
}

