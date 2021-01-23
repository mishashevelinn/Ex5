//
// Created by misha on 22/01/2021.
//
#include <exception>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>

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

int main() {
    char c ='a', b='f', e = 'r' , r= 'd' ;

    Store<char> my_s("Test.bin");
    string msg = "Could not open file ";
    string file_name = "Trst.bin";
//    my_s.append(c);
//    my_s.append(b);
//    my_s.append(e);
//    my_s.append(r);
//    my_s.write(b, 4);
//    my_s.append(*(c+4));
//    g = my_s.read(0);
//    cout << my_s.read(4);
    return 0;
}
