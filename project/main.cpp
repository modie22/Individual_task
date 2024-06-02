#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

const int RECORD_SIZE = 20;  // Розмір одного запису в байтах
const int INDEX_SIZE = 4;    // Розмір поля індексу в байтах

struct Record {
    int index;
    char data[RECORD_SIZE - INDEX_SIZE];

    Record() {
        std::memset(this, 0, sizeof(Record));
    }
};

void readRecords(const std::string& filePath, const std::vector<int>& indices) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для читання" << std::endl;
        return;
    }

    for (int index : indices) {
        file.seekg(index * RECORD_SIZE, std::ios::beg);
        Record record;
        file.read(reinterpret_cast<char*>(&record), RECORD_SIZE);
        if (record.index == index) {
            std::cout << "Індекс: " << record.index << ", Дані: " << record.data << std::endl;
        } else {
            std::cout << "Запис з індексом " << index << " не знайдено." << std::endl;
        }
    }

    file.close();
}

void deleteRecords(const std::string& filePath, const std::vector<int>& indices) {
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису" << std::endl;
        return;
    }

    for (int index : indices) {
        file.seekp(index * RECORD_SIZE, std::ios::beg);
        Record zeroedRecord;
        file.write(reinterpret_cast<char*>(&zeroedRecord), RECORD_SIZE);
    }

    file.close();
}

int main() {
    const std::string filePath = "records.dat";

    std::vector<int> indicesToRead = {1, 3, 5};
    std::vector<int> indicesToDelete = {2, 4};

    std::cout << "Читання записів:" << std::endl;
    readRecords(filePath, indicesToRead);

    std::cout << "\nВидалення записів:" << std::endl;
    deleteRecords(filePath, indicesToDelete);

    return 0;
}