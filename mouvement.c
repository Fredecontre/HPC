#include "mouvement.h"

void initialisation(uint8**I, uint8**V, uint8**M,int nrl, int nrh, int ncl, int nch){
	for(uint16_t i = nrl; i <=nrh; i++){
		for(uint16_t j = ncl; j <=nch; j++){
			M[i][j] = I[i][j];
			V[i][j] = VMIN;
		}
	}
}

uint8** sigma_delta(uint8**I_t, uint8**V_t, uint8**M_t,uint8**V_t_1, uint8**M_t_1, int nrl, int nrh, int ncl, int nch){

	uint8** O_t = ui8matrix(nrl, nrh, ncl, nch);
	uint8** E_t = ui8matrix(nrl, nrh, ncl, nch);

	zero_ui8matrix(O_t, nrl, nrh, ncl, nch);
	zero_ui8matrix(E_t, nrl, nrh, ncl, nch);

	//Etape 1 : Estimation Mt
	for(uint16_t i = nrl; i <=nrh; i++){
		for(uint16_t j = ncl; j <=nch; j++){
			if(M_t_1[i][j] < I_t[i][j])
				M_t[i][j] = M_t_1[i][j] + 1;
			else if(M_t_1[i][j] > I_t[i][j])
				M_t[i][j] = M_t_1[i][j] - 1;
			else
				M_t[i][j] = M_t_1[i][j];
			}
	}
	//Etape 2 Traitement des différences
	for(uint16_t i = nrl; i <=nrh; i++){
		for(uint16_t j = ncl; j <=nch; j++){
			O_t[i][j] = abs(M_t[i][j] - I_t[i][j]);
		}
	}
	//Etape 3 : mettre à jour et serrage
	for(uint16_t i = nrl; i <=nrh; i++){
		for(uint16_t j = ncl; j <=nch; j++){
			if(V_t_1[i][j] < N0*O_t[i][j])
				V_t[i][j] = V_t_1[i][j] + 1;
			else if(V_t_1[i][j] > N0*O_t[i][j])
				V_t[i][j] = V_t_1[i][j] - 1;
			else
				V_t[i][j] = V_t_1[i][j];
			V_t[i][j] = MAX(MIN(V_t[i][j],VMAX),VMIN);
		}
	}
	//Etape 4 : Estimation de Et
	for(uint16_t i = nrl; i <=nrh; i++){
		for(uint16_t j = ncl; j <=nch; j++){
			if(O_t[i][j] < V_t[i][j])
				E_t[i][j] = 0;
			else
				E_t[i][j] = WHITE;

		}
	}
	return E_t;
}