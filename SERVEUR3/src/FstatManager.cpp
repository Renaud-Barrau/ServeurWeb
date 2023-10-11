#include "FstatManager.h"
#include "Fstat.h"
FstatManager::FstatManager(){
    //statvect.resize(1);
};

int FstatManager::add(string path,int size){
        statvect.resize(statvect.size()+1);
        statvect[statvect.size()-1].path = path;
        statvect[statvect.size()-1].nbReq = 1;
        statvect[statvect.size()-1].size = size;
    return statvect.size()-1;
};

int FstatManager:: exist(string path){
    for(int i = 0; i< statvect.size() ;i++){
        if(statvect[i].path == path){
           return i+1;
        }


    }
    return 0;
}

bool FstatManager::remove(string path){
    int i = 0;
        while(statvect[i].path != path){
            i++;
        }
        for(i; i< statvect.size()-1 ;i++){
            statvect[i] = statvect[i+1];
        }
        statvect.resize(statvect.size()-1);
    return 1;
};


bool FstatManager::sort(){
    int position = 0;
    for(int i = 1; i< statvect.size() ;i++){
        position = i;
        int current_val = statvect[i].nbReq;
        Fstat curr_fstat = statvect[i];
        while(position > 0 && statvect[position-1].nbReq > current_val){
            statvect[position] = statvect[position-1];
            position = position - 1;
        }
        statvect[position] = curr_fstat;
    }

return 1;
};
