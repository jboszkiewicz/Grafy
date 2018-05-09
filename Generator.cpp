#include<iostream>
#include<stdlib.h>

using namespace std;

bool CheckAcyclic(bool ** macierz, int * kolory, int v, int n){
	if(kolory[v] == 2) return true;//wierzcho�ek przetworzony
	else if(kolory[v] == 1) return false;//znaleziony cykl
	else{
		kolory[v] = 1;
		for(int i = 0; i < n; i++){
			if(macierz[v][i] == 1){
				if(!CheckAcyclic(macierz, kolory, i, n)){
					return false;
				}
			}
		}
		kolory[v] = 2;
		return true;
	}
}

void GenerateGraph(bool **macierz, int v, int e){
	int i, j, x, y;

	int *kolory = (int*)malloc(v * sizeof(int));//tablica kolor�w wierzcho�k�w grafu, 0 bia�y, 1 szary, 2 czarny

	i = 0;
	while(i < e){
		x = rand() % v;
		y = rand() % v;
		if(x != y && !macierz[x][y]){
			macierz[x][y] = 1;
			for(j = 0; j < v; j++)kolory[j] = 0;
			cout << "\rLosowanie kraw�dzi nr " << i;
			//cout << i << " Sprawdzam " << x << " " << y << endl;
			if(CheckAcyclic(macierz, kolory, x, v) == true){
				i++;
			//	cout << "Dodano" << endl;
			} else{
				macierz[x][y] = 0;
			//	cout << "nie dodano" << endl;
			}
		}
	}
	delete[] kolory;
}
