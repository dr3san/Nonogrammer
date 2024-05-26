#ifndef BACKEND_H
#define BACKEND_H
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <string>

using namespace std;

vector<vector<int>> generateNonogram();
vector<string> formatNonogramInterface(const vector<vector<int>>& matrix);
#endif
