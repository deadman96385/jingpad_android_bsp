/*************************************************************************/ /*!
@Title          Hardware definition file nn_sys_cr_gyrus.h
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
*/ /**************************************************************************/

/*               ****   Autogenerated C -- do not edit    ****               */

/*
 */


#ifndef _NN_SYS_CR_GYRUS_H_
#define _NN_SYS_CR_GYRUS_H_

#define NN_SYS_CR_GYRUS_REVISION 1

/*
    Register NN_SYS_CR_PRODUCT_ID
*/
#define NN_SYS_CR_PRODUCT_ID                              (0x0018U)
#define NN_SYS_CR_PRODUCT_ID_MASKFULL                     (IMG_UINT64_C(0x00000000FFFF0000))
#define NN_SYS_CR_PRODUCT_ID_IMG_PRODUCT_ID_SHIFT         (16U)
#define NN_SYS_CR_PRODUCT_ID_IMG_PRODUCT_ID_CLRMSK        (IMG_UINT64_C(0XFFFFFFFF0000FFFF))


/*
    Register NN_SYS_CR_CORE_ID
*/
#define NN_SYS_CR_CORE_ID                                 (0x0020U)
#define NN_SYS_CR_CORE_ID_MASKFULL                        (IMG_UINT64_C(0xFFFFFFFFFFFFFFFF))
#define NN_SYS_CR_CORE_ID_BRANCH_ID_SHIFT                 (48U)
#define NN_SYS_CR_CORE_ID_BRANCH_ID_CLRMSK                (IMG_UINT64_C(0X0000FFFFFFFFFFFF))
#define NN_SYS_CR_CORE_ID_VERSION_ID_SHIFT                (32U)
#define NN_SYS_CR_CORE_ID_VERSION_ID_CLRMSK               (IMG_UINT64_C(0XFFFF0000FFFFFFFF))
#define NN_SYS_CR_CORE_ID_NUMBER_OF_SCALABLE_UNITS_SHIFT  (16U)
#define NN_SYS_CR_CORE_ID_NUMBER_OF_SCALABLE_UNITS_CLRMSK (IMG_UINT64_C(0XFFFFFFFF0000FFFF))
#define NN_SYS_CR_CORE_ID_CONFIG_ID_SHIFT                 (0U)
#define NN_SYS_CR_CORE_ID_CONFIG_ID_CLRMSK                (IMG_UINT64_C(0XFFFFFFFFFFFF0000))


/*
    Register NN_SYS_CR_CORE_IP_INTEGRATOR_ID
*/
#define NN_SYS_CR_CORE_IP_INTEGRATOR_ID                   (0x0028U)
#define NN_SYS_CR_CORE_IP_INTEGRATOR_ID_MASKFULL          (IMG_UINT64_C(0x00000000FFFFFFFF))
#define NN_SYS_CR_CORE_IP_INTEGRATOR_ID_VALUE_SHIFT       (0U)
#define NN_SYS_CR_CORE_IP_INTEGRATOR_ID_VALUE_CLRMSK      (IMG_UINT64_C(0XFFFFFFFF00000000))


/*
    Register NN_SYS_CR_CORE_IP_CHANGELIST
*/
#define NN_SYS_CR_CORE_IP_CHANGELIST                      (0x0030U)
#define NN_SYS_CR_CORE_IP_CHANGELIST_MASKFULL             (IMG_UINT64_C(0x00000000FFFFFFFF))
#define NN_SYS_CR_CORE_IP_CHANGELIST_VALUE_SHIFT          (0U)
#define NN_SYS_CR_CORE_IP_CHANGELIST_VALUE_CLRMSK         (IMG_UINT64_C(0XFFFFFFFF00000000))


#define NN_SYS_CR_CLK_CTRL_MODE_MASK                      (0x00000003U)
/*
 The domain clock is forced off */
#define NN_SYS_CR_CLK_CTRL_MODE_OFF                       (0x00000000U)
/*
 The domain clock is forced on */
