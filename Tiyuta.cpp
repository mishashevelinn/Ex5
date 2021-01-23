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

    Store(const char *name) : file_name((name)), size(sizeof(T)), fileSize(0), file() {

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
//    static int counter;


public:

    Store() : file_name(("temp")), size(sizeof(char)), fileSize(0), file(file_name, ios::out | ios::binary) {
        //file.open(file_name);
//        counter++;
    }

    Store(char *name) : file_name((name)), size(sizeof(char)), fileSize(0),  file() {

    }


    void append(char &c) {
        //TODO file.write(reinterpret_cast<const char*>(&obj)
        file.open(file_name, ios::app | ios::binary);
        file.seekg(fileSize * size);
        file.write(reinterpret_cast<const char*>(&c), size);
        file.close();
        fileSize++;

    }

    void write(const char &c, int i) {
        file.open(file_name, ios::out | ios::binary);
        //TODO check counter range and what happened to file
        file.seekg(i * size);
        file.write(reinterpret_cast<const char*>(&c),size);
        file.close();
    }

    char &read(int i) { // TODO check index bounds
        char buff;
        file.open(file_name, ios::in | ios::binary);
        file.seekg(i * size);
        file.read(&buff, size);
        file.close();
        return *(strdup(reinterpret_cast<const char *>(&buff)));
    }

};

int main() {
    char c ='a', b='f', e = 'r' , r= 'd' ;

    Store<char> my_s("Test.bin");
    my_s.append(c);
    my_s.append(b);
    my_s.append(e);
    my_s.append(r);
//    my_s.append(*(c+4));
//    g = my_s.read(0);
    cout << my_s.read(3);
    return 0;
}
