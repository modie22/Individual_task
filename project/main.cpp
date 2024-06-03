#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

// Розмір одного запису в байтах
const int RECORD_SIZE = 20;

// Розмір поля індексу в байтах
const int INDEX_SIZE = 4;

// Структура для зберігання запису
struct Record {
    int index; // Індекс запису
    char data[RECORD_SIZE - INDEX_SIZE]; // Дані запису

    // Конструктор, який ініціалізує запис нулями
    Record() {
        std::memset(this, 0, sizeof(Record));
    }
};

// Функція для читання записів із файлу за заданими індексами
void readRecords(const std::string& filePath, const std::vector<int>& indices) {
    std::ifstream file(filePath, std::ios::binary); // Відкрити файл для читання в двійковому режимі
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для читання" << std::endl;
        return;
    }

    for (int index : indices) {
        file.seekg(index * RECORD_SIZE, std::ios::beg); // Перейти до потрібного запису
        Record record;
        file.read(reinterpret_cast<char*>(&record), RECORD_SIZE); // Прочитати запис із файлу
        if (record.index == index) {
            std::cout << "Індекс: " << record.index << ", Дані: " << record.data << std::endl;
        } else {
            std::cout << "Запис з індексом " << index << " не знайдено." << std::endl;
        }
    }

    file.close(); // Закрити файл
}

// Функція для видалення записів із файлу за заданими індексами
void deleteRecords(const std::string& filePath, const std::vector<int>& indices) {
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary); // Відкрити файл для читання і запису в двійковому режимі
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису" << std::endl;
        return;
    }

    for (int index : indices) {
        file.seekp(index * RECORD_SIZE, std::ios::beg); // Перейти до потрібного запису
        Record zeroedRecord; // Створити нульовий запис
        file.write(reinterpret_cast<char*>(&zeroedRecord), RECORD_SIZE); // Записати нульовий запис у файл
    }

    file.close(); // Закрити файл
}

int main() {
    const std::string filePath = "records.txt"; // Шлях до файлу

    // Індекси для читання записів
    std::vector<int> indicesToRead = {1, 3, 5};

    // Індекси для видалення записів
    std::vector<int> indicesToDelete = {2, 4};

    std::cout << "Читання записів:" << std::endl;
    readRecords(filePath, indicesToRead); // Виклик функції для читання записів

    std::cout << "\nВидалення записів:" << std::endl;
    deleteRecords(filePath, indicesToDelete); // Виклик функції для видалення записів

    return 0;
}
