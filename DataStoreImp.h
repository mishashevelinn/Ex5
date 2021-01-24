
#ifndef EX5_DATASTOREIMP_H
#define EX5_DATASTOREIMP_H
#include "DataStore.h"
/*
 * initializing map
 */
DataStore::DataStore(): mapOfStores(){}

/*
 * destructor delete all Stores in map (values)
 */
DataStore::~DataStore() {
    map<const char*, StoreBase*>::iterator it1;
    for (it1 = mapOfStores.begin(); it1!=mapOfStores.end(); ++it1) {
        delete it1->second;
    }
}
/*
 * check if DataStore has already file with same name.
 * check if file already exist.
 * if the two condition are false, make new store with the type.
 */
template<typename T>
void DataStore::create(const char *fileName) {
    if (mapOfStores.count(typeid(T).name()) != 0) throw DuplicateStoreException();
    ifstream file(fileName);
    if (file.good()) throw DuplicateFileException();
    try{
        mapOfStores.insert( std::make_pair( typeid(T).name(), new Store<T>(fileName) ) );
    }
    catch (bad_alloc &ba) {
        cout << ba.what() << endl;
    }

}
/*
 * check if file exist, check if no other store with same type in Datastore and if the file's type and
 * object type are the same. finaly, add the file as new store to Datastore
 */
template<typename T>
void DataStore::load(const char *fileName) {
    ifstream file(fileName);
    if (!file.good()) throw FileNotFoundException();
    if (mapOfStores.count(typeid(T).name()) != 0) throw DuplicateStoreException();
    char temp[strlen(typeid(T).name())];
    file.read(temp, strlen(typeid(T).name()));
    if(!strcmp(typeid(T).name(), temp))
    {
        throw UnMatchingTypeException();
    }
    mapOfStores.insert( std::make_pair(typeid(T).name(), new Store<T>(fileName) ) );
}
/*
 * 'getter' to specific store, return store with wanted type.
 */
template<typename T>
Store<T>*  DataStore::store() {
    if (mapOfStores.count(typeid(T).name()) != 1) throw StoreNotFoundException();
    try {
        return dynamic_cast<Store<T>*>( mapOfStores[typeid(T).name()]);
    }
    catch (bad_cast &bc) {
        cout << bc.what() << endl;
    }
}






#endif //EX5_DATASTOREIMP_H
