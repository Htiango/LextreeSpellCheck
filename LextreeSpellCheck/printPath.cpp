#include "printPath.h"

//print the table of levenshtein distance
void printPath(const string& s1, const string& s2, int** pathArray, int** flagArray) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    int** printArray;
    printArray = new int*[len2 + 1];
    for (int i = 0; i < len2 + 1; i++) {
        printArray[i] = new int[len1 + 1];
        memset(printArray[i], 0, (len1 + 1) * sizeof(int));
    }
    
    std::vector<unsigned int> col(len2 + 1), prevCol(len2 + 1);
    for (unsigned int i = 0; i < prevCol.size(); i++) {
        prevCol[i] = i;
        printArray[i][0] = i;
    }
    for (unsigned int i = 0; i < len1; i++) {
        col[0] = i + 1;
        printArray[1][i + 1] = i + 1;
        for (unsigned int j = 0; j < len2; j++) {
            col[j + 1] = std::min({ prevCol[1 + j] + 1, col[j] + 1, prevCol[j] + (s1[i] == s2[j] ? 0 : 1) });
            printArray[j + 1][i] = col[j + 1];
        }
        col.swap(prevCol);
    }
    
    for (int i = 0; i < len2 + 2; i++) {
        for (int j = 0; j < len1 + 2; j++) {
            if(j != 0) {
                if (i < len2) {
                    if (j != 1) {
                        pathArray[i][j - 1] = printArray[len2 - i][j - 2];
                    }
                    else {
                        pathArray[i][0] = len2 - i;
                    }
                }
                else if(i == len2){
                    pathArray[i][j - 1] = j - 1;
                }
            }
        }
    }
    
    char *c1 = new char[len1 + 1];
    strcpy(c1, s1.c_str());
    char *c2 = new char[len2 + 1];
    strcpy(c2, s2.c_str());
    //print the optimal path
//    vector<vector<int[2]>> point;
    //count the point in path
    int count1 = 0;
    int count2 = 0;
    for (int j = len1; j >= 0; j--) {
        for (int i = 0; i <= len2; i++) {
            if (i != len2 && j != 0) {
                if (i == 0 && j == len1) {
                    flagArray[i][j] = 1;
                    int m = min({ pathArray[i][j - 1], pathArray[i + 1][j], pathArray[i + 1][j - 1] });
                    if (m == pathArray[i][j - 1] && m < pathArray[i][j])
                        flagArray[i][j - 1] = 1;
                    if (m == pathArray[i + 1][j] && m < pathArray[i][j])
                        flagArray[i + 1][j] = 1;
                    if (m == pathArray[i + 1][j - 1]) {
                        if(m == pathArray[i][j] && c1[j - 1] == c2[len2 - 1 - i])
                            flagArray[i + 1][j - 1] = 1;
                        if (m < pathArray[i][j] && c1[j - 1] != c2[len2 - 1 - i])
                            flagArray[i + 1][j - 1] = 1;
                    }
                }
                else {
                    if (flagArray[i][j] == 1) {
                        int m = min({ pathArray[i][j - 1], pathArray[i + 1][j], pathArray[i + 1][j - 1] });
                        if (m == pathArray[i][j - 1] && m < pathArray[i][j])
                            flagArray[i][j - 1] = 1;
                        if (m == pathArray[i + 1][j] && m < pathArray[i][j])
                            flagArray[i + 1][j] = 1;
                        if (m == pathArray[i + 1][j - 1]) {
                            if (m == pathArray[i][j] && c1[j - 1] == c2[len2 - 1 - i])
                                flagArray[i + 1][j - 1] = 1;
                            if (m < pathArray[i][j] && c1[j - 1] != c2[len2 - 1 - i])
                                flagArray[i + 1][j - 1] = 1;
                        }
                    }
                }
            }
            else if(i == len2 && j != 0){
                if (flagArray[i][j] == 1 && pathArray[i][j - 1] < pathArray[i][j]) {
                    flagArray[i][j - 1] = 1;
                }
            }
            else if (j == 0 && i != len2) {
                if (flagArray[i][j] == 1 && pathArray[i + 1][j] < pathArray[i][j]) {
                    flagArray[i + 1][j] = 1;
                }
            }
        }
    }
    delete[] c1;
    delete[] c2;
    delete[] printArray;
}

