/******************************************************************************
 ** File Name:    USB200.h                                                    *
 ** Author:       Daniel.Ding                                                 *
 ** DATE:         3/9/2005                                                    *
 ** Copyright:    2005 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 9/1/2003      Daniel.Ding     Create.                                     *
 ******************************************************************************/
#ifndef _USB200_FDL_H_
#define _USB200_FDL_H_
/*----------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **-------------------------------------------------------------------------- */

#include "common.h"
/**---------------------------------------------------------------------------*
 **                             Compiler Flag                                 *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif
/**----------------------------------------------------------------------------*
**                               Micro Define                                 **
**----------------------------------------------------------------------------*/
#define MAXIMUM_USB_STRING_LENGTH 255

#define USB_GETSTATUS_SELF_POWERED                0x01
#define USB_GETSTATUS_REMOTE_WAKEUP_ENABLED       0x02


#define USB_DEVICE_DESCRIPTOR_TYPE                0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE         0x02
#define USB_STRING_DESCRIPTOR_TYPE                0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE             0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE              0x05
#define USB_POWER_DESCRIPTOR_TYPE                 0x06

#define STR_INDEX_LANGUAGE                        0x00
#define STR_INDEX_MANUFACTURER                    0x01
#define STR_INDEX_PRODUCT                         0x02
#define STR_INDEX_SERIALNUMBER                    0x03
#define STR_INDEX_CONFIGURATION                   0x04
#define STR_INDEX_INTERFACE                       0x05

#define USB_DESCRIPTOR_MAKE_TYPE_AND_INDEX(d, i) ((short)((short)d<<8 | i))

//
// Values for bmAttributes field of an
// endpoint descriptor
//

#define USB_ENDPOINT_TYPE_MASK                    0x03

#define USB_ENDPOINT_TYPE_CONTROL                 0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS             0x01
#define USB_ENDPOINT_TYPE_BULK                    0x02
#define USB_ENDPOINT_TYPE_INTERRUPT               0x03


//
// definitions for bits in the bmAttributes field of a
// configuration descriptor.
//
#define USB_CONFIG_POWERED_MASK                   0xc0

#define USB_CONFIG_BUS_POWERED                    0x80
#define USB_CONFIG_SELF_POWERED                   0x40
#define USB_CONFIG_REMOTE_WAKEUP                  0x20

//
// Endpoint direction bit, stored in address
//

#define USB_ENDPOINT_DIRECTION_MASK               0x80

// test direction bit in the bEndpointAddress field of
// an endpoint descriptor.
#define USB_ENDPOINT_DIRECTION_OUT(addr)          (!((addr) & USB_ENDPOINT_DIRECTION_MASK))
#define USB_ENDPOINT_DIRECTION_IN(addr)           ((addr) & USB_ENDPOINT_DIRECTION_MASK)

//
// USB defined request codes
// see chapter 9 of the USB 1.0 specifcation for
// more information.
//

// These are the correct values based on the USB 1.0
// specification

#define USB_REQUEST_GET_STATUS                    0x00
#define USB_REQUEST_CLEAR_FEATURE                 0x01

#define USB_REQUEST_SET_FEATURE                   0x03

#define USB_REQUEST_SET_ADDRESS                   0x05
#define USB_REQUEST_GET_DESCRIPTOR                0x06
#define USB_REQUEST_SET_DESCRIPTOR                0x07
#define USB_REQUEST_GET_CONFIGURATION             0x08
#define USB_REQUEST_SET_CONFIGURATION             0x09
#define USB_REQUEST_GET_INTERFACE                 0x0A
#define USB_REQUEST_SET_INTERFACE                 0x0B
#define USB_REQUEST_SYNC_FRAME                    0x0C


//
// defined USB device classes
//


#define USB_DEVICE_CLASS_RESERVED           0x00
#define USB_DEVICE_CLASS_AUDIO              0x01
#define USB_DEVICE_CLASS_COMMUNICATIONS     0x02
#define USB_DEVICE_CLASS_HUMAN_INTERFACE    0x03
#define USB_DEVICE_CLASS_MONITOR            0x04
#define USB_DEVICE_CLASS_PHYSICAL_INTERFACE 0x05
#define USB_DEVICE_CLASS_POWER              0x06
#define USB_DEVICE_CLASS_PRINTER            0x07
#define USB_DEVICE_CLASS_STORAGE            0x08
#define USB_DEVICE_CLASS_HUB                0x09
#define USB_DEVICE_CLASS_VENDOR_SPECIFIC    0xFF

