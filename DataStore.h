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
class DataStore {
private:
    map<const char*, StoreBase*> mapOfStores;

public:
    DataStore();

    template<typename T>
    void create(const char* fileName);

    template<typename T>
    void load(const char* fileName);

    template<typename T>
    Store<T>* store();
};
#include "DataStoreImp.h"
#endif //EX5_DATASTORE_H
