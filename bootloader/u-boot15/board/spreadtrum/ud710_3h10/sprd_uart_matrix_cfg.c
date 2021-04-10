#include <asm/io.h>
#include <asm/arch/pinmap.h>
#include <hw_mux_cfg.h>

#define PIN_UART_MATRIX_MTX_CFG_VALUE	(0x06010806)
#define PIN_UART_MATRIX_MTX_CFG1_VALUE	(0x0000002B)
/* uart port mux*/
#define UART_INFO_SYS_SEL_MASK4	(BIT_0 | BIT_1 | BIT_2 | BIT_3)
#define UART_INFO_SYS_SEL_MASK3	(BIT_0 | BIT_1 | BIT_2)
#define UART_INFO1_SHIFT		3
#define UART_INFO2_SHIFT		9
#define UART_INFO3_SHIFT		15
#define UART_INFO4_SHIFT		19
#define UART_INFO5_SHIFT		23
#define UART_INFO6_SHIFT		26

#define UART_INFO7_SHIFT		0
#define UART_INFO8_SHIFT		4

#define BITS_UART_INF0_SYS_SEL(_x_)	(( _x_ ) & UART_INFO_SYS_SEL_MASK3)
#define BITS_UART_INF1_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO1_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF2_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO2_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF3_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO3_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF4_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO4_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF5_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO5_SHIFT ) & UART_INFO_SYS_SEL_MASK3)
#define BITS_UART_INF6_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO6_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF7_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO7_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF8_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO8_SHIFT ) & UART_INFO_SYS_SEL_MASK4)

#define UART_MATRIX_MTX_CFG(u0, u1, u2, u3, u4, u5, u6) \
	((u0) | ((u1) << UART_INFO1_SHIFT) | ((u2) << UART_INFO2_SHIFT) | ((u3) << UART_INFO3_SHIFT) | \
	((u4) << UART_INFO4_SHIFT) | ((u5) << UART_INFO5_SHIFT) | ((u6) << UART_INFO6_SHIFT))
#define UART_MATRIX_MTX_CFG1(u7, u8) \
	((u7) | ((u8) << UART_INFO8_SHIFT))

volatile pin_mux uport = {
	.magic_header = SPRD_MAGIC_HEADER,
	.uart_port_num = 9,
	.version = SPRD_UART_MUX_VERSION,
	.port = {
			{
				.index = 0,
				.reg = BITS_UART_INF0_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 8,
				.name = {
					"ap_uart0", "pubcp_uart0", "ltedsp_uart0", "ltedsp_uart1",
					"cm4_uart0", "cm4_uart1", "auddsp_uart0", "pubcp_uart1",
				},
			},
			{
				.index = 1,
				.reg = BITS_UART_INF1_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 11,
				.name = {
					"ap_uart1", "ap_uart0", "ap_uart2", "pubcp_uart0",
					"tgdsp_uart0", "ltedsp_uart0", "ltedsp_uart1",
					"cm4_uart0", "cm4_uart1", "auddsp_uart0", "pubcp_uart1",
				},
			},
			{
				.index = 2,
				.reg = BITS_UART_INF2_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 11,
				.name = {
					"ap_uart2", "ap_uart1", "ap_uart0", "cm4_uart0",
					"pubcp_uart0", "tgdsp_uart0", "ltedsp_uart0",
					"ltedsp_uart1", "cm4_uart1", "auddsp_uart0", "pubcp_uart1",
				},
			},
			{
				.index = 3,
				.reg = BITS_UART_INF3_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 12,
				.name = {
					"wtlcp_wci2", "tgdsp_uart0", "ltedsp_uart0", "ltedsp_uart1",
					"cm4_uart0", "pubcp_uart0", "cm4_uart1", "auddsp_uart0",
					"ap_uart0", "ap_uart1", "ap_uart2", "pubcp_uart1",
				},
			},
			{
				.index = 4,
				.reg = BITS_UART_INF4_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 11,
				.name = {
					"ap_uart0", "tgdsp_uart0", "ltedsp_uart0", "ltedsp_uart1",
					"pubcp_uart0", "cm4_uart0", "cm4_uart1", "auddsp_uart0",
					"ap_uart1", "ap_uart2", "pubcp_uart1",
				},
			},
			{
				.index = 5,
				.reg = BITS_UART_INF5_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 8,
				.name = {
					"ap_uart1", "ltedsp_uart0", "ltedsp_uart1", "wtlcp_wci2",
					"cm4_uart0", "cm4_uart1", "pubcp_uart1", "auddsp_uart0",
				},
			},
			{
				.index= 6,
				.reg = BITS_UART_INF6_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 12,
				.name = {
					"pubcp_uart0", "tgdsp_uart0", "ltedsp_uart0", "ltedsp_uart1",
					"auddsp_uart0", "wtlcp_wci2", "cm4_uart0", "cm4_uart1",
					"ap_uart0", "ap_uart1", "ap_uart2", "pubcp_uart1",
				},
			},
			{
				.index = 7,
				.reg = BITS_UART_INF7_SYS_SEL(PIN_UART_MATRIX_MTX_CFG1_VALUE),
				.select = 12,
				.name = {
					"pubcp_uart0", "tgdsp_uart0", "ltedsp_uart0", "ltedsp_uart1",
					"auddsp_uart0", "wtlcp_wci2", "cm4_uart0", "cm4_uart1",
					"ap_uart0", "ap_uart1", "ap_uart2", "pubcp_uart1",
				},
			},
			{
				.index = 8,
				.reg = BITS_UART_INF8_SYS_SEL(PIN_UART_MATRIX_MTX_CFG1_VALUE),
				.select = 12,
				.name = {
					"ap_uart0", "ap_uart1", "ap_uart2", "pubcp_uart0", "pubcp_uart1",
					"tgdsp_uart0", "ltedsp_uart0", "ltedsp_uart1", "auddsp_uart0",
					"wtlcp_wci2", "cm4_uart0", "cm4_uart1",
				},
			},
		},
	.magic_end = SPRD_MAGIC_END,
};

void pin_uart_port_cfg(void)
{
	pin_uart_port_sel_t *up = uport.port;
	__raw_writel(UART_MATRIX_MTX_CFG(up[0].reg, up[1].reg, up[2].reg,
					up[3].reg, up[4].reg, up[5].reg,
					up[6].reg), CTL_PIN_BASE + REG_PIN_UART_MATRIX_MTX_CFG );
	__raw_writel(UART_MATRIX_MTX_CFG1(up[7].reg, up[8].reg),
					CTL_PIN_BASE + REG_PIN_UART_MATRIX_MTX_CFG1 );
}
