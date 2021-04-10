/******************************************************************************
 ** File Name:      adc_drvapi.h                                                  *
 ** Author:         hao.liu                                             *
 ** DATE:           06/12/2010                                                *
 ** Copyright:      2002 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic input and output operations   *
 **                 on hardware, it can be treated as a hardware abstract     *
 **                 layer interface.                                          *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               * ** 06/12/2010     hao.liu    Create.                                   *
 ******************************************************************************/

#ifndef _ADC_DRVAPI_H_
#define _ADC_DRVAPI_H_

#define ADC_SCALE_3V       0
#define ADC_SCALE_1V2   1

typedef enum
{
    ADIN_0 = 0,
    ADIN_1,
    ADIN_2,
    ADIN_3,
    ADIN_4,
    ADIN_5,
    ADIN_6,
    ADIN_7,
    ADIN_8,
    ADIN_9,
    ADIN_10,
    ADIN_11,
    ADIN_12,
    ADIN_13,
    ADIN_14,
    ADIN_15,
    ADIN_16,
    ADIN_17,
    ADIN_18,
    ADIN_19,
    ADIN_20,
    ADIN_21,
    ADIN_22,
    ADIN_23,
    ADIN_24,
    ADIN_25,
    ADIN_26,
    ADIN_27,
    ADIN_28,
    ADIN_29,
    ADIN_30,
    ADIN_31,
    ADC_MAX
} adc_channel;
//typedef enum{false, true} bool;

#define ADC_CHANNEL_VBAT 5
#define ADC_CHANNEL_PROG 4
#define ADC_CHANNEL_VCHG 6

#ifdef __cplusplus
extern   "C"
{
#endif

void ADC_Init (void);
int32_t ADC_GetValues(adc_channel id, bool scale, uint8_t num, int32_t *p_buf);
int32_t ADC_GetValue(adc_channel adcSource, bool scale);

#ifdef __cplusplus
}
#endif

#endif  // _ADC_DRVAPI_H_

