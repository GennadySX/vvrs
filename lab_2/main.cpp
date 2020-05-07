#include <iostream>
#include <omp.h>
#include <time.h>
using namespace std;


// Основной метод сортировки
void oddEvenSort(int arr[], int n) {
    bool isSorted = false; //Пока false так как массивы рандомные несортированы

    int ds = 0;

    while (!isSorted) {
        isSorted = true;

        // Сортировка Bubble sort on even 
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        // Сортировка Bubble sort on odd 
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        ds++;
    }
    //    cout << "loop : " << ds << endl;
    return;
}


int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

void mnogo(int arr[], int n) {
    cout << "===========================================******MnogoPotochny*******==================================================" << endl;
    double  start = omp_get_wtime();
#pragma omp parallel
    //Сюда только добавил распараллелирование для пропуска 
    oddEvenSort(arr, n);
    //printArray(arr, n);

    cout << " omp time: " << omp_get_wtime() - start << endl;
}



void odin(int arr[], int n) {
     cout << "===========================================******OdinPotochny*******==================================================" << endl;
    int  startx = omp_get_wtime();
    oddEvenSort(arr, n);
    //printArray(arr, n);
    cout << " odin time: " << omp_get_wtime() - startx << endl;
}


int main() {
    int v = 20000;
    srand(time(0));


    int* arr = new int[v];
    int* arr2 = new int[v];

    for (int i = 0; i < v; i++) {
        arr[i] = random(0, 99);
        arr2[i] = random(0, 99);
        //cin >> arr[i];
    }

    odin(arr, v);
    mnogo(arr2, v);

    return (0);
}