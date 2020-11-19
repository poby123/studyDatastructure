template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node(T val)
    {
        this->data = val;
        this->next = nullptr;
    }
};

template <typename T>
class SinglyLinkedList
{
private:
    Node<T> *head;
    int length;

public:
    SinglyLinkedList()
    {
        this->head = nullptr;
        this->length = 0;
    }
    ~SinglyLinkedList()
    {
        Node<T> *it = this->head;
        while (it != nullptr)
        {
            Node<T> *next = it->next;
            delete it;
            it = next;
        }
    }
    void pushFront(T val)
    {
        ++this->length;
        if (this->head == nullptr)
        {
            this->head = new Node<T>(val);
        }
        else
        {
            Node<T> *n = new Node<T>(val);
            n->next = this->head;
            this->head = n;
        }
    }
    void pushBack(T val)
    {
        ++this->length;
        if (this->head == nullptr)
        {
            head = new Node<T>(val);
        }
        else
        {
            Node<T> *it = this->head;
            while (it->next != nullptr)
            {
                it = it->next;
            }
            it->next = new Node<T>(val);
        }
    }
    T popFront()
    {
        if (this->head != nullptr)
        {
            Node<T> *target = this->head;
            this->head = this->head->next;
            --this->length;
            T key = target->data;
            delete target;
            return key;
        }
        else
        {
            throw "head is nullptr";
        }
    }
    T popBack()
    {
        if (this->head == nullptr) //남은 노드가 0개인 경우.
        {
            throw "head is nullptr";
        }
        else
        {
            Node<T> *it = this->head;
            Node<T> *prev = nullptr;
            while (it->next != nullptr)
            {
                prev = it;
                it = it->next;
            }
            --this->length;
            T key = it->data;
            delete it;
            if (prev != nullptr) //남은 노드가 2개 이상인 경우
            {
                prev->next = nullptr;
            }
            else //남은 노드가 1개인 경우
            {
                this->head = nullptr;
            }
            return key;
        }
    }
    int getLength()
    {
        return this->length;
    }
};

#include <iostream>
using namespace std;

int main()
{

    SinglyLinkedList<int> sl;
    int arr[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i)
    {
        sl.pushFront(arr[i]);
        sl.pushBack(arr[i]);
    }
    while (sl.getLength() > 0)
    {
        try
        {
            cout << sl.popFront() << " ";
            cout << sl.popBack() << " ";
        }
        catch (const char *e)
        {
            cout << e << endl;
        }
    }
    return 0;
}