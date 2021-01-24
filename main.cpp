//
// Created by tal5s on 23/01/2021.
//

#include "DataStore.h"

int main(){
    DataStore dataStore= DataStore();
    dataStore.create<bool>("bool_test");

    dataStore.store<bool>()->append(true);
    dataStore.store<bool>()->append(false);
    dataStore.store<bool>()->append(true);
    dataStore.store<bool>()->append(false);
    cout << dataStore.store<bool>()->read(0);
    cout << dataStore.store<bool>()->read(1);
    cout << dataStore.store<bool>()->read(2);
    cout << dataStore.store<bool>()->read(3);
    cout << endl;
//    Store<char> c("char_test");
//    char abc[] = "gfda";
//    for (int j = 0; j < 4; ++j) {
//        c.append(abc[j]);
//    }
    dataStore.load<char>("char_test");
//    for (int j = 0; j < 4; ++j) {
//        cout << dataStore.store<char>()->read(j);
//    }

    return 0;
};