#include <vector>

template <typename T>
class Stack
{
private:
    std::vector<T> data;

public:
    Stack() {}
    void push(T val)
    {
        this->data.push_back(val);
    }
    T pop()
    {
        if (!this->empty())
        {
            T key = this->top();
            this->data.pop_back();
            return key;
        }
        else
        {
            throw "Stack is empty";
        }
    }
    T top()
    {
        if(!this->empty())
        {
            return this->data.back();   
        }
        else
        {
            throw "Stack is empty";
        }
    }
    bool empty()
    {
        return data.size() == 0;
    }
};

#include <iostream>
using namespace std;
int main()
{
    Stack<int> s;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; ++i)
    {
        s.push(arr[i]);
    }
    cout << s.empty() << endl;
    cout << s.top() << endl;
    for (int i = 0; i < 11; ++i)
    {
        try{
            cout << s.pop() << endl;
        }
        catch(const char* e)
        {
            cout << e << endl;
        }
    }
    getchar();
    return 0;
}