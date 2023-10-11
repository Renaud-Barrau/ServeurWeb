#ifndef FSTATMANAGER_H
#define FSTATMANAGER_H
#include "Fstat.h"
#include <Qvector>

using namespace std;

class FstatManager{
public :
    QVector<Fstat> statvect;
    int CacheLastIndex;

public:
    FstatManager();
    int exist(string path);
    int add(string path,int size);
    bool newreq(string path);
    bool remove(string path);
    bool sort();


};

#endif // FSTATMANAGER_H
