/******************************************************************************
 ** File Name:    sprd_module_config.h                                        *
 ** Author:       Tim.Luo                                                 *
 ** DATE:         07/08/2010                                                  *
 ** Copyright:    2010 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 07/08/2010    Tim.Luo         Create.                                     *
 ******************************************************************************/
#ifndef _SPRD_MODULE_CONFIG_H_
#define _SPRD_MODULE_CONFIG_H_
/*----------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **------------------------------------------------------------------------- */

/**---------------------------------------------------------------------------*
 **                             Compiler Flag                                 *
 **--------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif
/**---------------------------------------------------------------------------*
**                               Macro Define                                **
**---------------------------------------------------------------------------*/
#define WDG_INIT_COUNT          (0x0009FFFF) //uint : 1/32768s 
/**---------------------------------------------------------------------------*
**                               Macro Define for bus monitor                       **
**---------------------------------------------------------------------------*/
#define MAX_BM_POINTS_NUM       2

/**---------------------------------------------------------------------------*
**                               Macro Define for kpd                        **
**---------------------------------------------------------------------------*/
#define KPD_ROW_NUM                     8               // KPD_ROW_MIN_NUM <= value <= KPD_ROW_MAX_NUM   changed by yong.zou
#define KPD_COL_NUM                     8           // KPD_COL_MIN_NUM <= value <= KPD_COL_MAX_NUM   changed by yong.zou    

#define CFG_ROW_POLARITY    (0x00FF & KPDPOLARITY_ROW)
#define CFG_COL_POLARITY    (0xFF00 & KPDPOLARITY_COL)

#define CFG_CLK_DIV         1
#define MAX_MUL_KEY_NUM     4

#ifdef KEYPAD_TYPE_QWERTY_KEYPAD
#define KPD_NUM  ((0x0F << 16) | (0x1F << 20))//KPDCTL_KPD ;//  8*8
#else
#define KPD_NUM  ((0x01 << 16) | (0x03 << 20))//KPDCTL_KPD ;//  5*5
#endif

//#define KPD_NUM  (0x31 << 16)

/**---------------------------------------------------------------------------*
**                               Macro Define for pwm                        **
**---------------------------------------------------------------------------*/
#define PWM_NUM    4
#define PWMx_BASE(x)    (PWM_BASE + (x)*0x20 )

#define GEN_PWM  GR_CLK_EN
#define GEN_PWMx(x)    (CLK_PWM0_EN << (x))

// the prescale = 0, and the mod = 10
#define   PWM_MAX_FREQ( _pwm_clk )   ( (_pwm_clk) / 10 )
#define   PWM_MIN_FREQ( _pwm_clk )   ( (_pwm_clk) / 256 / 256 )
/**---------------------------------------------------------------------------*
**                               Macro Define for spi                        **
**---------------------------------------------------------------------------*/

#define SPI_PORT                    0x0
#define MAX_SPI_PORT_NUM            (1UL)

#define SPI_TX_WATERMARK            0x28
#define SPI_RX_WATERMARK            0x28

#define SPI_TX_CHANNEL             19 
#define SPI_RX_CHANNEL              20

#define SPI_DMA_TIME_OUT            0x80000
#define SPI_BURST_SIZE                  16
#define SPI_BURST_SIZE_MARK             0xF
#define LENGTH_4_DIVIDE             4

#define SPI_RX_FIFO_FULL            BIT_0
#define SPI_RX_FIFO_EMPTY           BIT_1
#define SPI_TX_FIFO_FULL            BIT_2
#define SPI_TX_FIFO_EMPTY           BIT_3
#define SPI_RX_FIFO_REALLY_FULL     BIT_4
#define SPI_RX_FIFO_REALLY_EMPTY    BIT_5
#define SPI_TX_FIFO_REALLY_FULL     BIT_6
#define SPI_TX_FIFO_REALLY_EMPTY    BIT_7

/**---------------------------------------------------------------------------*
**                               Macro Define for adc/tpc                    **
**---------------------------------------------------------------------------*/

