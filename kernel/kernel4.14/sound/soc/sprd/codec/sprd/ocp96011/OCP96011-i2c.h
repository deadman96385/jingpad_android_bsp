#ifndef __OCP96011_H__
#define __OCP96011_H__
extern bool ocp96011_switch_to_usb(void) ;
extern bool ocp96011_switch_to_headset(void);
extern bool ocp96011_swap_gnd_mic(void);
extern bool ocp96011_switch_to_off(void);
extern int ocp96011_get_switch_mode(void);
extern bool ocp96011_swap_audio_sense(void);
#endif