//
// USB defined Feature selectors
//

#define USB_FEATURE_ENDPOINT_STALL          0x0000
#define USB_FEATURE_REMOTE_WAKEUP           0x0001
#define USB_FEATURE_POWER_D0                0x0002
#define USB_FEATURE_POWER_D1                0x0003
#define USB_FEATURE_POWER_D2                0x0004
#define USB_FEATURE_POWER_D3                0x0005


//Define direction ;
#define HOST_IN     0x01        //From device to host ;
#define HOST_OUT    0x00        //From host to device ;

//Define request type;
#define USB_REQ_STANDARD    0x00
#define USB_REQ_CLASS       0x01
#define USB_REQ_VENDOR      0x02
#define USB_REQ_RESERVED    0x03

//Define accepter ;
#define USB_REC_DEVICE      0x00
#define USB_REC_INTERFACE   0x01
#define USB_REC_ENDPOINT    0x02
#define USB_REC_OTHER       0x03

#define USB_MAX_REQ_TYPE    0x04
#define USB_MAX_RECIPIENT   0x05
#define USB_MAX_REQUEST     0x30

#define BUS_POWERED                           0x80
#define SELF_POWERED                          0x40
#define REMOTE_WAKEUP                         0x20

//
// USB power descriptor added to core specification
//

#define USB_SUPPORT_D0_COMMAND      0x01
#define USB_SUPPORT_D1_COMMAND      0x02
#define USB_SUPPORT_D2_COMMAND      0x04
#define USB_SUPPORT_D3_COMMAND      0x08

#define USB_SUPPORT_D1_WAKEUP       0x10
#define USB_SUPPORT_D2_WAKEUP       0x20

/**----------------------------------------------------------------------------*
**                             Data Prototype                                 **
**----------------------------------------------------------------------------*/
//Stand USB device request command type define ;
typedef union _USB_STD_DEV_REQ_T
{
    struct
    {
        union
        {
            struct bit_map
            {
                char direction :1;
                char command   :2;
                char receiver  :5;
            } bits;
            char octet;
        } uReqType;
        char  bReqCode;
        short wValue;
        short wIndex;
        short wLength;
    } sData;
    char bBuf[8];
} USB_STD_DEV_REQ_U;

typedef union
{
    struct
    {
        short   type    :8;
        short   index   :8;
    } sDescriptor;
    short wValue;
} VALUE_U;

//Four bytes buildup a 32bit value ;
typedef union _USB_DWORD_U
{
    union
    {
        struct
        {
            char  c0;
            char  c1;
            char  c2;
            char  c3;
        } sOcts;
        char bBuf[4];
    } uData;
    int dwValue;
} USB_DWORD_U;


//Two bytes buildup a 16bit value ;
typedef union _USB_WORD_U
{
    union
    {
        struct
        {
            char  c0;
            char  c1;
        } sOcts;
        char bBuf[2];
    } uData;
    int wValue;
} USB_WORD_U;

//
// values for bmAttributes Field in
// USB_CONFIGURATION_DESCRIPTOR
//


//
// Standard USB HUB definitions
//
// See Chapter 11
//
typedef struct _USB_DEVICE_DESCRIPTOR
{
    char bLength;
    char bDescriptorType;
    short bcdUSB;
    char bDeviceClass;
    char bDeviceSubClass;
    char bDeviceProtocol;
    char bMaxPacketSize0;
    short idVendor;
    short idProduct;
    short bcdDevice;
    char iManufacturer;
    char iProduct;
    char iSerialNumber;
    char bNumConfigurations;
} USB_DEVICE_DESCRIPTOR, *PUSB_DEVICE_DESCRIPTOR;

typedef struct _USB_CONFIGURATION_DESCRIPTOR
{
    char bLength;
    char bDescriptorType;
    short wTotalLength;
    char bNumInterfaces;
    char bConfigurationValue;
    char iConfiguration;
    char bmAttributes;
    char MaxPower;
} USB_CONFIGURATION_DESCRIPTOR, *PUSB_CONFIGURATION_DESCRIPTOR;

typedef struct _USB_INTERFACE_DESCRIPTOR
{
    char bLength;
    char bDescriptorType;
    char bInterfaceNumber;
    char bAlternateSetting;
    char bNumEndpoints;
    char bInterfaceClass;
    char bInterfaceSubClass;
    char bInterfaceProtocol;
    char iInterface;
} USB_INTERFACE_DESCRIPTOR, *PUSB_INTERFACE_DESCRIPTOR;

