//
// Created by tal5s on 24/01/2021.
//

#ifndef EX5_DATASTORE_H
#define EX5_DATASTORE_H
#include "StoreBase.h "
#include <string>
#include <map>
#include <typeinfo>
#include "Store.h"
using namespace std;
class DataStore {
private:
    map<string, StoreBase*> mapOfMarks;
    int storeCount;

public:
    DataStore();

    template<typename T>
    void create(const char* fileName);

};

#endif //EX5_DATASTORE_H
