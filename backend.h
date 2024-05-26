#ifndef BACKEND_H
#define BACKEND_H
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

vector<vector<int>> generateNonogram();
void formatNonogramInterface(const vector<vector<int>>& matrix);
#endif
