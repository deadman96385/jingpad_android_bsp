/*  sci_img.h - SCI image function declaration.
 *
 *  Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 *  History:
 *  2017-3-15 Zhang Ziyi
 *  Initial version.
 */

#ifndef _SCI_IMG_H_
#define _SCI_IMG_H_

#include <stddef.h>

#include "loader_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*	get_modem_img_info - get the MODEM image parameters.
 *	@img_info: the image
 *	@secure_offset: the offset of the partition where to search for the
 *			MODEM image. The unit is byte.
 *	@is_sci: pointer to the variable to indicate whether the image is of
 *		 SCI format.
 *	@total_len: pointer to the variable to hold the length of the whole
 *		    MODEM image size in byte, excluding the secure header.
 *	@modem_exe_size: pointer to the variable to hold the MODEM
 *			 executable size.
 *
 *	Return Value:
 *		If the MODEM image is not SCI, return 0;
 *		if the MODEM image is SCI format, return the offset of the
 *		MODEM executable to the beginning of the SCI image (in unit
 *		of byte).
 *		if the function fails to read eMMC, return 0.
 */
unsigned get_modem_img_info(const boot_image_required_t* img_info,
			    unsigned secure_offset,
			    int* is_sci,
			    size_t* total_len,
			    size_t* modem_exe_size);

#ifdef __cplusplus
}
#endif

#endif  //!_SCI_IMG_H_
