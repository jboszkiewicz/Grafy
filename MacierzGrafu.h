#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string>

std::string DFS_MG(int ** macierz, int n);
std::string DEL_MG(int **macierz, int n);
bool DFStsort_MG(int ** macierz, int v, int n, int * kolory);
