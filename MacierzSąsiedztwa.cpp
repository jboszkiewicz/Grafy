#include "MacierzS�siedztwa.h"

std::stack < int > stosMS;

std::string DFS_MS(bool ** macierz, int n){
	std::string wynik = "";
	int *kolory = (int*)malloc(n * sizeof(int));//tablica kolor�w wierzcho�k�w grafu, 0 bia�y, 1 szary, 2 czarny
	for(int i = 0; i < n; i++){
		kolory[i] = 0;
	}
	for(int i = 0; i < n; i++){
		if(!DFStsort_MS(macierz, i, n, kolory)){//przerywa je�li znajdzie cykl
			printf("\nError: Graf posiada cykl!\n");
			while(!stosMS.empty())//czyszczenie stosu
				stosMS.pop();
			return "";
		}
	}
	while(!stosMS.empty()){//wypisanie element�w
		wynik += std::to_string(stosMS.top()) + " ";
	//	printf("%d ", stosMS.top());
		stosMS.pop();
	}
	return wynik;
	delete[] kolory;
}

bool DFStsort_MS(bool ** macierz, int v, int n, int * kolory){
	if(kolory[v] == 2) return true;//wierzcho�ek przetworzony
	if(kolory[v] == 1) return false;//znaleziony cykl
	else{
		kolory[v] = 1;
		for(int j = 0; j < n; j++){
			if(macierz[v][j])
				if(!DFStsort_MS(macierz, j, n, kolory)) return false;
		}
		kolory[v] = 2;
		stosMS.push(v);
		return true;
	}
}

std::string DEL_MS(bool ** macierz, int n){
	std::string wynik = "";
	int *Vin = (int*)malloc(n * sizeof(int));//tablica stopni wchodz�cych wierzcho�k�w grafu
	bool *deleted = (bool*)malloc(n * sizeof(bool));//tablica usuni�tych wierzcho�k�w
	for(int i = 0; i < n; i++){
		Vin[i] = 0;
		deleted[i] = false;
	}
	//zliczanie stopni wej�ciowych wierzcho�k�w grafu
	for(int i = 0; i < n; i++){//wiersz - wierzcho�ek pocz�tkowy
		for(int j = 0; j < n; j++){//kolumna - wierzcho�ek ko�cowy
			if(macierz[i][j]){
				Vin[j]++;
			}
		}
	}
	bool test = false;
	for(int i = 0; i < n; i++){
		if(Vin[i] || deleted[i]){
			if(Vin[i])	test = false; //je�eli po zako�czeniu wykonywania p�tli test b�dzie false, to istnieje wierzcho�ek o wi�kszym od 0 stopniu wej�ciowym czyli graf posiada cykl
			continue;
		}
		test = true;
		deleted[i] = true;
		///zmniejszenie stopni wej�ciowych dla nast�pnik�w
		for(int j = 0; j < n; j++)
			if(macierz[i][j]) Vin[j]--;
		wynik += std::to_string(i) + " ";
	//	printf("%d ", i);
		i = -1;//powr�t do pierwszego wierzcho�ka
	}
	if(!test){
		printf("\nError: Graf posiada cykl!\n");
		wynik = "";
	}
	return wynik;
	delete[] Vin;
	delete[] deleted;
}