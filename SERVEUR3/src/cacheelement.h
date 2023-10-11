#ifndef CACHEELEMENT_H
#define CACHEELEMENT_H
#include <QHash>
using namespace std;

class CacheElement
{
public:
    QByteArray data;
    int freq;

public:
    CacheElement();
    CacheElement(QByteArray _data);
    void increase();

};

#endif // CACHEELEMENT_H
