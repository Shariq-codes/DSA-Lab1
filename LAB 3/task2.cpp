#include <iostream>
#include <string>
using namespace std;

//########## TASK 2 ##########
class StringPool {
public:
    string* stringPool[5]; // Dynamic array of strings (pointers)
    int currentSize;
    int maxSize;
    // Constructor
    StringPool() {
        maxSize = 5;
        currentSize = 0;
        for (int i = 0; i < maxSize; i++) {
            stringPool[i] = NULL;
        }
    }
    //Destructor to clean up memory
    ~StringPool() {
        for (int i = 0; i < currentSize; i++) {
            if (stringPool[i] != NULL) {
                delete stringPool[i];
                stringPool[i] = NULL;
            }
        }
    }

    //Add string to pool
    void addString(string val) {
        if (currentSize < maxSize) {
            stringPool[currentSize] = new string(val);
            currentSize++;
            cout << "Added: " << val << endl;
        } else {
            cout << "Pool is full!" << endl;
        }
    }

    //Removes a string from pool without freeing memory (creates leak/dangling pointer)
    string* removeString(int index) {
        if (index < 0 || index >= currentSize) {
            cout << "Invalid index!" << endl;
            return NULL;
        }

        //Save the pointer address before removing reference
        string* leakedPtr = stringPool[index];
        // Shift remaining elements
        for (int i = index; i < currentSize - 1; i++) {
            stringPool[i] = stringPool[i + 1];
        }

        stringPool[currentSize - 1] = NULL;
        currentSize--;
        cout << "Removed string at index " << index << " without deleting memory." << endl;
        return leakedPtr;
    }

    //Display pool status
    void displayPool() {
        cout << "\n##### Current Pool Status #####" << endl;
        cout << "Size: " << currentSize << "/" << maxSize << endl;
        for (int i = 0; i < currentSize; i++) {
            cout << "Index " << i << ": " << *stringPool[i] << endl;
        }

        cout << "-----------------------------------\n" << endl;
    }
};

int main() {
    StringPool pool;
    // Adding multiple strings to pool
    pool.addString("Apple");
    pool.addString("Banana");
    pool.addString("Cherry");
    pool.addString("Date");

    pool.displayPool(); }