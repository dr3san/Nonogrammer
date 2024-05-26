#ifndef BACKEND_H
#define BACKEND_H
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

vector<vector<int>> generateNonogram();
vector<vector<tuple<int>>> formatNonogramInterface(const vector<vector<int>>& matrix);
#endif
