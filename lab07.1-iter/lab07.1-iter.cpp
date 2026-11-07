// Lab_7_1_Iter.cpp
// Капшук Ілля Віталійович
// Лабораторна робота № 7.1. 
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Ітераційний спосіб. Варіант 6.

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// Прототипи функцій
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High);
void Print(int** a, const int rowCount, const int colCount);
void Sort(int** a, const int rowCount, const int colCount);
void Change(int** a, const int row1, const int row2, const int colCount);
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k);

int main()
{
    srand((unsigned)time(NULL));

    const int Low = 16;
    const int High = 97;
    const int rowCount = 8;
    const int colCount = 6;

    // Динамічне виділення пам'яті під матрицю 8x6
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    // 1. Формування та виведення початкової матриці
    Create(a, rowCount, colCount, Low, High);
    cout << "Initial Matrix:" << endl;
    Print(a, rowCount, colCount);

    // 2. Впорядкування рядків за ключами: 0-й col (desc), 1-й col (asc), 3-й col (desc)
    Sort(a, rowCount, colCount);
    cout << "Sorted Matrix (Keys: 0-col desc, 1-col asc, 3-col desc):" << endl;
    Print(a, rowCount, colCount);

    // 3. Обчислення суми, кількості та заміна нулями за критерієм
    int S = 0;
    int k = 0;
    Calc(a, rowCount, colCount, S, k);

    cout << "S = " << S << endl;
    cout << "k = " << k << endl;

    cout << "Modified Matrix (satisfied elements replaced with 0):" << endl;
    Print(a, rowCount, colCount);

    // Звільнення динамічної пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

// Формування матриці випадковими числами з діапазону [Low, High]
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

// Форматне виведення матриці
void Print(int** a, const int rowCount, const int colCount)
{
    cout << endl;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
            cout << setw(5) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

// Сортування методів бульбашки згідно з ключами Варіанта 6 (desc, asc, desc)
void Sort(int** a, const int rowCount, const int colCount)
{
    for (int i0 = 0; i0 < rowCount - 1; i0++)
    {
        for (int i1 = 0; i1 < rowCount - i0 - 1; i1++)
        {
            if ((a[i1][0] < a[i1 + 1][0]) ||
                (a[i1][0] == a[i1 + 1][0] && a[i1][1] > a[i1 + 1][1]) ||
                (a[i1][0] == a[i1 + 1][0] && a[i1][1] == a[i1 + 1][1] && a[i1][3] < a[i1 + 1][3]))
            {
                Change(a, i1, i1 + 1, colCount);
            }
        }
    }
}

// Обмін двох рядків матриці місцями
void Change(int** a, const int row1, const int row2, const int colCount)
{
    int tmp;
    for (int j = 0; j < colCount; j++)
    {
        tmp = a[row1][j];
        a[row1][j] = a[row2][j];
        a[row2][j] = tmp;
    }
}

// Пошук суми та кількості елементів (кратні 7 АБО i%2!=0 АБО j%2!=0) та заміна їх нулями
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k)
{
    S = 0;
    k = 0;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            if (a[i][j] % 7 == 0 || i % 2 != 0 || j % 2 != 0)
            {
                S += a[i][j];
                k++;
                a[i][j] = 0;
            }
        }
    }
}
