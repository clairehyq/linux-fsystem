// Studio19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TextFile.h"
#include "ImageFile.h"
#include "SimpleFileSystem.h"
#include "SimpleFileFactory.h"
#include "BasicDisplayVisitor.h"

int main()
{
	SimpleFileFactory sff;

	/*AbstractFile* file = sff.createFile("sample.txt");
	vector<char> content = file->read();
	string original{content.begin(), content.end()};
	cout << "file content : " << original << endl;
	vector<char> new_content = {'p','i','g'};
	file->write(new_content);
	content = file->read();
	string result{ content.begin(), content.end() };
	cout << "new file content : " << result << endl;*/

	AbstractFileVisitor* bdv = new BasicDisplayVisitor;
	AbstractFile* displaytxt = sff.createFile("displaytxt.txt");
	AbstractFile* displayimg = sff.createFile("displayimg.img");
	vector<char> displaytxtcontent = { 'p','i','g' };
	displaytxt->write(displaytxtcontent);
	vector<char> displayimgcontent = { 'X',' ','X',' ','X',' ','X',' ','X','3' };
	displayimg->write(displayimgcontent);

	cout << "display text should be 'pig' : " << endl;
	displaytxt->accept(bdv);
	cout << "" << endl;

	cout << "display text should be a 3 * 3 big 'X' : " << endl;
	displayimg->accept(bdv);
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
