#include <iostream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

void CreateMatrinx(int** &a, int NUM) {
    a = new int* [NUM];
    for (int i = 0; i < NUM; i++)
        a[i] = new int[NUM];

}

void FildMatrix(int** a, int NUM) {
    const int NUMRANGE = 10;
    for (int i = 0; i < NUM; i++)
        for (int j = 0; j < NUM; j++)
            a[i][j] = rand() * NUMRANGE / RAND_MAX + 1;
}

void PrintMatrix(int** a, int NUM) {
    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j < NUM; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
    printf("\n");
}

void DeleteMatrix(int** a, int NUM) {
    for (int i = 0; i < NUM; ++i)
        delete[] a[i];
    delete[] a;
}

void MulMatrix(int** a, int** b, int** c, int NUM) {
    for (int i = 0; i < NUM; i++)
        for (int j = 0; j < NUM; j++) {
            c[i][j] = 0;
            for (int k = 0; k < NUM; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
}

clock_t Test(int NUM) {
    int** a = nullptr;
    int** b = nullptr;
    int** c = nullptr;
    clock_t clocks;

    CreateMatrinx(a, NUM);
    FildMatrix(a, NUM);

    CreateMatrinx(b, NUM);
    FildMatrix(b, NUM);

    CreateMatrinx(c, NUM);
    clocks = clock();
    MulMatrix(a, b, c, NUM);
    clocks = clock() - clocks;
    printf("Dimension matrix: %d\nClock nambers: %d\nTime: %f\n", NUM, clocks, (double)clocks / CLOCKS_PER_SEC); 

    DeleteMatrix(a, NUM);
    DeleteMatrix(b, NUM);
    DeleteMatrix(c, NUM);

    return clocks;
}

int main()
{
    int i = 1;
    clock_t clk;
    ofstream resolt;
    resolt.open("resolt.txt");
    while (i < 1500) {
        clk = Test(i);
        resolt << i << " " << clk << " " << (double)clk / CLOCKS_PER_SEC << endl;
        if (i < 10)
            i += 1;
        else if (i < 500)
            i += 10;
        else
            i += 100;
    }
    resolt.close();
    return 0;
}