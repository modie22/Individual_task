#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const int MAX_RECORDS = 1000;
const int MAX_LENGTH = 100;  


int readFile(const std::string& filename, std::string records[], int maxSize) {
    std::ifstream file(filename);
    int count = 0;
    std::string line;
    while (count < maxSize && std::getline(file, line)) {
        records[count++] = line;
    }
    return count;
}


void writeFile(const std::string& filename, std::string records[], int size) {
    std::ofstream file(filename);
    for (int i = 0; i < size; ++i) {
        file << records[i] << std::endl;
    }
}


void getRecords(std::string records[], int size, int indices[], int indicesSize, std::string result[], int& resultSize) {
    resultSize = 0;
    for (int i = 0; i < indicesSize; ++i) {
        int index = indices[i];
        if (index >= 0 && index < size && !records[index].empty() && records[index][0] != '\0') {
            result[resultSize++] = records[index];
        }
    }
}


void deleteRecords(std::string records[], int size, int indices[], int indicesSize) {
    for (int i = 0; i < indicesSize; ++i) {
        int index = indices[i];
        if (index >= 0 && index < size) {
            records[index] = std::string(1, '\0'); 
        }
    }
}

int main() {
    std::string filename = "records.txt";

  
    std::string records[MAX_RECORDS];


    int recordCount = readFile(filename, records, MAX_RECORDS);


    int readIndices[] = {0, 2};
    int deleteIndices[] = {1};
    int readIndicesSize = sizeof(readIndices) / sizeof(readIndices[0]);
    int deleteIndicesSize = sizeof(deleteIndices) / sizeof(deleteIndices[0]);

 
    std::string readRecords[MAX_RECORDS];
    int readRecordsSize;

 
    getRecords(records, recordCount, readIndices, readIndicesSize, readRecords, readRecordsSize);
    std::cout << "Read Records:" << std::endl;
    for (int i = 0; i < readRecordsSize; ++i) {
        std::cout << readRecords[i] << std::endl;
    }

    deleteRecords(records, recordCount, deleteIndices, deleteIndicesSize);


    writeFile(filename, records, recordCount);

    return 0;
}