//print the table of levenshtein distance
void printSinglePath(const string& s1, const string& s2, string filePath, string fileName) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    int** printArray;
    printArray = new int*[len2 + 1];
    for (int i = 0; i < len2 + 1; i++) {
        printArray[i] = new int[len1 + 1];
        memset(printArray[i], 0, (len1 + 1) * sizeof(int));
    }
    
    std::vector<unsigned int> col(len2 + 1), prevCol(len2 + 1);
    for (unsigned int i = 0; i < prevCol.size(); i++) {
        prevCol[i] = i;
        printArray[i][0] = i;
    }
    for (unsigned int i = 0; i < len1; i++) {
        col[0] = i + 1;
        printArray[1][i + 1] = i + 1;
        for (unsigned int j = 0; j < len2; j++) {
            col[j + 1] = std::min({ prevCol[1 + j] + 1, col[j] + 1, prevCol[j] + (s1[i] == s2[j] ? 0 : 1) });
            printArray[j + 1][i] = col[j + 1];
        }
        col.swap(prevCol);
    }
    
    ofstream out(filePath + fileName);
    if (!out.is_open())
        cout << "fail to open file in printPath" << endl;
    
    char *c1 = new char[len1 + 1];
    strcpy(c1, s1.c_str());
    char *c2 = new char[len2 + 1];
    strcpy(c2, s2.c_str());
    
    for (int i = 0; i < len2 + 2; i++) {
        for (int j = 0; j < len1 + 2; j++) {
            if (j == 0) {
                if (i < len2) {
                    cout << setw(TABLE_GAP) << c2[len2 - 1 - i];
                    out << setw(TABLE_GAP) << c2[len2 - 1 - i];
                }
                else if (i == len2){
                    cout << setw(TABLE_GAP) << "$";
                    out << setw(TABLE_GAP) << "$";
                }
                else {
                    cout << setw(TABLE_GAP) << " ";
                    out << setw(TABLE_GAP) << " ";
                }
            }
            else {
                if (i < len2) {
                    if (j != 1) {
                        cout << setw(TABLE_GAP) << printArray[len2 - i][j - 2];
                        out << setw(TABLE_GAP) << printArray[len2 - i][j - 2];
                    }
                    else {
                        cout << setw(TABLE_GAP) << len2 - i;
                        out << setw(TABLE_GAP) << len2 - i;
                    }
                }
                else if(i == len2){
                    cout << setw(TABLE_GAP) << j - 1;
                    out << setw(TABLE_GAP) << j - 1;
                }
                else {
                    if (j != 1) {
                        cout << setw(TABLE_GAP) << c1[j - 2];
                        out << setw(TABLE_GAP) << c1[j - 2];
                    }
                    else {
                        cout << setw(TABLE_GAP) << "$";
                        out << setw(TABLE_GAP) << "$";
                    }
                }
            }
        }
        cout << endl;
        out << endl;
    }
    delete[] c1;
    delete[] c2;
    delete[] printArray;
}
//
void print(string s1, string s2, ofstream& out) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    //store pathArray
    int** pathArray;
    //flag point
    int** flagArray;
    pathArray = new int*[len2 + 1];
    flagArray = new int*[len2 + 1];
    for (int i = 0; i < len2 + 1; i++) {
        pathArray[i] = new int[len1 + 1];
        memset(pathArray[i], 0, (len1 + 1) * sizeof(int));
        flagArray[i] = new int[len1 + 1];
        memset(flagArray[i], 0, (len1 + 1) * sizeof(int));
    }
    
    printPath(s1, s2, pathArray, flagArray);
    
    char *c1 = new char[len1 + 1];
    strcpy(c1, s1.c_str());
    char *c2 = new char[len2 + 1];
    strcpy(c2, s2.c_str());
    if (!out.is_open())
        cout << "fail to open file in printPath" << endl;
    for (int i = 0; i < len2 + 2; i++) {
        for (int j = 0; j < len1 + 2; j++) {
            if (j == 0) {
                if (i < len2) {
                    cout << setw(TABLE_GAP) << c2[len2 - 1 - i];
                    out << setw(TABLE_GAP) << c2[len2 - 1 - i];
                }
                else if (i == len2) {
                    cout << setw(TABLE_GAP) << "$";
                    out << setw(TABLE_GAP) << "$";
                }
                else {
                    cout << setw(TABLE_GAP) << " ";
                    out << setw(TABLE_GAP) << " ";
                }
            }
            else {
                if (i < len2) {
                    if (j != 1) {
                        cout << setw(TABLE_GAP) << pathArray[i][j - 1];
                        out << setw(TABLE_GAP) << pathArray[i][j - 1];
                        if (flagArray[i][j - 1] == 1){
                            cout << "*";
                            out << "*";
                        }
                    }
                    else {
                        cout << setw(TABLE_GAP) << len2 - i;
                        out << setw(TABLE_GAP) << len2 - i;
                        if (flagArray[i][0] == 1){
                            cout << "*";
                            out << "*";
                        }
                    }
                }
                else if (i == len2) {
                    cout << setw(TABLE_GAP) << j - 1;
                    out << setw(TABLE_GAP) << j - 1;
                    if (flagArray[i][j - 1] == 1){
                        cout << "*";
                        out << "*";
                    }
                }
                else {
                    if (j != 1) {
                        cout << setw(TABLE_GAP) << c1[j - 2];
                        out << setw(TABLE_GAP) << c1[j - 2];
                    }
                    else {
                        cout << setw(TABLE_GAP) << "$";
                        out << setw(TABLE_GAP) << "$";
                    }
                }
            }
        }
        cout << endl;
        out << endl;
    }
    
    delete[] c1;
    delete[] c2;
    delete[] pathArray;
    delete[] flagArray;
}


