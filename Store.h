#ifndef EX5_STORE_H
#define EX5_STORE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include "StoreBase.h"
using namespace std;
class FileNotFoundException{};
/*
 * Generic store, requires methods:
 * --serialized() - returns char array representing an object
 *--deserialized() - returns an object, represented by char array
 * Big three implementation is required
 */
template<class T>
class Store : public StoreBase{
private:
    const char *file_name;
    unsigned int size; //size of object
    unsigned int fileSize; //number of objects in storage
    fstream file;

public:
    /*
     * Default constructor.
     * Creates temp file
     * Checks if file is previously initialized.
     * If file is not initialized, writes the class name int the beginning of file
     * */
    Store() : file_name(("temp")), size(sizeof(T)), fileSize(0), file() {
        file.open(file_name, ios::app | ios::binary | ios::in | ios::out);
        if (file.fail()) throw FileNotFoundException();
        if(file.tellg() == 0){
            file.seekp(0, ios::beg);
            file.write(typeid(T).name(), strlen(typeid(T).name()));
        }
        else{
            int typeSize = strlen(typeid(T).name());
            file.seekp(typeSize);
            file.seekg(0, ios_base::end);
            int length = file.tellg();
            fileSize = (length - typeSize)/size;
        }
        file.close();
    }

    /*Same as default constructor, except a parameter - file name*/
    Store(const char *name) : file_name((name)), size(sizeof(T)), fileSize(0), file() {
        file.open(file_name, ios::app | ios::binary | ios::in | ios::out);
        if (file.fail()) throw FileNotFoundException();
        if(file.tellg() == 0){
            file.seekp(0, ios::beg);
            file.write(typeid(T).name(), strlen(typeid(T).name()));
        }
        else{
            int typeSize = strlen(typeid(T).name());
            file.seekp(typeSize);
            file.seekg(0, ios_base::end);
            int length = file.tellg();
            fileSize = (length - typeSize)/size;
        }
        file.close();
    }


    /*
     * Writes a sequence of bytes, representing an object to an end of binary file
     * Bytes sequence produced by serialized() method
     * */
    void append(const T &obj) {

        file.open(file_name, ios::app | ios::binary);
       if(file.fail()){
           throw FileNotFoundException();
       }
        const char *temp = obj.serialized();
        file.write(temp, size);
        file.close();
        fileSize++;

    }

    /*Same as append, except for getting certain index to be writen at in binary file
     * Performs bounds check, since index is involved
     * */
    void write(const T &obj, int i) {
        file.open(file_name, ios::out | ios::in | ios::binary);
        if (file.fail()){
            throw FileNotFoundException();
        }
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        const char *temp = obj.serialized();
        file.write(temp, size);
        file.close();
    }

    /*Gets index of byte sequence in binary file and returns an
     * object, represented by a sequence by invoking deserialized() method*/
    T &read(int i) {
        file.open(file_name, ios::in | ios::binary);
        if (file.fail()){
            throw FileNotFoundException();
        }if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        char buff[size];
        T obj = T();
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.read(buff, size);
        file.close();
        obj.deserialized(buff);
        return obj;
    }
};

/*Following classes are specializations for primitive types.
 * The functionality is as in generic analog.*/

template<>
class Store<char> : public StoreBase{
private:
    const char *file_name;
    unsigned int size; //size of object
    unsigned int fileSize; //number of objects in storage
    fstream file;

public:
    Store() : file_name(("temp")), size(sizeof(char)), fileSize(0), file() {
        file.open(file_name, ios::app | ios::binary | ios::in | ios::out);
        if (file.fail()) throw FileNotFoundException();
        if(file.tellg() == 0){
            file.seekp(0, ios::beg);
            file.write(typeid(char).name(), strlen(typeid(char).name()));
        }
        else{
            int typeSize = strlen(typeid(char).name());
            file.seekp(typeSize);
            file.seekg(0, ios_base::end);
            int length = file.tellg();
            fileSize = (length - typeSize)/size;
        }
        file.close();
    }
    Store(const char *name) : file_name((name)), size(sizeof(char)), fileSize(0),  file() {
        file.open(file_name, ios::app | ios::binary | ios::in | ios::out);
        if (file.fail()) throw FileNotFoundException();
        if(file.tellg() == 0)
        {
            file.seekp(0, ios::beg);
            file.write(typeid(char).name(), 1);
        }
        else{
            int typeSize = strlen(typeid(char).name());
            file.seekp(typeSize);
            file.seekg(0, ios_base::end);
            int length = file.tellg();
            fileSize = (length - typeSize)/size;
        }
        file.close();
    }


    void append(char &c) {
        file.open(file_name, ios::app | ios::binary);
        if (file.fail()) throw FileNotFoundException();
        file.write(reinterpret_cast<const char*>(&c), size);
        file.close();
        fileSize++;
    }

    void write(const char &c, int i) {
        file.open(file_name, ios::binary | ios::out | ios::in);
        if (file.fail()) throw FileNotFoundException();
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.write(reinterpret_cast<const char*>(&c),size);
        file.close();
    }

