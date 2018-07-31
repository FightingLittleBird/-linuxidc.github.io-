#ifndef __GCODE_H
#define __GCODE_H

#include "MK_A9.h"

#define MAX_INT_DIGITS 12

#define X_PARA 0 				
#define Y_PARA 1
#define Z_PARA 2 
#define A_PARA 3 

u8 gc_execute_line(u8 *line);

#endif
