//
//  main.cpp
//  LextreeSpellCheck
//
//  Created by hty on 12/10/2016.
//  Copyright © 2016 hty. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "LextreeProcess.h"
#include "printPath.h"

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
    
    readFile(filePath, inFileName, typos);
//    readTestFile(filePath, inFileName, outFileName, typos);
    createTrie(filePath, dictFileName, trie);
    
    for (int i = 0; i < typos.size(); i++) {
        map<string, double> resultSet;
        double minCost = INT_MAX / 2;
        string bestString;
        beamSearch(resultSet, trie, typos[i]);
        map<string, double>::const_iterator iter = resultSet.begin();
        for (; iter != resultSet.end(); iter++){
            if (iter->second < minCost) {
                minCost = iter->second;
                bestString = iter->first;
                bestString = bestString.erase(0, 1);
            }
        }
        //        cout << typos[i] << "    " << bestString << endl;
        out << bestString + ' ';
        cout << bestString << " ";
    }
    out.close();
    //    beamSearch(resultSet, trie, input);
    //
    //    map<string, int>::const_iterator iter = resultSet.begin();
    //    for (; iter != resultSet.end(); iter++)
    //        cout << iter->first << " " << iter->second << endl;
}


void part2(string seg1FileName)
{
    string filePath = "/Users/hty/Desktop/Speech Recognition/project/project5/LextreeSpellCheck/LextreeSpellCheck/";
    
    string dictFileName = "dict_1.txt";
    string correctSegFileName = "segmented.txt";
    Trie trie;
    createTrie(filePath, dictFileName, trie);
    
    vector<string> unSeg1, unseg2;  // 1 for the wrong one, 2 for the correct one.
    readFile(filePath, seg1FileName, unSeg1);
    
    vector<string> correctWords;
    vector<string> segWords;
    
    readFile(filePath, correctSegFileName, correctWords);
    
    for(int i = 0; i < unSeg1.size(); i++){
    
        vector<TrieNode*> minLeafNodeSet;
        vector<double> minLeafCostSet;
        beamSearchLoop(trie, unSeg1[i], minLeafNodeSet, minLeafCostSet);
        int input_len = int(unSeg1[i].size());
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
        cout << word << " ";
        segWords.push_back(word);
        int vectorLen = int(vectorTemp.size());
        for (int i = vectorLen - 1; i >=0; i--) {
            vectorSegWords.push_back(vectorTemp[i]);
            cout << vectorTemp[i] << " ";
            segWords.push_back(vectorTemp[i]);
        }
        cout << endl;
//        cout << "Cost = " << minLeafCostSet[input_len - 1] << endl;
    }
    
    ofstream out(filePath + "path.txt");
    int errorRecord[4] = {0, 0, 0, 0};
    
    printString(segWords, correctWords, out, errorRecord);
    cout << endl;
    cout << "Words' number: "<< segWords.size() <<endl;
    cout << "Template words' number: "<< correctWords.size() <<endl;
    cout << "Correct: "<< errorRecord[3] <<  endl;
    cout << "Substitution: " <<errorRecord[0] <<endl;
    cout << "Insertion: " << errorRecord[1] << endl;
    cout << "Deletion: " << errorRecord[2] << endl;
    int accuracy;
    int difference = int (segWords.size() - correctWords.size());
    accuracy = abs(difference)  + errorRecord[0];
    cout << "Accuracy = " << accuracy << endl;
}



int main(int argc, const char * argv[]) {
    cout << "----------------------------------------PROBLEM 1--------------------------------------------------------------------------"<< endl;
    cout << endl;

    part1();
    cout << endl;
    cout << endl;
    cout << "----------------------------------------PROBLEM 2---------------------------------------------------------------------------"<< endl;
    cout << endl;
    cout << endl;
    cout << "****************************************CORRECT ONE****************************************"<< endl;
    cout << endl;
    string seg1FileName = "unsegmented0.txt";
    part2(seg1FileName);
    cout << endl;
    cout << endl;
    cout << "****************************************WRONG ONE****************************************"<< endl;
    cout << endl;
    string seg2FileName = "unsegmented.txt";
    part2(seg2FileName);

    return 0;
}
