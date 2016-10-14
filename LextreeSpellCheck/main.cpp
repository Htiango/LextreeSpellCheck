//
//  main.cpp
//  LextreeSpellCheck
//
//  Created by hty on 12/10/2016.
//  Copyright © 2016 hty. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "LextreeProcess.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    string filePath = "/Users/hty/Desktop/Speech Recognition/project/project5/LextreeSpellCheck/LextreeSpellCheck/";
    string inFileName = "typos.txt";
    string outFileName = "pureTypos.txt";
    string dictFileName = "dict_1.txt";
    
    string input = "abbreviation";
    
    vector<string> typos;
    Trie trie;
    map<string, int> resultSet;
    
    //readTestFile(filePath, inFileName, outFileName, typos);
    createTrie(filePath, dictFileName, trie);
    beamSearch(resultSet, trie, input);
    
    map<string, int>::const_iterator iter = resultSet.begin();
    for (; iter != resultSet.end(); iter++)
        cout << iter->first << " " << iter->second << endl;
    
    return 0;
}
