#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>


struct Record {
    int index;
    char data[20]; 
};


Record readRecord(std::fstream &file, int recordSize, int index) {
    Record record;
    file.seekg(index * recordSize, std::ios::beg);
    file.read(reinterpret_cast<char*>(&record), recordSize);
    return record;
}


void deleteRecord(std::fstream &file, int recordSize, int index) {
    Record emptyRecord = {0, {0}}; 
    file.seekp(index * recordSize, std::ios::beg);
    file.write(reinterpret_cast<const char*>(&emptyRecord), recordSize);
}

int main() {
    const std::string filename = "records.dat";
    const int recordSize = sizeof(Record);

   
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open the file!" << std::endl;
        return 1;
    }


    std::vector<int> indicesToRead = {1, 3, 5};
    for (int index : indicesToRead) {
        Record record = readRecord(file, recordSize, index);
        if (record.index != 0) { 
            std::cout << "Index: " << record.index << ", Data: " << record.data << std::endl;
        } else {
            std::cout << "No record at index: " << index << std::endl;
        }
    }


    std::vector<int> indicesToDelete = {2, 4}; 
    for (int index : indicesToDelete) {
        deleteRecord(file, recordSize, index);
        std::cout << "Record at index " << index << " deleted." << std::endl;
    }

    file.close();
    return 0;
}
