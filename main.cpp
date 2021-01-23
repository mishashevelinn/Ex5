#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int i = 0;
template<class T>
class Store {
private:
    const char *file_name;
    unsigned int size; //size of object
    unsigned int fileSize; //number of objects in storage
    fstream file;
    static int counter;


public:

    Store() : file_name(("temp")), size(sizeof(T)), fileSize(0), file() {
        //file.open(file_name);
        counter++;
    }

    Store(char *name) : file_name((name)), size(sizeof(T)), fileSize(0), file() {

    }


    void append(const T &obj) {
        //TODO file.write(reinterpret_cast<const char*>(&obj)
        file.open(file_name, ios::app);
        const char *temp = obj.serialized();
        file.write(temp, size);
        file.close();
        fileSize++;

    }

    void write(const T &obj, int i) {
        file.open(file_name, ios::app);
        //TODO check counter range and what happened to file
        file.seekg(i * size);
        const char *temp = obj.serialized();
        file.write(temp, size);
        file.close();
    }

    T &read(int i) { // TODO check index bounds
        char buff[size];
        T obj;
        file.open(file_name, ios::app);
        file.seekg(i * size);
        file.read(buff, size);
        file.close();
        return obj.deserialized(buff);
    }
};

class obj{
public:
    string name;
    obj(string name):name(name){}
};
int main() {
    obj k("obj");
    Store<obj> s;
    s.

    return 0;
}
