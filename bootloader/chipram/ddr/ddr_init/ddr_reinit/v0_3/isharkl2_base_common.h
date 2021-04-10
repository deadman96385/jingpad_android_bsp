
//typedef unsigned int				uint32;

//#define REG32(_x_)	(*(volatile uint32*)(_x_))
//#define REG32(_x_)	(*(volatile uint32*)((uint64)(_x_)))


#define BOOLEAN          unsigned char
#define TRUE				1
#define FALSE			0
#define NULL        		0


#define AON_PMU_APB_BASE				0xe42b0000
#define AON_COM_PMU_APB_BASE			0xe42c0000
#define AON_PRE_DIV_CLK_GEN_BASE		0xe42d0000
#define AON_CLK_CORE_BASE				0xe42d0200
#define AON_APB_CTL_BASE                    	0xe42e0000
#define PUB0_APB_RF_PUB0_BASE			0xc0010000
#define BUSMON_TIMER_BASE				0xe44d0000


#define	CANDS_CTL_REG_BASE			0xc0000000
#define	CANDS_PI_REG_BASE				0xc0000800
#define 	CANDS_PHY_REG_BASE			0xc0002000


#define	CANDS_CTL0_(i)				(CANDS_CTL_REG_BASE + i*4)
#define	CANDS_PI0_(i)				(CANDS_PI_REG_BASE + i*4)
#define	CANDS_PHY0_(i)				(CANDS_PHY_REG_BASE + i*4)


