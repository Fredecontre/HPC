#include "morpho.h"
int flag_break2;

uint8** erosion_SIMD(uint8**E_t, int nrl, int nrh, int ncl, int nch){
	
	uint8**E_t_bis=ui8matrix(nrl, nrh, ncl, nch);
	zero_ui8matrix(E_t_bis, nrl, nrh, ncl, nch);

	//Coin haut gauche
	for(uint16_t i_temp = nrl; i_temp <= nrl + 1; i_temp++){
		for(uint16_t j_temp = ncl; j_temp <= ncl + 1; j_temp++){
			if(E_t[i_temp][j_temp] == 0 && j_temp != ncl && i_temp != nrl){
				E_t_bis[nrl][ncl] = 0;				
				flag_break2 = 1;
				break;
			}
			else{
				E_t_bis[nrl][ncl] = E_t[nrl][ncl];
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Coin haut droite
	for(uint16_t i_temp = nrl; i_temp <= nrl + 1; i_temp++){
		for(uint16_t j_temp = nch - 1; j_temp <= nch; j_temp++){
			if(E_t[i_temp][j_temp] == 0 && j_temp != nch && i_temp != nrl){
				E_t_bis[nrl][nch] = 0;				
				flag_break2 = 1;
				break;
			}
			else{
				E_t_bis[nrl][nch] = E_t[nrl][nch];
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Coin bas droite
	for(uint16_t i_temp = nrh-1 ; i_temp <= nrh; i_temp++){
		for(uint16_t j_temp = nch-1 ; j_temp <= nch; j_temp++){
			if(E_t[i_temp][j_temp] == 0 && j_temp != nch && i_temp != nrh){
				E_t_bis[nrh][nch] = 0;				
				flag_break2 = 1;
				break;
			}
			else{
				E_t_bis[nrh][nch] = E_t[nrh][nch];
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Coin bas gauche
	for(uint16_t i_temp = nrh - 1; i_temp <= nrh; i_temp++){
		for(uint16_t j_temp = ncl; j_temp <= ncl + 1; j_temp++){
			if(E_t[i_temp][j_temp] == 0 && j_temp != ncl && i_temp != nrh){
				E_t_bis[nrh][ncl] = 0;				
				flag_break2 = 1;
				break;
			}
			else{
				E_t_bis[nrh][ncl] = E_t[nrh][ncl];
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Bord gauche
	for(uint16_t i = nrl + 1; i < nrh; i++){
		for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
			for(uint16_t j_temp = ncl; j_temp <= ncl + 1; j_temp++){
				if(E_t[i_temp][j_temp] == 0 && j_temp != ncl && i_temp != i){
					E_t_bis[i][ncl] = 0;				
					flag_break2 = 1;
					break;
				}
				else{
					E_t_bis[i][ncl] = E_t[i][ncl];
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	//Bord haut
	for(uint16_t j = ncl + 1; j < nch; j++){
		for(uint16_t j_temp = j - 1; j_temp <= j + 1; j_temp++){
			for(uint16_t i_temp = nrl; i_temp <= nrl + 1; i_temp++){
				if(E_t[i_temp][j_temp] == 0 && j_temp != j && i_temp != nrl){
					E_t_bis[nrl][j] = 0;				
					flag_break2 = 1;
					break;
				}
				else{
					E_t_bis[nrl][j] = E_t[nrl][j];
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	//Bord droit
	for(uint16_t i = nrl + 1; i < nrh; i++){
		for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
			for(uint16_t j_temp = nch - 1; j_temp <= nch; j_temp++){
				if(E_t[i_temp][j_temp] == 0 && j_temp != nch && i_temp != i){
					E_t_bis[i][nch] = 0;				
					flag_break2 = 1;
					break;
				}
				else{
					E_t_bis[i][nch] = E_t[i][nch];
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	//Bord bas
	for(uint16_t j = ncl + 1; j < nch; j++){
		for(uint16_t j_temp = j - 1; j_temp <= j + 1; j_temp++){
			for(uint16_t i_temp = nrh - 1; i_temp <= nrh; i_temp++){
				if(E_t[i_temp][j_temp] == 0 && j_temp != j && i_temp != nrh){
					E_t[nrh][j] = 0;				
					flag_break2 = 1;
					break;
				}
				else{
					E_t_bis[nrh][j] = E_t[nrh][j];
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	for(uint16_t i = nrl + 1; i < nrh; i++){
		for(uint16_t j = ncl + 1; j < nch; j++){
			if(E_t[i-1][j-1] == 0 || E_t[i-1][j] == 0 ||E_t[i-1][j+1] == 0 ||E_t[i][j-1] == 0 ||E_t[i][j] == 0 ||E_t[i][j+1] == 0 ||E_t[i+1][j-1] == 0 ||E_t[i+1][j] == 0 ||E_t[i+1][j+1] == 0 )
				E_t_bis[i][j] = 0;
			else{
				E_t_bis[i][j] = E_t[i][j];
			}

			/*for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
				for(uint16_t j_temp = j - 1; j_temp <= j + 1; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break2 = 1;
						E_t_bis[i][j] = 0;
						break;
					}
					else{
						E_t_bis[i][j] = E_t[i][j];
					}
				}
			
			}*/
		}
	}
	return E_t_bis;
}

uint8** dilatation_SIMD(uint8**E_t, int nrl, int nrh, int ncl, int nch){

	uint8**E_t_bis=ui8matrix(nrl, nrh, ncl, nch);
	zero_ui8matrix(E_t_bis, nrl, nrh, ncl, nch);

	//Coin haut gauche
	for(uint16_t i_temp = nrl; i_temp <= nrl + 1; i_temp++){
		for(uint16_t j_temp = ncl; j_temp <= ncl + 1; j_temp++){
			if(E_t[i_temp][j_temp] == 255 && j_temp != ncl && i_temp != nrl){
				E_t_bis[nrl][ncl] = 255;				
				flag_break2 = 1;
				break;
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Coin haut droite
	for(uint16_t i_temp = nrl; i_temp <= nrl + 1; i_temp++){
		for(uint16_t j_temp = nch - 1; j_temp <= nch; j_temp++){
			if(E_t[i_temp][j_temp] == 255 && j_temp != nch && i_temp != nrl){
				E_t_bis[nrl][nch] = 255;				
				flag_break2 = 1;
				break;
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Coin bas droite
	for(uint16_t i_temp = nrh - 1 ; i_temp <= nrh; i_temp++){
		for(uint16_t j_temp = nch - 1; j_temp <= nch; j_temp++){
			if(E_t[i_temp][j_temp] == 255 && j_temp != nch && i_temp != nrh){
				E_t_bis[nrh][nch] = 255;				
				flag_break2 = 1;
				break;
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Coin bas gauche
	for(uint16_t i_temp = nrh - 1; i_temp <= nrh; i_temp++){
		for(uint16_t j_temp = ncl; j_temp <= ncl + 1; j_temp++){
			if(E_t[i_temp][j_temp] == 255 && j_temp != ncl && i_temp != nrh){
				E_t_bis[nrh][ncl] = 255;				
				flag_break2 = 1;
				break;
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Bord gauche
	for(uint16_t i = nrl + 1; i < nrh; i++){
		for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
			for(uint16_t j_temp = ncl; j_temp <= ncl + 1; j_temp++){
				if(E_t[i_temp][j_temp] == 255 && j_temp != ncl && i_temp != i){
					E_t_bis[i][ncl] = 255;				
					flag_break2 = 1;
					break;
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	//Bord haut
	for(uint16_t j = ncl + 1; j < nch; j++){
		for(uint16_t j_temp = j - 1; j_temp <= j + 1; j_temp++){
			for(uint16_t i_temp = nrl; i_temp <= nrl + 1; i_temp++){
				if(E_t[i_temp][j_temp] == 255 && j_temp != j && i_temp != nrl){
					E_t_bis[nrl][j] = 255;				
					flag_break2 = 1;
					break;
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	//Bord droit
	for(uint16_t i = nrl + 1; i < nrh; i++){
		for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
			for(uint16_t j_temp = nch - 1; j_temp <= nch; j_temp++){
				if(E_t[i_temp][j_temp] == 255 && j_temp != nch && i_temp != i){
					E_t_bis[i][nch] = 255;				
					flag_break2 = 1;
					break;
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	//Bord bas
	for(uint16_t j = ncl + 1; j < nch; j++){
		for(uint16_t j_temp = j - 1; j_temp <= j + 1; j_temp++){
			for(uint16_t i_temp = nrh - 1; i_temp <= nrh; i_temp++){
				if(E_t[i_temp][j_temp] == 255 && j_temp != j && i_temp != nrh){
					E_t_bis[nrh][j] = 255;				
					flag_break2 = 1;
					break;
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	for(uint16_t i = nrl +1; i < nrh; i++){
		for(uint16_t j = ncl + 1; j < nch; j++){
			if(E_t[i-1][j-1] == 255 || E_t[i-1][j] == 255 ||E_t[i-1][j+1] == 255 ||E_t[i][j-1] == 255 ||E_t[i][j] == 255 ||E_t[i][j+1] == 255 ||E_t[i+1][j-1] == 255 ||E_t[i+1][j] == 255 ||E_t[i+1][j+1] == 255 )
				E_t_bis[i][j] = 255;
	

			/*for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
				for(uint16_t j_temp = j - 1; j_temp <= j + 1; j_temp++){
					if(E_t[i_temp][j_temp] == 255 ){
						flag_break2 = 1;
						E_t_bis[i][j] = 255;
						break;
					}
				}
				
			}*/
		}
	}
	return E_t_bis;
}


uint8** erosion_dilatation_SIMD(uint8**E_t, int nrl, int nrh, int ncl, int nch){
	
	//uint8**E_t=ui8matrix(nrl, nrh, ncl, nch);
	//zero_ui8matrix(E_t, nrl, nrh, ncl, nch);

	uint8**E_t_3_3=ui8matrix(nrl, 3, ncl, 3);
	zero_ui8matrix(E_t_3_3, nrl, 3, ncl, 3);

	//Coin haut gauche
	/*for(uint16_t i_temp = nrl; i_temp <= nrl + 1; i_temp++){
		for(uint16_t j_temp = ncl; j_temp <= ncl + 1; j_temp++){
			if(E_t[i_temp][j_temp] == 0 && j_temp != ncl && i_temp != nrl){
				E_t[nrl][ncl] = 0;				
				flag_break2 = 1;
				break;
			}
			else{
				E_t[nrl][ncl] = E_t[nrl][ncl];
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Coin haut droite
	for(uint16_t i_temp = nrl; i_temp <= nrl + 1; i_temp++){
		for(uint16_t j_temp = nch - 1; j_temp <= nch; j_temp++){
			if(E_t[i_temp][j_temp] == 0 && j_temp != nch && i_temp != nrl){
				E_t[nrl][nch] = 0;				
				flag_break2 = 1;
				break;
			}
			else{
				E_t[nrl][nch] = E_t[nrl][nch];
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Coin bas droite
	for(uint16_t i_temp = nrh-1 ; i_temp <= nrh; i_temp++){
		for(uint16_t j_temp = nch-1 ; j_temp <= nch; j_temp++){
			if(E_t[i_temp][j_temp] == 0 && j_temp != nch && i_temp != nrh){
				E_t[nrh][nch] = 0;				
				flag_break2 = 1;
				break;
			}
			else{
				E_t[nrh][nch] = E_t[nrh][nch];
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Coin bas gauche
	for(uint16_t i_temp = nrh - 1; i_temp <= nrh; i_temp++){
		for(uint16_t j_temp = ncl; j_temp <= ncl + 1; j_temp++){
			if(E_t[i_temp][j_temp] == 0 && j_temp != ncl && i_temp != nrh){
				E_t[nrh][ncl] = 0;				
				flag_break2 = 1;
				break;
			}
			else{
				E_t[nrh][ncl] = E_t[nrh][ncl];
			}
		}
		if(flag_break2){
			flag_break2 = 0;
			break;
		}
	}
	//Bord gauche
	for(uint16_t i = nrl + 1; i < nrh; i++){
		for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
			for(uint16_t j_temp = ncl; j_temp <= ncl + 1; j_temp++){
				if(E_t[i_temp][j_temp] == 0 && j_temp != ncl && i_temp != i){
					E_t[i][ncl] = 0;				
					flag_break2 = 1;
					break;
				}
				else{
					E_t[i][ncl] = E_t[i][ncl];
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	//Bord haut
	for(uint16_t j = ncl + 1; j < nch; j++){
		for(uint16_t j_temp = j - 1; j_temp <= j + 1; j_temp++){
			for(uint16_t i_temp = nrl; i_temp <= nrl + 1; i_temp++){
				if(E_t[i_temp][j_temp] == 0 && j_temp != j && i_temp != nrl){
					E_t[nrl][j] = 0;				
					flag_break2 = 1;
					break;
				}
				else{
					E_t[nrl][j] = E_t[nrl][j];
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	//Bord droit
	for(uint16_t i = nrl + 1; i < nrh; i++){
		for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
			for(uint16_t j_temp = nch - 1; j_temp <= nch; j_temp++){
				if(E_t[i_temp][j_temp] == 0 && j_temp != nch && i_temp != i){
					E_t[i][nch] = 0;				
					flag_break2 = 1;
					break;
				}
				else{
					E_t[i][nch] = E_t[i][nch];
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}
	//Bord bas
	for(uint16_t j = ncl + 1; j < nch; j++){
		for(uint16_t j_temp = j - 1; j_temp <= j + 1; j_temp++){
			for(uint16_t i_temp = nrh - 1; i_temp <= nrh; i_temp++){
				if(E_t[i_temp][j_temp] == 0 && j_temp != j && i_temp != nrh){
					E_t[nrh][j] = 0;				
					flag_break2 = 1;
					break;
				}
				else{
					E_t[nrh][j] = E_t[nrh][j];
				}
			}
			if(flag_break2){
				flag_break2 = 0;
				break;
			}
		}
	}*/
	/*for(uint16_t i = nrl + 2; i < nrh - 1; i++){
		for(uint16_t j = ncl + 2; j < nch - 1 ; j++){

			//PIXEL HAUT GAUCHE
			for(uint16_t i_temp = i - 2; i_temp <= i ; i_temp++){ 
				for(uint16_t j_temp = j - 2 ;j_temp <= j ; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break2 = 1;
						//E_t[i-1][j-1] = 0;
						E_t_3_3[0][0] = 0;
						break;
					}
					else{
						//E_t[i-1][j-1] = E_t[i-1][j-1];
						E_t_3_3[0][0] = E_t[i-1][j-1];
					}
				}
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
			}
			//PIXEL MILIEU GAUCHE
			for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
				for(uint16_t j_temp = j - 2 ;j_temp <= j ; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break2 = 1;
						//E_t[i][j-1] = 0;
						E_t_3_3[1][0] = 0;
						break;
					}
					else{
						//E_t[i][j-1] = E_t[i][j-1];
						E_t_3_3[1][0] =  E_t[i][j-1];
					}
				}
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
			}
			//PIXEL BAS GAUCHE
			for(uint16_t i_temp = i ; i_temp <= i + 2; i_temp++){
				for(uint16_t j_temp = j - 2 ;j_temp <= j ; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break2 = 1;
						//E_t[i+1][j-1] = 0;
						E_t_3_3[2][0] = 0;
						break;
					}
					else{
						//E_t[i+1][j-1] = E_t[i+1][j-1];
						E_t_3_3[2][0] = E_t[i+1][j-1];
					}
				}
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
			}
			//PIXEL BAS MILIEU
			for(uint16_t i_temp = i ; i_temp <= i + 2; i_temp++){
				for(uint16_t j_temp = j - 1 ;j_temp <= j + 1; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break2 = 1;
						//E_t[i+1][j] = 0;
						E_t_3_3[2][1] = 0;

						break;
					}
					else{
						//E_t[i+1][j] = E_t[i+1][j];
						E_t_3_3[2][1]=E_t[i+1][j];
					}
				}
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
			}

			//PIXEL BAS DROITE
			for(uint16_t i_temp = i ; i_temp <= i + 2; i_temp++){
				for(uint16_t j_temp = j; j_temp <= j + 2; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break2 = 1;
						//E_t[i+1][j+1] = 0;
						E_t_3_3[2][2] = 0;
						break;
					}
					else{
						//E_t[i+1][j+1] = E_t[i+1][j+1];
						E_t_3_3[2][2] =  E_t[i+1][j+1];
					}
				}
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
			}

			//PIXEL DROITE MILIEU
			for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
				for(uint16_t j_temp = j; j_temp <= j + 2; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break2 = 1;
						//E_t[i][j+1] = 0;
						E_t_3_3[1][2] = 0;
						break;
					}
					else{
						//E_t[i][j+1] = E_t[i][j+1];
						E_t_3_3[1][2] = E_t[i][j+1];
					}
				}
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
			}

			//PIXEL DROITE HAUT
			for(uint16_t i_temp = i - 2; i_temp <= i; i_temp++){
				for(uint16_t j_temp = j; j_temp <= j + 2; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break2 = 1;
						//E_t[i-1][j+1] = 0;
						E_t_3_3[0][2] = 0;
						break;
					}
					else{
						//E_t[i-1][j+1] = E_t[i-1][j+1];
						E_t_3_3[0][2] = E_t[i-1][j+1];
					}
				}
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
			}

			//PIXEL MILIEU HAUT
			for(uint16_t i_temp = i - 2; i_temp <= i; i_temp++){
				for(uint16_t j_temp = j - 1 ; j_temp <= j +1; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break2 = 1;
						E_t_3_3[0][1] = 0;
						//E_t[i-1][j] = 0;
						break;
					}
					else{
						//E_t[i-1][j] = E_t[i-1][j];
						E_t_3_3[0][1] = E_t[i-1][j];
					}
				}
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
			}
			//DILATION POINT I J
			//for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
			//	for(uint16_t j_temp = j - 1; j_temp <= j + 1; j_temp++){
			for(uint16_t i_temp = 0; i_temp <= 2; i_temp++){
				for(uint16_t j_temp =0; j_temp <= 2 ;j_temp++){
					if(E_t_3_3[i_temp][j_temp] == 255 ){
						//&& j_temp != j && i_temp != i){
						flag_break2 = 1;
						E_t[i][j] = 255;
						break;
					}
				}
				if(flag_break2){
					flag_break2 = 0;
					break;
				}
			}

		}
	}*/
	return E_t;
}