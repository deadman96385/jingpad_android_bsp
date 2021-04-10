/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "sprd_dphy.h"

#define REF_CLOCK		(26000)
/* Reference clock frequency divided by Input Frequency Division Ratio LIMITS */
#define DPHY_DIV_UPPER_LIMIT	(40000)
#define DPHY_DIV_LOWER_LIMIT	(1000)

struct pll_ranges {
	u32 freq;  /* upper margin of frequency range */
	u8 hs_freq; /* hsfreqrange */
	u8 vco_range; /* vcorange */
};

struct pll_bandwidth {
	u32 loop_div; /* upper limit of loop divider range */
	u8 cp_current; /* icpctrl */
	u8 lpf_resistor; /* lpfctrl */
};

static const struct pll_ranges ranges[] = {
	{90, 0x00, 0x01}, {100, 0x10, 0x01}, {110, 0x20, 0x01},
	{125, 0x01, 0x01}, {140, 0x11, 0x01}, {150, 0x21, 0x01},
	{160, 0x02, 0x01}, {180, 0x12, 0x03}, {200, 0x22, 0x03},
	{210, 0x03, 0x03}, {240, 0x13, 0x03}, {250, 0x23, 0x03},
	{270, 0x04, 0x07}, {300, 0x14, 0x07}, {330, 0x24, 0x07},
	{360, 0x15, 0x07}, {400, 0x25, 0x07}, {450, 0x06, 0x07},
	{500, 0x16, 0x07}, {550, 0x07, 0x0f}, {600, 0x17, 0x0f},
	{650, 0x08, 0x0f}, {700, 0x18, 0x0f}, {750, 0x09, 0x0f},
	{800, 0x19, 0x0f}, {850, 0x0A, 0x0f}, {900, 0x1A, 0x0f},
	{950, 0x2A, 0x0f}, {1000, 0x3A, 0x0f}
};

static const struct pll_bandwidth loop_bandwidth[] = {
	{32, 0x06, 0x10}, {64, 0x06, 0x10}, {128, 0x0C, 0x08},
	{256, 0x04, 0x04}, {512, 0x00, 0x01}, {768, 0x01, 0x01},
	{1000, 0x02, 0x01}
};

static int dphy_pll_config(struct dphy_context *ctx)
{
	u32 loop_divider = 0; /* (M) */
	u32 input_divider = 1; /* (N) */
	u8 data;
	u8 i, j;
	int flag = 0;
	u32 output_freq = ctx->freq;
	struct regmap *regmap = ctx->regmap;

	/* find M and N dividers */
	for (input_divider = 1 + (REF_CLOCK / DPHY_DIV_UPPER_LIMIT);
	    ((REF_CLOCK / input_divider) >= DPHY_DIV_LOWER_LIMIT) && (!flag);
	    input_divider++) {
		/* here the >= DPHY_DIV_LOWER_LIMIT is a phy constraint, formula should be above 1 MHz */
		if (((output_freq * input_divider) % (REF_CLOCK )) == 0) {
			/* values found */
			loop_divider = ((output_freq * input_divider) / (REF_CLOCK ));
			if (loop_divider >= 12)
				flag = 1;
		}
	}

	if ((!flag) || ((REF_CLOCK / input_divider) < DPHY_DIV_LOWER_LIMIT)) {
		/* no exact value found in previous for loop */
		/* this solution is not favourable as jitter would be maximum */
		loop_divider = output_freq / DPHY_DIV_LOWER_LIMIT;
		input_divider = REF_CLOCK / DPHY_DIV_LOWER_LIMIT;
	} else {
		/* variable was incremented before exiting the loop */
		input_divider--;
	}

	/* find bandwidth */
	for (i = 0; i < ARRAY_SIZE(loop_bandwidth); i++) {
		if (loop_divider <= loop_bandwidth[i].loop_div)
			break;
	}
	if (i == ARRAY_SIZE(loop_bandwidth)) {
		pr_err("dphy bandwidth is out of range\n");
		return -1;
	}
	pr_info("Gen1 D-PHY: Approximated Frequency: %d KHz\n",
		(loop_divider * (REF_CLOCK / input_divider)));

	/* find ranges */
	for (j = 0; j < ARRAY_SIZE(ranges); j++) {
		if((output_freq / 1000) <= ranges[j].freq)
			break;
	}
	if (j == ARRAY_SIZE(ranges)) {
		pr_err("dphy freq is out of range\n");
		return -1;
	}

	/* setup digital part */
	/* hs frequency range [7]|[6:1]|[0]*/
	data = (0 << 7) | (ranges[j].hs_freq << 1) | 0;
	regmap_write(regmap, 0x44, data);

	/* setup PLL */
	/* vco range  [7]|[6:3]|[2:1]|[0] */
	data = (1 << 7) | (ranges[j].vco_range << 3) | (0 << 1) | 0;
//	regmap_write(regmap, 0x10, data);

	/* PLL  reserved|Input divider control|Loop Divider Control|Post Divider Ratio [7:6]|[5]|[4]|[3:0] */
	/* post divider default = 0x03 - it is only used for clock out 2*/
	data = (0x00 << 6) | (0x01 << 5) | (0x01 << 4) | (0x03 << 0);
//	regmap_write(regmap, 0x19, data);

	/* PLL Lock bypass|charge pump current [7:4]|[3:0] */
	data = (0x00 << 4) | (loop_bandwidth[i].cp_current << 0);
//	regmap_write(regmap, 0x11, data);

	/* bypass CP default|bypass LPF default| LPF resistor [7]|[6]|[5:0] */
	data = (0x01 << 7) | (0x01 << 6) | (loop_bandwidth[i].lpf_resistor << 0);
//	regmap_write(regmap, 0x12, data);

	/* PLL input divider ratio [7:0] */
	data = input_divider - 1;
//	regmap_write(regmap, 0x17, data);

	/* short the delay time before BTA */
//	regmap_write(regmap, 0x07, 0x04);
	regmap_write(regmap, 0xB0, 0x01);
	regmap_write(regmap, 0x22, 0x8B);

	/* pll loop divider (code 0x18) takes 2 bytes (10 bits in data) */
	/* PLL loop divider ratio - index|reserved|feedback divider [7]|[6:5]|[4:0] */
	data = (u8)(loop_divider - 1);
	regmap_write(regmap, 0x18, data);
	data = (u8)(((1 << 7) | (loop_divider - 1) >> 5) & 0x1F);
	regmap_write(regmap, 0x18, data);

	return 0;
}

