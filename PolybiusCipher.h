#ifndef RGR_POLYBIUS_CIPHER
#define RGR_POLYBIUS_CIPHER

#include <string>
#include <map>
#include <fstream>

using namespace std;

map<char, string> createPolybiusSquareEngUpper();
map<char, string> createPolybiusSquareEngLower();
map<char, string> createPolybiusSquareRusUpper();
map<char, string> createPolybiusSquareRusLower();
map<string, char> createReversePolybiusSquareEngUpper();
map<string, char> createReversePolybiusSquareEngLower();
map<string, char> createReversePolybiusSquareRusUpper();
map<string, char> createReversePolybiusSquareRusLower();
string encryptPolybius(const string& text, const map<char, string>& polybiusSquare);
string decryptPolybius(const string& text, const map<string, char>& reversePolybiusSquare);
string readPolybiusFile(const string& fileName);
void DisplayPolybius();

#endif