#define NN_SYS_CR_CLK_CTRL_MODE_ON                        (0x00000001U)
/*
 Automatic clock gating is active, the domain clock is only on whilst data is being processed */
#define NN_SYS_CR_CLK_CTRL_MODE_AUTO                      (0x00000002U)


/*
    Register NN_SYS_CR_CLK_CTRL
*/
#define NN_SYS_CR_CLK_CTRL                                (0x0200U)
#define NN_SYS_CR_CLK_CTRL_MASKFULL                       (IMG_UINT64_C(0x0000000000000003))
#define NN_SYS_CR_CLK_CTRL_NN_SYS_SHIFT                   (0U)
#define NN_SYS_CR_CLK_CTRL_NN_SYS_CLRMSK                  (0XFFFFFFFCU)
#define NN_SYS_CR_CLK_CTRL_NN_SYS_OFF                     (00000000U)
#define NN_SYS_CR_CLK_CTRL_NN_SYS_ON                      (0X00000001U)
#define NN_SYS_CR_CLK_CTRL_NN_SYS_AUTO                    (0X00000002U)


/*
 Clock is gated and the module is inactive */
#define NN_SYS_CR_CLK_STATUS_MODE_GATED                   (0x00000000U)
/*
 Clock is running */
#define NN_SYS_CR_CLK_STATUS_MODE_RUNNING                 (0x00000001U)


/*
    Register NN_SYS_CR_CLK_STATUS
*/
#define NN_SYS_CR_CLK_STATUS                              (0x0208U)
#define NN_SYS_CR_CLK_STATUS_MASKFULL                     (IMG_UINT64_C(0x0000000000000001))
#define NN_SYS_CR_CLK_STATUS_NN_SYS_SHIFT                 (0U)
#define NN_SYS_CR_CLK_STATUS_NN_SYS_CLRMSK                (0XFFFFFFFEU)
#define NN_SYS_CR_CLK_STATUS_NN_SYS_GATED                 (00000000U)
#define NN_SYS_CR_CLK_STATUS_NN_SYS_RUNNING               (0X00000001U)


/*
    Register NN_SYS_CR_EVENT_CLEAR
*/
#define NN_SYS_CR_EVENT_CLEAR                             (0x0210U)
#define NN_SYS_CR_EVENT_CLEAR_MASKFULL                    (IMG_UINT64_C(0x0000000000000003))
#define NN_SYS_CR_EVENT_CLEAR_NN_SYS_PWR_ABORT_SHIFT      (1U)
#define NN_SYS_CR_EVENT_CLEAR_NN_SYS_PWR_ABORT_CLRMSK     (0XFFFFFFFDU)
#define NN_SYS_CR_EVENT_CLEAR_NN_SYS_PWR_ABORT_EN         (0X00000002U)
#define NN_SYS_CR_EVENT_CLEAR_NN_SYS_PWR_COMPLETE_SHIFT   (0U)
#define NN_SYS_CR_EVENT_CLEAR_NN_SYS_PWR_COMPLETE_CLRMSK  (0XFFFFFFFEU)
#define NN_SYS_CR_EVENT_CLEAR_NN_SYS_PWR_COMPLETE_EN      (0X00000001U)


/*
    Register NN_SYS_CR_EVENT_ENABLE
*/
#define NN_SYS_CR_EVENT_ENABLE                            (0x0218U)
#define NN_SYS_CR_EVENT_ENABLE_MASKFULL                   (IMG_UINT64_C(0x0000000000000003))
#define NN_SYS_CR_EVENT_ENABLE_NN_SYS_PWR_ABORT_SHIFT     (1U)
#define NN_SYS_CR_EVENT_ENABLE_NN_SYS_PWR_ABORT_CLRMSK    (0XFFFFFFFDU)
#define NN_SYS_CR_EVENT_ENABLE_NN_SYS_PWR_ABORT_EN        (0X00000002U)
#define NN_SYS_CR_EVENT_ENABLE_NN_SYS_PWR_COMPLETE_SHIFT  (0U)
#define NN_SYS_CR_EVENT_ENABLE_NN_SYS_PWR_COMPLETE_CLRMSK (0XFFFFFFFEU)
#define NN_SYS_CR_EVENT_ENABLE_NN_SYS_PWR_COMPLETE_EN     (0X00000001U)


