/*
 * some string and ostream utils
 */

#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

string trim(const string&);

vector<string> splitBySpace(const string&);

ostream& operator<<(ostream&, const vector<char>&);
