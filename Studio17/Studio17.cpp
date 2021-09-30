// Studio17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include "TextFile.h"
#include "ImageFile.h"
#include "SimpleFileSystem.h"

int main()
{
/*
    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    cout << "imgName: " << fileName << endl;
    cout << "imgSize: " << fileSize << endl;

    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
    cout << "write op(0 represents success): " << t.write(v) << endl;
    cout << "content size: " << t.getSize() << endl;

    auto read1 = t.read();
    istringstream ss(string{read1.begin(), read1.end()});
    string word1;
    cout << "img content: " << endl;
    while (ss >> word1) 
    {
       cout << word1 << endl;
    }
    cout << "append op(none-zero represents success): " << t.append(v) << endl;
    auto read2 = t.read();
    istringstream sss(string{read2.begin(), read2.end()});
    string word2;
    cout << "img content: " << endl;
    while (sss >> word2) 
    {
       cout << word2 << endl;
    }
*/

    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    TextFile* txt = new TextFile("FileName.txt");
    cout << "addFile_img op:(0 is correct) " << sfs.addFile(img->getName(), img) << endl;
    cout << "addFile_txt op:(0 is correct) " << sfs.addFile(txt->getName(), txt) << endl;
    //cout << "deletefile op:(0 is correct) " << sfs.deleteFile(img->getName()) << endl;
   
    sfs.addFile(img->getName(), img);
    sfs.openFile(img->getName());
    int res1 = sfs.closeFile(img);
    cout << "openfile op:(0 is correct) " << res1 << endl;
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
