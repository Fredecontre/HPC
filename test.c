#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "nrc2.h"
#include "mouvement.h"
#include "morpho.h"
#include <pthread.h>
#define NUM_THREADS 200

void init_tabs(uint8*** E_t_bis,int nrl, int nrh, int ncl, int nch){
	for(int k = 0 ; k < NUM_THREADS ; k++){
		E_t_bis[k]=ui8matrix(nrl, nrh, ncl, nch);
		zero_ui8matrix(E_t_bis[k], nrl, nrh, ncl, nch);
	}

}


int main(){

	int nrl, nrh, ncl, nch;
	char nom_image[NUM_THREADS][250];
	char nom_image_0[250] = "car3/car_3000.pgm";
	char indice_i[16];
	char indice_i_temp[16];
	char nom_output[NUM_THREADS][16];
	char nom_output_0[16] = "output000.pgm";
	double time_spent = 0.0;
	clock_t begin = clock();
	args_thread *arguments = (args_thread *)malloc(NUM_THREADS*sizeof(args_thread));


	//Création threads
	pthread_t threads[NUM_THREADS];

	uint8** I_t = LoadPGM_ui8matrix(nom_image_0, &nrl, &nrh, &ncl, &nch);
	

	uint8*** E_t_bis = (uint8***)malloc(sizeof(uint8**)*NUM_THREADS);
	init_tabs(E_t_bis,nrl, nrh, ncl, nch);

	uint8** E_t = ui8matrix(nrl, nrh, ncl, nch);
	zero_ui8matrix(E_t, nrl, nrh, ncl, nch);

	uint8** M_t_1 = ui8matrix(nrl, nrh, ncl, nch);
	zero_ui8matrix(M_t_1, nrl, nrh, ncl, nch);

	uint8** M_t = ui8matrix(nrl, nrh, ncl, nch);
	zero_ui8matrix(M_t, nrl, nrh, ncl, nch);

	uint8** V_t_1 = ui8matrix(nrl, nrh, ncl, nch);
	zero_ui8matrix(V_t_1, nrl, nrh, ncl, nch);

	uint8** V_t = ui8matrix(nrl, nrh, ncl, nch);
	zero_ui8matrix(V_t, nrl, nrh, ncl, nch);

	initialisation_SIMD(I_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);
	//initialisation(I_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);

	E_t = sigma_delta_SIMD(I_t, V_t, M_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);
	


	E_t =  erosion(E_t,nrl, nrh, ncl, nch);
	E_t =  dilatation(E_t,nrl, nrh, ncl, nch);
	//E_t =  erosion_dilatation(E_t,nrl, nrh, ncl, nch);
	E_t =  dilatation(E_t,nrl, nrh, ncl, nch);
	E_t =  erosion(E_t,nrl, nrh, ncl, nch);

	SavePGM_ui8matrix(E_t, nrl, nrh, ncl, nch, nom_output_0);

	//E_t_bis[0] = E_t;


	for(uint16_t i = 1; i < 200 - NUM_THREADS; i+=NUM_THREADS){
		//Mouvement sur images
		for(int k = 0 ; k < NUM_THREADS ; k++){
			sprintf(nom_image[k],"car3/car_3%03d.pgm",i+k);
			sprintf(nom_output[k],"output%03d.pgm",i+k);
			I_t = LoadPGM_ui8matrix(nom_image[k], &nrl, &nrh, &ncl, &nch);
			E_t_bis[k] = sigma_delta(I_t, V_t, M_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);

		}
		
		for(int k = 0 ; k < NUM_THREADS ; k++){
			arguments[k].E_t = E_t_bis[k];
			arguments[k].nrl = nrl;
			arguments[k].nrh = nrh;
			arguments[k].ncl = ncl;
			arguments[k].nch = nch;
		}

		for(int k = 0 ; k < NUM_THREADS ; k++){
			pthread_create(&threads[k], NULL,morphologies_image, &arguments[k]);
			
		}

		for(int k = 0 ; k < NUM_THREADS ; k++){
			pthread_join(threads[k],NULL);
			
		}

		for(int k = 0 ; k < NUM_THREADS ; k++){
			SavePGM_ui8matrix(arguments[k].E_t, nrl, nrh, ncl, nch, nom_output[k]);
			
		}

	}
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);

	return 0;
}