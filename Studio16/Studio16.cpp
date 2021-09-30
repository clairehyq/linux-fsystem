// Studio16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TextFile.h"

int main()
{
    std::string fileName = "FileName.txt";
    std::string Another_fileName = "Another_fileName.txt";
    unsigned int fileSize = 0;
    TextFile t(fileName);
    cout << "fileName: " << fileName << endl;
    cout << "fileSize: " << fileSize << endl;
    std::vector<char> v = { 'h', 'i' };
    cout << "write op(0 represents success): " << t.write(v) << endl;
    cout << "content size: " << t.getSize() << endl;
    auto read1 = t.read();
    string word1{read1.begin(), read1.end()};
    cout << "file content: " << word1 << endl;
    cout << "append op(0 represents success): " << t.append(v) << endl;
    auto read2 = t.read();
    string word2{read2.begin(), read2.end()};
    cout << "file content: " << word2 << endl;

    TextFile t2(Another_fileName);
    std::vector<char> vv(word2.begin(), word2.end());
    t2.append(vv);
    auto read3 = t2.read();
    string word3{read3.begin(), read3.end()};
    cout << "interact content: " << word3 << endl;
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
