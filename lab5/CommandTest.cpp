#include "CommandTest.h"
#include "ErrorCodes.h"
using namespace std;

CommandTest::CommandTest(AbstractFileSystem* _afs): afs(_afs)
{
}

int CommandTest::execute(string info)
{
	if (info == "") {
		cout << "command-test-no-info" << endl;
	}
	else {
		replace(info.begin(), info.end(), ' ', ':');
		cout << "\n" << info << "\n" << endl;
	}
	return OK;
}

void CommandTest::displayInfo()
{
	cout << "aRandomStringz" << endl;
  (void)afs;
}
