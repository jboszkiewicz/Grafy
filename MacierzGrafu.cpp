#include "MacierzGrafu.h"

std::stack < int > stosMG;

std::string DFS_MG(int ** macierz, int n){
	std::string wynik = "";
	int *kolory = (int*)malloc(n * sizeof(int));//tablica kolor�w wierzcho�k�w grafu numerowana od 0/ 0 bia�y, 1 szary, 2 czarny
	for(int i = 0; i < n; i++){
		kolory[i] = 0;
	}
	for(int i = 1; i < n + 1; i++){
		if(!DFStsort_MG(macierz, i, n, kolory)){//przerywa je�li znajdzie cykl
			printf("\nError: Graf posiada cykl!\n");
			while(!stosMG.empty())//czyszczenie stosu
				stosMG.pop();
			delete[] kolory;
			return wynik;
		}
	}
	while(!stosMG.empty()){//wypisanie element�w
		wynik += std::to_string(stosMG.top()) + " ";//
		stosMG.pop();
	}
	delete[] kolory;
	return wynik;
}

bool DFStsort_MG(int ** macierz, int v, int n, int * kolory){
	if(kolory[v - 1] == 2) return true;//wierzcho�ek przetworzony
	if(kolory[v - 1] == 1) return false;//znaleziony cykl
	else{
		kolory[v - 1] = 1;
		int k = macierz[v][n + 1];
		if(k){
			while(k != macierz[n + 1][v]){//dop�ki k != od ostatniego elementu listy
				if(!DFStsort_MG(macierz, k, n, kolory)) return false;
				k = macierz[v][k] - n;
			}
			if(!DFStsort_MG(macierz, k, n, kolory)) return false;//wywo�anie dla ostatniego elementu, p�tla ko�czy si� przed wywo�aniem
		}
		kolory[v - 1] = 2;
		stosMG.push(v);
		return true;
	}
}


//n - ilo�� element�w w grafie, macierz o rozmiarze (n+2)^2
std::string DEL_MG(int ** macierz, int n){
	std::string wynik = "";
	int *Vin = (int*)malloc(n * sizeof(int));//tablica stopni wchodz�cych wierzcho�k�w grafu, numerowana od 0
	bool *deleted = (bool*)malloc(n * sizeof(bool));//tablica usuni�tych wierzcho�k�w, numerowana od 0
	for(int i = 0; i < n; i++){
		Vin[i] = 0;
		deleted[i] = false;
	}
	//zliczanie stopni wej�ciowych wierzcho�k�w grafu
	for(int i = 1; i <= n; i++){//wiersz - wierzcho�ek pocz�tkowy
		
		int k = macierz[i][n + 1];
		if(k){
			while(k != macierz[n + 1][i]){//dop�ki k != od ostatniego elementu listy
				Vin[k - 1]++;
				k = macierz[i][k] - n;
			}
			Vin[k - 1]++;//zwi�kszenie Vin dla ostatniego elementu, p�tla ko�czy si� przed zwi�kszeniem
		}
	}
	bool test = false;
	for(int i = 1; i <= n; i++){
		if(Vin[i - 1] || deleted[i - 1]){
			if(Vin[i - 1])	test = false; //je�eli po zako�czeniu wykonywania p�tli test b�dzie false, to istnieje wierzcho�ek o wi�kszym od 0 stopniu wej�ciowym czyli graf posiada cykl
			continue;
		}
		test = true;
		deleted[i - 1] = true;
		///zmniejszenie stopni wej�ciowych dla nast�pnik�w
		int k = macierz[i][n + 1];
		if(k){
			while(k != macierz[n + 1][i]){//dop�ki k != od ostatniego elementu listy
				Vin[k - 1]--;
				k = macierz[i][k] - n;
			}
			if(!deleted[k - 1]) Vin[k - 1]--;//zmniejszenie Vin dla ostatniego elementu, p�tla ko�czy si� przed zmniejszeniem
		}
		wynik += std::to_string(i) + " ";
		i = 0;//powr�t do pierwszego wierzcho�ka
	}
	if(!test){
		printf("\nError: Graf posiada cykl!\n");
		wynik = "";
	}
	delete[] Vin;
	delete[] deleted;
	return wynik;

}