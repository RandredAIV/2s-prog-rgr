#ifndef RGR_TARABAR_H
#define RGR_TARABAR_H


#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>

using namespace std;

string readFileToString2(const string& fileName);
string encryptGramota(const string& text, map<char, char>& GramotaRus);
string decryptGramota(const string& text, map<char, char>& GramotaRus);
void DisplayGramota();



#endif //RGR_TARABAR_H