/*
    Register NN_SYS_CR_EVENT_STATUS
*/
#define NN_SYS_CR_EVENT_STATUS                            (0x0220U)
#define NN_SYS_CR_EVENT_STATUS_MASKFULL                   (IMG_UINT64_C(0x0000000000000003))
#define NN_SYS_CR_EVENT_STATUS_NN_SYS_PWR_ABORT_SHIFT     (1U)
#define NN_SYS_CR_EVENT_STATUS_NN_SYS_PWR_ABORT_CLRMSK    (0XFFFFFFFDU)
#define NN_SYS_CR_EVENT_STATUS_NN_SYS_PWR_ABORT_EN        (0X00000002U)
#define NN_SYS_CR_EVENT_STATUS_NN_SYS_PWR_COMPLETE_SHIFT  (0U)
#define NN_SYS_CR_EVENT_STATUS_NN_SYS_PWR_COMPLETE_CLRMSK (0XFFFFFFFEU)
#define NN_SYS_CR_EVENT_STATUS_NN_SYS_PWR_COMPLETE_EN     (0X00000001U)


/*
    Register NN_SYS_CR_IDLE_HYSTERESIS_COUNT
*/
#define NN_SYS_CR_IDLE_HYSTERESIS_COUNT                   (0x0228U)
#define NN_SYS_CR_IDLE_HYSTERESIS_COUNT_MASKFULL          (IMG_UINT64_C(0x000000000000001F))
#define NN_SYS_CR_IDLE_HYSTERESIS_COUNT_NN_SYS_SHIFT      (0U)
#define NN_SYS_CR_IDLE_HYSTERESIS_COUNT_NN_SYS_CLRMSK     (0XFFFFFFE0U)


/*
 Power event type is power down */
#define NN_SYS_CR_POWER_EVENT_MODE_POWER_DOWN             (0x00000000U)
/*
 Power event type is power up  */
#define NN_SYS_CR_POWER_EVENT_MODE_POWER_UP               (0x00000001U)


/*
    Register NN_SYS_CR_POWER_EVENT
*/
#define NN_SYS_CR_POWER_EVENT                             (0x0230U)
#define NN_SYS_CR_POWER_EVENT_MASKFULL                    (IMG_UINT64_C(0x0000000000000033))
#define NN_SYS_CR_POWER_EVENT_DOMAIN_NNA_SHIFT            (5U)
#define NN_SYS_CR_POWER_EVENT_DOMAIN_NNA_CLRMSK           (0XFFFFFFDFU)
#define NN_SYS_CR_POWER_EVENT_DOMAIN_NNA_EN               (0X00000020U)
#define NN_SYS_CR_POWER_EVENT_DOMAIN_NNSYS_SHIFT          (4U)
#define NN_SYS_CR_POWER_EVENT_DOMAIN_NNSYS_CLRMSK         (0XFFFFFFEFU)
#define NN_SYS_CR_POWER_EVENT_DOMAIN_NNSYS_EN             (0X00000010U)
#define NN_SYS_CR_POWER_EVENT_REQUEST_SHIFT               (1U)
#define NN_SYS_CR_POWER_EVENT_REQUEST_CLRMSK              (0XFFFFFFFDU)
#define NN_SYS_CR_POWER_EVENT_REQUEST_POWER_DOWN          (00000000U)
#define NN_SYS_CR_POWER_EVENT_REQUEST_POWER_UP            (0X00000002U)
#define NN_SYS_CR_POWER_EVENT_TYPE_SHIFT                  (0U)
#define NN_SYS_CR_POWER_EVENT_TYPE_CLRMSK                 (0XFFFFFFFEU)
#define NN_SYS_CR_POWER_EVENT_TYPE_EN                     (0X00000001U)


