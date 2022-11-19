#ifndef __MORPHO_H__
#define __MORPHO_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "nrc2.h"
#include <mipp.h>

typedef struct {
    
    uint8**E_t;
    int nrl; 
    int nrh; 
    int ncl; 
    int nch;
    int num_image;
} args_thread;

uint8** dilatation(uint8**E_t, int nrl, int nrh, int ncl, int nch);
uint8** erosion(uint8**E_t, int nrl, int nrh, int ncl, int nch);
void* erosion_thread(void*arguments);
uint8** dilatation_SIMD(uint8**E_t, int nrl, int nrh, int ncl, int nch);
uint8** erosion_SIMD(uint8**E_t, int nrl, int nrh, int ncl, int nch);
uint8** erosion_dilatation(uint8**E_t, int nrl, int nrh, int ncl, int nch);
uint8** erosion_dilatation_SIMD(uint8**E_t, int nrl, int nrh, int ncl, int nch);
void* morphologies_image(void*arguments);
#endif
