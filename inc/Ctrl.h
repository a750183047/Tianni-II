#ifndef CTRL_H_
#define CRTL_H_

#include "includes.h"


/**********************
 * PID
 *********************/

#define  KPPLUSMAX      (170)
#define  KPNEGATIVEMAX  (-170)
#define  KIPLUSMAX      (170)
#define  KINEGATIVEMAX  (-170)
#define  KDPLUSMAX      (170)
#define  KDNEGATIVEMAX  (-170)
#define  KWPLUSMAX      (170)
#define  KWNEGATIVEMAX  (-170)
#define  KOUPLUSMAX     (5000)


#define  DUTY_MAX        170
#define  DUTY_MIN        -170 


void readencode(void);
void  ctrls(void);


void speedCtrl(void); //ËÙ¶È¿ØÖÆ


#endif







