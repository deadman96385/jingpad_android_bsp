#ifndef FDL_COMMAND_H
#define FDL_COMMAND_H

#include "dl_engine.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cpluslus */

/******************************************************************************
 * sys_connect
 ******************************************************************************/
int sys_connect(PACKET_T *packet, void *arg);

/******************************************************************************
 * data_start
 ******************************************************************************/
int data_start(PACKET_T *packet, void *arg);

/******************************************************************************
 * data_midst
 ******************************************************************************/
int data_midst(PACKET_T *packet, void *arg);

/******************************************************************************
 * data_end
 ******************************************************************************/
int data_end(PACKET_T *packet, void *arg);

/******************************************************************************
 * data_exec
 ******************************************************************************/
int data_exec(PACKET_T *packet, void *arg);

/******************************************************************************
 * set_baudrate
 ******************************************************************************/
int set_baudrate(PACKET_T *packet, void *arg);

/******************************************************************************
 * set charge flag
 * ****************************************************************************/
int set_chg_flag(PACKET_T *packet, void *arg);

/******************************************************************************
 * verify total ddr
 * ****************************************************************************/
int ddr_verify_start(PACKET_T *packet, void *arg);

/******************************************************************************
* ddr selfrefresh test
 * ****************************************************************************/
int ddr_sr_test_start(PACKET_T *packet, void *arg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FDL_COMMAND_H */
