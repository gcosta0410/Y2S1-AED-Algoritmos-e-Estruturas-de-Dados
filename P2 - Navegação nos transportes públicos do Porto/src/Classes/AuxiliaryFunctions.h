#ifndef AED2122_TRABALHO2_AUXILIARYFUNCTIONS_H
#define AED2122_TRABALHO2_AUXILIARYFUNCTIONS_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

bool getAnswer();
bool isAllDigits(const std::string &str);
bool isNumber(const std::string &s);
bool parseInput(int a, const std::string& text);
char getChar();
float getFloat();
int getInt();
std::string getName();
std::string getString();
std::string toLowerStr(std::string original);
unsigned int getUnsignedInt();
void clrscr();

double haversine(double lat1, double lon1, double lat2, double lon2);
bool validCoords(const std::string& coords, double &lat, double &lon);
bool validName(const std::string& name, const std::unordered_map<std::string,std::string>& paragens);
bool validCode(const std::string& name, const std::unordered_map<std::string,int>& paragens);
bool isDouble(const std::string& s);

#endif //AED2122_TRABALHO2_AUXILIARYFUNCTIONS_H
