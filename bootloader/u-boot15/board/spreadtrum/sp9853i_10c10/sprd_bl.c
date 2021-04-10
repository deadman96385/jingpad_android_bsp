#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include "../../../drivers/video/sprdfb/sprdfb.h"
#include "../../../drivers/video/sprdfb/sprdfb_panel.h"

extern struct sprdfb_device *dev_cabc_bl;
void set_backlight(uint32_t brightness)
{
	if(0 == brightness)
	{
		//lcd cabc backlight disabled in lcd init already ,
		//and if lcd has not initialized,brightness can not be set;
	}
	else
	{
		//cabc backlight brightness setting must be after lcd initialized
		if(NULL != dev_cabc_bl->panel->ops->panel_set_brightness){
			dev_cabc_bl->panel->ops->panel_set_brightness(dev_cabc_bl->panel,brightness);
		}
	}
	printk("lcd cabc backlight brightness==%d\n",brightness);
	return;
}
