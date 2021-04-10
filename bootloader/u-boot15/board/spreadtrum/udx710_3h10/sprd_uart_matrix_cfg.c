#include <asm/io.h>
#include <asm/arch/pinmap.h>
#include <hw_mux_cfg.h>

#define PIN_UART_MATRIX_MTX_CFG_VALUE	(0x16A81C20)
/* uart port mux*/
#define UART_INFO_SYS_SEL_MASK4	(BIT_0 | BIT_1 | BIT_2 | BIT_3)
#define UART_INFO_SYS_SEL_MASK1 (BIT_0)
#define UART_INFO1_SHIFT		4
#define UART_INFO2_SHIFT		10
#define UART_INFO3_SHIFT		16
#define UART_INFO4_SHIFT		20
#define UART_INFO5_SHIFT		24
#define UART_INFO6_SHIFT		28

#define BITS_UART_INF0_SYS_SEL(_x_)	(( _x_ ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF1_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO1_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF2_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO2_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF3_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO3_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF4_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO4_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF5_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO5_SHIFT ) & UART_INFO_SYS_SEL_MASK4)
#define BITS_UART_INF6_SYS_SEL(_x_)	((( _x_ ) >> UART_INFO6_SHIFT ) & UART_INFO_SYS_SEL_MASK1)

#define UART_MATRIX_MTX_CFG(u0, u1, u2, u3, u4, u5, u6) \
	((u0) | ((u1) << UART_INFO1_SHIFT) | ((u2) << UART_INFO2_SHIFT) | ((u3) << UART_INFO3_SHIFT) | \
	((u4) << UART_INFO4_SHIFT) | ((u5) << UART_INFO5_SHIFT) | ((u6) << UART_INFO6_SHIFT))

volatile pin_mux uport = {
	.magic_header = SPRD_MAGIC_HEADER,
	.uart_port_num = 7,
	.version = SPRD_UART_MUX_VERSION,
	.port = {
			{
				.index = 0,
				.reg = BITS_UART_INF0_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 11,
				.name = {
					"ap_uart0", "cm4_uart", "ps_cp_uart0", "v3_ps_uart0",
					"v3_phy_uart0", "v3_phy_wci2", "auddsp_uart0",
					"nr_cp_uart0", "nr_cp_uart1", "nr_cp_uart2",
					"nr_cp_wci2_3",
				},
			},
			{
				.index = 1,
				.reg = BITS_UART_INF1_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 11,
				.name = {
					"ap_uart0", "cm4_uart", "ps_cp_uart0", "v3_ps_uart0",
					"v3_phy_uart0", "v3_phy_wci2", "auddsp_uart0",
					"nr_cp_uart0", "nr_cp_uart1", "nr_cp_uart2",
					"nr_cp_wci2_3",
				},
			},
			{
				.index = 2,
				.reg = BITS_UART_INF2_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 11,
				.name = {
					"ap_uart0", "cm4_uart", "ps_cp_uart0", "v3_ps_uart0",
					"v3_phy_uart0", "v3_phy_wci2", "auddsp_uart0",
					"nr_cp_uart0", "nr_cp_uart1", "nr_cp_uart2",
					"nr_cp_wci2_3",
				},
			},
			{
				.index = 3,
				.reg = BITS_UART_INF3_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 11,
				.name = {
					"ap_uart0", "cm4_uart", "ps_cp_uart0", "v3_ps_uart0",
					"v3_phy_uart0", "v3_phy_wci2", "auddsp_uart0",
					"nr_cp_uart0", "nr_cp_uart1", "nr_cp_uart2",
					"nr_cp_wci2_3",
				},
			},
			{
				.index = 4,
				.reg = BITS_UART_INF4_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 11,
				.name = {
					"ap_uart0", "cm4_uart", "ps_cp_uart0", "v3_ps_uart0",
					"v3_phy_uart0", "v3_phy_wci2", "auddsp_uart0",
					"nr_cp_uart0", "nr_cp_uart1", "nr_cp_uart2",
					"nr_cp_wci2_3",
				},
			},
			{
				.index = 5,
				.reg = BITS_UART_INF5_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 11,
				.name = {
					"ap_uart0", "cm4_uart", "ps_cp_uart0", "v3_ps_uart0",
					"v3_phy_uart0", "v3_phy_wci2", "auddsp_uart0",
					"nr_cp_uart0", "nr_cp_uart1", "nr_cp_uart2",
					"nr_cp_wci2_3",
				},
			},
			{
				.index= 6,
				.reg = BITS_UART_INF6_SYS_SEL(PIN_UART_MATRIX_MTX_CFG_VALUE),
				.select = 2,
				.name = {
					"ap_uart0", "cm4_uart",
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
}
