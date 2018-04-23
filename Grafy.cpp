// Grafy.cpp : Defines the entry point for the console application.
//

#include "MacierzGrafu.h"
#include "MacierzSąsiedztwa.h"
#include <ctime>
#include <chrono>
#include <iostream>

using namespace std;
using tp = chrono::time_point<chrono::system_clock>; //do pomiaru czasu


int main()
{
	setlocale(LC_ALL, "polish");
	srand(time(NULL));
	bool isCorrectAnswer = false;
	int answer, type, source, n;
	tp start, end;
	string fileName;

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
					while(true){ 
						puts("Podaj nazwę pliku: ");
						if(!scanf_s("%s", &fileName))
						puts("Incorrect answer. Try again.");
						else break;
					}
					//TODO: wczytanie grafu z pliku
					isCorrectAnswer = true;
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
						start = chrono::system_clock::now();
						DFS_MS(MS, n);
						end = chrono::system_clock::now();
						cout << endl << "Time in microseconds(MS DFS): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 2://DEL
						start = chrono::system_clock::now();
						DEL_MS(MS, n);
						end = chrono::system_clock::now();
						cout << endl << "Time in microseconds(MS DEL): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
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
						start = chrono::system_clock::now();
						DFS_MG(MG, n);
						end = chrono::system_clock::now();
						cout << endl << "Time in microseconds(): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 2://DEL
						start = chrono::system_clock::now();
						DEL_MG(MG, n);
						end = chrono::system_clock::now();
						cout << endl << "Time in microseconds(): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
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