static int dphy_timing_config(struct dphy_context *ctx)
{
	struct regmap *regmap = ctx->regmap;

	/* clock lane lpx, about 52ns */
//	regmap_write(regmap, 0x60, 0x42);
	/* prepare time */
//	regmap_write(regmap, 0x61, 0x0);
	/* zero time */
//	regmap_write(regmap, 0x62, 0x0);
	/* data lane lpx, about 52ns */
//	regmap_write(regmap, 0x70, 0x42);
	/* prepare time */
//	regmap_write(regmap, 0x71, 0x0);
	/* zero time */
//	regmap_write(regmap, 0x72, 0x0);

	return 0;
}

#if 0
void mipi_dsih_dphy_write(dphy_t * instance, u8 address, u8 * data, u8 data_length)
{
	unsigned i = 0;
	if (data != 0)
	{
		/* set the TESTCLK input high in preparation to latch in the desired test mode */
		mipi_dsih_dphy_test_clock(instance, 1);
		/* set the desired test code in the input 8-bit bus TESTDIN[7:0] */
		mipi_dsih_dphy_test_data_in(instance, address);
		/* set TESTEN input high  */
		mipi_dsih_dphy_test_en(instance, 1);
		/* drive the TESTCLK input low; the falling edge captures the chosen test code into the transceiver */
		mipi_dsih_dphy_test_clock(instance, 0);
		/* set TESTEN input low to disable further test mode code latching  */
		mipi_dsih_dphy_test_en(instance, 0);
		/* start writing MSB first */
		for (i = data_length; i > 0; i--)
		{	/* set TESTDIN[7:0] to the desired test data appropriate to the chosen test mode */
			mipi_dsih_dphy_test_data_in(instance, data[i - 1]);
			/* pulse TESTCLK high to capture this test data into the macrocell; repeat these two steps as necessary */
			mipi_dsih_dphy_test_clock(instance, 1);
			mipi_dsih_dphy_test_clock(instance, 0);
		}
	}
}
#endif

static struct dphy_pll_ops dwc_mipi_dphy_bidir_4l_ops = {
	.pll_config = dphy_pll_config,
	.timing_config = dphy_timing_config,
};

struct dphy_pll_ops *dphy_pll_ops_attach(void)
{
	return &dwc_mipi_dphy_bidir_4l_ops;
}

