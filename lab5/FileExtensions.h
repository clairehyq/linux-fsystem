/*
 * all available file extensions and utils
 */

#include <string>
using namespace std;

int splitExt(const string&, string&, string&);

const char EXT_IMG[] = "img";
const char EXT_TXT[] = "txt";

string getExt(const string&);
string getExtInfo(const string& ext);