typedef struct _USB_STRING_DESCRIPTOR
{
    char bLength;
    char bDescriptorType;
    char bString[1];
} USB_STRING_DESCRIPTOR, *PUSB_STRING_DESCRIPTOR;

typedef struct _USB_ENDPOINT_DESCRIPTOR
{
    char bLength;
    char bDescriptorType;
    union _bEndpointAddress
    {
        struct
        {
            char direction      :1;
            char reserved       :3;
            char number         :4;
        } bits;
        char value;
    } bEndpointAddress;
    union _bmAttributes
    {
        struct
        {
            char reserved       :2;
            char usage_type     :2;
            char sync_type      :2;
            char trans_type     :2;
        } bits;
        char value;
    } bmAttributes;
    short wMaxPacketSize;
    char bInterval;
} USB_ENDPOINT_DESCRIPTOR, *PUSB_ENDPOINT_DESCRIPTOR;


typedef struct _USB_HUB_DESCRIPTOR
{
    char        bDescriptorLength;      // Length of this descriptor
    char        bDescriptorType;        // Hub configuration type
    char        bNumberOfPorts;         // number of ports on this hub
    short       wHubCharacteristics;    // Hub Charateristics
    char        bPowerOnToPowerGood;    // port power on till power good in 2ms
    char        bHubControlCurrent;     // max current in mA
    //
    // room for 255 ports power control and removable bitmask
    char        bRemoveAndPowerMask[64];
} USB_HUB_DESCRIPTOR, *PUSB_HUB_DESCRIPTOR;


typedef struct _USB_STRING_LANGUAGE_DESCRIPTOR
{
    char  bLength;
    char  bDescriptorType;
    short ulanguageID;
} USB_STRING_LANGUAGE_DESCRIPTOR,*PUSB_STRING_LANGUAGE_DESCRIPTOR;

typedef struct _USB_STRING_INTERFACE_DESCRIPTOR
{
    char  bLength;
    char  bDescriptorType;
    char  Interface[22];
} USB_STRING_INTERFACE_DESCRIPTOR,*PUSB_STRING_INTERFACE_DESCRIPTOR;

typedef struct _USB_STRING_CONFIGURATION_DESCRIPTOR
{
    char  bLength;
    char  bDescriptorType;
    char  Configuration[16];
} USB_STRING_CONFIGURATION_DESCRIPTOR,*PUSB_STRING_CONFIGURATION_DESCRIPTOR;

typedef struct _USB_STRING_SERIALNUMBER_DESCRIPTOR
{
    char  bLength;
    char  bDescriptorType;
    char  SerialNum[24];
} USB_STRING_SERIALNUMBER_DESCRIPTOR,*PUSB_STRING_SERIALNUMBER_DESCRIPTOR;

typedef struct _USB_STRING_PRODUCT_DESCRIPTOR
{
    char  bLength;
    char  bDescriptorType;
    char  Product[30];
} USB_STRING_PRODUCT_DESCRIPTOR,*PUSB_STRING_PRODUCT_DESCRIPTOR;

typedef struct _USB_STRING_MANUFACTURER_DESCRIPTOR
{
    char  bLength;
    char  bDescriptorType;
    char  Manufacturer[24];
} USB_STRING_MANUFACTURER_DESCRIPTOR,*PUSB_STRING_MANUFACTURER_DESCRIPTOR;

typedef struct _USB_POWER_DESCRIPTOR
{
    char bLength;
    char bDescriptorType;
    char bCapabilitiesFlags;
    short EventNotification;
    short D1LatencyTime;
    short D2LatencyTime;
    short D3LatencyTime;
    char PowerUnit;
    short D0PowerConsumption;
    short D1PowerConsumption;
    short D2PowerConsumption;
} USB_POWER_DESCRIPTOR, *PUSB_POWER_DESCRIPTOR;


typedef struct _USB_COMMON_DESCRIPTOR
{
    char bLength;
    char bDescriptorType;
} USB_COMMON_DESCRIPTOR, *PUSB_COMMON_DESCRIPTOR;

/**----------------------------------------------------------------------------*
**                         Local Function Prototype                           **
**----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------*
**                           Function Prototype                               **
**----------------------------------------------------------------------------*/


/**----------------------------------------------------------------------------*
**                         Compiler Flag                                      **
**----------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
/**---------------------------------------------------------------------------*/
#endif
// End