/*
    Register NN_SYS_CR_RESET_CLK_CTRL
*/
#define NN_SYS_CR_RESET_CLK_CTRL                          (0x0238U)
#define NN_SYS_CR_RESET_CLK_CTRL_MASKFULL                 (IMG_UINT64_C(0x0000000000000003))
#define NN_SYS_CR_RESET_CLK_CTRL_NN_SYS_SHIFT             (0U)
#define NN_SYS_CR_RESET_CLK_CTRL_NN_SYS_CLRMSK            (0XFFFFFFFCU)


/*
    Register NN_SYS_CR_RESET_CTRL
*/
#define NN_SYS_CR_RESET_CTRL                              (0x0240U)
#define NN_SYS_CR_RESET_CTRL_MASKFULL                     (IMG_UINT64_C(0x0000000000000001))
#define NN_SYS_CR_RESET_CTRL_NN_SYS_SHIFT                 (0U)
#define NN_SYS_CR_RESET_CTRL_NN_SYS_CLRMSK                (0XFFFFFFFEU)
#define NN_SYS_CR_RESET_CTRL_NN_SYS_EN                    (0X00000001U)


/*
    Register NN_SYS_CR_SOCIF_WAKEUP_ENABLE
*/
#define NN_SYS_CR_SOCIF_WAKEUP_ENABLE                     (0x0248U)
#define NN_SYS_CR_SOCIF_WAKEUP_ENABLE_MASKFULL            (IMG_UINT64_C(0x0000000000000001))
#define NN_SYS_CR_SOCIF_WAKEUP_ENABLE_ALWAYS_SHIFT        (0U)
#define NN_SYS_CR_SOCIF_WAKEUP_ENABLE_ALWAYS_CLRMSK       (0XFFFFFFFEU)
#define NN_SYS_CR_SOCIF_WAKEUP_ENABLE_ALWAYS_EN           (0X00000001U)


/*
    Register NN_SYS_CR_AXI_EXACCESS
*/
#define NN_SYS_CR_AXI_EXACCESS                            (0x0250U)
#define NN_SYS_CR_AXI_EXACCESS_MASKFULL                   (IMG_UINT64_C(0x0000000000000001))
#define NN_SYS_CR_AXI_EXACCESS_SOCIF_ENABLE_SHIFT         (0U)
#define NN_SYS_CR_AXI_EXACCESS_SOCIF_ENABLE_CLRMSK        (0XFFFFFFFEU)
#define NN_SYS_CR_AXI_EXACCESS_SOCIF_ENABLE_EN            (0X00000001U)


/*
    Register NN_SYS_CR_REGBANK_REQUEST_INVALID
*/
#define NN_SYS_CR_REGBANK_REQUEST_INVALID                 (0x0258U)
#define NN_SYS_CR_REGBANK_REQUEST_INVALID_MASKFULL        (IMG_UINT64_C(0x0000000000000001))
#define NN_SYS_CR_REGBANK_REQUEST_INVALID_FLAG_SHIFT      (0U)
#define NN_SYS_CR_REGBANK_REQUEST_INVALID_FLAG_CLRMSK     (0XFFFFFFFEU)
#define NN_SYS_CR_REGBANK_REQUEST_INVALID_FLAG_EN         (0X00000001U)


/*
    Register NN_SYS_CR_NOC_LOWER_ADDR1
*/
#define NN_SYS_CR_NOC_LOWER_ADDR1                         (0x0268U)
#define NN_SYS_CR_NOC_LOWER_ADDR1_MASKFULL                (IMG_UINT64_C(0x0000000FFFFFFFFF))
#define NN_SYS_CR_NOC_LOWER_ADDR1_LOWER_ADDR_SHIFT        (0U)
#define NN_SYS_CR_NOC_LOWER_ADDR1_LOWER_ADDR_CLRMSK       (IMG_UINT64_C(0XFFFFFFF000000000))


