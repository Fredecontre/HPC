#include "morpho.h"
int flag_break;

/*void* morphologies_image(void*arguments){

	args_thread* args=(args_thread* )arguments;
	int nrl=args->nrl, nrh=args->nrh, ncl=args->ncl, nch=args->nch;

	args->E_t =  erosion(args->E_t,nrl, nrh, ncl, nch);
	args->E_t =  dilatation(args->E_t,args->nrl, args->nrh, args->ncl, args->nch);
	args->E_t =  dilatation(args->E_t,args->nrl, args->nrh, args->ncl, args->nch);
	args->E_t =  erosion(args->E_t,args->nrl, args->nrh, args->ncl, args->nch);

	return args->E_t;

}*/

void* morphologies_image(void*arguments){


	

	args_thread* args=(args_thread* )arguments;
	int nrl=args->nrl, nrh=args->nrh, ncl=args->ncl, nch=args->nch;

	args->E_t =  erosion(args->E_t,nrl, nrh, ncl, nch);
	args->E_t =  dilatation(args->E_t,args->nrl, args->nrh, args->ncl, args->nch);
	args->E_t =  dilatation(args->E_t,args->nrl, args->nrh, args->ncl, args->nch);
	args->E_t =  erosion(args->E_t,args->nrl, args->nrh, args->ncl, args->nch);

	return 0;

}

uint8** erosion(uint8**E_t, int nrl, int nrh, int ncl, int nch){
	
	uint8**E_t_bis = ui8matrix(nrl, nrh, ncl, nch);
	zero_ui8matrix(E_t_bis, nrl, nrh, ncl, nch);

	//Coin haut gauche
	if(E_t[nrl][ncl] == 0 || E_t[nrl+1][ncl] == 0 || E_t[nrl][ncl+1] == 0 || E_t[nrl+1][ncl+1] == 0)
		E_t_bis[nrl][ncl] = 0;
	else
		E_t_bis[nrl][ncl] = E_t[nrl][ncl];
	//Coin haut droite
	if(E_t[nrl][nch] == 0 || E_t[nrl+1][nch] == 0 || E_t[nrl][nch-1] == 0 || E_t[nrl+1][nch-1] == 0)
		E_t_bis[nrl][nch] = 0;
	else
		E_t_bis[nrl][nch] = E_t[nrl][nch];
	//Coin bas droite
	if(E_t[nrh][nch] == 0 || E_t[nrh-1][nch] == 0 || E_t[nrh][nch-1] == 0 || E_t[nrh-1][nch-1] == 0)
		E_t_bis[nrh][nch] = 0;
	else
		E_t_bis[nrh][nch] = E_t[nrh][nch];
	//Coin bas gauche
	if(E_t[nrh][ncl] == 0 || E_t[nrh-1][ncl] == 0 || E_t[nrh-1][ncl+1] == 0 || E_t[nrh][ncl+1] == 0)
		E_t_bis[nrh][ncl] = 0;
	else
		E_t_bis[nrh][ncl] = E_t[nrh][ncl];
	//Bord gauche
	for(uint16_t i = nrl + 1; i < nrh; i++){
		if(E_t[i-1][ncl] == 0 || E_t[i-1][ncl+1] == 0 || E_t[i][ncl] == 0 || E_t[i][ncl+1] == 0 || E_t[i+1][ncl] == 0 || E_t[i+1][ncl+1] == 0)
			E_t_bis[i][ncl] = 0;
		else{
			E_t_bis[i][ncl] = E_t[i][ncl];
		}
	}
	//Bord haut
	for(uint16_t j = ncl + 1; j < nch; j++){
		if(E_t[nrl][j-1] == 0 || E_t[nrl][j] == 0 || E_t[nrl][j+1] == 0 || E_t[nrl+1][j-1] == 0 || E_t[nrl+1][j] == 0 || E_t[nrl+1][j+1] == 0)
			E_t_bis[nrl][j] = 0;
		else{
			E_t_bis[nrl][j] = E_t[nrl][j];
		}
	}
	//Bord droit
	for(uint16_t i = nrl + 1; i < nrh; i++){
		if(E_t[i-1][nch-1] == 0 || E_t[i-1][nch] == 0 || E_t[i][nch-1] == 0 || E_t[i][nch] == 0 || E_t[i+1][nch-1] == 0 || E_t[i+1][nch] == 0)
			E_t_bis[i][nch] = 0;
		else{
			E_t_bis[i][nch] = E_t[i][nch];
		}
	}
	//Bord bas
	for(uint16_t j = ncl + 1; j < nch; j++){
		if(E_t[nrh][j-1] == 0 || E_t[nrh][j] == 0 || E_t[nrh][j+1] == 0 || E_t[nrh-1][j-1] == 0 || E_t[nrh-1][j] == 0 || E_t[nrh-1][j+1] == 0)
			E_t_bis[nrh][j] = 0;
		else{
			E_t_bis[nrh][j] = E_t[nrh][j];
		}
	}

	//Rotation de variables
	int8_t p1 = E_t[nrl][ncl],
	p2 = E_t[nrl][ncl+1],
	p3 = E_t[nrl][ncl+2],
	p4 = E_t[nrl+1][ncl+2],
	p5 = E_t[nrl+2][ncl+2],
	p6 = E_t[nrl+2][ncl+1],
	p7 = E_t[nrl+2][ncl],
	p8 = E_t[nrl+1][ncl],
	p_curr = E_t[nrl+1][ncl+1];

	for(uint16_t i = nrl + 1; i < nrh; i++){
		for(uint16_t j = ncl + 1; j < nch; j++){
			p3 = E_t[i-1][j+1]; //Pixel haut droite
			p4 = E_t[i][j+1]; //Pixel milieu droite
			p5 = E_t[i+1][j+1]; //Pixel bas droite

			if(p1 == 0 || p2 == 0 ||p3 == 0 ||p4 == 0 ||p5 == 0 ||p6 == 0 ||p7== 0 ||p8== 0 ||p_curr== 0 ){
				E_t_bis[i][j] = 0;
			}
			else{
				E_t_bis[i][j]= E_t[i][j];
			}
			

			//Rotation
			p1 = p2;
			p8 = p_curr;
			p7 = p6;
			p2 = p3;
			p_curr = p4;
			p6 = p5;
		}
		//Rotation de variables nouvelle ligne
		p1 = E_t[i-1][ncl];
		p2 = E_t[i-1][ncl+1];
		p3 = E_t[i-1][ncl+2];
		p4 = E_t[i][ncl+2];
		p5 = E_t[i+1][ncl+2];
		p6 = E_t[i+1][ncl+1];
		p7 = E_t[i+1][ncl];
		p8 = E_t[i][ncl];
		p_curr = E_t[i][ncl+1];
	}
	/*for(uint16_t i = nrl + 1; i < nrh; i++){
		for(uint16_t j = ncl + 1; j < nch; j++){
			if(E_t[i-1][j-1] == 0 || E_t[i-1][j] == 0 || E_t[i-1][j+1] == 0 || E_t[i][j-1] == 0 || E_t[i][j] == 0 || E_t[i][j+1] == 0 || E_t[i+1][j-1] == 0 || E_t[i+1][j] == 0 || E_t[i+1][j+1] == 0)
				E_t_bis[i][j] = 0;
			else{
				E_t_bis[i][j] = E_t[i][j];
			}
		}
	}*/
	return E_t_bis;
}


