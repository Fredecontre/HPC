#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "nrc2.h"
#include "mouvement.h"
#include "morpho.h"

// token thomas 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

//COMMANDE COMPIL g++ -o main main.c mouvement.c mouvement_SIMD.c morpho_SIMD.c morpho.c -Inrc2-master/include/ -Lnrc2-master/build/lib/ -IMIPP-master/src -lnrc -g
//COMMANDE COMPIL THOMAS gcc -o main main.c mouvement.c mouvement_SIMD.c morpho_SIMD.c morpho.c -Inrc2/include/ -Lnrc2/build/lib/ -lnrc -g

int main(){

	int nrl, nrh, ncl, nch;
	char nom_image[250] = "/home/fredecontre/Bureau/HPC/Projet/HPC/car3/car_3";
	//char nom_image[250] = "/home/rossi/Documents/HPC_Projet/car3/car_3";
	char indice_i[16];
	char indice_i_temp[16];
	char nom_output[16] = "output";
	double time_spent = 0.0;
	clock_t begin = clock();

	uint8** I_t = LoadPGM_ui8matrix("/home/fredecontre/Bureau/HPC/Projet/HPC/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	//uint8** I_t = LoadPGM_ui8matrix("/home/rossi/Documents/HPC_Projet/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);

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

	//E_t = sigma_delta(I_t, V_t, M_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);
	E_t = sigma_delta_SIMD(I_t, V_t, M_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);

	E_t =  erosion(E_t,nrl, nrh, ncl, nch);
	E_t =  dilatation(E_t,nrl, nrh, ncl, nch);
	//E_t =  erosion_dilatation(E_t,nrl, nrh, ncl, nch);
	E_t =  dilatation(E_t,nrl, nrh, ncl, nch);
	E_t =  erosion(E_t,nrl, nrh, ncl, nch);
	SavePGM_ui8matrix(E_t, nrl, nrh, ncl, nch, "output000.pgm");

	for(uint16_t i = 1; i < 200 ; i++){
		memset(indice_i,0,16);
		memset(indice_i_temp,0,16);
		memset(nom_image,0,16);
		memset(nom_output,0,16);

		strcpy(nom_output,"output");
		strcpy(nom_image,"/home/fredecontre/Bureau/HPC/Projet/HPC/car3/car_3");
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
		strcat(nom_output,".pgm");

		I_t = LoadPGM_ui8matrix(nom_image, &nrl, &nrh, &ncl, &nch);
		//E_t = sigma_delta(I_t, V_t, M_t,V_t_1, M_t_1, nrl,  nrh,  ncl, nch);
		E_t = sigma_delta_SIMD(I_t, V_t, M_t, V_t_1, M_t_1, nrl, nrh, ncl, nch);
		
		E_t =  erosion(E_t,nrl, nrh, ncl, nch);
		E_t =  dilatation(E_t,nrl, nrh, ncl, nch);
		//E_t =  erosion_dilatation(E_t,nrl, nrh, ncl, nch);
		E_t =  dilatation(E_t,nrl, nrh, ncl, nch);
		E_t =  erosion(E_t,nrl, nrh, ncl, nch);

		SavePGM_ui8matrix(E_t, nrl, nrh, ncl, nch, nom_output);

	}
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);

	return 0;
}
