#ifndef __AS6480_H__
#define __AS6480_H__
extern bool as6480_switch_to_usb(void) ;
extern bool as6480_switch_to_headset(void);
extern bool as6480_swap_gnd_mic(void);
extern bool as6480_switch_to_off(void);
extern int as6480_get_switch_mode(void);
#endif
