//
// Created by tal5s on 24/01/2021.
//

#include "DataStore.h"

DataStore::DataStore(): mapOfMarks(), storeCount(0){
}

template<typename T>
void DataStore::create(const char *fileName) {
    mapOfMarks.insert(typeid(T).name(), new Store<T>);
    storeCount++;
}




