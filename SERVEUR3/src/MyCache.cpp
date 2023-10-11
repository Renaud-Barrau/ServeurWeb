#include "cache.h"
#include "cacheelement.h"
#include <iostream>


MyCache::MyCache(){
    cacheSize = 0;
    minFreq = 1;
    cacheByteSize = 0;
    cacheHit = 0;
    cacheMiss = 0;
};

MyCache::MyCache(int _maxCacheSize){
    maxCacheSize = _maxCacheSize;
    cacheSize = 0;
    minFreq = 1;
    cacheByteSize = 0;
    cacheHit = 0;
    cacheMiss = 0;
};

bool MyCache::isInCache(string path){
    if(cache.contains(path) == true){
        cacheHit++;
        return true;
    }
    else{
        cacheMiss++;
        return false;
    }
};



void MyCache::cacheInfo(){
        int freqtest = 0;
        int cpt = 0;
         cout << "cacheSize " << cacheSize << endl;
         cout << "cacheByteSize " << cacheByteSize << endl;
         cout << "minFreq " << minFreq << endl;
         cout << "Cache Hit : " << cacheHit << "| Cache Miss : " << cacheMiss<< endl;
         if(cacheHit + cacheMiss != 0){
             int cacheRate = (100*cacheHit)/(cacheHit + cacheMiss);
         cout << "Cache Rate : " << cacheRate << "%" << endl;}
         QList keys = freqMap.keys();

         for (int i = 0; i< keys.length(); i++){
             cout << "freq "<< keys[i] << " : "<< endl;

             for(int j = 0; j<freqMap.value(keys[i]).size();j++){
                 cout << "   - " << freqMap.value(keys[i])[j] << endl;
             }
         }

}

bool MyCache::clearCache(){
    QList keys = freqMap.keys();

    for (int i = 0; i< keys.length(); i++){
        cout << "freq "<< keys[i] << " : "<< endl;

        for(int j = 0; j<freqMap.value(keys[i]).size();j++){
            cache.remove(freqMap.value(keys[i])[j]);
        }
        freqMap.remove(keys[i]);
    }

    cacheSize = 0;
    minFreq = 1;
    cacheByteSize = 0;
    cacheHit = 0;
    cacheMiss = 0;
cout << "clearing cache"<<endl;
    return 1;
}

QByteArray MyCache::getFromCache(string path){
    if(cache.contains(path) == true){

        int cur_freq = cache.value(path).freq;
        int ind = freqMap[cur_freq].indexOf(path);
        freqMap[cur_freq].remove(ind);

        if(cur_freq == minFreq && cacheSize == maxCacheSize){
            minFreq++;
        }
        cache[path].increase();

        cur_freq = cache.value(path).freq;
        cout << "freqq : " << cur_freq << endl;

        if(freqMap.value(cur_freq-1).size() == 0){
            freqMap.remove(cur_freq-1);
            cout << "VIDE" << endl;
        }else if(cur_freq-1 == minFreq-1 && cacheSize == maxCacheSize){
            minFreq--;
        }
        if(freqMap.contains(cur_freq) == 1){
           freqMap[cur_freq].append(path);
           cout << "CONTIENT" << endl;
        }
        else{
            QVector<string> vect(1);
            vect[0] = path;
            freqMap.insert(cur_freq,vect);
            cout << "NOUVEAU" << endl;
        }

        return cache.value(path).data;
    }
    else{
        cacheHit--;
        // ???
    }
};



bool MyCache::removeLRU(){
    string key = freqMap.value(minFreq).first();
    freqMap[minFreq].removeFirst();
    if(freqMap.value(minFreq).size() == 0){
        freqMap.remove(minFreq);
    }
    cacheByteSize -= cache.value(key).data.size();
    cache.remove(key);

    return 1;
}

bool MyCache::toCache(string path,QByteArray _data){
    if(cache.contains(path) == true){
        return 0;
    }
    else if (maxCacheSize > cacheSize){
        CacheElement newElement(_data);
        cache.insert(path,newElement);
        cacheSize ++;
       // if(cacheSize == maxCacheSize){
       //    minFreq = 1;
       // }
        cacheByteSize += _data.size();
    }
    else if (maxCacheSize == cacheSize){
        removeLRU();
        minFreq = 1;
        CacheElement newElement(_data);
        // QVector<string> vect(1);
        //vect[0] = path;
        //freqMap.insert(1,vect);
        cache.insert(path,newElement);
        cacheByteSize += _data.size();
    }
    if(freqMap.contains(1)){
       freqMap[1].append(path);
       cout << "CONTIENT tocache" << endl;
    }
    else{
        QVector<string> vect(1);
        vect[0] = path;
        freqMap.insert(1,vect);
        cout << "NOUVEAU tocache" << endl;
    }

   // cacheMiss--; // Si l'on considère que la premiere fois que l'on demande un objet ne compte pas comme un miss

    return 1;
};

int MyCache::getMaxSize(){
    return maxCacheSize;
};

int MyCache::getSize(){
    return cacheSize;
};
