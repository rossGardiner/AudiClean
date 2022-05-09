//
// Created by ross on 18/02/2022.
//

#ifndef AUDICLEAN_BLOCKINGQUEUE_H
#define AUDICLEAN_BLOCKINGQUEUE_H
#include <deque>
#include <mutex>
#include <condition_variable>


template <typename T>
//!  BlockingQueue Class
/*!
    
*/

/*!
 * Class to wrap around std::deque and block thread execution when no data is available at the output.
 * @tparam T Type of elements in the queue
 */
class BlockingQueue {
public:
    BlockingQueue(int maxSize=1);
    void Push(T toPush);
    T Pop();
    bool IsEmpty();
    int Size();
    bool Full();
private:
    int maxSize;
    std::deque<T> internalQueue;
    std::mutex mutex;
    std::condition_variable isFull;
    std::condition_variable isEmpty;
};


#endif //AUDICLEAN_BLOCKINGQUEUE_H