/*
    Register NN_SYS_CR_NOC_UPPER_ADDR1
*/
#define NN_SYS_CR_NOC_UPPER_ADDR1                         (0x0278U)
#define NN_SYS_CR_NOC_UPPER_ADDR1_MASKFULL                (IMG_UINT64_C(0x0000000FFFFFFFFF))
#define NN_SYS_CR_NOC_UPPER_ADDR1_UPPER_ADDR_SHIFT        (0U)
#define NN_SYS_CR_NOC_UPPER_ADDR1_UPPER_ADDR_CLRMSK       (IMG_UINT64_C(0XFFFFFFF000000000))


/*
    Register NN_SYS_CR_SYS_BUS_DIRECT_ACCESS
*/
#define NN_SYS_CR_SYS_BUS_DIRECT_ACCESS                   (0x0280U)
#define NN_SYS_CR_SYS_BUS_DIRECT_ACCESS_MASKFULL          (IMG_UINT64_C(0x0000000000000001))
#define NN_SYS_CR_SYS_BUS_DIRECT_ACCESS_SYS_BUS_DIRECT_ACCESS_SHIFT (0U)
#define NN_SYS_CR_SYS_BUS_DIRECT_ACCESS_SYS_BUS_DIRECT_ACCESS_CLRMSK (IMG_UINT64_C(0XFFFFFFFFFFFFFFFE))
#define NN_SYS_CR_SYS_BUS_DIRECT_ACCESS_SYS_BUS_DIRECT_ACCESS_EN (IMG_UINT64_C(0X0000000000000001))


/*
    Register NN_SYS_CR_NNPU_ACE_QOS_CTRL
*/
#define NN_SYS_CR_NNPU_ACE_QOS_CTRL                       (0x02A0U)
#define NN_SYS_CR_NNPU_ACE_QOS_CTRL_MASKFULL              (IMG_UINT64_C(0x000000000000FFFF))
#define NN_SYS_CR_NNPU_ACE_QOS_CTRL_CRITICAL_SHIFT        (12U)
#define NN_SYS_CR_NNPU_ACE_QOS_CTRL_CRITICAL_CLRMSK       (0XFFFF0FFFU)
#define NN_SYS_CR_NNPU_ACE_QOS_CTRL_HIGH_SHIFT            (8U)
#define NN_SYS_CR_NNPU_ACE_QOS_CTRL_HIGH_CLRMSK           (0XFFFFF0FFU)
#define NN_SYS_CR_NNPU_ACE_QOS_CTRL_MEDIUM_SHIFT          (4U)
#define NN_SYS_CR_NNPU_ACE_QOS_CTRL_MEDIUM_CLRMSK         (0XFFFFFF0FU)
#define NN_SYS_CR_NNPU_ACE_QOS_CTRL_LOW_SHIFT             (0U)
#define NN_SYS_CR_NNPU_ACE_QOS_CTRL_LOW_CLRMSK            (0XFFFFFFF0U)


#define NN_SYS_CR_NNPU_ACE_QOS_SEL_ENUM_PRIORITIES_MASK   (0x00000003U)
/*
 Low */
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_ENUM_PRIORITIES_LOW    (0x00000000U)
/*
 Medium */
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_ENUM_PRIORITIES_MEDIUM (0x00000001U)
/*
 High */
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_ENUM_PRIORITIES_HIGH   (0x00000002U)
/*
 Critical */
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_ENUM_PRIORITIES_CRITICAL (0x00000003U)


/*
    Register NN_SYS_CR_NNPU_ACE_QOS_SEL
*/
#define NN_SYS_CR_NNPU_ACE_QOS_SEL                        (0x02A8U)
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_MASKFULL               (IMG_UINT64_C(0x00000000000000F1))
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_MMU_SHIFT              (6U)
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_MMU_CLRMSK             (IMG_UINT64_C(0XFFFFFFFFFFFFFF3F))
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_MMU_LOW                (IMG_UINT64_C(0000000000000000))  
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_MMU_MEDIUM             (IMG_UINT64_C(0x0000000000000040))  
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_MMU_HIGH               (IMG_UINT64_C(0x0000000000000080))  
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_MMU_CRITICAL           (IMG_UINT64_C(0x00000000000000c0))  
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_NON_MMU_SHIFT          (4U)
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_NON_MMU_CLRMSK         (IMG_UINT64_C(0XFFFFFFFFFFFFFFCF))
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_NON_MMU_LOW            (IMG_UINT64_C(0000000000000000))  
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_NON_MMU_MEDIUM         (IMG_UINT64_C(0x0000000000000010))  
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_NON_MMU_HIGH           (IMG_UINT64_C(0x0000000000000020))  
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_NON_MMU_CRITICAL       (IMG_UINT64_C(0x0000000000000030))  
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_NNPU_QOS_ENABLE_SHIFT  (0U)
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_NNPU_QOS_ENABLE_CLRMSK (IMG_UINT64_C(0XFFFFFFFFFFFFFFFE))
#define NN_SYS_CR_NNPU_ACE_QOS_SEL_NNPU_QOS_ENABLE_EN     (IMG_UINT64_C(0X0000000000000001))


