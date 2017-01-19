#ifndef __POLYFIT__H
#define __POLYFIT__H

#ifdef __cplusplus
 extern "C" {
#endif 
#include "stdio.h"
#include "stdint.h"

int polyfit(const double* BufferX, const double* BufferY, int Amount, int SizeSrc, double* ParaResK);


#ifdef __cplusplus
}
#endif
#endif