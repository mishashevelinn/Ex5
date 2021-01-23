//
// Created by misha on 22/01/2021.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;
int i = 0;
template<class T>
class Store {
private:
    const char *file_name;
    unsigned int size; //size of object
    unsigned int fileSize; //number of objects in storage
    fstream file;
    static int counter;


public:

    Store() : file_name(("temp")), size(sizeof(T)), fileSize(0), file() {
        //file.open(file_name);
        counter++;
    }

    Store(char *name) : file_name((name)), size(sizeof(T)), fileSize(0), file() {

    }


    void append(const T &obj) {
        //TODO file.write(reinterpret_cast<const char*>(&obj)
        file.open(file_name, ios::app | ios::binary);
        const char *temp = obj.serialized();
        file.write(temp, size);
        file.close();
        fileSize++;

    }

    void write(const T &obj, int i) {
        file.open(file_name, ios::app | ios::binary);
        //TODO check counter range and what happened to file
        file.seekg(i * size);
        const char *temp = obj.serialized();
        file.write(temp, size);
        file.close();
    }

    T &read(int i) { // TODO check index bounds
        char buff[size];
        T obj;
        file.open(file_name, ios::app | ios::binary);
        file.seekg(i * size);
        file.read(buff, size);
        file.close();
        return obj.deserialized(buff);
    }
};

template<>
class Store<char> {
private:
    const char *file_name;
    unsigned int size; //size of object
    unsigned int fileSize; //number of objects in storage
    fstream file;
    static int counter;


public:

    Store() : file_name(("temp")), size(sizeof(char)), fileSize(0), file() {
        //file.open(file_name);
        counter++;
    }

    Store(char *name) : file_name((name)), size(sizeof(char)), fileSize(0), file() {

    }


    void append(const char &c) {
        //TODO file.write(reinterpret_cast<const char*>(&obj)
        file.open(file_name,  ios::binary);
        file.write(&c, size);
        file.close();
        fileSize++;

    }

    void write(const char &c, int i) {
        file.open(file_name, ios::app | ios::binary);
        //TODO check counter range and what happened to file
        file.seekg(i * size);
        file.write(&c, size);
        file.close();
    }

    char &read(int i) { // TODO check index bounds
        char buff;
        file.open(file_name, ios::in);
        file.seekg(i * size);
        file.read(&buff, size);
        file.close();
        return *(strdup(reinterpret_cast<const char *>(&buff)));
    }

};

int main() {
    char c='f', b='a';
    Store<char> my_s("Test");
    my_s.append(c);

    return 0;
}
