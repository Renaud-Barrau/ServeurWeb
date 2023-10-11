#include "cacheelement.h"

CacheElement::CacheElement()
{

}

CacheElement::CacheElement(QByteArray _data)
{
    data = _data;
    freq = 1;
}

void CacheElement::increase()
{
    freq++;
}