//print the table of levenshtein distance of word string
void printStringPath(const vector<string>& s1, const vector<string>& s2, int** pathArray, int** flagArray, int* errorRecord) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    int** printArray;
    printArray = new int*[len2 + 1];
    for (int i = 0; i < len2 + 1; i++) {
        printArray[i] = new int[len1 + 1];
        memset(printArray[i], 0, (len1 + 1) * sizeof(int));
    }
    
    std::vector<unsigned int> col(len2 + 1), prevCol(len2 + 1);
    for (unsigned int i = 0; i < prevCol.size(); i++) {
        prevCol[i] = i;
        printArray[i][0] = i;
    }
    for (unsigned int i = 0; i < len1; i++) {
        col[0] = i + 1;
        printArray[1][i + 1] = i + 1;
        for (unsigned int j = 0; j < len2; j++) {
            col[j + 1] = std::min({ prevCol[1 + j] + 1, col[j] + 1, prevCol[j] + (s1[i].compare(s2[j]) == 0 ? 0 : 1) });
            printArray[j + 1][i] = col[j + 1];
        }
        col.swap(prevCol);
    }
    
    for (int i = 0; i < len2 + 2; i++) {
        for (int j = 0; j < len1 + 2; j++) {
            if (j != 0) {
                if (i < len2) {
                    if (j != 1) {
                        pathArray[i][j - 1] = printArray[len2 - i][j - 2];
                    }
                    else {
                        pathArray[i][0] = len2 - i;
                    }
                }
                else if (i == len2) {
                    pathArray[i][j - 1] = j - 1;
                }
            }
        }
    }
    
    //print the optimal path
    //vector<vector<int[2]>> point;
    //count the point in path
    int count1 = 0;
    int count2 = 0;
    for (int j = len1; j >= 0; j--) {
        for (int i = 0; i <= len2; i++) {
            if (i != len2 && j != 0) {
                if (i == 0 && j == len1) {
                    flagArray[i][j] = 1;
                    int m = min({ pathArray[i][j - 1], pathArray[i + 1][j], pathArray[i + 1][j - 1] });
                    if (m == pathArray[i + 1][j - 1]) {
                        if (m == pathArray[i][j] && s1[j - 1].compare(s2[len2 - 1 - i])==0){
                            flagArray[i + 1][j - 1] = 1;
                            errorRecord[3]++;
                            continue;
                        }
                        if (m < pathArray[i][j] && s1[j - 1].compare(s2[len2 - 1 - i]) != 0){
                            flagArray[i + 1][j - 1] = 1;
                            errorRecord[0]++;
                            continue;
                        }
                    }
                    if (m == pathArray[i][j - 1] && m < pathArray[i][j]){
                        flagArray[i][j - 1] = 1;
                        errorRecord[1]++;
                        continue;
                    }
                    if (m == pathArray[i + 1][j] && m < pathArray[i][j]){
                        flagArray[i + 1][j] = 1;
                        errorRecord[2]++;
                        continue;
                    }
                }
                else {
                    if (flagArray[i][j] == 1) {
                        int m = min({ pathArray[i][j - 1], pathArray[i + 1][j], pathArray[i + 1][j - 1] });
                        if (m == pathArray[i + 1][j - 1]) {
                            if (m == pathArray[i][j] && s1[j - 1].compare(s2[len2 - 1 - i])==0){
                                flagArray[i + 1][j - 1] = 1;
                                errorRecord[3]++;
                                continue;
                            }
                            if (m < pathArray[i][j] && s1[j - 1].compare(s2[len2 - 1 - i]) != 0){
                                flagArray[i + 1][j - 1] = 1;
                                errorRecord[0]++;
                                continue;
                            }
                        }
                        if (m == pathArray[i][j - 1] && m < pathArray[i][j]){
                            flagArray[i][j - 1] = 1;
                            errorRecord[1]++;
                            continue;
                        }
                        if (m == pathArray[i + 1][j] && m < pathArray[i][j]){
                            flagArray[i + 1][j] = 1;
                            errorRecord[2]++;
                            continue;
                        }
                    }
                }
            }
            else if (i == len2 && j != 0) {
                if (flagArray[i][j] == 1 && pathArray[i][j - 1] < pathArray[i][j]) {
                    flagArray[i][j - 1] = 1;
                    errorRecord[1]++;
                    break;
                }
            }
            else if (j == 0 && i != len2) {
                if (flagArray[i][j] == 1 && pathArray[i + 1][j] < pathArray[i][j]) {
                    flagArray[i + 1][j] = 1;
                    errorRecord[2]++;
                    break;
                }
            }
        }
    }
    delete[] printArray;
}

