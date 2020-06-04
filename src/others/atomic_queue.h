#ifndef SO2_PROJEKT_ATOMICQUEUE
#define SO2_PROJEKT_ATOMICQUEUE

#include <mutex>
#include <condition_variable>

template <typename T>
class atomic_queue
{
public:

    void push(const T &value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queque.push(value);
        queue_push_cv.notify_all();
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queque.pop();
    }

    T pop_and_get()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_queque.size() > 0)
        {
            T obj = m_queque.front();
            m_queque.pop();
            return obj;
        }
        return nullptr;
    }

    bool pop_and_get(T obj)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_queque.size() > 0)
        {
            obj = m_queque.front();
            m_queque.pop();
            return true;
        }
        return false;
    }

    int size()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queque.size();
    }

    T front()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queque.front();
    }

    std::condition_variable queue_push_cv;

private:
    std::queue<T> m_queque;
    mutable std::mutex m_mutex;
};

#endif //SO2_PROJEKT_ATOMICQUEUE