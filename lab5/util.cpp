/*
 * some string and ostream utils
 */

#include "util.h"
#include <sstream>
using namespace std;

string trim(const string &str)
{
  const int n = str.size();

  int l = 0;
  for (; l < n && isspace(str[l]); ++l);
  if (l == n) return "";  // empty string

  int r = n-1;
  for (; r >= 0 && isspace(str[r]); --r);

  return str.substr(l, r-l+1);   // right exclusive
}

vector<string> splitBySpace(const string &str)
{
  vector<string> ret;
  istringstream iss{str};
  for (string s; iss >> s; ret.push_back(s));
  return ret;
}

ostream& operator<<(ostream& out, const vector<char>& vec)
{
  for (char c : vec) out << c;
  return out;
}

