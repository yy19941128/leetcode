#include <iostream>

using namespace std;

class MyHashSet {
    /**
     *  Open Addressing
     *  index = (5 * index + 1) % this->capacity;
     */
public:
    int capacity;
    float load_factor;
    int size;
    int *table;

    /** Initialize your data structure here. */
    MyHashSet() {
        this->capacity = 1 << 3;
        this->load_factor = 0.75;
        this->size = 0;
        this->table = new int[capacity];

        for (int i = 0; i < this->capacity; i++)
            this->table[i] = -1;
    }

    int myhash(int key) {
        return key % this->capacity;
    }

    void add(int key) {
        if (float(this->size) / this->capacity >= 0.75) {
            this->capacity <<= 1;
            int *newTable = new int[this->capacity];
            for (int i = 0; i < this->capacity; i++)
                newTable[i] = -1;

            for (int i = 0; i < this->capacity >> 1; i++) {
                if ((this->table[i] != -1) && (this->table[i] != -2)) {
                    int index = this->myhash(this->table[i]);
                    while (newTable[index] != -1)
                        index = (5 * index + 1) % this->capacity;
                    newTable[index] = this->table[i];
                }
            }
            this->table = newTable;
        }

        int index = this->myhash(key);
        if (this->table[index] == key)
            return;

        while (this->table[index] != -1) {
            index = (5 * index + 1) % this->capacity;
            if (this->table[index] == -2)
                break;
        }
        this->table[index] = key;
        this->size += 1;
    }

    void remove(int key) {
        int index = this->myhash(key);
        while (this->table[index] != -1) {
            if (this->table[index] == key) {
                this->table[index] = -2;
                this->size -= 1;
                return;
            }
            index = (5 * index + 1) % this->capacity;
        }
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int index = this->myhash(key);
        while (this->table[index] != -1) {
            if (this->table[index] == key)
                return true;
            index = (5 * index + 1) % this->capacity;
        }
        return false;
    }

    void displayHash() {
        for (int i = 0; i < this->capacity; i++) {
            cout << i << " --> " << this->table[i] << endl;
        }
    }
};


int main() {
    MyHashSet *obj = new MyHashSet();
    int add[] = {30, 8, 79, 78, 81, 73, 99, 64, 77, 64, 57, 55, 27, 68, 70, 45, 54, 1, 84, 39, 19, 59, 38, 16, 51, 7,
                 10, 46,
                 33, 89, 18, 89, 68, 25, 12, 48, 61, 93, 41, 57, 34, 29, 63, 65, 98, 73, 88, 24, 74, 38};

    int rv[] = {9, 53, 5, 81, 84, 33, 24, 62, 55, 23, 10, 63, 98, 15, 36, 69, 30, 35, 26, 53, 81, 42, 98, 45, 43, 78,
                19, 42,
                74, 77};

    int contain[] = {87, 71, 85, 60, 72, 78, 1, 29, 83, 95, 57, 70, 70, 71, 43, 76, 47, 75, 77, 93, 79, 42, 16, 71, 48,
                     3, 61,
                     71, 76, 49};

    for (int a: add)
        obj->add(a);

    for (int r: rv)
        obj->remove(r);

    for (int c: contain)
        cout << obj->contains(c) << endl;

    obj->displayHash();

//    output
//    False     0     False
//    False     0     False
//    False     0     False
//    False     0     False
//    False     0     False
//    False     0     False
//    True      1     True
//    True      1     True
//    False     0     False
//    False     0     False
//    True      1     True
//    True      1     True
//    True      1     True
//    False     0     False
//    False     0     False
//    False     0     False
//    False     0     False
//    False     0     False
//    False     0     False
//    True      1     True
//    True      1     True
//    False     0     False
//    True      1     True
//    False     0     False
//    True      1     True
//    False     0     False
//    True      1     True
//    False     0     False
//    False     0     False
//    False     0     False
    return 0;
}