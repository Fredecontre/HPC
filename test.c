#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "nrc2.h"
#include "mouvement.h"
#include "morpho.h"
#include <pthread.h>
#define NUM_THREADS 4

void init_tabs(uint8*** E_t_bis,uint8*** I_t_bis,uint8*** V_t_bis,uint8*** M_t_bis,uint8*** V_t_1_bis,uint8*** M_t_1_bis,int nrl, int nrh, int ncl, int nch){
		E_t_bis = (uint8***)malloc(sizeof(uint8**)*NUM_THREADS);

		for(int k = 0 ; k < NUM_THREADS ; k++){
			E_t_bis[k]=ui8matrix(nrl, nrh, ncl, nch);
			/*I_t_bis[k]=ui8matrix(nrl, nrh, ncl, nch);
			V_t_bis[k]=ui8matrix(nrl, nrh, ncl, nch);
			M_t_1_bis[k]=ui8matrix(nrl, nrh, ncl, nch);
			V_t_1_bis[k]=ui8matrix(nrl, nrh, ncl, nch);
			M_t_bis[k]=ui8matrix(nrl, nrh, ncl, nch);*/

			zero_ui8matrix(E_t_bis[k], nrl, nrh, ncl, nch);
			/*zero_ui8matrix(V_t_bis[k], nrl, nrh, ncl, nch);
			zero_ui8matrix(M_t_bis[k], nrl, nrh, ncl, nch);
			zero_ui8matrix(I_t_bis[k], nrl, nrh, ncl, nch);
			zero_ui8matrix(V_t_1_bis[k], nrl, nrh, ncl, nch);
			zero_ui8matrix(M_t_1_bis[k], nrl, nrh, ncl, nch);*/

		}

}



// token thomas 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

//COMMANDE COMPIL g++ -o main main.c mouvement.c mouvement_SIMD.c morpho_SIMD.c morpho.c -Inrc2-master/include/ -Lnrc2-master/build/lib/ -IMIPP-master/src -lnrc -g
//COMMANDE COMPIL THOMAS gcc -o main main.c mouvement.c mouvement_SIMD.c morpho_SIMD.c morpho.c -Inrc2/include/ -Lnrc2/build/lib/ -lnrc -g

