#include <iostream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

void Swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void QuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

void PrintArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("n");
}

clock_t Test(int NUM) {
    clock_t clocks;
    const int NUMRANGE = 1000;
    int* arr = new int[NUM];
    for (int i = 0; i < NUM; i++)
        arr[i] = rand() * NUMRANGE / RAND_MAX + 1;

    clocks = clock();
    QuickSort(arr, 0, NUM - 1);    
    clocks = clock() - clocks;
    printf("Array size: %d   Time: %f\n", NUM, (double)clocks / CLOCKS_PER_SEC);

    
    delete[] arr;

    return clocks;
}

int main()
{
    int i = 0;
    clock_t clk;
    ofstream resolt;
    resolt.open("resolt.txt");
    while (i < 5000000) {
        clk = Test(i);
        resolt << i << " " << clk << " " << (double)clk / CLOCKS_PER_SEC << endl;
        if (i < 10000)
            i += 1000;
        else if (i < 100000)
            i += 10000;
        else if (i < 1000000)
            i += 100000;
        else
            i += 1000000;
    }
    resolt.close();
    return 0;
}