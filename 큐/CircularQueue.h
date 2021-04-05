#include <iostream>
#include <algorithm>

template <typename T>
class CircularQueue
{
private:
    T *data;
    int rearIdx;
    int frontIdx;
    int capacity;
    const char *emptyError = "Queue is empty.";

public:
    CircularQueue();
    CircularQueue(int capacity);
    ~CircularQueue();
    void push(const T &);
    void pop();
    T front();
    T rear();
    bool isEmpty();
    bool isFull();

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const CircularQueue<U> &cq);
};

// Constructor
template <typename T>
CircularQueue<T>::CircularQueue() : CircularQueue(5)
{
}

template <typename T>
CircularQueue<T>::CircularQueue(int capacity) : data(new T[capacity]), rearIdx(0), frontIdx(0), capacity(capacity)
{
}

// Destructor
template <typename T>
CircularQueue<T>::~CircularQueue()
{
    delete[] data;
    data = nullptr;
}

// Pop
template <typename T>
void CircularQueue<T>::pop()
{
    if (isEmpty()){
        throw "Queue is empty.";
    }

    frontIdx = (frontIdx + 1) % capacity;
    data[frontIdx].~T();
}

// Push
template <typename T>
void CircularQueue<T>::push(const T &t)
{
    if (isFull())
    {
        T *temp = new T[capacity * 2];
        int startIdx = (frontIdx + 1) % capacity;

        // startIdx가 rearIdx 보다 앞에 있는 경우.
        if (startIdx < rearIdx)
        {                                              // 또는 start < 2
            std::copy(data + startIdx, data + capacity, temp); // start가 rearIdx보다 앞에 있으므로, start~capacity 범위를 그냥 복사하면 된다.
        }

        // startIdx 가 rearIdx보다 뒤에 있는 경우.
        else
        {
            std::copy(data + startIdx, data + capacity, temp);               // rearIdx보다 뒤에 start가 있으므로, start~capacity로 data 배열 뒷 부분을, temp 앞에 복사하고,
            std::copy(data, data + rearIdx + 1, temp + capacity - startIdx); // data 배열 앞 부분 ~ rear 을 위에서 복사한 다음 인덱스(temp + capacity - start)에 복사한다.
        }

        // update
        frontIdx = 2 * capacity - 1;
        rearIdx = capacity - 2;
        capacity *= 2;

        // memory update
        delete[] data;
        data = temp;
    }

    rearIdx = (rearIdx + 1) % capacity;
    data[rearIdx] = t;
}

// Front
template <typename T>
T CircularQueue<T>::front()
{
    if (isEmpty())
    {
        throw emptyError;
    }
    return data[(frontIdx + 1) % capacity];
}

// Rear
template <typename T>
T CircularQueue<T>::rear()
{
    if (isEmpty())
    {
        throw emptyError;
    }
    return data[rearIdx];
}

// isEmpty
template <typename T>
bool CircularQueue<T>::isEmpty()
{
    return frontIdx == rearIdx;
}

// isFull
template <typename T>
bool CircularQueue<T>::isFull()
{
    return (rearIdx + 1) % capacity == frontIdx;
}

// utility
template <typename T>
std::ostream &operator<<(std::ostream &os, const CircularQueue<T> &cq)
{
    int i = (cq.frontIdx + 1) % cq.capacity;
    int endIdx = (cq.rearIdx + 1) % cq.capacity;

    while (i != endIdx)
    {
        os << cq.data[i] << " ";
        i = (i + 1) % cq.capacity;
    }

    return os;
}