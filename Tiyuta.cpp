//
// Created by misha on 22/01/2021.
//
#include <exception>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <tr1/cstdint>

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
        counter++;
    }

    Store(const char *name) : file_name((name)), size(sizeof(T)), fileSize(0), file() {
    }


    void append(const T &obj) {

        file.open(file_name, ios::app | ios::binary);
        const char *temp = obj.serialized();
        file.write(temp, size);
        file.close();
        fileSize++;

    }

    void write(const T &obj, int i) {
        file.open(file_name, ios::out | ios::in | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekp( i * size, ios::beg);
        const char *temp = obj.serialized();
        file.write(temp, size);
        file.close();
    }

    T &read(int i) { // TODO check index bounds
        file.open(file_name, ios::in | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        char buff[size];
        T obj;
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
        counter++;
    }
    Store(char *name) : file_name((name)), size(sizeof(char)), fileSize(0),  file() {

    }


    void append(char &c) {
        file.open(file_name, ios::app | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        file.write(reinterpret_cast<const char*>(&c), size);
        file.close();
        fileSize++;
    }

    void write(const char &c, int i) {
        file.open(file_name, ios::binary | ios::out | ios::in);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekp(i * size, ios::beg);
        file.write(reinterpret_cast<const char*>(&c),size);
        file.close();
    }

    char &read(int i) { // TODO check index bounds
        char buff;
        file.open(file_name, ios::in | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(i * size);
        file.read(&buff, size);
        file.close();
        return *(strdup(reinterpret_cast<const char *>(&buff)));
    }

};



template<>
class Store<int> {
private:
    const char *file_name;
    unsigned int size; //size of object
    unsigned int fileSize; //number of objects in storage
    fstream file;
    static int counter;


public:

    Store() : file_name(("temp")), size(sizeof(int)), fileSize(0), file() {
        counter++;
    }
    Store(char *name) : file_name((name)), size(sizeof(int)), fileSize(0),  file() {

    }


    void append(int &n) {
        file.open(file_name, ios::app | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        file.write(reinterpret_cast<const char*>(&n), size);
        file.close();
        fileSize++;
    }

    void write(const int &n, int i) {
        file.open(file_name, ios::binary | ios::out | ios::in);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekp(i * size, ios::beg);
        file.write(reinterpret_cast<const char*>(&n),size);
        file.close();
    }

    int &read(int i) { // TODO check index bounds
        int *buff = new int(1);
        file.open(file_name, ios::in | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(i * size);
        file.read((char*)buff, size);
        file.close();
        return *buff;
    }

};
int main() {
    char c ='a', b='f', e = 'r' , r= 'd' ;

    Store<int> s("TestInt.bin");
    for (int k = 0; k < 10; k++) {
        s.append(k);
    }
    s.write(3, 10);
    for (int k = 0; k < 10; k++) {
        int m = s.read(k);
        cout << m << " ";
    }
    return 0;
}
