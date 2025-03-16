#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;


class PhoneBook {
public:
    int page;
    string surname;
    
    
    PhoneBook(int p = -1, string s = "") : page(p), surname(s) {}

    bool isEmpty() const { return page == -1; }
};


class HashTable {
private:
    vector<PhoneBook> table;
    vector<bool> deleted; 
    int capacity;//размер
    int size;//колво элементов

    //первая хеш-функция
    int hash1(int key) const {
        return key % capacity;//остаток от деления на ключ
    }

    //вторая хеш-функция 
    int hash2(int key) const {
        return 1 + (key % (capacity - 1));//тут остаток от деления должен быть нечетным 
    }

    //поиск
    int findIndex(int key) const {
        int index = hash1(key);
        int step = hash2(key);
        
        for (int i = 0; i < capacity; ++i) {
            if (table[index].isEmpty() && !deleted[index]) {
                return -1; 
            }
            if (table[index].page == key) {
                return index;
            }
            index = (index + step) % capacity;
        }
        return -1;
    }

public:
    HashTable(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
        deleted.resize(capacity, false);
    }

    //вставка
    void insert(int page, string surname) {
        if (size == capacity) {
            cout << "Hash table is full!" << endl;
            return;
        }

        int index = hash1(page);
        int step = hash2(page);
        
        
        for (int i = 0; i < capacity; ++i) {
            if (table[index].isEmpty() || deleted[index]) {
                table[index] = PhoneBook(page, surname);
                deleted[index] = false;
                size++;
                return;
            }
            index = (index + step) % capacity;
        }
        cout << "Failed to insert!" << endl;
    }

    //поиск
    bool search(int page, string& surname) const {
        int index = findIndex(page);
        if (index != -1) {
            surname = table[index].surname;
            return true;
        }
        return false;
    }

    //удаление
    bool remove(int page) {
        int index = findIndex(page);
        if (index != -1) {
            table[index] = PhoneBook();
            deleted[index] = true;
            size--;
            return true;
        }
        return false;
    }

    //принт
    void print() const {
        for (int i = 0; i < capacity; ++i) {
            if (!table[i].isEmpty()) {
                cout << "Index " << i << ": " << table[i].page << " - " << table[i].surname << endl;
            }
            else {
                cout << "Index " << i << ": [Empty]" << endl;
            }
        }
    }
};


int main() {
    HashTable phoneBook(10);

    phoneBook.insert(13, "Ivanov");
    phoneBook.insert(54, "Borovkov");
    phoneBook.insert(31, "Zibaev");
    phoneBook.insert(65, "Nevidimov");
    phoneBook.insert(25, "Gagarin");


    cout << "Phone book:" << endl;
    phoneBook.print();

    string surname;
    if (phoneBook.search(54, surname)) {
        cout << "Poisk: " << surname << endl;
    }
    else {
        cout << "Net takogo!" << endl;
    }
    cout << endl;
    phoneBook.remove(31);
    cout << "Phone book s udaleniem:" << endl;
    phoneBook.print();

    return 0;
}
