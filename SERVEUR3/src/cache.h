#ifndef CACHE_H
#define CACHE_H
#include <QHash>
//#include "Fstat.h"
#include "cacheelement.h"
#include <Qvector>

using namespace std;

class MyCache{

private:
   // QHash<string,QByteArray> cache;
    QHash<string,CacheElement> cache;
    QHash<int,QVector<string>> freqMap;
    int minFreq;


public :
    int cacheByteSize;
    int maxCacheSize;
    int cacheSize;
    int cacheHit;
    int cacheMiss;

public:
    // Constructeur
    MyCache();
    MyCache(int _maxCacheSize);
    int getMaxSize();
    bool isInCache(string path);
    QByteArray getFromCache(string path);           // RECUPERER DU CACHE
    bool toCache(string path, QByteArray _data);     // METTRE EN CACHE (1 si succès 0 sinon)
    bool removeLRU();              // RETIRER DU CACHE (1 si succès 0 sinon)
    //bool isCachable();                      // VERIFIE SI ASSEZ DE PLACE DANS LE CACHE SINON EFFACE L'ELEMENT LE MOINS DEMANDE
    void cacheInfo();
    bool clearCache();

    //int getByteSyze();
    int getSize();                                  // RENVOIE LE NB DE FICHEIRS
    int setMaxSize(int _maxCacheSize);
        // REGLER LE NB MAX DE FICHIERS


};

#endif // CACHE_H
