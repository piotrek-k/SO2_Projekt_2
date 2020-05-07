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

    int size(){
        return m_queque.size();
    }

    T front(){
        return m_queque.front();
    }

private:
    std::queue<T> m_queque;
    mutable std::mutex m_mutex;
};

#endif //SO2_PROJEKT_ATOMICQUEUE