#define ADC_SCALE_3V        SCI_FALSE
#define ADC_SCALE_1V2       SCI_TRUE
//
#define TPC_CHANNEL_X       2
#define TPC_CHANNEL_Y       3
#define ADC_CHANNEL_PROG    4
#define ADC_CHANNEL_VBAT    5
#define ADC_CHANNEL_VCHG    6

/**---------------------------------------------------------------------------*
**                               Macro Define for GPIO                   **
**---------------------------------------------------------------------------*/
#define GPIO_INVALID_ID             0x0FF
#define GPIO_MAX_PIN_NUM            271
#define GPIO_MAX_REC_NUM            10


/**---------------------------------------------------------------------------*
**                               Micro Define for SDIO                    **
**---------------------------------------------------------------------------*/
#define     SDIO_BASE_CLK_384M      384000000        // 384 MHz
#define     SDIO_BASE_CLK_312M      312000000        // 312 MHz
#define     SDIO_BASE_CLK_256M      256000000        // 256 MHz
#define     SDIO_BASE_CLK_192M      192000000        // 192 MHz
#define     SDIO_BASE_CLK_153M      153000000        // 153 MHz
#define     SDIO_BASE_CLK_96M       96000000        // 96 MHz
#define     SDIO_BASE_CLK_80M       80000000        // 80 MHz
#define     SDIO_BASE_CLK_64M       64000000        // 64 MHz
#define     SDIO_BASE_CLK_50M       50000000        // 50 MHz   ,should cfg MPLL to 300/350/400???
#define     SDIO_BASE_CLK_48M       48000000        // 48 MHz
#define     SDIO_BASE_CLK_40M       40000000        // 40 MHz
#define     SDIO_BASE_CLK_32M       32000000        // 32 MHz
#define     SDIO_BASE_CLK_26M       26000000            // 26  MHz
#define     SDIO_BASE_CLK_25M       25000000            // 25  MHz
#define     SDIO_BASE_CLK_20M       20000000            // 20  MHz
#define     SDIO_BASE_CLK_16M       16000000        // 16 MHz
#define     SDIO_BASE_CLK_8M        8000000         // 8  MHz

#define     SDIO_CLK_50M            50000000        // 50   MHz, 1 div for 50MHz
#define     SDIO_CLK_48M            48000000        // 48  MHz
#define     SDIO_CLK_40M            40000000        // 40  MHz
#define     SDIO_CLK_32M            32000000        // 32  MHz
#define     SDIO_CLK_25M            25000000        // 25   MHz, 2 div for 50MHz
#define     SDIO_CLK_24M            24000000        // 25   MHz, 2 div for 50MHz
#define     SDIO_CLK_20M            20000000        // 20   MHz
#define     SDIO_CLK_16M            16000000        // 16  MHz
#define     SDIO_CLK_12P5M          12500000        // 12.5   MHz, 4 div for 50MHz
#define     SDIO_CLK_10M            10000000        // 10   MHz
#define     SDIO_CLK_8M             8000000         // 8   MHz
#define     SDIO_CLK_6P25M          6250000         // 6.25   MHz, 8 div for 50MHz
#define     SDIO_CLK_4M             4000000         // 4   MHz
#define     SDIO_CLK_3P125M         3125000         // 3.125 MHz, 16 div for 50MHz
#define     SDIO_CLK_2M             2000000         // 2   MHz
#define     SDIO_CLK_1P56M          1562500         // 1.562 MHz, 32 div for 50MHz
#define     SDIO_CLK_1M             1000000         // 1   MHz
#define     SDIO_CLK_781K           781250          // 781 KHz, 64 div for 50MHz
#define     SDIO_CLK_390K           390625          // 390 KHz, 128 div for 50MHz
#define     SDIO_CLK_250K           250000          // 250 KHz
#define     SDIO_CLK_195K           195312          // 195 KHz, 256 div for 50MHz
#define     SDIO_CLK_125K           125000          // 125 KHz

