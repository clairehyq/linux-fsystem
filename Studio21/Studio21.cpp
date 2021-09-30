// Studio21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TextFile.h"
#include "ImageFile.h"
#include "SimpleFileSystem.h"
#include "SimpleFileFactory.h"
#include "PasswordProxy.h"
#include "TouchCommand.h"
#include "CommandPrompt.h"
#include "BasicDisplayVisitor.h"
using namespace std;

int main()
{
	AbstractFileSystem* sfs = new SimpleFileSystem();
	AbstractFileFactory* sff = new SimpleFileFactory();
	CommandPrompt* cp = new CommandPrompt;

	TouchCommand* tc = new TouchCommand(sfs, sff);
	string touch = "touch";
	cp->addCommand(touch, tc);

	cp->run();

	cout << "" << endl;
	cout << "All the files you created by touch command should be displayed below:" << endl;
	set<string> pig = sfs->getFileNames();
	int index = 1;
	for (string lilpig : pig)
	{
		cout << index << ": " << lilpig << endl;
		++index;
	}
	cout << "" << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