uint8** dilatation(uint8**E_t, int nrl, int nrh, int ncl, int nch){

	//Coin haut gauche
	if(E_t[nrl][ncl] == 255 || E_t[nrl+1][ncl] == 255 || E_t[nrl][ncl+1] == 255 || E_t[nrl+1][ncl+1] == 255)
		E_t[nrl][ncl] = 255;
	//Coin haut droite
	if(E_t[nrl][nch] == 255 || E_t[nrl+1][nch] == 255 || E_t[nrl][nch-1] == 255 || E_t[nrl+1][nch-1] == 255)
		E_t[nrl][nch] = 255;
	//Coin bas droite
	if(E_t[nrh][nch] == 255 || E_t[nrh-1][nch] == 255 || E_t[nrh][nch-1] == 255 || E_t[nrh-1][nch-1] == 255)
		E_t[nrh][nch] = 255;
	//Coin bas gauche
	if(E_t[nrh][ncl] == 255 || E_t[nrh-1][ncl] == 255 || E_t[nrh-1][ncl+1] == 255 || E_t[nrh][ncl+1] == 255)
		E_t[nrh][ncl] = 255;
	//Bord gauche
	for(uint16_t i = nrl + 1; i < nrh; i++){
		if(E_t[i-1][ncl] == 255 || E_t[i-1][ncl+1] == 255 || E_t[i][ncl] == 255 || E_t[i][ncl+1] == 255 || E_t[i+1][ncl] == 255 || E_t[i+1][ncl+1] == 255)
			E_t[i][ncl] = 255;
	}
	//Bord haut
	for(uint16_t j = ncl + 1; j < nch; j++){
		if(E_t[nrl][j-1] == 255 || E_t[nrl][j] == 255 || E_t[nrl][j+1] == 255 || E_t[nrl+1][j-1] == 255 || E_t[nrl+1][j] == 255 || E_t[nrl+1][j+1] == 255)
			E_t[nrl][j] = 255;
	}
	//Bord droit
	for(uint16_t i = nrl + 1; i < nrh; i++){
		if(E_t[i-1][nch-1] == 255 || E_t[i-1][nch] == 255 || E_t[i][nch-1] == 255 || E_t[i][nch] == 255 || E_t[i+1][nch-1] == 255 || E_t[i+1][nch] == 255)
			E_t[i][nch] = 255;
	}
	//Bord bas
	for(uint16_t j = ncl + 1; j < nch; j++){
		if(E_t[nrh][j-1] == 255 || E_t[nrh][j] == 255 || E_t[nrh][j+1] == 255 || E_t[nrh-1][j-1] == 255 || E_t[nrh-1][j] == 255 || E_t[nrh-1][j+1] == 255)
				E_t[nrh][j] = 255;
	}
	//Rotation de variables
	int8_t p1 = E_t[nrl][ncl],
	p2 = E_t[nrl][ncl+1],
	p3 = E_t[nrl][ncl+2],
	p4 = E_t[nrl+1][ncl+2],
	p5 = E_t[nrl+2][ncl+2],
	p6 = E_t[nrl+2][ncl+1],
	p7 = E_t[nrl+2][ncl],
	p8 = E_t[nrl+1][ncl],
	p_curr = E_t[nrl+1][ncl+1];

	for(uint16_t i = nrl + 1; i < nrh; i++){
		for(uint16_t j = ncl + 1; j < nch; j++){
			p3 = E_t[i-1][j+1]; //Pixel haut droite
			p4 = E_t[i][j+1]; //Pixel milieu droite
			p5 = E_t[i+1][j+1]; //Pixel bas droite

			if(p1 == 255 || p2 == 255 ||p3 == 255 ||p4 == 255 ||p5 == 255 ||p6 == 255 ||p7== 255 ||p8== 255 ||p_curr== 255 ){
				E_t[i][j] = 255;
			}
			/*else{
				E_t_bis[i][j] = E_t[i][j];
			}*/

			//Rotation
			p1 = p2;
			p8 = p_curr;
			p7 = p6;
			p2 = p3;
			p_curr = p4;
			p6 = p5;
		}
		//Rotation de variables nouvelle ligne
		p1 = E_t[i-1][ncl];
		p2 = E_t[i-1][ncl+1];
		p3 = E_t[i-1][ncl+2];
		p4 = E_t[i][ncl+2];
		p5 = E_t[i+1][ncl+2];
		p6 = E_t[i+1][ncl+1];
		p7 = E_t[i+1][ncl];
		p8 = E_t[i][ncl];
		p_curr = E_t[i][ncl+1];
	}
	return E_t;
}


