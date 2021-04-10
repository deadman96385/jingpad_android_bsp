#ifndef CHIP_ID_H
#define CHIP_ID_H

#define ISHA		0x69536861
#define RKL2		0x726B4C32
#define IWHA		0x69576861
#define LE2		0x6C653200
#define PIKE		0x50696B65
#define TWO		0x32000000
#define SHAR		0x53686172
#define KL2		0x6B4C3200
#define	SHARKLC		0x96301000
#define KLE		0x6B4C6500	//TODO:the spec is KL2
#define KLS		0x6B4C5300
#define KLJ1		0x6B4C4A31
#define TSHARK2		0x8730C000
#define TSHARK3		0x8730D000
#define WHAL		0x5768616C
#define E2		0x65320000
#define KLT8		0x6B4C5438
#define NEMO		0x4E656D6F
#define G		0x47000000

enum chip_type{
	IWHALE2 = 0,
	ISHARKL2,
	PIKE2,
	SHARKL2,
	SRKLC,
	SHARKLE,
	SHARKLS,
	TSRK2,
	TSRK3,
	WHALE2,
	SHARKLT8,
	NEMOG,
	SHARKLJ1,
	CHIP_TYPE_MAX
};

struct chipid{
	uint32_t chipid_0;
	uint32_t chipid_1;
	uint32_t ver_id;
	char* name;
};


struct chipid chipid[CHIP_TYPE_MAX] = {
	{LE2,IWHA,0,"iwhale2"},
	{RKL2,ISHA, 0,"isharkl2"},
	{TWO,PIKE,0,"pike2"},
	{KL2,SHAR,0,"sharkl2"},
	{SHARKLC,0,0,"sharklc"},
	{KLE,SHAR,0,"sharkle"},
	{KLS,SHAR,0,"sharkls"},
	{TSHARK2,0,0,"Tshark2"},
	{TSHARK3,0,0,"Tshark3"},
	{E2,WHAL,0,"whale2"},
	{KLT8,SHAR,0,"sharklT8"},
	{G,NEMO,0,"NEMOG"},
	{KLJ1,SHAR,0,"sharklj1"},
};
extern void sprd_get_chipid(void);
extern uint32_t sprd_get_chipid_h(void);
extern uint32_t sprd_get_chipid_l(void);
extern uint32_t sprd_get_chip_version(void);
#endif
