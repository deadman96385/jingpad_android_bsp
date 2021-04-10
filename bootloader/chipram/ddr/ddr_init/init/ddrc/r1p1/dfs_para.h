
#ifndef DFS_PARA_H
#define DFS_PARA_H
#include "roc1_dfs.h"

//ratio clk_mode ratio_d2
static DFS_PARA para_256_pll = {256,0x4,0x1,0x9};
static DFS_PARA para_256_dll = {256,0x4,0x2,0x9};
static DFS_PARA para_256_bypass = {256,0x4,0x0,0x9};

static DFS_PARA para_384_pll = {384,0x5,0x1,0x9};
static DFS_PARA para_384_dll = {384,0x5,0x2,0x9};
static DFS_PARA para_384_bypass = {384,0x5,0x0,0x9};

static DFS_PARA para_667_pll = {667,0x8,0x1,0x4};
static DFS_PARA para_667_dll = {667,0x0,0x2,0x9};
static DFS_PARA para_667_bypass = {667,0x0,0x0,0x9};

static DFS_PARA para_768_pll = {768,0x5,0x1,0x4};
static DFS_PARA para_768_dll = {768,0x6,0x2,0xa};
static DFS_PARA para_768_bypass = {768,0x6,0x0,0xa};

static DFS_PARA para_1024 = {1024,0x4,0x1,0x0};

static DFS_PARA para_1333 = {1333,0x8,0x1,0x0};

static DFS_PARA para_1536 = {1536,0x5,0x1,0x0};

static DFS_PARA para_1866 = {1866,0x1,0x1,0x0};

static DFS_PARA *dfs_para_init[DFS_SEL] =
{
	&para_256_bypass,
	&para_384_bypass,
	&para_667_bypass,
	&para_768_pll,
	&para_1024,
	&para_1333,
	&para_1536,
	&para_1866
};
#endif
