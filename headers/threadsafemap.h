#ifndef THREADSAFEMAP_H
#define THREADSAFEMAP_H

#include <QMutex>
#include <QMap>


template<class K, class V>
/**
 * @brief The ThreadSafeMap class used for storage and manipulation of order safey between threads.
 */
class ThreadSafeMap
{

public:
    /**
     * @brief Default ThreadSafeMap Constructor.
     */
    explicit ThreadSafeMap()
    {}

    /**
     * @brief Inserts a value.
     * @param key The key for the value.
     * @param value The value to be inserted.
     */
    void insert(K key, V value)
    {
        mutex.lock();
        map[key] = value;
        mutex.unlock();
    }

    /**
     * @brief Gets a value from the map using a key.
     * @param key The key of the value.
     * @return The value pointed at by the key.
     */
    V get(K key)
    {
        V value = map[key];
        return value;
    }

    /**
     * @brief Returns the size of the map.
     * @return How many elements are in the map.
     */
    int size()
    {
        mutex.lock();
        int size = map.size();
        mutex.unlock();
        return size;
    }

    /**
     * @brief Gets the mutex the map is useing to make it thread safe.
     * @return The mutex.
     */
    QMutex& getMutex()
    {
        return mutex;
    }

    /**
     * @brief Returns an iterator to the start of the map.
     */
    auto begin()
    {
        return map.begin();
    }

    /**
     * @brief Returns an iterator to the end of the map.
     */
    auto end()
    {
        return map.end();
    }

    /**
     * @brief Returns whether or not an key is contined in the map.
     * @param key The key to be tested.
     * @return True if the key is contained, otherwise false.
     */
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
