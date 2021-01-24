//
// Created by tal5s on 24/01/2021.
//

#ifndef EX5_DATASTORE_H
#define EX5_DATASTORE_H
#include "StoreBase.h"
#include <map>
#include <vector>
#include <typeinfo>
#include "Store.h"
using namespace std;
/*
 * DataStore can have any class of Store<T> type. it has map with typeid (key) and it's Store as value.
 */
class DataStore {
private:
    map<const char*, StoreBase*> mapOfStores;

public:
    DataStore();
    ~DataStore();

    template<typename T>
    void create(const char* fileName);

    template<typename T>
    void load(const char* fileName);

    template<typename T>
    Store<T>* store();
    class DuplicateStoreException{};
    class FileNotFoundException{};
    class UnMatchingTypeException{};
    class StoreNotFoundException{};
    class DuplicateFileException{};
};
#include "DataStoreImp.h"
#endif //EX5_DATASTORE_H
