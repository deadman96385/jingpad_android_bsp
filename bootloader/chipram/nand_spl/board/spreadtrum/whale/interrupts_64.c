/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <linux/compiler.h>

/*
 * do_bad_sync handles the impossible case in the Synchronous Abort vector.
 */
void loop()
{
	while(1);
}

