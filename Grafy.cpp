﻿// Grafy.cpp : Defines the entry point for the console application.
//

#include "MacierzGrafu.h"
#include "MacierzSąsiedztwa.h"
#include "Generator.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using tp = std::chrono::time_point<std::chrono::system_clock>; //do pomiaru czasu

void MStoMG(bool ** MS, int ** MG, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(MS[i][j] == 1){
				//dodanie j do listy następników i
				if(MG[i + 1][n + 1] == 0){//pusta lista następników
					MG[i + 1][n + 1] = MG[n + 1][i + 1] = j + 1;
					MG[i + 1][j + 1] = j + 1 + n;
				} else{//niepusta lista
					MG[i + 1][j + 1] = MG[i + 1][n + 1] + n;
					MG[i + 1][n + 1] = j + 1;
				}
				//dodanie i do listy poprzedników j
				if(MG[j + 1][0] == 0){//pusta lista poprzedników
					MG[j + 1][0] = MG[0][j + 1] = i + 1;
					MG[j + 1][i + 1] = i + 1;
				} else{//niepusta lista
					MG[j + 1][i + 1] = MG[j + 1][0];
					MG[j + 1][0] = i + 1;
				}
			}
		}
	}
	for(int i = 1; i < n + 1; i++){
		for(int j = 1; j < n + 1; j++){
			//lista wierzchołków nie będących następnikami ani poprzednikami
			if(i != j && MG[i][j] == 0){
				if(MG[i][i] == 0){//pusta lista
					MG[i][i] = -j;
					MG[i][j] = -j;
				} else{
					MG[i][j] = MG[i][i];
					MG[i][i] = -j;
				}
			}
		}
		if(MG[i][i] == 0)
			MG[i][i] = -i;
	}
}