int main(){

	int nrl, nrh, ncl, nch;
	char nom_image[NUM_THREADS][250] ;
	char nom_image_0[250] = "car3/car_3000.pgm";
	//char nom_image[250] = "/home/rossi/Documents/HPC_Projet/car3/car_3";
	char indice_i[16];
	char indice_i_temp[16];
	char nom_output[NUM_THREADS][16];
	char nom_output_0[16] = "output000.pgm";
	double time_spent = 0.0;
	clock_t begin = clock();
	args_thread arguments[NUM_THREADS];
	uint8*** E_t_bis;
	uint8*** V_t_bis;
	uint8*** M_t_bis;
	uint8*** V_t_1_bis;
	uint8*** M_t_1_bis;
	uint8*** I_t_bis;
	init_tabs(E_t_bis,I_t_bis,V_t_bis,M_t_bis,V_t_1_bis,M_t_1_bis,nrl, nrh, ncl, nch);


	//Création threads
	pthread_t threads[NUM_THREADS];
	

	uint8** I_t = LoadPGM_ui8matrix(nom_image_0, &nrl, &nrh, &ncl, &nch);

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

	//initialisation_SIMD(I_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);
	initialisation(I_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);

	E_t = sigma_delta(I_t, V_t, M_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);
	//E_t = sigma_delta_SIMD(I_t, V_t, M_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);
	
	//pthread_create (&thread_dilatation1, NULL,dilatation, &arguments);
	//pthread_create (&thread_dilatation2, NULL,dilatation, &arguments);
	//pthread_create (&thread_erosion2, NULL,erosion, &arguments);
	
	//pthread_join (thread_erosion1, (void**)E_t);
	//pthread_join (thread_dilatation1, (void**)E_t);
	//pthread_join (thread_dilatation2, (void**)E_t);
	
	//morphologies_image(&arguments);
	//E_t=arguments.E_t;

	E_t =  erosion(E_t,nrl, nrh, ncl, nch);
	E_t =  dilatation(E_t,nrl, nrh, ncl, nch);
	//E_t =  erosion_dilatation(E_t,nrl, nrh, ncl, nch);
	E_t =  dilatation(E_t,nrl, nrh, ncl, nch);
	E_t =  erosion(E_t,nrl, nrh, ncl, nch);

	//pthread_join (thread_erosion2, (void**)E_t);

	SavePGM_ui8matrix(E_t, nrl, nrh, ncl, nch, nom_output_0);

	E_t_bis[0] = E_t;


	for(uint16_t i = 1; i < 200 ; i+NUM_THREADS){
		//sprintf(nom_image,"car3/car_3%03d.pgm",i);
		//sprintf(nom_output,"output%03d.pgm",i);
		/*memset(indice_i,0,16);
		memset(indice_i_temp,0,16);
		memset(nom_image,0,16);
		memset(nom_output,0,16);

		strcpy(nom_output,"output");
		strcpy(nom_image,"car3/car_3");
		//strcpy(nom_image,"/home/rossi/Documents/HPC_Projet/car3/car_3");
		
		if(i < 10){
			sprintf(indice_i,"%d",i); //Conversion en string
			strcpy(indice_i_temp,"00"); 
			strcat(indice_i_temp,indice_i);//Ajout des zéros
		}

		else if(i < 100){
			sprintf(indice_i,"%d",i); //Conversion en string
			strcpy(indice_i_temp,"0"); 
			strcat(indice_i_temp,indice_i);//Ajout des zéros
		}

		else{
			sprintf(indice_i_temp,"%d",i); //Conversion en string
		}
		strcat(nom_output,indice_i_temp);
		strcat(nom_image,indice_i_temp);
		strcat(nom_image,".pgm");
		strcat(nom_output,".pgm");*/

		for(int k = 0 ; k < NUM_THREADS ; k++){
			sprintf(nom_image[k],"car3/car_3%03d.pgm",i+k);
			sprintf(nom_output[k],"output%03d.pgm",i+k);


		}
		
		//I_t = LoadPGM_ui8matrix(nom_image, &nrl, &nrh, &ncl, &nch);

		for(int k = 0 ; k < NUM_THREADS ; k++){
			I_t_bis[k] = LoadPGM_ui8matrix(nom_image[k], &nrl, &nrh, &ncl, &nch);					
			E_t_bis[k] = sigma_delta(I_t_bis[k], V_t_bis[k], M_t_bis[k],V_t_1_bis[k], M_t_1_bis[k], nrl,  nrh,  ncl, nch);
		}

		
		//E_t = sigma_delta_SIMD(I_t, V_t, M_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);
		for(int k = 1 ; k < NUM_THREADS ; k++){
			arguments[k].E_t = E_t_bis[k];
		}

		for(int k = 0 ; k < NUM_THREADS ; k++){
			pthread_create(&threads[k], NULL,morphologies_image, &arguments[k]);
			
		}

		for(int k = 0 ; k < NUM_THREADS ; k++){
			pthread_join(threads[k],NULL);
			
		}
		/*for(uint16_t i = nrl ; i <=nrh; i++){
			for(uint16_t j = ncl ; j <= nch; j++){
				printf("%d ",E_t[i][j]);
			}
			printf("\n");
		}*/
		//pthread_join (thread_erosion1, (void**)E_t);
		/*E_t =  erosion(E_t,nrl, nrh, ncl, nch);
		E_t =  dilatation(E_t,nrl, nrh, ncl, nch);
		//E_t =  erosion_dilatation(E_t,nrl, nrh, ncl, nch);
		E_t =  dilatation(E_t,nrl, nrh, ncl, nch);
		
		//pthread_join(thread_erosion2, (void**)E_t);
		E_t =  erosion(E_t,nrl, nrh, ncl, nch);*/

		//arguments.E_t = E_t;

		//morphologies_image(&arguments);

		//SavePGM_ui8matrix(arguments.E_t, nrl, nrh, ncl, nch, nom_output);

		for(int k = 0 ; k < NUM_THREADS ; k++){
			SavePGM_ui8matrix(arguments[k].E_t, nrl, nrh, ncl, nch, nom_output[k]);
			
		}

	}
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);

	return 0;
}