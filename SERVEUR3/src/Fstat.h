#ifndef FSTAT_H
#define FSTAT_H

#include <string.h>
#include <string>

using namespace std;

class Fstat{
public:
    string path;            //Identifier
    int nbReq;
    int size;

public:
    Fstat();
    Fstat(string _path, int _nbReq, int _size);

};

#endif // FSTAT_H
