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

void part1()
{
    string filePath = "/Users/hty/Desktop/Speech Recognition/project/project5/LextreeSpellCheck/LextreeSpellCheck/";
    string inFileName = "typos.txt";
    string outFileName = "pureTypos.txt";
    string outFileName2 = "correct.txt";
    string dictFileName = "dict_1.txt";
    
    string input = "abbreviate";
    
    vector<string> typos;
    Trie trie;
    
    ofstream out(filePath + outFileName2);
    
    
    readTestFile(filePath, inFileName, outFileName, typos);
    createTrie(filePath, dictFileName, trie);
    
    for (int i = 0; i < typos.size(); i++) {
        map<string, int> resultSet;
        int minCost = INT_MAX / 2;
        string bestString;
        beamSearch(resultSet, trie, typos[i]);
        map<string, int>::const_iterator iter = resultSet.begin();
        for (; iter != resultSet.end(); iter++){
            if (iter->second < minCost) {
                minCost = iter->second;
                bestString = iter->first;
                bestString = bestString.erase(0, 1);
            }
        }
        //        cout << typos[i] << "    " << bestString << endl;
        out << bestString + ' ';
    }
    out.close();
    //    beamSearch(resultSet, trie, input);
    //
    //    map<string, int>::const_iterator iter = resultSet.begin();
    //    for (; iter != resultSet.end(); iter++)
    //        cout << iter->first << " " << iter->second << endl;
}


int main(int argc, const char * argv[]) {
    
//    part1();
    
    return 0;
}