    char &read(int i) {
        char buff = 0;
        file.open(file_name, ios::in | ios::binary);
        if (file.fail()) throw FileNotFoundException();
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

public:
    Store() : file_name(("temp")), size(sizeof(int)), fileSize(0), file() {
        file.open(file_name, ios::app | ios::binary | ios::in | ios::out);
        if (file.fail()) throw FileNotFoundException();
        if(file.tellg() == 0)
        {
            file.seekp(0, ios::beg);
            file.write(typeid(int).name(), strlen(typeid(int).name()));
        }
        else{
            int typeSize = strlen(typeid(int).name());
            file.seekp(typeSize);
            file.seekg(0, ios_base::end);
            int length = file.tellg();
            fileSize = (length - typeSize)/size;
        }
        file.close();
    }
    Store(char *name) : file_name((name)), size(sizeof(int)), fileSize(0),  file() {
        file.open(file_name, ios::app | ios::binary | ios::in | ios::out);
        if (file.fail()) throw FileNotFoundException();
        if(file.tellg() == 0)
        {
            file.seekp(0, ios::beg);
            file.write(typeid(int).name(), strlen(typeid(int).name()));
        }
        else{
            int typeSize = strlen(typeid(int).name());
            file.seekp(typeSize);
            file.seekg(0, ios_base::end);
            int length = file.tellg();
            fileSize = (length - typeSize)/size;
        }
        file.close();
    }


    void append(int &n) {
        file.open(file_name, ios::app | ios::binary);
        if (file.fail()) throw FileNotFoundException();
        file.write(reinterpret_cast<const char*>(&n), size);
        file.close();
        fileSize++;
    }

    void write(const int &n, int i) {
        file.open(file_name, ios::binary | ios::out | ios::in);
        if (file.fail()) throw FileNotFoundException();
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.write(reinterpret_cast<const char*>(&n),size);
        file.close();
    }

    int &read(int i) {
        int *buff = new int(1);
        file.open(file_name, ios::in | ios::binary);
        if (file.fail()) throw FileNotFoundException();
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

public:

    Store() : file_name(("temp")), size(sizeof(double )), fileSize(0), file() {

        file.open(file_name, ios::app | ios::binary | ios::in | ios::out);
        if (file.fail()) throw FileNotFoundException();
        if(file.tellg() == 0)
        {
            file.seekp(0, ios::beg);
            file.write(typeid(double).name(), strlen(typeid(double).name()));
        }
        else{
            int typeSize = strlen(typeid(double).name());
            file.seekp(typeSize);
            file.seekg(0, ios_base::end);
            int length = file.tellg();
            fileSize = (length - typeSize)/size;
        }
        file.close();
    }
    Store(char *name) : file_name((name)), size(sizeof(double )), fileSize(0),  file() {
        file.open(file_name, ios::app | ios::binary | ios::in | ios::out);
        if (file.fail()) throw FileNotFoundException();
        if(file.tellg() == 0)
        {
            file.seekp(0, ios::beg);
            file.write(typeid(double).name(), strlen(typeid(double).name()));
        }
        else{
            int typeSize = strlen(typeid(double).name());
            file.seekp(typeSize);
            file.seekg(0, ios_base::end);
            int length = file.tellg();
            fileSize = (length - typeSize)/size;
        }
        file.close();
    }


    void append(double &d) {
        file.open(file_name, ios::app | ios::binary);
        if (file.fail()) throw FileNotFoundException();
        file.write(reinterpret_cast<const char*>(&d), size);
        file.close();
        fileSize++;
    }

    void write(const int &n, int i) {
        file.open(file_name, ios::binary | ios::out | ios::in);
        if (file.fail()) throw FileNotFoundException();
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.write(reinterpret_cast<const char*>(&n),size);
        file.close();
    }

    double &read(int i) {
        double * buff = new double (1);
        file.open(file_name, ios::in | ios::binary);
        if (file.fail()) throw FileNotFoundException();
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
public:

    Store() : file_name(("temp")), size(sizeof(bool)), fileSize(0), file() {
        file.open(file_name, ios::app | ios::binary | ios::in | ios::out);
        if (file.fail()) throw FileNotFoundException();
        if(file.tellg() == 0)
        {
            file.seekp(0, ios::beg);
            file.write(typeid(bool).name(), strlen(typeid(bool).name()));
        }
        else{
            int typeSize = strlen(typeid(bool).name());
            file.seekp(typeSize);
            file.seekg(0, ios_base::end);
            int length = file.tellg();
            fileSize = (length - typeSize)/size;
        }
        file.close();
    }
    Store(const char *name) : file_name((name)), size(sizeof(bool )), fileSize(0),  file() {
        file.open(file_name, ios::app | ios::binary | ios::in | ios::out);
        if (file.fail()) throw FileNotFoundException();
        if(file.tellg() == 0)
        {
            file.seekp(0, ios::beg);
            file.write(typeid(bool).name(), strlen(typeid(bool).name()));
        }
        else{
            int typeSize = strlen(typeid(bool).name());
            file.seekp(typeSize);
            file.seekg(0, ios_base::end);
            int length = file.tellg();
            fileSize = (length - typeSize)/size;
        }
        file.close();
    }


    void append(const bool &b) {
        file.open(file_name, ios::app | ios::binary);
        if (file.fail()) throw FileNotFoundException();
        file.write(reinterpret_cast<const char*>(&b), size);
        file.close();
        fileSize++;
    }

    void write(const bool &b, int i) {
        file.open(file_name, ios::binary | ios::out | ios::in);
        if (file.fail()) throw FileNotFoundException();
        if (i < 0 || i>= fileSize) throw range_error("index is out of bounds\n");
        file.seekg(0, ios_base::end);
        int length = file.tellg();
        file.seekg((length - (fileSize-i)*size), ios_base::beg);
        file.write(reinterpret_cast<const char*>(&b),size);
        file.close();
    }

    bool read(int i) {
        bool * buff = new bool() ;
        file.open(file_name, ios::in | ios::binary);
        if (file.fail()) throw FileNotFoundException();
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
s