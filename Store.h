//
// Created by misha on 22/01/2021.
//

#ifndef EX5_STORE_H
#define EX5_STORE_H
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
#include "StoreBase.h"
using namespace std;
int i = 0;
template<class T>
class Store : public StoreBase{
private:
    const char *file_name;
    unsigned int size; //size of object
    unsigned int fileSize; //number of objects in storage
    fstream file;
    static int counter;

public:

    Store() : file_name(("temp")), size(sizeof(T)), fileSize(0), file() {
        counter++;
        file.open(file_name, ios::app | ios::binary);
        if(file.peek() == std::ifstream::traits_type::eof())
        {
            file.write(typeid(T).name(), sizeof (typeid(T).name()));
        }
        file.close();
    }

    Store(const char *name) : file_name((name)), size(sizeof(T)), fileSize(0), file() {
        file.open(file_name, ios::app | ios::binary);
        if(file.peek() == std::ifstream::traits_type::eof())
        {
            file.write(typeid(T).name(), sizeof (typeid(T).name()));
        }
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
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
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
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.read(buff, size);
        file.close();
        return obj.deserialized(buff);
    }
};

template<>
class Store<char> : public StoreBase{
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
    Store(const char *name) : file_name((name)), size(sizeof(char)), fileSize(0),  file() {

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
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.write(reinterpret_cast<const char*>(&c),size);
        file.close();
    }

    char &read(int i) { // TODO check index bounds
        char buff = 0;
        file.open(file_name, ios::in | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.read(&buff, size);
        file.close();
        return *(strdup(reinterpret_cast<const char *>(&buff)));
    }

};



template<>
class Store<int>: public StoreBase {
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
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
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
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.read((char*)buff, size);
        file.close();
        return *buff;
    }

};

template<>
class Store<double>: public StoreBase {
private:
    const char *file_name;
    unsigned int size; //size of object
    unsigned int fileSize; //number of objects in storage
    fstream file;
    static int counter;


public:

    Store() : file_name(("temp")), size(sizeof(double )), fileSize(0), file() {
        counter++;
    }
    Store(char *name) : file_name((name)), size(sizeof(double )), fileSize(0),  file() {

    }


    void append(double &d) {
        file.open(file_name, ios::app | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        file.write(reinterpret_cast<const char*>(&d), size);
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
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.write(reinterpret_cast<const char*>(&n),size);
        file.close();
    }

    double &read(int i) { // TODO check index bounds
        double * buff = new double (1);
        file.open(file_name, ios::in | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.read((char*)buff, size);
        file.close();
        return *buff;
    }

};

template<>
class Store<bool> : public StoreBase{
private:
    const char *file_name;
    unsigned int size; //size of object
    unsigned int fileSize; //number of objects in storage
    fstream file;
    static int counter;


public:

    Store() : file_name(("temp")), size(sizeof(bool)), fileSize(0), file() {
        counter++;
    }
    Store(const char *name) : file_name((name)), size(sizeof(bool )), fileSize(0),  file() {

    }


    void append(const bool &b) {
        file.open(file_name, ios::app | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        file.write(reinterpret_cast<const char*>(&b), size);
        file.close();
        fileSize++;
    }

    void write(const bool &b, int i) {
        file.open(file_name, ios::binary | ios::out | ios::in);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.write(reinterpret_cast<const char*>(&b),size);
        file.close();
    }

    bool read(int i) { // TODO check index bounds
        bool * buff = new bool() ;
        file.open(file_name, ios::in | ios::binary);
        if (!file){
            stringstream ss1, ss2(file_name);
            ss1 << "Could not open the file ";
            ss1 << ss2.str() << "\n";
            throw runtime_error( ss1.str());
        }
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.read((char*)buff, size);
        file.close();
        return *buff;
    }

};


#endif //EX5_STORE_H
