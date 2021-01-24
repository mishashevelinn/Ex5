
#ifndef EX5_DATASTOREIMP_H
#define EX5_DATASTOREIMP_H
#include "DataStore.h"

DataStore::DataStore(): mapOfStores(){
}

template<typename T>
void DataStore::create(const char *fileName) {
    if (mapOfStores.count(typeid(T).name()) != 0) throw "DuplicateStoreException";
    ifstream file(fileName);

    if (file.good()) throw "DuplicateFileException";
//    iterator mapOfStores.insert({key, element});
        mapOfStores.insert( std::make_pair( typeid(T).name(), new Store<T>(fileName) ) );
//        mapOfStores.insert({(typeid(T).name()), (new Store<T>(fileName))} );

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
    mapOfStores.insert( std::make_pair( typeid(T).name(), new Store<T>(fileName) ) );





}

template<typename T>
Store<T>*  DataStore::store() {
//    char type[strlen(typeid(T).name())];
//    strcpy(type,typeid(T).name());
    if (mapOfStores.count(typeid(T).name()) != 1) throw "InvalidStoreException";
    return dynamic_cast<Store<T>*>( mapOfStores[typeid(T).name()]);
}






#endif //EX5_DATASTOREIMP_H
