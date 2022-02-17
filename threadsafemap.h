#ifndef THREADSAFEMAP_H
#define THREADSAFEMAP_H

#include <QMutex>
#include <QMap>

template<class K, class V>
class ThreadSafeMap
{

public:
    explicit ThreadSafeMap()
    {

    }

    void insert(K key, V value)
    {
        mutex.lock();
        map[key] = value;
        mutex.unlock();
    }

    V get(K key)
    {
        V value = map[key];
        return value;
    }

    int size()
    {
        mutex.lock();
        int size = map.size();
        mutex.unlock();
        return size;
    }

    QMutex& getMutex()
    {
        return mutex;
    }

    auto begin()
    {
        return map.begin();
    }

    auto end()
    {
        return map.end();
    }

    bool contains(const K key)
    {
        mutex.lock();
        bool isContained = map.contains(key);
        mutex.unlock();
        return isContained;
    }

private:
    QMutex mutex;
    QMap<K, V> map;
};



#endif // THREADSAFEMAP_H
