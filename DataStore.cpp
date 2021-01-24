//
// Created by tal5s on 24/01/2021.
//

#include "DataStore.h"

DataStore::DataStore(): mapOfStores(){
}

template<typename T>
void DataStore::create(const char *fileName) {
    if (mapOfStores.count(typeid(T).name()) != 0) throw "DuplicateStoreException";
    ifstream file(fileName);
    if (file.good()) throw "DuplicateFileException";
    mapOfStores.insert(typeid(T).name(), new Store<T>(fileName));
}

template<typename T>
void DataStore::load(const char *fileName) {
    string type = typeid(T).name();
    ifstream file(fileName);
    if (file.bad()) throw "FileNotFoundException";
    if (mapOfStores.count(typeid(T).name()) != 0) throw "DuplicateStoreException";
    char temp[type.length()];
    file.read(temp, type.length());
    if(strcmp(type.c_str(), temp))
    {
        throw "UnmatchingTypeException";
    }
    mapOfStores.insert(typeid(T).name(), new Store<T>(fileName));





}

template<typename T>
Store<T> DataStore::store() {
    if (mapOfStores.count(typeid(T).name()) != 1) throw "InvalidStoreException";
    return mapOfStores.at(typeid(T).name());
}




