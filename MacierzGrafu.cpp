#include "MacierzGrafu.h"

std::stack < int > stosMG;

void DFS_MS(int ** macierz, int n){
	int *kolory = (int*)malloc(n * sizeof(int));//tablica kolorów wierzcho³ków grafu numerowana od 0/ 0 bia³y, 1 szary, 2 czarny
	for(int i = 0; i < n; i++){
		kolory[i] = 0;
	}
	for(int i = 0; i < n; i++){
		if(!DFStsort_MG(macierz, i, n, kolory)){//przerywa jeœli znajdzie cykl
			printf("\nError: Graf posiada cykl!\n");
			while(!stosMG.empty())//czyszczenie stosu
				stosMG.pop();
			return;
		}
	}
	while(!stosMG.empty()){//wypisanie elementów
		printf("%d ", stosMG.top());
		stosMG.pop();
	}
	delete[] kolory;
}

bool DFStsort_MG(int ** macierz, int v, int n, int * kolory){
	if(kolory[v - 1] == 2) return true;//wierzcho³ek przetworzony
	if(kolory[v - 1] == 1) return false;//znaleziony cykl
	else{
		kolory[v - 1] = 1;
		int k = macierz[v][n + 1];
		if(k){
			while(k != macierz[n + 1][v]){//dopóki k != od ostatniego elementu listy
				if(!DFStsort_MG(macierz, k, n, kolory)) return false;
				k = macierz[v][k] - n;
			}
			if(!DFStsort_MG(macierz, k, n, kolory)) return false;//wywo³anie dla ostatniego elementu, pêtla koñczy siê przed wywo³aniem
		}
		kolory[v - 1] = 2;
		stosMG.push(v);
		return true;
	}
}


//n - iloœæ elementów w grafie, macierz o rozmiarze (n+2)^2
void DEL_MG(int ** macierz, int n){
	int *Vin = (int*)malloc(n * sizeof(int));//tablica stopni wchodz¹cych wierzcho³ków grafu, numerowana od 0
	bool *deleted = (bool*)malloc(n * sizeof(bool));//tablica usuniêtych wierzcho³ków, numerowana od 0
	for(int i = 0; i < n; i++){
		Vin[i] = 0;
		deleted[i] = false;
	}
	//zliczanie stopni wejœciowych wierzcho³ków grafu
	for(int i = 1; i <= n; i++){//wiersz - wierzcho³ek pocz¹tkowy
		int k = macierz[i][n + 1];
		if(k){
			while(k != macierz[n + 1][i]){//dopóki k != od ostatniego elementu listy
				Vin[k - 1]++;
				k = macierz[i][k] - n;
			}
			Vin[k - 1]++;//zwiêkszenie Vin dla ostatniego elementu, pêtla koñczy siê przed zwiêkszeniem
		}
	}
	bool test = false;
	for(int i = 1; i <= n; i++){
		if(Vin[i] || deleted[i]){
			if(Vin[i])	test = false; //je¿eli po zakoñczeniu wykonywania pêtli test bêdzie false, to istnieje wierzcho³ek o wiêkszym od 0 stopniu wejœciowym czyli graf posiada cykl
			continue;
		}
		test = true;
		deleted[i] = true;
		///zmniejszenie stopni wejœciowych dla nastêpników
		int k = macierz[i][n + 1];
		if(k){
			while(k != macierz[n + 1][i]){//dopóki k != od ostatniego elementu listy
				Vin[k - 1]--;
				k = macierz[i][k] - n;
			}
			if(!deleted[k - 1]) Vin[k - 1]--;//zmniejszenie Vin dla ostatniego elementu, pêtla koñczy siê przed zmniejszeniem
		}
		printf("%d ", i);
		i = 0;//powrót do pierwszego wierzcho³ka
	}
	if(!test){
		printf("\nError: Graf posiada cykl!\n");
	}

}