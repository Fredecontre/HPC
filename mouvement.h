#ifndef __MOUVEMENT_H__
#define __MOUVEMENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "nrc2.h"

#define VMIN 1
#define VMAX 254
#define N0 2
#define WHITE 255

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void initialisation(uint8**I, uint8**V, uint8**M,int nrl, int nrh, int ncl, int nch);
uint8** sigma_delta(uint8**I_t, uint8**V_t, uint8**M_t,uint8**V_t_1, uint8**M_t_1, int nrl, int nrh, int ncl, int nch);
void initialisation_SIMD(uint8**I, uint8**V, uint8**M,int nrl, int nrh, int ncl, int nch);
uint8** sigma_delta_SIMD(uint8**I_t, uint8**V_t, uint8**M_t,uint8**V_t_1, uint8**M_t_1, int nrl, int nrh, int ncl, int nch);

#endif
