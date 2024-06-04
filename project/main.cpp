#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_RECORDS = 1000; 
const int MAX_LENGTH = 100;   


int readFile(const string& filename, string records[], int maxSize) {
    ifstream file(filename);
    int count = 0;
    string line;
    while (count < maxSize && getline(file, line)) {
        records[count++] = line;
    }
    return count;
}


void writeFile(const string& filename, string records[], int size) {
    ofstream file(filename);
    for (int i = 0; i < size; ++i) {
        file << records[i] << std::endl;
    }
}


void getRecords(string records[], int size, int indices[], int indicesSize, string result[], int& resultSize) {
    resultSize = 0;
    for (int i = 0; i < indicesSize; ++i) {
        int index = indices[i];
        if (index >= 0 && index < size && !records[index].empty() && records[index][0] != '\0') {
            result[resultSize++] = records[index];
        }
    }
}


void deleteRecords(string records[], int size, int indices[], int indicesSize) {
    for (int i = 0; i < indicesSize; ++i) {
        int index = indices[i];
        if (index >= 0 && index < size) {
            records[index] = string(1, '\0'); 
        }
    }
}

int main() {
    string filename = "records.txt";


    string records[MAX_RECORDS];

  
    int recordCount = readFile(filename, records, MAX_RECORDS);

    int readIndices[] = {0, 2};
    int deleteIndices[] = {1};
    int readIndicesSize = sizeof(readIndices) / sizeof(readIndices[0]);
    int deleteIndicesSize = sizeof(deleteIndices) / sizeof(deleteIndices[0]);

 
    string readRecords[MAX_RECORDS];
    int readRecordsSize;

    getRecords(records, recordCount, readIndices, readIndicesSize, readRecords, readRecordsSize);
        cout << "Read Records:" << std::endl;
    for (int i = 0; i < readRecordsSize; ++i) {
        cout << readRecords[i] << std::endl;
    }


    deleteRecords(records, recordCount, deleteIndices, deleteIndicesSize);


    writeFile(filename, records, recordCount);

    return 0;
}