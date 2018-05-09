#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string>

std::string DFS_MS(bool **macierz, int n);
std::string DEL_MS(bool **macierz, int n);
bool DFStsort_MS(bool ** macierz, int v, int n, int * kolory);



