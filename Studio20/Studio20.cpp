// Studio20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TextFile.h"
#include "ImageFile.h"
#include "SimpleFileSystem.h"
#include "SimpleFileFactory.h"
#include "PasswordProxy.h"
#include "BasicDisplayVisitor.h"

int main()
{
	SimpleFileFactory sff;
	AbstractFile* pig = sff.createFile("encrypted.txt");
	vector<char> content = { 'p','i','g' };
	pig->write(content);
	string password = "pigispig";
	PasswordProxy* pp = new PasswordProxy(pig, password);
	cout << "test read method" << endl;
	vector<char> readContent = pp->read();
	string readResult{ readContent.begin(), readContent.end() };
	cout << "the result should be 'pig' once you entered the correct password:" << endl;
	cout << "result: " << readResult << endl;

	content = { 'p','i','g',' ','i','s',' ','n','o','t',' ','d','o','g' };
	cout << "" << endl;
	cout << "test writing method: ";
	pp->write(content);
	readContent = pig->read();
	string readnewResult{ readContent.begin(), readContent.end() };
	cout << "the new result should be 'pig is not dog' once you entered the correct password:" << endl;
	cout << "result: " << readnewResult << endl;

	cout << "" << endl;
	AbstractFileVisitor* bdv = new BasicDisplayVisitor;
	cout << "test display method: " << endl;
	pp->accept(bdv);
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
