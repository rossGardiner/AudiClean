//
// Blocking queue implementation, currently only blocks when Get is attempted while there are no elements inside the queue. In the future and max size could be defined and blocking could be added when the queue is full
//
#include "BlockingQueue.h"

/*!
 * constructor for BlockingQueue, maxSize may be set
 * @tparam T
 * @param _maxSize maximum size of the blocking queue to set
*/
template<typename T>
BlockingQueue<T>::BlockingQueue(int _maxSize) {
    maxSize = _maxSize;
}

/*!
 * Pop method, uses mutex lock to sleep the current thread until data are available on the queue. This may be used to synchonise and schedule threads.
 * @tparam T
 * @return Element on deque back
 */
template <typename T>
T BlockingQueue<T>::Pop() {
    std::unique_lock<std::mutex> lock(mutex);
    isEmpty.wait(lock, [=]{ return !internalQueue.empty(); });
    T ret = internalQueue.back();
    internalQueue.pop_back();
    if(!Full()) isFull.notify_all();
    return ret;
}
/*!
 *
 * @tparam T
 * @return true if internal queue empty, false otherwise
 */
template <typename T>
bool BlockingQueue<T>::IsEmpty(){
    return internalQueue.empty();
}

/*!
 * Gets the current length of elements in the queue.
 * @tparam T
 * @return size of internal deque
 */
template <typename T>
int BlockingQueue<T>::Size(){
    return internalQueue.size();
}

/*!
  * adds element to the queue.
  * @tparam T
  * @param toPush
  */
template <typename T>
void BlockingQueue<T>::Push(T toPush) {
     std::unique_lock<std::mutex> lock(mutex);
     isFull.wait(lock, [=]{ return !Full(); });
     internalQueue.push_front(toPush);
     isEmpty.notify_all();
}

/*!
 * checks if the queue is full
 * @tparam T
 * @return true if full; false otherwise
 */
template <typename T>
bool BlockingQueue<T>::Full(){
    return  internalQueue.size() >= maxSize;
}