uint8** erosion_dilatation(uint8**E_t, int nrl, int nrh, int ncl, int nch){
	
	uint8**E_t_bis=ui8matrix(nrl, nrh, ncl, nch);
	zero_ui8matrix(E_t_bis, nrl, nrh, ncl, nch);

	uint8**E_t_3_3=ui8matrix(nrl, 3, ncl, 3);
	zero_ui8matrix(E_t_3_3, nrl, 3, ncl, 3);

	//Rotation de variables
	int8_t p1 = E_t[nrl][ncl],
	p2 = E_t[nrl][ncl+1],
	p3 = E_t[nrl][ncl+2],
	p4 = E_t[nrl+1][ncl+2],
	p5 = E_t[nrl+2][ncl+2],
	p6 = E_t[nrl+2][ncl+1],
	p7 = E_t[nrl+2][ncl],
	p8 = E_t[nrl+1][ncl],
	p_curr = E_t[nrl+1][ncl+1];

	for(uint16_t i = nrl + 2; i < nrh - 1; i++){
		for(uint16_t j = ncl + 2; j < nch - 1 ; j++){
			for(uint16_t i_temp = i - 1; i_temp <= i +1; i_temp++){ 
				for(uint16_t j_temp = j - 1 ;j_temp <= j +1; j_temp++){
					p3 = E_t[i_temp-1][j_temp+1]; //Pixel haut droite
					p4 = E_t[i_temp][j_temp+1]; //Pixel milieu droite
					p5 = E_t[i_temp+1][j_temp+1]; //Pixel bas droite
					if(p1 == 0 || p2 == 0 ||p3 == 0 ||p4 == 0 ||p5 == 0 ||p6 == 0 ||p7== 0 ||p8== 0 ||p_curr== 0 ){
						E_t_3_3[i_temp-i][j_temp-j] = 0;
					}
					else{
						E_t_3_3[i_temp-i][j_temp-j] =E_t[i_temp][j_temp];
					}

					p1 = p2;
					p8 = p_curr;
					p7 = p6;
					p2 = p3;
					p_curr = p4;
					p6 = p5;
						
				}
				p1 = E_t[i_temp-1][ncl];
				p2 = E_t[i_temp-1][ncl+1];
				p3 = E_t[i_temp-1][ncl+2];
				p4 = E_t[i_temp][ncl+2];
				p5 = E_t[i_temp+1][ncl+2];
				p6 = E_t[i_temp+1][ncl+1];
				p7 = E_t[i_temp+1][ncl];
				p8 = E_t[i_temp][ncl];
				p_curr = E_t[i_temp][ncl+1];
			}

			/*for(uint16_t i_temp = i - 2; i_temp <= i ; i_temp++){ 
				for(uint16_t j_temp = j - 2 ;j_temp <= j ; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break = 1;
						E_t_bis[i-1][j-1] = 0;
						break;
					}
					else{
						E_t_bis[i-1][j-1] = E_t[i-1][j-1];
					}
				}
				if(flag_break){
					flag_break = 0;
					break;
				}
			}
			//PIXEL HAUT GAUCHE
			for(uint16_t i_temp = i - 2; i_temp <= i ; i_temp++){ 
				for(uint16_t j_temp = j - 2 ;j_temp <= j ; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break = 1;
						E_t_bis[i-1][j-1] = 0;
						break;
					}
					else{
						E_t_bis[i-1][j-1] = E_t[i-1][j-1];
					}
				}
				if(flag_break){
					flag_break = 0;
					break;
				}
			}
			//PIXEL MILIEU GAUCHE
			for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
				for(uint16_t j_temp = j - 2 ;j_temp <= j ; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break = 1;
						E_t_bis[i][j-1] = 0;
						break;
					}
					else{
						E_t_bis[i][j-1] = E_t[i][j-1];
					}
				}
				if(flag_break){
					flag_break = 0;
					break;
				}
			}
			//PIXEL BAS GAUCHE
			for(uint16_t i_temp = i ; i_temp <= i + 2; i_temp++){
				for(uint16_t j_temp = j - 2 ;j_temp <= j ; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break = 1;
						E_t_bis[i+1][j-1] = 0;
						break;
					}
					else{
						E_t_bis[i+1][j-1] = E_t[i+1][j-1];
					}
				}
				if(flag_break){
					flag_break = 0;
					break;
				}
			}
			//PIXEL BAS MILIEU
			for(uint16_t i_temp = i ; i_temp <= i + 2; i_temp++){
				for(uint16_t j_temp = j - 1 ;j_temp <= j + 1; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break = 1;
						E_t_bis[i+1][j] = 0;
						break;
					}
					else{
						E_t_bis[i+1][j] = E_t[i+1][j];
					}
				}
				if(flag_break){
					flag_break = 0;
					break;
				}
			}

			//PIXEL BAS DROITE
			for(uint16_t i_temp = i ; i_temp <= i + 2; i_temp++){
				for(uint16_t j_temp = j; j_temp <= j + 2; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break = 1;
						E_t_bis[i+1][j+1] = 0;
						break;
					}
					else{
						E_t_bis[i+1][j+1] = E_t[i+1][j+1];
					}
				}
				if(flag_break){
					flag_break = 0;
					break;
				}
			}

			//PIXEL DROITE MILIEU
			for(uint16_t i_temp = i - 1; i_temp <= i + 1; i_temp++){
				for(uint16_t j_temp = j; j_temp <= j + 2; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break = 1;
						E_t_bis[i][j+1] = 0;
						break;
					}
					else{
						E_t_bis[i][j+1] = E_t[i][j+1];
					}
				}
				if(flag_break){
					flag_break = 0;
					break;
				}
			}

			//PIXEL DROITE HAUT
			for(uint16_t i_temp = i - 2; i_temp <= i; i_temp++){
				for(uint16_t j_temp = j; j_temp <= j + 2; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break = 1;
						E_t_bis[i-1][j+1] = 0;
						break;
					}
					else{
						E_t_bis[i-1][j+1] = E_t[i-1][j+1];
					}
				}
				if(flag_break){
					flag_break = 0;
					break;
				}
			}

			//PIXEL MILIEU HAUT
			for(uint16_t i_temp = i - 2; i_temp <= i; i_temp++){
				for(uint16_t j_temp = j - 1 ; j_temp <= j +1; j_temp++){
					if(E_t[i_temp][j_temp] == 0){
						flag_break = 1;
						E_t_bis[i-1][j] = 0;
						break;
					}
					else{
						E_t_bis[i-1][j] = E_t[i-1][j];
					}
				}
				if(flag_break){
					flag_break = 0;
					break;
				}
			}*/
			//DILATION POINT I J
			/*for(uint16_t i_temp = 0; i_temp <= i2; i_temp++){
				for(uint16_t j_temp = j; j_temp <= 2; j_temp++){
					if(E_t_3_3[i_temp][j_temp] == 255 ){
						//&& j_temp != j && i_temp != i){
						flag_break = 1;
						E_t_bis[i][j] = 255;
						break;
					}
				}
				if(flag_break){
					flag_break = 0;
					break;
				}
			}*/

		}
	}
	return E_t_bis;
}