int main()
{
	setlocale(LC_ALL, "polish");
	srand((unsigned)time(NULL));
	bool isCorrectAnswer = false, newGraph = true;
	int answer, type, source, n, m;
	tp start, end;
	std::string fileName = "";
	std::string wynik;
	std::fstream plik;

	bool ** MS = NULL;
	int ** MG = NULL;
	
	while(true){ //pętla główna programu
		isCorrectAnswer = false;
		while(newGraph){ //wybór źródła danych
			printf("\nWybierz źródło danych:\n");
			printf("   '1' - Generator;\n");
			printf("   '2' - Plik;\n");

			scanf_s("%d", &source);

			switch(source){
				case 1:// Generator
					while(true){ 
						puts("Podaj ilość wierzchołków: ");
						if(!scanf_s("%d", &n) || n < 1)
						puts("Incorrect answer. Try again.");
						else break;
					}
					//Generowanie grafu
					MS = new bool*[n];
					for(int i = 0; i < n; i++){
						MS[i] = new bool[n];
						for(int j = 0; j < n; j++)
							MS[i][j] = 0;
					}
					m = (int)ceil(n*(n - 1) / 4.0);//50% z n*(n-1)/2
					GenerateGraph(MS, n, m);

					newGraph = false;
					break;
				case 2:// Plik	
			
					while(!isCorrectAnswer){
						puts("Podaj nazwę pliku: ");
						std::cin >> fileName;

						plik.open(fileName, std::ios::in);
						if(plik.good() == true){
							std::cerr << "otworzono plik " << fileName << std::endl;
							std::string dane;
							getline(plik, dane);
							int spacja = dane.find(' ');
							n = atoi(dane.substr(0, spacja).c_str());
							m = atoi(dane.substr(spacja).c_str());
							std::cerr << "V=" << n << " E=" << m << std::endl;
							MS = new bool*[n];
							for(int i = 0; i < n; i++){
								MS[i] = new bool[n];
								for(int j = 0; j < n; j++)
									MS[i][j] = 0;
							}
							int i = 0;
							while(!plik.eof()){
								if(i == m){
									std::cout << "Ostrzeżenie: Za dużo krawędzi!" << std::endl;
									i++;
									break;
								}
								getline(plik, dane); //wczytanie CAŁEGO jednego wiersza danych
								int x, y;
								x = atoi(dane.substr(0, spacja).c_str());
								y= atoi(dane.substr(spacja).c_str());
								std::cerr <<i <<" X=" << x << " Y=" << y << std::endl;
								if(MS[x][y]){
									std::cout << "Krawędź już istnieje" << std::endl;
								} else{
									MS[x][y] = 1;
									i++;
								}
							}
							if(i > m){
								continue;
							}
							if(i < m){
								std::cout << "Ostrzeżenie: Za mało krawędzi!" << std::endl;
								continue;
							}
							std::cout << "zakończono" << std::endl;
							plik.close();
							newGraph = false;
							isCorrectAnswer = true;
						} else
							printf("Error: Nie znaleziono pliku!\n");
					}
					
					break;
				default:
					printf("Incorrect answer. Try again.");
					break;
			}
		}

		isCorrectAnswer = false;

		while(!isCorrectAnswer){
			printf("\nWybierz reprezentację maszynową grafu:\n");
			printf("   '1' - Macierz sąsiedztwa;\n");
			printf("   '2' - Macierz grafu;\n");

			scanf_s("%d", &type);
			switch(type){
				case 1:// Macierz sąsiedztwa - już istnieje
					isCorrectAnswer = true;
					break;
				case 2:// Macierz grafu
						//stworzenie MG
						MG = new int*[n + 2];
						for(int i = 0; i < n + 2; i++){
							MG[i] = new int[n + 2];
							for(int j = 0; j < n + 2; j++)
								MG[i][j] = 0;
						}
						MStoMG(MS, MG, n); // konwersja MS do MG
					isCorrectAnswer = true;
					break;
				default:
					printf("Incorrect answer. Try again.");
					break;
			}
		}

		isCorrectAnswer = false;

		while(!isCorrectAnswer){
			printf("\nCo chcesz zrobić z grafem:\n");
			printf("  1  Posortuj topologicznie z wykorzystaniem DFS;\n");
			printf("  2  Posortuj topologicznie z usuwaniem wierzchołków o zerowym stopniu wejściowym;\n");
			printf("  3  Zmień reprezentację maszynową;\n");
			printf("  4  Nowy graf;\n");
			printf("  5  Zakończ;\n");

			printf("Give your answer:");
			scanf_s("%d", &answer);

			if(type == 1){// Macierz sąsiedztwa
				switch(answer){
					case 1://DFS
						start = std::chrono::system_clock::now();
						wynik = DFS_MS(MS, n);
						end = std::chrono::system_clock::now();
						std::cout << wynik << std::endl;
						std::cout << "\nTime in microseconds(MS DFS): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 2://DEL
						start = std::chrono::system_clock::now();
						wynik = DEL_MS(MS, n);
						end = std::chrono::system_clock::now();
						std::cout << wynik << std::endl;
						std::cout << "\nTime in microseconds(MS DEL): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 3:
						isCorrectAnswer = true;
						break;
					case 4:
						newGraph = true;
						isCorrectAnswer = true;
						for(int i = 0; i < n; ++i)
							delete[] MS[i];
						delete[] MS;
						break;
					case 5:
						printf("Exited" );
						return 0;
					default:
						printf("Incorrect answer. Try again.");
						break;
				}
			} else{//Macierz grafu
				switch(answer){
					case 1://DFS
						start = std::chrono::system_clock::now();
						wynik = DFS_MG(MG, n);
						end = std::chrono::system_clock::now();
						std::cout << wynik << std::endl;
						std::cout  << "\nTime in microseconds(MG DFS): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 2://DEL
						start = std::chrono::system_clock::now();
						wynik = DEL_MG(MG, n);
						end = std::chrono::system_clock::now();
						std::cout << wynik << std::endl;
						std::cout << "\nTime in microseconds(MG DEL): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 3:
						for(int i = 0; i < n + 2; ++i)
							delete[] MG[i];
						delete[] MG;
						isCorrectAnswer = true;
						break;
					case 4:
						newGraph = true;
						isCorrectAnswer = true;
						for(int i = 0; i < n + 2; ++i)
							delete[] MG[i];
						delete[] MG;
						for(int i = 0; i < n; ++i)
							delete[] MS[i];
						delete[] MS;
						break;
					case 5:
						printf("Exited");
						return 0;
					default:
						printf("Incorrect answer. Try again.");
						break;
				}
			}
		}
	}

    return 0;
}

