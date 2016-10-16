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


void part2()
{
    string filePath = "/Users/hty/Desktop/Speech Recognition/project/project5/LextreeSpellCheck/LextreeSpellCheck/";
    string dictFileName = "dict_1.txt";
    Trie trie;
    createTrie(filePath, dictFileName, trie);
    
    string input = "butbutand";
    
    vector<TrieNode*> minLeafNodeSet;
    vector<int> minLeafCostSet;
    beamSearchLoop(trie, input, minLeafNodeSet, minLeafCostSet);
    int input_len = int(input.size());
    TrieNode* minNode = minLeafNodeSet[input_len - 1];
    string word = minNode->getWord();
    vector<string> vectorTemp;
    for (int i = input_len - 1; i >= 0; i--)
    {
        if (minNode->vectorBool[i])
        {
            vectorTemp.push_back(word);
            minNode = minLeafNodeSet[i - 1];
            word = minNode->getWord();
        }
        else
        {
            minNode = minNode->vectorNode[i];
        }
    }
    vector<string> vectorSegWords;
    vectorSegWords.push_back(word);
    cout << "* " << word << " * ";
    int vectorLen = int(vectorTemp.size());
    for (int i = vectorLen - 1; i >=0; i--) {
        vectorSegWords.push_back(vectorTemp[i]);
        cout << vectorTemp[i] << " * ";
    }
    cout << endl;
    cout << "Cost = " << minLeafCostSet[input_len - 1] << endl;
    
}


int main(int argc, const char * argv[]) {
    
//    part1();
    part2();
    return 0;
}
