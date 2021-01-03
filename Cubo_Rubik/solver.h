#ifndef SOLVER_H // include guard
#define SOLVER_H

#include<iostream>
#include <vector>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  

namespace solver{

void rotar(char& c1, char& c2, char& c3, char& c4) {
	char aux = c1;
	c1 = c2;
	c2 = c3;
	c3 = c4;
	c4 = aux;
}
void rotarPrima(char& c1, char& c2, char& c3, char& c4) {
	char aux = c1;
	c1 = c4;
	c4 = c3;
	c3 = c2;
	c2 = aux;
}
void rotarCaraH(int cara,char piezas[6][3][4]){
	char aux = piezas[cara][0][1];
	piezas[cara][0][1]=piezas[cara][1][0];
	piezas[cara][1][0]=piezas[cara][2][1];
	piezas[cara][2][1]=piezas[cara][1][2];
	piezas[cara][1][2]=aux;
	aux = piezas[cara][0][0];
	piezas[cara][0][0]=piezas[cara][2][0];
	piezas[cara][2][0]=piezas[cara][2][2];
	piezas[cara][2][2]=piezas[cara][0][2];
	piezas[cara][0][2]=aux;
}
void rotarCaraA(int cara,char piezas[6][3][4]){
	char aux = piezas[cara][0][1];
	piezas[cara][0][1]=piezas[cara][1][2];
	piezas[cara][1][2]=piezas[cara][2][1];
	piezas[cara][2][1]=piezas[cara][1][0];
	piezas[cara][1][0]=aux;
	aux = piezas[cara][0][0];
	piezas[cara][0][0]=piezas[cara][0][2];
	piezas[cara][0][2]=piezas[cara][2][2];
	piezas[cara][2][2]=piezas[cara][2][0];
	piezas[cara][2][0]=aux;
}
void U(char piezas[6][3][4]){
	rotarCaraH(0,piezas);
	for(int i=0;i<3;++i)
		rotar(piezas[1][0][i],piezas[2][0][i],piezas[3][0][i],piezas[4][0][i]);
}
void Uprima(char piezas[6][3][4]){
	rotarCaraA(0,piezas);
	for(int i=0;i<3;++i)
		rotarPrima(piezas[1][0][i],piezas[2][0][i],piezas[3][0][i],piezas[4][0][i]);
}
void E(char piezas[6][3][4]){
	for(int i=0;i<3;++i)
		rotar(piezas[1][1][i],piezas[4][1][i],piezas[3][1][i],piezas[2][1][i]);
}
void Eprima(char piezas[6][3][4]){
	for(int i=0;i<3;++i)
		rotarPrima(piezas[1][1][i],piezas[4][1][i],piezas[3][1][i],piezas[2][1][i]);
}
void D(char piezas[6][3][4]){
	rotarCaraH(5,piezas);
	for(int i=0;i<3;++i)
		rotar(piezas[1][2][i],piezas[4][2][i],piezas[3][2][i],piezas[2][2][i]);
}
void Dprima(char piezas[6][3][4]){
	rotarCaraA(5,piezas);
	for(int i=0;i<3;++i)
		rotarPrima(piezas[1][2][i],piezas[4][2][i],piezas[3][2][i],piezas[2][2][i]);
}
void F(char piezas[6][3][4]){
	rotarCaraH(1,piezas);
	for(int i=0;i<3;++i)
		rotar(piezas[0][2][i],piezas[4][2-i][2],piezas[5][0][2-i],piezas[2][i][0]);
}
void Fprima(char piezas[6][3][4]){
	rotarCaraA(1,piezas);
	for(int i=0;i<3;++i)
		rotarPrima(piezas[0][2][i],piezas[4][2-i][2],piezas[5][0][2-i],piezas[2][i][0]);
}
void S(char piezas[6][3][4]){
	for(int i=0;i<3;++i)
		rotar(piezas[0][1][i],piezas[4][2-i][1],piezas[5][1][2-i],piezas[2][i][1]);
}
void Sprima(char piezas[6][3][4]){
	for(int i=0;i<3;++i)
		rotarPrima(piezas[0][1][i],piezas[4][2-i][1],piezas[5][1][2-i],piezas[2][i][1]);
}
void B(char piezas[6][3][4]){
	rotarCaraH(3,piezas);
	for(int i=0;i<3;++i)
		rotar(piezas[0][0][i],piezas[2][i][2],piezas[5][2][2-i],piezas[4][2-i][0]);
}
void Bprima(char piezas[6][3][4]){
	rotarCaraA(3,piezas);
	for(int i=0;i<3;++i)
		rotarPrima(piezas[0][0][i],piezas[2][i][2],piezas[5][2][2-i],piezas[4][2-i][0]);
}
void R(char piezas[6][3][4]){
	rotarCaraH(2,piezas);
	for(int i=0;i<3;++i)
		rotar(piezas[0][i][2],piezas[1][i][2],piezas[5][i][2],piezas[3][2-i][0]);
}
void Rprima(char piezas[6][3][4]){
	rotarCaraA(2,piezas);
	for(int i=0;i<3;++i)
		rotarPrima(piezas[0][i][2],piezas[1][i][2],piezas[5][i][2],piezas[3][2-i][0]);
}
void M(char piezas[6][3][4]){
	for(int i=0;i<3;++i)
		rotar(piezas[0][i][1],piezas[3][2-i][1],piezas[5][i][1],piezas[1][i][1]);
}
void Mprima(char piezas[6][3][4]){
	for(int i=0;i<3;++i)
		rotarPrima(piezas[0][i][1],piezas[3][2-i][1],piezas[5][i][1],piezas[1][i][1]);
}
void L(char piezas[6][3][4]){
	rotarCaraH(4,piezas);
	for(int i=0;i<3;++i)
		rotar(piezas[0][i][0],piezas[3][2-i][2],piezas[5][i][0],piezas[1][i][0]);
}
void Lprima(char piezas[6][3][4]){
	rotarCaraA(4,piezas);
	for(int i=0;i<3;++i)
		rotarPrima(piezas[0][i][0],piezas[3][2-i][2],piezas[5][i][0],piezas[1][i][0]);
}

void Y(char piezas[6][3][4]){
	rotarCaraH(0,piezas);
	rotarCaraA(5,piezas);
	for(int i=0;i<3;++i){
		rotar(piezas[1][0][i],piezas[2][0][i],piezas[3][0][i],piezas[4][0][i]);
		rotar(piezas[1][1][i],piezas[2][1][i],piezas[3][1][i],piezas[4][1][i]);
		rotar(piezas[1][2][i],piezas[2][2][i],piezas[3][2][i],piezas[4][2][i]);
	}
}
	
void Z(char piezas[6][3][4]){
	rotarCaraH(1,piezas);
	rotarCaraA(3,piezas);
	for(int i=0;i<3;++i){
		rotar(piezas[0][2][i],piezas[4][2-i][2],piezas[5][0][2-i],piezas[2][i][0]);
		rotar(piezas[0][1][i],piezas[4][2-i][1],piezas[5][1][2-i],piezas[2][i][1]);
		rotar(piezas[0][0][i],piezas[4][2-i][0],piezas[5][2][2-i],piezas[2][i][2]);
	}
}

void X(char piezas[6][3][4]){
	rotarCaraH(2,piezas);
	rotarCaraA(4,piezas);
	for(int i=0;i<3;++i){
		rotar(piezas[0][i][2],piezas[1][i][2],piezas[5][i][2],piezas[3][2-i][0]);
		rotar(piezas[0][i][1],piezas[1][i][1],piezas[5][i][1],piezas[3][2-i][1]);
		rotar(piezas[0][i][0],piezas[1][i][0],piezas[5][i][0],piezas[3][2-i][2]);
	}
}
void Yprima(char piezas[6][3][4]){
	rotarCaraA(0,piezas);
	rotarCaraH(5,piezas);
	for(int i=0;i<3;++i){
		rotarPrima(piezas[1][0][i],piezas[2][0][i],piezas[3][0][i],piezas[4][0][i]);
		rotarPrima(piezas[1][1][i],piezas[2][1][i],piezas[3][1][i],piezas[4][1][i]);
		rotarPrima(piezas[1][2][i],piezas[2][2][i],piezas[3][2][i],piezas[4][2][i]);
	}
}
void Zprima(char piezas[6][3][4]){
	rotarCaraA(1,piezas);
	rotarCaraH(3,piezas);
	for(int i=0;i<3;++i){
		rotarPrima(piezas[0][2][i],piezas[4][2-i][2],piezas[5][0][2-i],piezas[2][i][0]);
		rotarPrima(piezas[0][1][i],piezas[4][2-i][1],piezas[5][1][2-i],piezas[2][i][1]);
		rotarPrima(piezas[0][0][i],piezas[4][2-i][0],piezas[5][2][2-i],piezas[2][i][2]);
	}
}
void Xprima(char piezas[6][3][4]){
	rotarCaraA(2,piezas);
	rotarCaraH(4,piezas);
	for(int i=0;i<3;++i){
		rotarPrima(piezas[0][i][2],piezas[1][i][2],piezas[5][i][2],piezas[3][2-i][0]);
		rotarPrima(piezas[0][i][1],piezas[1][i][1],piezas[5][i][1],piezas[3][2-i][1]);
		rotarPrima(piezas[0][i][0],piezas[1][i][0],piezas[5][i][0],piezas[3][2-i][2]);
	}
}
void (*movimientos[24])(char[6][3][4])={
	U,E,D,F,S,B,R,M,L,
	Uprima,Eprima,Dprima,Fprima,Sprima,Bprima,Rprima,Mprima,Lprima,
	Y,Z,X,Yprima,Zprima,Xprima
};
struct solverRubik{
	char piezasPropias[6][3][4];
	int mov;
	int prof;
	solverRubik*prev;
	solverRubik*next;
	std::vector<int>vectorMovInverso;
	solverRubik(int i){
		prof=0;
		prev=0;
		next=0;
		mov=-1;
		for(int i=0;i<9;i++){
			piezasPropias[0][i/3][i%3]='w';//Up
			piezasPropias[1][i/3][i%3]='r';//Front
			piezasPropias[2][i/3][i%3]='b';//Right
			piezasPropias[3][i/3][i%3]='o';//Back
			piezasPropias[4][i/3][i%3]='g';//Left
			piezasPropias[5][i/3][i%3]='y';//Down
		}
		for(int i=0;i<18;i++){
			piezasPropias[i/3][i%3][3]=0;
		}
		
	}
	solverRubik(solverRubik*nC,int m){
		prev=nC;
		mov=m;
		prof=nC->prof+1;
		for(int i=0;i<6;i++){
			for(int j=0;j<3;j++){
				for(int k=0;k<4;k++){
					piezasPropias[i][j][k]=nC->piezasPropias[i][j][k];
				}
			}
		}
		if(m>=0)
			(*movimientos[m])(piezasPropias);
	}
	void movimiento(int i){
		if(i<9)
			vectorMovInverso.insert(vectorMovInverso.begin(),i+9);
		else if(i<18)
			vectorMovInverso.insert(vectorMovInverso.begin(),i-9);
		else if(i<21)
			vectorMovInverso.insert(vectorMovInverso.begin(),i+3);
		else if(i<24)
			vectorMovInverso.insert(vectorMovInverso.begin(),i-3);
		else
			return;
		(*movimientos[i])(piezasPropias);
	}
	void scramble(int n){
		srand(time(NULL));
		for(int i=0;i<n;i++){
			movimiento(rand()%18);
		}
	}
	bool ochoEsquinas(){
		return piezasPropias[1][0][0]==piezasPropias[1][0][2] &&
			piezasPropias[1][2][0]==piezasPropias[1][2][2] &&
			piezasPropias[2][0][0]==piezasPropias[2][0][2] &&
			piezasPropias[2][2][0]==piezasPropias[2][2][2] &&
			piezasPropias[3][0][0]==piezasPropias[3][0][2] &&
			piezasPropias[3][2][0]==piezasPropias[3][2][2] &&
			piezasPropias[4][0][0]==piezasPropias[4][0][2] &&
			piezasPropias[4][2][0]==piezasPropias[4][2][2] && 
			piezasPropias[1][0][0]==piezasPropias[1][2][2] && 
			piezasPropias[0][0][0]==piezasPropias[0][2][2] && 
			piezasPropias[2][0][0]==piezasPropias[2][2][2] && 
			piezasPropias[3][0][0]==piezasPropias[3][2][2] && 
			piezasPropias[4][0][0]==piezasPropias[4][2][2];
	}
	bool penultimoPaso(){
		return (piezasPropias[0][0][0] == piezasPropias[0][2][2] &&
				piezasPropias[4][0][0] == piezasPropias[4][1][0] &&
				piezasPropias[4][1][0] == piezasPropias[4][1][1] &&
				piezasPropias[4][1][1] == piezasPropias[4][1][2] &&
				piezasPropias[1][1][0] == piezasPropias[1][1][1] &&
				piezasPropias[1][1][1] == piezasPropias[1][1][2] &&
				piezasPropias[3][1][1] == piezasPropias[3][1][2] &&
				piezasPropias[2][0][0] == piezasPropias[2][0][1] &&
				piezasPropias[2][1][0] == piezasPropias[2][0][1] &&
				piezasPropias[2][1][0] == piezasPropias[2][2][1] &&
				piezasPropias[2][1][0] == piezasPropias[2][1][2]);
	}
	bool paso2(std::vector<int>&movSolver, int i=0){
		if(ochoEsquinas() ){
			return true;
		}
		if(i>=14)
			return false;
		next=new solverRubik(this,2);
		if(mov!=11 && mov!=2){
			if(next->paso2(movSolver,i+1)){
				movSolver[i]=2;
				delete next;
				return true;
			}
			(*movimientos[2])(next->piezasPropias);
			if(next->paso2(movSolver,i+2)){
				movSolver[i]=2;
				movSolver[i+1]=2;
				delete next;
				return true;
			}
			(*movimientos[2])(next->piezasPropias);
			if(next->paso2(movSolver,i+1)){
				movSolver[i]=11;
				delete next;
				return true;
			}
			(*movimientos[2])(next->piezasPropias);
		}else{
			(*movimientos[11])(next->piezasPropias);
		}
		if(mov!=14 && mov!=5){
			next->mov=5;
			(*movimientos[5])(next->piezasPropias);
			if(next->paso2(movSolver,i+1)){
				movSolver[i]=5;
				delete next;
				return true;
			}
			(*movimientos[5])(next->piezasPropias);
			if(next->paso2(movSolver,i+2)){
				movSolver[i]=5;
				movSolver[i+1]=5;
				delete next;
				return true;
			}
			(*movimientos[5])(next->piezasPropias);
			if(next->paso2(movSolver,i+1)){
				movSolver[i]=14;
				delete next;
				return true;
			}
			(*movimientos[5])(next->piezasPropias);
		}
		if(mov!=17 && mov!=8){
			next->mov=8;
			(*movimientos[8])(next->piezasPropias);
			if(next->paso2(movSolver,i+1)){
				movSolver[i]=8;
				delete next;
				return true;
			}
			(*movimientos[8])(next->piezasPropias);
			if(next->paso2(movSolver,i+2)){
				movSolver[i]=8;
				movSolver[i+1]=8;
				delete next;
				return true;
			}
			(*movimientos[8])(next->piezasPropias);
			if(next->paso2(movSolver,i+1)){
				movSolver[i]=17;
				delete next;
				return true;
			}
			(*movimientos[8])(next->piezasPropias);
		}
		movSolver[i]=-1;
		movSolver[i+1]=-1;
		delete next;
		return false;
	}
	bool paso4(std::vector<int>&movSolver){//3,8,1,4,7.
		if( ochoEsquinas() && piezasPropias[0][1][0]== piezasPropias[0][0][0]
			&& piezasPropias[4][0][1]== piezasPropias[4][0][0]
			&& piezasPropias[4][2][1]== piezasPropias[4][2][0]
			&& piezasPropias[5][1][0]== piezasPropias[5][0][0]){
			//cout<<"Logrado\nLogrado\nLogrado\nLogrado\nLogrado\n";
			return true;
		}
		if(prof>=9)
		   return false;
		next=new solverRubik(this,1);
		if(mov!=10 ){
			if(next->paso4(movSolver)){
				movSolver[prof]=1;
				delete next;
				return true;
			}
		}
		(*movimientos[10])(next->piezasPropias);
		if(mov!=12){
			(*movimientos[3])(next->piezasPropias);
			next->mov=3;
			if(next->paso4(movSolver)){
				movSolver[prof]=3;
				delete next;
				return true;
			}
			(*movimientos[12])(next->piezasPropias);
		}
		if(mov!=13 && mov!=3 && mov!=12){
			(*movimientos[4])(next->piezasPropias);
			next->mov=4;
			if(next->paso4(movSolver)){
				movSolver[prof]=4;
				delete next;
				return true;
			}
			(*movimientos[13])(next->piezasPropias);
		}
		if(mov!=16){
			(*movimientos[7])(next->piezasPropias);
			next->mov=7;
			if(next->paso4(movSolver)){
				movSolver[prof]=7;
				delete next;
				return true;
			}
			(*movimientos[16])(next->piezasPropias);
		}
		if(mov!=17 && mov!=7 && mov!=16){
			(*movimientos[8])(next->piezasPropias);
			next->mov=8;
			if(next->paso4(movSolver)){
				movSolver[prof]=8;
				delete next;
				return true;
			}
			(*movimientos[17])(next->piezasPropias);
		}
		if(mov!=1){
			(*movimientos[10])(next->piezasPropias);
			next->mov=10;
			if(next->paso4(movSolver)){
				movSolver[prof]=10;
				delete next;
				return true;
			}
			(*movimientos[1])(next->piezasPropias);
		}
		if(mov!=3){
			(*movimientos[12])(next->piezasPropias);
			next->mov=12;
			if(next->paso4(movSolver)){
				movSolver[prof]=12;
				delete next;
				return true;
			}
			(*movimientos[3])(next->piezasPropias);
		}
		if(mov!=4 && mov!=3 && mov!=12){
			(*movimientos[13])(next->piezasPropias);
			next->mov=13;
			if(next->paso4(movSolver)){
				movSolver[prof]=13;
				delete next;
				return true;
			}
			(*movimientos[4])(next->piezasPropias);
		}
		if(mov!=7){
			(*movimientos[16])(next->piezasPropias);
			next->mov=16;
			if(next->paso4(movSolver)){
				movSolver[prof]=16;
				delete next;
				return true;
			}
			(*movimientos[7])(next->piezasPropias);
		}
		if(mov!=8 && mov!=7 && mov!=16){
			(*movimientos[17])(next->piezasPropias);
			next->mov=17;
			if(next->paso4(movSolver)){
				movSolver[prof]=17;
				delete next;
				return true;
			}
			(*movimientos[8])(next->piezasPropias);
		}
		
		movSolver[prof]=-1;
		delete next;
		return false;
	}
	bool paso5(std::vector<int>&movSolver){//5,6,1,7.
		if( ochoEsquinas() && piezasPropias[0][0][0]== piezasPropias[0][0][1]
							&& piezasPropias[3][0][0]== piezasPropias[3][0][1]
							&& piezasPropias[5][0][0]== piezasPropias[5][2][1]
							&& piezasPropias[3][2][0]== piezasPropias[3][2][1]){
			//cout<<"Logrado\nLogrado\nLogrado\nLogrado\nLogrado\n";
			return true;
		}
		if(prof>=9)
			return false;
		next=new solverRubik(this,1);
		if(mov!=10){
			if(next->paso5(movSolver)){
				movSolver[prof]=1;
				delete next;
				return true;
			}
		}
		(*movimientos[10])(next->piezasPropias);
		if(mov!=14){
			(*movimientos[5])(next->piezasPropias);
			next->mov=5;
			if(next->paso5(movSolver)){
				movSolver[prof]=5;
				delete next;
				return true;
			}
			(*movimientos[14])(next->piezasPropias);
		}
		if(mov!=15){
			(*movimientos[6])(next->piezasPropias);
			next->mov=6;
			if(next->paso5(movSolver)){
				movSolver[prof]=6;
				delete next;
				return true;
			}
			(*movimientos[15])(next->piezasPropias);
		}
		if(mov!=16 && mov!=6 && mov!=15){
			(*movimientos[7])(next->piezasPropias);
			next->mov=7;
			if(next->paso5(movSolver)){
				movSolver[prof]=7;
				delete next;
				return true;
			}
			(*movimientos[16])(next->piezasPropias);
		}
		
		if(mov!=1){
			(*movimientos[10])(next->piezasPropias);
			next->mov=10;
			if(next->paso5(movSolver)){
				movSolver[prof]=10;
				delete next;
				return true;
			}
			(*movimientos[1])(next->piezasPropias);
		}
		if(mov!=5){
			(*movimientos[14])(next->piezasPropias);
			next->mov=14;
			if(next->paso5(movSolver)){
				movSolver[prof]=14;
				delete next;
				return true;
			}
			(*movimientos[5])(next->piezasPropias);
		}
		if(mov!=6){
			(*movimientos[15])(next->piezasPropias);
			next->mov=15;
			if(next->paso5(movSolver)){
				movSolver[prof]=15;
				delete next;
				return true;
			}
			(*movimientos[6])(next->piezasPropias);
		}
		if(mov!=7 && mov!=6 && mov!=15){
			(*movimientos[16])(next->piezasPropias);
			next->mov=16;
			if(next->paso5(movSolver)){
				movSolver[prof]=16;
				delete next;
				return true;
			}
			(*movimientos[7])(next->piezasPropias);
		}
		
		movSolver[prof]=-1;
		delete next;
		return false;
	}
	bool paso7(std::vector<int>&movSolver,int i=0){//3,6,1,
		if( ochoEsquinas() ){
		
			if (piezasPropias[0][0][1]== piezasPropias[0][2][1]
				&& piezasPropias[1][0][0]== piezasPropias[1][0][1]
					&& piezasPropias[5][0][0]== piezasPropias[5][0][1]
						&& piezasPropias[1][2][0]== piezasPropias[1][2][1]){
				return true;
			}
						if(piezasPropias[0][1][2]== piezasPropias[0][2][2]
							&& piezasPropias[2][0][0]== piezasPropias[2][0][1]
								&& piezasPropias[5][0][0]== piezasPropias[5][1][2]
									&& piezasPropias[2][2][0]== piezasPropias[2][2][1]) {
							movSolver[i]=21;
							return true;
						}
									//cout<<"Logrado\nLogrado\nLogrado\nLogrado\nLogrado\n";
									
		}
		
	if(i>=12)
		return false;
	
	next=new solverRubik(this,1);
	if(mov!=10 && mov!=1){
		if(next->paso7(movSolver,i+1)){
			movSolver[i]=1;
			delete next;
			return true;
		}
		(*movimientos[1])(next->piezasPropias);
		if(next->paso7(movSolver,i+2)){
			movSolver[i]=1;
			movSolver[i+1]=1;
			delete next;
			return true;
		}
		(*movimientos[1])(next->piezasPropias);
		if(next->paso7(movSolver,i+1)){
			movSolver[i]=10;
			delete next;
			return true;
		}
		(*movimientos[1])(next->piezasPropias);
	}else{
		(*movimientos[10])(next->piezasPropias);
	}
	if(mov!=12 && mov!=3){
		next->mov=3;
		(*movimientos[3])(next->piezasPropias);
		if(next->paso7(movSolver,i+1)){
			movSolver[i]=3;
			delete next;
			return true;
		}
		(*movimientos[3])(next->piezasPropias);
		if(next->paso7(movSolver,i+2)){
			movSolver[i]=3;
			movSolver[i+1]=3;
			delete next;
			return true;
		}
		(*movimientos[3])(next->piezasPropias);
		if(next->paso7(movSolver,i+1)){
			movSolver[i]=12;
			delete next;
			return true;
		}
		(*movimientos[3])(next->piezasPropias);
	}
	if(mov!=15 && mov!=6){
		next->mov=6;
		(*movimientos[6])(next->piezasPropias);
		if(next->paso7(movSolver,i+1)){
			movSolver[i]=6;
			delete next;
			return true;
		}
		(*movimientos[6])(next->piezasPropias);
		if(next->paso7(movSolver,i+2)){
			movSolver[i]=6;
			movSolver[i+1]=6;
			delete next;
			return true;
		}
		(*movimientos[6])(next->piezasPropias);
		if(next->paso7(movSolver,i+1)){
			movSolver[i]=15;
			delete next;
			return true;
		}
		(*movimientos[6])(next->piezasPropias);
	}
	movSolver[i]=-1;
	movSolver[i+1]=-1;
	delete next;
	return false;
	}
	bool paso6(std::vector<int>&movSolver){
		if(piezasPropias[0][0][0] ==piezasPropias[0][1][1]){
			return true;
		}
		if(piezasPropias[0][0][0] ==piezasPropias[5][1][1]){//M,E,E
			movSolver[0]=7;
			movSolver[1]=1;
			movSolver[2]=1;
			movSolver[3]=16;
			return true;
		}
		if(piezasPropias[0][0][0] ==piezasPropias[1][1][1]){//E,M,Eprima
			movSolver[0]=1;
			movSolver[1]=7;
			movSolver[2]=10;
			movSolver[3]=16;
			return true;
		}
		if(piezasPropias[0][0][0] ==piezasPropias[3][1][1]){//E,M,E
			movSolver[0]=1;
			movSolver[1]=7;
			movSolver[2]=1;
			movSolver[3]=16;
			return true;
		}
		if(piezasPropias[0][0][0] ==piezasPropias[2][1][1]){//M,Eprima
			movSolver[0]=7;
			movSolver[1]=10;
			movSolver[2]=16;
			return true;
		}
		if(piezasPropias[0][0][0] ==piezasPropias[4][1][1]){//M,E
			movSolver[0]=7;
			movSolver[1]=1;
			movSolver[2]=16;
			return true;
		}
		return false;
	}
	bool paso8(std::vector<int>&movSolver){//6,1,
		if( penultimoPaso()){
									//cout<<"Logrado\nLogrado\nLogrado\nLogrado\nLogrado\n";
			return true;						
		}
		if(prof>=17)
		   return false;
		next=new solverRubik(this,1);
		if(mov!=10 ){
			if(next->paso8(movSolver)){
				movSolver[prof]=1;
				delete next;
				return true;
			}
		}
		(*movimientos[10])(next->piezasPropias);
		if(mov!=15   ){
			(*movimientos[6])(next->piezasPropias);
			next->mov=6;
			if(next->paso8(movSolver)){
				movSolver[prof]=6;
				delete next;
				return true;
			}
			(*movimientos[15])(next->piezasPropias);
		}
		
		if(mov!=1  ){
			(*movimientos[10])(next->piezasPropias);
			next->mov=10;
			if(next->paso8(movSolver)){
				movSolver[prof]=10;
				delete next;
				return true;
			}
			(*movimientos[1])(next->piezasPropias);
		}
		if(mov!=6 ){
			(*movimientos[15])(next->piezasPropias);
			next->mov=15;
			if(next->paso8(movSolver)){
				movSolver[prof]=15;
				delete next;
				return true;
			}
			(*movimientos[6])(next->piezasPropias);
		}
		
		movSolver[prof]=-1;
		delete next;
		return false;
	}
	bool paso9(std::vector<int>&movSolver){
		solverRubik cuboAuxiliar(this,-1);
		(*movimientos[22])(cuboAuxiliar.piezasPropias);
		movSolver[0]=22;
		if(cuboAuxiliar.piezasPropias[2][0][0]== cuboAuxiliar.piezasPropias[2][0][1] ){
			return true;
		}
		(*movimientos[15])(cuboAuxiliar.piezasPropias);
		(*movimientos[0])(cuboAuxiliar.piezasPropias);
		(*movimientos[15])(cuboAuxiliar.piezasPropias);
		(*movimientos[9])(cuboAuxiliar.piezasPropias);
		(*movimientos[15])(cuboAuxiliar.piezasPropias);
		(*movimientos[9])(cuboAuxiliar.piezasPropias);
		(*movimientos[15])(cuboAuxiliar.piezasPropias);
		(*movimientos[0])(cuboAuxiliar.piezasPropias);
		(*movimientos[6])(cuboAuxiliar.piezasPropias);
		(*movimientos[0])(cuboAuxiliar.piezasPropias);
		(*movimientos[6])(cuboAuxiliar.piezasPropias);
		(*movimientos[6])(cuboAuxiliar.piezasPropias);
		movSolver[1]=15;
		movSolver[2]=0;
		movSolver[3]=15;
		movSolver[4]=9;
		movSolver[5]=15;
		movSolver[6]=9;
		movSolver[7]=15;
		movSolver[8]=0;
		movSolver[9]=6;
		movSolver[10]=0;
		movSolver[11]=6;
		movSolver[12]=6;
		if(cuboAuxiliar.piezasPropias[2][0][0]== cuboAuxiliar.piezasPropias[2][0][1] ){
			return true;
		}
		(*movimientos[15])(cuboAuxiliar.piezasPropias);
		(*movimientos[0])(cuboAuxiliar.piezasPropias);
		(*movimientos[15])(cuboAuxiliar.piezasPropias);
		(*movimientos[9])(cuboAuxiliar.piezasPropias);
		(*movimientos[15])(cuboAuxiliar.piezasPropias);
		(*movimientos[9])(cuboAuxiliar.piezasPropias);
		(*movimientos[15])(cuboAuxiliar.piezasPropias);
		(*movimientos[0])(cuboAuxiliar.piezasPropias);
		(*movimientos[6])(cuboAuxiliar.piezasPropias);
		(*movimientos[0])(cuboAuxiliar.piezasPropias);
		(*movimientos[6])(cuboAuxiliar.piezasPropias);
		(*movimientos[6])(cuboAuxiliar.piezasPropias);
		movSolver[1]=8;
		movSolver[2]=9;
		movSolver[3]=8;
		movSolver[4]=0;
		movSolver[5]=8;
		movSolver[6]=0;
		movSolver[7]=8;
		movSolver[8]=9;
		movSolver[9]=17;
		movSolver[10]=9;
		movSolver[11]=17;
		movSolver[12]=17;
		if(cuboAuxiliar.piezasPropias[2][0][0]== cuboAuxiliar.piezasPropias[2][0][1] ){
			return true;
		}
		return false;
	}
	void simplificarMov(std::vector<int>&movSolver){
		int cambiosY[24]={0,1,2,6,16,8,5,4,3 ,9,10,11,15,7,17,14,13,12 ,18,20,22,21,23,19};
		int cambiosZ[24]={8,16,6,3,4,5,0,1,2 ,17,7,15,12,13,14,9,10,11 ,23,19,18, 20,22,21};
		int cambiosX[24]={3,13,5,2,1,0,6,7,8 ,12,4,14,11,10,9,15,16,17 ,19,21,20 ,22,18,23};
		int cambiosYprima[24]={0,1,2,8,7,6,3,13,5,9,10,11,17,16,15,12,4,14 ,18,23,19,21,20,22};
		int cambiosZprima[24]={6,7,8,3,4,5,2,10,0 ,15,16,17,12,13,14,11,1,9 ,20,19,21 ,23,22,18};
		int cambiosXprima[24]={5,4,3,0,10,2,6,7,8 ,14,13,12,9,1,11,15,16,17 ,22,18,20 ,19,21,23};
		for(int i=(int)movSolver.size()-1;i>-1;){
			if(movSolver[i]==18){
				for(int j=i+1;j<movSolver.size();j++)
					movSolver[j]=cambiosY[movSolver[j]];
				movSolver.erase (movSolver.begin()+i);
			}else if(movSolver[i]==19){
				for(int j=i+1;j<movSolver.size();j++)
					movSolver[j]=cambiosZ[movSolver[j]];
				movSolver.erase (movSolver.begin()+i);
			}else if(movSolver[i]==20){
				for(int j=i+1;j<movSolver.size();j++)
					movSolver[j]=cambiosX[movSolver[j]];
				movSolver.erase (movSolver.begin()+i);
			}else if(movSolver[i]==21){
				for(int j=i+1;j<movSolver.size();j++)
					movSolver[j]=cambiosYprima[movSolver[j]];
				movSolver.erase (movSolver.begin()+i);
			}else if(movSolver[i]==22){
				for(int j=i+1;j<movSolver.size();j++)
					movSolver[j]=cambiosZprima[movSolver[j]];
				movSolver.erase (movSolver.begin()+i);
			}else if(movSolver[i]==23){
				for(int j=i+1;j<movSolver.size();j++)
					movSolver[j]=cambiosXprima[movSolver[j]];
				movSolver.erase (movSolver.begin()+i);
			}
			--i;
		}
		for(int i=0;i<(int)movSolver.size()-3;){
			if(movSolver[i]==movSolver[i+1]&&movSolver[i]==movSolver[i+2]){
				if(movSolver[i]==movSolver[i+3]){
					movSolver.erase (movSolver.begin()+i,movSolver.begin()+i+4);	
				}else{
					movSolver.erase (movSolver.begin()+i,movSolver.begin()+i+2);
					if(movSolver[i]<9){
						movSolver[i]+=9;
					}else if(movSolver[i]<18){
						movSolver[i]-=9;
					}else if(movSolver[i]<21){
						movSolver[i]+=3;
					}else{
						movSolver[i]-=3;
					}
				}
				i=0;
			}else if(movSolver[i]<9){
				if(movSolver[i+1]==movSolver[i]+9){
					movSolver.erase (movSolver.begin()+i,movSolver.begin()+i+2);
					i=0;
				}else
				   ++i;
			}else if(movSolver[i]<18){
				if(movSolver[i+1]==movSolver[i]-9){
					movSolver.erase (movSolver.begin()+i,movSolver.begin()+i+2);
					i=0;
				}else
				   ++i;
			}else if(movSolver[i]<21){
				if(movSolver[i+1]==movSolver[i]+3){
					movSolver.erase (movSolver.begin()+i,movSolver.begin()+i+2);
					i=0;
				}else
				   ++i;
			}else{
				if(movSolver[i+1]==movSolver[i]-3){
					movSolver.erase (movSolver.begin()+i,movSolver.begin()+i+2);
					i=0;
				}else
					++i;
			}
		}
	}
	void reinicio() {
		prof = 0;
		prev = 0;
		next = 0;
		mov = -1;
		for (int i = 0; i < 9; i++) {
			piezasPropias[0][i / 3][i % 3] = 'w';//Up
			piezasPropias[1][i / 3][i % 3] = 'r';//Front
			piezasPropias[2][i / 3][i % 3] = 'b';//Right
			piezasPropias[3][i / 3][i % 3] = 'o';//Back
			piezasPropias[4][i / 3][i % 3] = 'g';//Left
			piezasPropias[5][i / 3][i % 3] = 'y';//Down
		}
		vectorMovInverso.resize(0);
	}
	std::vector<int> resolver (){
		std::vector<int> movSolver;
		std::vector<int> movSolverAux(20,-1);
		//solverRubik aux(this,-1);
		if(paso2(movSolverAux)){
			for(int i=0;movSolverAux[i]!=-1;++i){
				(*movimientos[movSolverAux[i] ])(piezasPropias);
				//std::cout<<movSolverAux[i]<<",";
				movSolver.push_back(movSolverAux[i]);
				movSolverAux[i]=-1;
			}
			//cout<<endl;
		}else{
			std::cout<<"Paso 2 Fallido"<<std::endl;
		}
		if(paso4(movSolverAux)){
			for(int i=0;movSolverAux[i]!=-1;++i){
				(*movimientos[movSolverAux[i] ])(piezasPropias);
				//cout<<movSolverAux[i]<<",";
				movSolver.push_back(movSolverAux[i]);
				movSolverAux[i]=-1;
			}
			//cout<<endl;
		}else{
			std::cout<<"Paso 4 Fallido"<<std::endl;
		}
		if(paso5(movSolverAux)){
			for(int i=0;movSolverAux[i]!=-1;++i){
				(*movimientos[movSolverAux[i] ])(piezasPropias);
				//cout<<movSolverAux[i]<<",";
				movSolver.push_back(movSolverAux[i]);
				movSolverAux[i]=-1;
			}
			//cout<<endl;
		}else{
			std::cout<<"Paso 5 Fallido"<<std::endl;
		}
		if(paso6(movSolverAux)){
			for(int i=0;movSolverAux[i]!=-1;++i){
				(*movimientos[movSolverAux[i] ])(piezasPropias);
				//cout<<movSolverAux[i]<<",";
				movSolver.push_back(movSolverAux[i]);
				movSolverAux[i]=-1;
			}
			//cout<<endl;
		}else{
			std::cout<<"Paso 6 Fallido"<<std::endl;
		}
		if(paso7(movSolverAux)){
			for(int i=0;movSolverAux[i]!=-1;++i){
				(*movimientos[movSolverAux[i] ])(piezasPropias);
				//cout<<movSolverAux[i]<<",";
				movSolver.push_back(movSolverAux[i]);
				movSolverAux[i]=-1;
			}
			//cout<<endl;
		}else{
			std::cout<<"Paso 7 Fallido"<<std::endl;
		}
		if(paso8(movSolverAux)){
			for(int i=0;movSolverAux[i]!=-1;++i){
				(*movimientos[movSolverAux[i] ])(piezasPropias);
				//cout<<movSolverAux[i]<<",";
				movSolver.push_back(movSolverAux[i]);
				movSolverAux[i]=-1;
			}
			//cout<<endl;
		}else{
			std::cout<<"Paso 8 Fallido"<<std::endl;
		}
		if(paso9(movSolverAux)){
			for(int i=0;movSolverAux[i]!=-1;++i){
				(*movimientos[movSolverAux[i] ])(piezasPropias);
				//cout<<movSolverAux[i]<<",";
				movSolver.push_back(movSolverAux[i]);
				movSolverAux[i]=-1;
			}
			std::cout<<std::endl;
		}else{
			std::cout<<"Paso 9 Fallido"<<std::endl;
		}
		std::cout<<std::endl;
		simplificarMov(movSolver);
		simplificarMov(vectorMovInverso);
		for (int i = 0; i < movSolver.size(); ++i) {
			std::cout << movSolver[i] << ",";
		}
		std::cout << std::endl;
		for (int i = 0; i < vectorMovInverso.size(); ++i) {
			std::cout << vectorMovInverso[i] << ",";
		}
		std::cout<<std::endl <<movSolver.size()<<std::endl;
		//print();
		if(movSolver.size()>vectorMovInverso.size()){
			movSolver = vectorMovInverso;
		}
		vectorMovInverso.resize(0);
		return movSolver;
	}
	void print(){
		for(int i=0;i<3;i++){
			std::cout<<piezasPropias[0][i]<<std::endl;
		}
		for(int i=0;i<3;i++){
			std::cout<<piezasPropias[1][i]<<" "<<piezasPropias[2][i]<<" "<<piezasPropias[3][i]<<" "<<piezasPropias[4][i]<<std::endl;
		}
		for(int i=0;i<3;i++){
			std::cout<<piezasPropias[5][i]<<std::endl;
		}
		std::cout<<std::endl;
	}
	void operator=(solverRubik nC){
		for(int i=0;i<6;i++){
			for(int j=0;j<3;j++){
				for(int k=0;k<3;k++){
					piezasPropias[i][j][k]=nC.piezasPropias[i][j][k];
				}
			}
		}
	}
};
}
#endif 