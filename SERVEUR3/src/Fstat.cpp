#include "Fstat.h"


Fstat::Fstat(){

};

Fstat::Fstat(string _path, int _nbReq, int _size){
    path = _path;
    nbReq = _nbReq;
    size = _size;
};
