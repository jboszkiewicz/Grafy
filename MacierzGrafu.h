#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stack>

void DFS_MG(int ** macierz, int n);
void DEL_MG(int **macierz, int n);
bool DFStsort_MG(int ** macierz, int v, int n, int * kolory);