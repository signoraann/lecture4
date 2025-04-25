#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

// Структура книги
struct Book {
    string title;
    int pages;
    int year;
};

// Структура хеш-таблицы
struct HashTable {
    static const int SIZE = 10; // Размер таблицы
    Book* table[SIZE]; // Массив указателей на книги
    int array[SIZE];   // Массив для шагов пробирования

    HashTable() {
        // Инициализация массива нулевыми значениями
        for (int i = 0; i < SIZE; i++) {
            table[i] = nullptr;
        }

        // Заполнение массива шагов случайными числами от 1 до 3
        srand(time(0));
        for (int i = 0; i < SIZE; i++) {
            array[i] = rand() % 3 + 1; // 1, 2 или 3
        }

        cout << "Массив шагов: ";
        for (int i = 0; i < SIZE; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    // Хеш-функция (остаток от деления на SIZE)
    int hash(int year) {
        return year % SIZE;
    }

    // Вставка книги в таблицу с открытой адресацией
    void insert(Book* book) {
        int index = hash(book->year);
        int p = 0; // Номер попытки

        while (p < SIZE) {
            if (table[index] == nullptr) {
                table[index] = book;
                return;
            }
            // Применяем формулу для следующей ячейки
            index = (index + array[p]) % SIZE;
            p++;
        }

        cout << "Не удалось вставить книгу " << book->title << " - таблица переполнена!" << endl;
    }

    // Поиск книги по году
    Book* search(int year) {
        int index = hash(year);
        int p = 0;

        while (p < SIZE) {
            if (table[index] != nullptr && table[index]->year == year) {
                return table[index];
            }
            index = (index + array[p]) % SIZE;
            p++;
        }

        return nullptr;
    }

    // Вывод хеш-таблицы
    void print() {
        cout << "\nХеш-таблица:\n";
        for (int i = 0; i < SIZE; i++) {
            cout << "Индекс " << i << ": ";
            if (table[i] != nullptr) {
                cout << "[" << table[i]->title << ", " << table[i]->year << "]";
            }
            cout << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
сout<<"Решение:"<<endl;
    // Исходный массив книг
    Book books[9] = {
        {"Война и мир", 1225, 1869}, {"Преступление и наказание", 671, 1866},
        {"1984", 328, 1949}, {"Мастер и Маргарита", 480, 1967},
        {"Гарри Поттер", 320, 1997}, {"Анна Каренина", 864, 1877},
        {"Три товарища", 544, 1936}, {"Человек в высоком замке", 256, 1962},
        {"Алхимик", 208, 1988}
    };

    // Создание хеш-таблицы
    HashTable hashTable;
    for (int i = 0; i < 9; i++) {
        hashTable.insert(&books[i]);
    }

    // Вывод хеш-таблицы
    hashTable.print();

    // Поиск книги по году издания
    int searchYear;
    cout << "\nВведите год издания для поиска: ";
    cin >> searchYear;

    Book* foundBook = hashTable.search(searchYear);
    if (foundBook) {
        cout << "\nНайденная книга:\n"
            << "Название: " << foundBook->title
            << ", Страниц: " << foundBook->pages
            << ", Год: " << foundBook->year << endl;
    }
    else {
        cout << "Книга с таким годом не найдена.\n";
    }

    return 0;
}
