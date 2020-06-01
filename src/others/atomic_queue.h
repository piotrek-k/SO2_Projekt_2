#ifndef SO2_PROJEKT_ATOMICQUEUE
#define SO2_PROJEKT_ATOMICQUEUE

template <typename T>
class atomic_queue
{
public:
    void push(const T &value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queque.push(value);
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queque.pop();
    }

    T pop_and_get(){
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queque.pop();
        return m_queque.front();
    }

    int size(){
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queque.size();
    }

    T front(){
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queque.front();
    }

private:
    std::queue<T> m_queque;
    mutable std::mutex m_mutex;
};

#endif //SO2_PROJEKT_ATOMICQUEUE