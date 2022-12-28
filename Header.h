//
// Created by danie on 01/12/2022.
//

#ifndef EX2_HEADER_H
#define EX2_HEADER_H

#endif //EX2_HEADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <string>
#include <cmath>
#include "Sample.h"
using namespace std;


vector<Sample> ReadFromFile(string fileName);
vector <double> CreateVector(string str, char seprate);
int CheckInput(vector <double> vector1,int size);
void printFun(double number);
void argumentsCheck(int k, string path, string distance);
void argumentsCheckClient (string distance, int k);
int main(int argc, char *argv[]);