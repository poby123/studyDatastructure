#include <iostream>
#include "CircularQueue.h"

using namespace std;

int main()
{
    CircularQueue<int> cq;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(int);

    for (int i = 0; i < size; i++)
    {
        cq.push(arr[i]);
    }

    for (int i = 0; i < size; i++)
    {
        int temp = cq.front();
        cq.pop();
        cout << "(" << i << ") front : "<< temp << ", rear : " << cq.rear() << "\n";

        cq.push(temp);
    }

    cout << "Final result : " << cq << "\n";

    return 0;
}