#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stack>

void DFS_MS(bool **macierz, int n);
void DEL_MS(bool **macierz, int n);
bool DFStsort_MS(bool ** macierz, int v, int n, int * kolory);


