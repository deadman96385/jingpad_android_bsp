#include "debug.h"

#ifdef DDRC_BR_DEBUG
#include "ddrc_r1p1.h"
#include "ddr_common.h"

#define BR_DEBUG_LOG_EN

#define RX_BUF_MAX_SIZE 2000
char uart_rx_buf[RX_BUF_MAX_SIZE];
uint32 g_uart_rx_buf_index = 0;
uint32 g_uart_rx_buf_index_avild = 0;
void br_debug_uart_put(char *string)
{
    #ifdef BR_DEBUG_LOG_EN
    serial_puts(string);
    #endif
}

char * br_debug_uart_get(void)
{
    #ifdef BR_DEBUG_LOG_EN
    char tmp = 0;
    g_uart_rx_buf_index_avild = g_uart_rx_buf_index;
    do{
        tmp = (serial_getc());
        uart_rx_buf[g_uart_rx_buf_index++] = tmp;
    }while('\r' != tmp);
    uart_rx_buf[g_uart_rx_buf_index-1] = '\0';
    return &(uart_rx_buf[g_uart_rx_buf_index_avild]);
    #endif
}

void br_debug_interface(void)
{
    char * uart_string = 0;
    char * ptr = 0;
    uint32 reg_addr = 0;
    uint32 reg_data = 0;
    g_uart_rx_buf_index = 0;
    br_debug_uart_put("Please input address in hex");
    uart_string = br_debug_uart_get();
    reg_addr = strtoul(uart_string, &ptr, 16);
    br_debug_uart_put("User's input: \r\n");
    br_debug_uart_put(uart_string);
    br_debug_uart_put("Please input value in hex");
    uart_string = br_debug_uart_get();
    reg_addr = strtoul(uart_string, &ptr, 16);
    br_debug_uart_put("User's input: \r\n");
    br_debug_uart_put(uart_string);
    REG32(reg_addr) = reg_data;
    br_debug_uart_put("modify done.\r\n");

}

void reg_modify_before_initial(void)
{
    char * uart_string = 0;
    br_debug_uart_put("Wile you want modify some registers' vaule, before initial? N will not modify, others will modify .\r\n");
    uart_string = br_debug_uart_get();
	br_debug_interface();
}

void reg_modify_before_bist(void)
{
    char * uart_string = 0;
    br_debug_uart_put("Wile you want modify some registers' vaule, before bist test? N will not modify, others will modify .\r\n");
    uart_string = br_debug_uart_get();
	br_debug_interface();
}
#else
void reg_modify_before_initial(void)
{}
void reg_modify_before_bist(void)
{}

#endif


