#include "mouvement.h"
double time_spent = 0.0;
clock_t begin, end;


void initialisation_SIMD(uint8**I, uint8**V, uint8**M,int nrl, int nrh, int ncl, int nch){

	for(uint16_t i = nrl; i <=nrh; i++){
		for(uint16_t j = ncl; j <=nch; j+=mipp::N<int8_t>()){
			mipp::Reg<int8_t> Reg_M = (int8_t*)&I[i][j];
			Reg_M.store((int8_t*)&M[i][j]);
		}
	}
	set_ui8matrix(V, nrl, nrh, ncl, nch, VMIN);
}

int16_t** convert_int16(uint8**tab, int nrh, int nch){
	int16_t** res =(int16_t**)malloc(nrh*sizeof(int16_t*));

	for(uint16_t i = 0; i <=nrh; i++){
		res[i] =(int16_t*)malloc(sizeof(int16_t)*nch);
		for(uint16_t j = 0; j <=nch; j++){
			res[i][j]=(int16_t)tab[i][j];
		}
	}
	return res;

}

uint8** convert_uint8(int16_t**tab, int nrh, int nch){
	uint8** res =(uint8**)malloc(nrh*sizeof(uint8*));

	for(uint16_t i = 0; i <=nrh; i++){
		res[i] =(uint8*)malloc(sizeof(uint8)*nch);
		for(uint16_t j = 0; j <=nch; j++){
			res[i][j]=(uint8)tab[i][j];
		}
	}


	return res;

}

uint8** sigma_delta_SIMD(uint8**I_t, uint8**V_t, uint8**M_t,uint8**V_t_1, uint8**M_t_1, int nrl, int nrh, int ncl, int nch){

	uint8** O_t = ui8matrix(nrl, nrh, ncl, nch);
	uint8** E_t = ui8matrix(nrl, nrh, ncl, nch);
	zero_ui8matrix(O_t, nrl, nrh, ncl, nch);
	zero_ui8matrix(E_t, nrl, nrh, ncl, nch);

	
	begin =clock();

	int16_t** E_t_16 = convert_int16(E_t,nrh,nch);
	int16_t** I_t_16 = convert_int16(I_t,nrh,nch);
	int16_t** M_t_16 = convert_int16(M_t,nrh,nch);
	int16_t** V_t_16 = convert_int16(V_t,nrh,nch);
	int16_t** V_t_1_16 = convert_int16(V_t_1,nrh,nch);
	int16_t** M_t_1_16 = convert_int16(M_t_1,nrh,nch);
	int16_t** O_t_16 = convert_int16(O_t,nrh,nch);

	end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;


	mipp::Reg<int16_t>Reg_un = 1;  
	mipp::Reg<int16_t>Reg_zero = (int16_t)0;  
	mipp::Reg<int16_t> Reg_M_t;
	mipp::Reg<int16_t> Reg_I_t;
	mipp::Reg<int16_t> Reg_M_t_1;
	mipp::Reg<int16_t> Reg_O_t;
	mipp::Reg<int16_t> Reg_V_t_1;
	mipp::Reg<int16_t> Reg_V_t;
	mipp::Reg<int16_t> Reg_E_t;

	mipp::Reg<int16_t>Reg_VMAX = (int16_t)VMAX;
	mipp::Reg<int16_t>Reg_VMIN = (int16_t)VMIN;
	mipp::Reg<int16_t>Reg_N0 = (int16_t)N0;
	mipp::Reg<int16_t>Reg_WHITE = (int16_t)WHITE;




	//Etape 1 : Estimation Mt
	for(uint16_t i = nrl; i <=nrh; i++){
		for(uint16_t j = ncl; j <=nch; j+=mipp::N<int16_t>()){
			Reg_M_t_1 = (int16_t*)&M_t_1_16[i][j];
			Reg_I_t = (int16_t*)&I_t_16[i][j];
         	Reg_M_t = mipp::blend(Reg_M_t_1 + Reg_un, Reg_zero, Reg_M_t_1 < Reg_I_t);
         	Reg_M_t = mipp::blend(Reg_M_t_1 - Reg_un, Reg_M_t_1, Reg_M_t_1> Reg_I_t);
         	Reg_M_t.store((int16_t*)&M_t_16[i][j]);
		}
	}
	//Etape 2 Traitement des différences
	for(uint16_t i = nrl; i <=nrh; i++){
		for(uint16_t j = ncl; j <=nch; j+=mipp::N<int16_t>()){
		//for(uint16_t j = ncl; j <=nch; j++){
			Reg_M_t.load((int16_t*)&M_t_16[i][j]);
			Reg_I_t.load((int16_t*)&I_t_16[i][j]);
			Reg_O_t = mipp::abs(Reg_M_t-Reg_I_t);
			Reg_O_t.store((int16_t*)&O_t_16[i][j]);
		}
	}
	//Etape 3 : mettre à jour et serrage
	for(uint16_t i = nrl; i <=nrh; i++){
		for(uint16_t j = ncl; j <=nch; j+=mipp::N<int16_t>()){		

			Reg_O_t = (int16_t*)&O_t_16[i][j];

			Reg_V_t_1 = (int16_t*)&V_t_1_16[i][j];
         	Reg_V_t = mipp::blend(Reg_V_t_1 + Reg_un, Reg_zero, Reg_V_t_1 < Reg_O_t + Reg_O_t);
         	Reg_V_t= mipp::blend(Reg_V_t_1 - Reg_un, Reg_V_t_1, Reg_V_t_1 > Reg_O_t + Reg_O_t);

         	Reg_V_t = mipp::max(mipp::min(Reg_V_t,Reg_VMAX),Reg_VMIN);
         	Reg_V_t.store((int16_t*)&V_t_16[i][j]);
		}
	}
	//Etape 4 : Estimation de Et
	for(uint16_t i = nrl; i <=nrh; i++){
		for(uint16_t j = ncl; j <=nch; j+=mipp::N<int16_t>()){
			Reg_O_t = (int16_t*)&O_t_16[i][j];
			Reg_V_t = (int16_t*)&V_t_16[i][j];
			Reg_E_t = mipp::blend(Reg_zero, Reg_WHITE, Reg_O_t < Reg_V_t);
			Reg_E_t.store((int16_t*)&E_t_16[i][j]);

		}
	}

	begin =clock();
	E_t = convert_uint8(E_t_16,nrh,nch);
	I_t = convert_uint8(I_t_16,nrh,nch);
	M_t = convert_uint8(M_t_16,nrh,nch);
	V_t = convert_uint8(V_t_16,nrh,nch);
	V_t_1 = convert_uint8(V_t_1_16,nrh,nch);
	M_t_1 = convert_uint8(M_t_1_16,nrh,nch);
	O_t = convert_uint8(O_t_16,nrh,nch);
	end = clock();

	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	return E_t;
}