void printString(const vector<string>& s1, const vector<string>& s2, ofstream& out, int* errorRecord) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    //store pathArray
    int** pathArray;
    //flag point
    int** flagArray;
    pathArray = new int*[len2 + 1];
    flagArray = new int*[len2 + 1];
    for (int i = 0; i < len2 + 1; i++) {
        pathArray[i] = new int[len1 + 1];
        memset(pathArray[i], 0, (len1 + 1) * sizeof(int));
        flagArray[i] = new int[len1 + 1];
        memset(flagArray[i], 0, (len1 + 1) * sizeof(int));
    }
    
    printStringPath(s1, s2, pathArray, flagArray, errorRecord);
    if (!out.is_open())
        cout << "fail to open file in printStringPath" << endl;
    for (int i = 0; i < len2 + 2; i++) {
        for (int j = 0; j < len1 + 2; j++) {
            if (j == 0) {
                if (i < len2) {
//                    cout << setw(TABLE_GAP) << s2[len2 - 1 - i];
                    out << setw(TABLE_GAP) << s2[len2 - 1 - i];
                }
                else if (i == len2) {
//                    cout << setw(TABLE_GAP) << "$";
                    out << setw(TABLE_GAP) << "$";
                }
                else {
//                    cout << setw(TABLE_GAP) << " ";
                    out << setw(TABLE_GAP) << " ";
                }
            }
            else {
                if (i < len2) {
                    if (j != 1) {
//                        cout << setw(TABLE_GAP) << pathArray[i][j - 1];
                        out << setw(TABLE_GAP) << pathArray[i][j - 1];
                        if (flagArray[i][j - 1] == 1){
//                            cout << "*";
                            out << "*";
                        }
                    }
                    else {
//                        cout << setw(TABLE_GAP) << len2 - i;
                        out << setw(TABLE_GAP) << len2 - i;
                        if (flagArray[i][0] == 1){
//                            cout << "*";
                            out << "*";
                        }
                    }
                }
                else if (i == len2) {
//                    cout << setw(TABLE_GAP) << j - 1;
                    out << setw(TABLE_GAP) << j - 1;
                    if (flagArray[i][j - 1] == 1){
//                        cout << "*";
                        out << "*";
                    }
                }
                else {
                    if (j != 1) {
//                        cout << setw(TABLE_GAP) << s1[j - 2];
                        out << setw(TABLE_GAP) << s1[j - 2];
                    }
                    else {
//                        cout << setw(TABLE_GAP) << "$";
                        out << setw(TABLE_GAP) << "$";
                    }
                }
            }
        }
//        cout << endl;
        out << endl;
    }
    out.close();
    delete[] pathArray;
    delete[] flagArray;
}

