#ifndef RGR_TABLE_H
#define RGR_TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <cmath>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <cstdint>

using namespace std;

string readFileToString1(const string& fileName);
void fillTable(const string& message, vector<vector<char>>& table, int size, char fillChar, char fillChar2);
void permuteTablerow(vector<vector<char>>& table, const vector<int>& key);
void permuteTablecol(vector<vector<char>>& table, const vector<int>& key);

vector<int> generateRandomKey(int size);
vector<int> generatereverseKey(const vector<int>& Key1, int size);

string encrypt(const string& message, const vector<int>& colKey, const vector<int>& rowKey, char fillChar, char fillChar2);
string decrypt(const string& message, const vector<int>& colKey, const vector<int>& rowKey, char fillChar, char fillChar2);

void DisplayTable();

#endif //RGR_TABLE_H
