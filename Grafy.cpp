// Grafy.cpp : Defines the entry point for the console application.
//

#include "MacierzGrafu.h"
#include "MacierzSąsiedztwa.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using tp = std::chrono::time_point<std::chrono::system_clock>; //do pomiaru czasu


int main()
{
	setlocale(LC_ALL, "polish");
	srand(time(NULL));
	bool isCorrectAnswer = false;
	int answer, type, source, n, m;
	tp start, end;
	std::string fileName = "";
	std::fstream plik;
	int **arcs = NULL;

	bool ** MS = NULL;
	int ** MG = NULL;

	while(true){ //pętla główna programu

		while(!isCorrectAnswer){ //wybór źródła danych
			printf("Wybierz źródło danych:");
			printf("   '1' - Generator;");
			printf("   '2' - Plik;");

			scanf_s("%d", &source);

			switch(source){
				case 1:// Generator
					while(true){ 
						puts("Enter number of data: ");
						if(!scanf_s("%d", &n) || n < 1)
						puts("Incorrect answer. Try again.");
						else break;
					}
					//TODO: Generator grafu
					isCorrectAnswer = true;
					break;
				case 2:// Plik	
					while(!isCorrectAnswer){
						puts("Podaj nazwę pliku: ");
						std::cin >> fileName;

					//TODO: wczytanie grafu z pliku

						plik.open(fileName, std::ios::in);
						if(plik.good() == true){
							std::string dane;
							getline(plik, dane);
							int spacja = dane.find(' ');
							n = atoi(dane.substr(0, spacja - 1).c_str());
							m = atoi(dane.substr(spacja + 1).c_str());
							arcs = new int*[m];
							for(int i = 0; i < m; i++)
								arcs[i] = new int[2];
							while(!plik.eof()){
								getline(plik, dane); //wczytanie CAŁEGO jednego wiersza danych


							}
							plik.close();
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
			printf("Wybierz reprezentację maszynową grafu:" );
			printf("   '1' - Macierz sąsiedztwa;" );
			printf("   '2' - Macierz grafu;" );

			scanf_s("%d", &type);
			switch(type){
				case 1:// Macierz sąsiedztwa
					//TODO: tworzenie grafu
					isCorrectAnswer = true;
					break;
				case 2:// Macierz grafu	
					//TODO: tworzenie grafu
					isCorrectAnswer = true;
					break;
				default:
					printf( "Incorrect answer. Try again.");
					break;
			}
		}

		isCorrectAnswer = false;

		while(!isCorrectAnswer){
			printf("\nCo chcesz zrobić z grafem:\n");
			printf("  1  Posortuj topologicznie z wykorzystaniem DFS;\n");
			printf("  2  Posortuj topologicznie z usuwaniem wierzchołków o zerowym stopniu wejściowym;\n");
			printf("  3  Zmień reprezentację maszynową;\n");
			printf("  4  Zakończ;\n");

			printf("Give your answer:");
			scanf_s("%d", &answer);

			if(type == 1){// Macierz sąsiedztwa
				switch(answer){
					case 1://DFS
						start = std::chrono::system_clock::now();
						DFS_MS(MS, n);
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(MS DFS): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 2://DEL
						start = std::chrono::system_clock::now();
						DEL_MS(MS, n);
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(MS DEL): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 3:
						isCorrectAnswer = true;
						break;
					case 4:
						printf("Exited" );
						return 0;
					default:
						printf("Incorrect answer. Try again.");
						break;
				}
			} else{
				switch(answer){
					case 1://DFS
						start = std::chrono::system_clock::now();
						DFS_MG(MG, n);
						end = std::chrono::system_clock::now();
						std::cout  << "\nTime in microseconds(): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 2://DEL
						start = std::chrono::system_clock::now();
						DEL_MG(MG, n);
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 3:
						isCorrectAnswer = true;
						break;
					case 4:
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

