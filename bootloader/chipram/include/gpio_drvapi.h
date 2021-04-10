/******************************************************************************
 ** File Name:      gpio_drvapi.h                                                *
 ** Author:         Xueliang.Wang                                             *
 ** DATE:           03/18/2003                                                *
 ** Copyright:      2003 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic operation interfaces of       *
 **                 GPIO device.                                              *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 03/18/2003     Xueliang.Wang     Create.                                  *
 ** 09/05/2003     Zhemin.Lin       Added functions for SM5100B EVB1.0        *
 ** 22/11/2004     Benjamin.Wang    Modified according CR16760              *
 ** 08/01/2008     Yiyue.He         modified the code for more generic adptation
 ******************************************************************************/

#ifndef _GPIO_DRVAPI_H_
#define _GPIO_DRVAPI_H_

/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

typedef enum GPIO_INT_tag
{
    GPIO_INT_DISABLE = 0,   // Disable the relative gpio interrupt.
    GPIO_INT_LEVEL_HIGH,    // detect high level.
    GPIO_INT_LEVEL_LOW,     // detect low level.
    GPIO_INT_EDGES_BOTH,    // detect the rising edges and falling edges.
    GPIO_INT_EDGES_RISING,  // detect the rising edges.
    GPIO_INT_EDGES_FALLING  // detect the falling edges.
} GPIO_INT_TYPE;


#define GPIO_DEFAULT_SHAKING_TIME   50

void sprd_gpio_init(void);
int sprd_gpio_request(unsigned int offset);
void sprd_gpio_free(unsigned int offset);
void sprd_gpio_set(unsigned int offset, int value);
int sprd_gpio_get(unsigned int offset);
int sprd_gpio_direction_input(unsigned int offset);
int sprd_gpio_direction_output(unsigned int offset, int value);

#ifdef __cplusplus
}
#endif

#endif  // _GPIO_DRVAPI_H_

// End of gpio_drvapi.h