#define     SDIO_BASE_CLK           SDIO_BASE_CLK_96M    // 96MHz
#define     SDIO_SD_MAX_CLK         SDIO_CLK_48M          //SDIO_CLK_50M//

#define USB_FIFO_MAX_WORD               16
#define USB_FIFO_MAX_BYTE               1024
#define USB_MAX_TRANSFER_SIZE           (32*1024)


//=====
//define transfer mode and command mode...
//command mode
#define SDIO_CMD_TYPE_ABORT                 (3<<22)
#define SDIO_CMD_TYPE_RESUME                    (2<<22)
#define SDIO_CMD_TYPE_SUSPEND                   (1<<22)
#define SDIO_CMD_TYPE_NML                       (0<<22)

#define SDIO_CMD_DATA_PRESENT                   BIT_21

#define SDIO_CMD_INDEX_CHK                  BIT_20
#define SDIO_CMD_CRC_CHK                        BIT_19
#define SDIO_CMD_NO_RSP                     (0x00<<16)
#define SDIO_CMD_RSP_136                        (0x01<<16)
#define SDIO_CMD_RSP_48                     (0x02<<16)
#define SDIO_CMD_RSP_48_BUSY                    (0x03<<16)

#define SDIO_NO_RSP     0x0;
#define SDIO_R1     ( SDIO_CMD_RSP_48 | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
#define SDIO_R2     ( SDIO_CMD_RSP_136 | SDIO_CMD_CRC_CHK )
#define SDIO_R3     SDIO_CMD_RSP_48
#define SDIO_R4     SDIO_CMD_RSP_48
#define SDIO_R5     ( SDIO_CMD_RSP_48 | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
#define SDIO_R6     ( SDIO_CMD_RSP_48 | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
#define SDIO_R7     ( SDIO_CMD_RSP_48 | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
#define SDIO_R1B    ( SDIO_CMD_RSP_48_BUSY | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
#define SDIO_R5B    ( SDIO_CMD_RSP_48_BUSY | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
//transfer mode
#define SDIO_TRANS_COMP_ATA         BIT_6
#define SDIO_TRANS_MULTIBLK         BIT_5
#define SDIO_TRANS_DIR_READ         BIT_4
#define SDIO_TRANS_AUTO_CMD12_EN        BIT_2
#define SDIO_TRANS_BLK_CNT_EN           BIT_1
#define SDIO_TRANS_DMA_EN               BIT_0

//=====
//define normal and error sts index...
#define SDIO_VENDOR_SPEC_ERR        (BIT_29|BIT_30|BIT_31)
#define SDIO_TARGET_RESP_ERR        (BIT_28)
#define SDIO_AUTO_CMD12_ERR         (BIT_24)
#define SDIO_CURRENT_LMT_ERR        (BIT_23)
#define SDIO_DATA_ENDBIT_ERR        (BIT_22)
#define SDIO_DATA_CRC_ERR           (BIT_21)
#define SDIO_DATA_TMOUT_ERR         (BIT_20)
#define SDIO_CMD_INDEX_ERR          (BIT_19)
#define SDIO_CMD_ENDBIT_ERR         (BIT_18)
#define SDIO_CMD_CRC_ERR            (BIT_17)
#define SDIO_CMD_TMOUT_ERR          (BIT_16)
#define SDIO_ERROR_INT              (BIT_15)
#define SDIO_CARD_INT               (BIT_8)
#define SDIO_CARD_REMOVAL           (BIT_7)
#define SDIO_CARD_INSERTION         (BIT_6)
#define SDIO_BUF_READ_RDY           (BIT_5)
#define SDIO_BUF_WRITE_RDY          (BIT_4)
#define SDIO_DMA_INT                (BIT_3)
#define SDIO_BLK_GAP_EVT            (BIT_2)
#define SDIO_TRANSFER_CMPLETE       (BIT_1)
#define SDIO_CMD_CMPLETE            (BIT_0)

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

