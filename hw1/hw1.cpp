#include <iostream>

using namespace std;

int main()
{
    int capacity = 5, *data = new int[capacity], *tmp = new int[2 * capacity];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    for (int i = 0; i < capacity; i++)
    {
        // cout << data[i] << endl;
        tmp[i] = data[i];
    }
    delete data;
    data = tmp;

    // delete tmp;
    capacity = 2 * capacity;
    delete data;
    // delete data;
    // for (int i = 0; i < capacity / 2; i++)
    // cout << data[i] << endl;
}