/*
    Register NN_SYS_CR_RTM_CTRL
*/
#define NN_SYS_CR_RTM_CTRL                                (0x1000U)
#define NN_SYS_CR_RTM_CTRL_MASKFULL                       (IMG_UINT64_C(0x00000000C0000FF8))
#define NN_SYS_CR_RTM_CTRL_RTM_ENABLE_SHIFT               (31U)
#define NN_SYS_CR_RTM_CTRL_RTM_ENABLE_CLRMSK              (0X7FFFFFFFU)
#define NN_SYS_CR_RTM_CTRL_RTM_ENABLE_EN                  (0X80000000U)
#define NN_SYS_CR_RTM_CTRL_RTM_CHECK_SHIFT                (30U)
#define NN_SYS_CR_RTM_CTRL_RTM_CHECK_CLRMSK               (0XBFFFFFFFU)
#define NN_SYS_CR_RTM_CTRL_RTM_CHECK_EN                   (0X40000000U)
#define NN_SYS_CR_RTM_CTRL_RTM_SELECTOR_SHIFT             (3U)
#define NN_SYS_CR_RTM_CTRL_RTM_SELECTOR_CLRMSK            (0XFFFFF007U)


/*
    Register NN_SYS_CR_RTM_DATA
*/
#define NN_SYS_CR_RTM_DATA                                (0x1008U)
#define NN_SYS_CR_RTM_DATA_MASKFULL                       (IMG_UINT64_C(0x00000000FFFFFFFF))
#define NN_SYS_CR_RTM_DATA_RTM_DATA_SHIFT                 (0U)
#define NN_SYS_CR_RTM_DATA_RTM_DATA_CLRMSK                (00000000U)


/*
    Register NN_SYS_CR_SOCIF_BUS_UNTRUSTED
*/
#define NN_SYS_CR_SOCIF_BUS_UNTRUSTED                     (0x1A000U)
#define NN_SYS_CR_SOCIF_BUS_UNTRUSTED_MASKFULL            (IMG_UINT64_C(0xFFFFFFFFFFFFFFFF))
#define NN_SYS_CR_SOCIF_BUS_UNTRUSTED_VALUE_SHIFT         (0U)
#define NN_SYS_CR_SOCIF_BUS_UNTRUSTED_VALUE_CLRMSK        (IMG_UINT64_C(0000000000000000))


/*
    Register NN_SYS_CR_SOCIF_BUS_SECURE
*/
#define NN_SYS_CR_SOCIF_BUS_SECURE                        (0x1A100U)
#define NN_SYS_CR_SOCIF_BUS_SECURE_MASKFULL               (IMG_UINT64_C(0x0000000000000001))
#define NN_SYS_CR_SOCIF_BUS_SECURE_ENABLE_SHIFT           (0U)
#define NN_SYS_CR_SOCIF_BUS_SECURE_ENABLE_CLRMSK          (0XFFFFFFFEU)
#define NN_SYS_CR_SOCIF_BUS_SECURE_ENABLE_EN              (0X00000001U)


#endif /* _NN_SYS_CR_GYRUS_H_ */

/*****************************************************************************
 End of file (nn_sys_cr_gyrus.h)
*****************************************************************************/

