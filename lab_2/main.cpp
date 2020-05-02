#include <iostream>
#include <omp.h>
#include <time.h>
using namespace std;


// A function to sort the algorithm using Odd Even sort
void oddEvenSort(int arr[], int n) {
    bool isSorted = false; // Initially array is unsorted

    int ds = 0;

    while (!isSorted) {
        isSorted = true;

        // Perform Bubble sort on even indexed element
        for (int i = 0; i < n - 1; i +=  2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        // Perform Bubble sort on odd indexed element
        for (int i = 1; i < n - 1; i +=  2) {
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


int random(int from, int to){
    return rand() % (to - from + 1) + from;
}

// A utility function ot print an array of size n
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

void mnogo(int arr[], int n ) {

    double  start = omp_get_wtime();
#pragma omp parallel
    oddEvenSort(arr, n);
    //printArray(arr, n);

    cout << " mn time: "<< omp_get_wtime() - start << endl;
}



void odin(int arr[], int n ) {

    double  startx = omp_get_wtime();
    oddEvenSort(arr, n);
    //printArray(arr, n);
    cout << " odin time: " << omp_get_wtime() - startx  << endl;
}


// Driver program to test above functions.
int main() {
    int v = 10000;
    srand(time(0));

    //cout << "Vvedite kolichestvo massiva: ";
    //cin >> v;
    cout << endl;
    int arr[v];
    int arr2[v];
    cout << "Kolichestvo massiva: " << v << endl;
    for(int i =0; i < v; i++) {
         arr[i] = random(0, 1000);
         arr2[i] = random(0, 1000);
        //cin >> arr[i] ;
        //cin >> arr2[i] ;
    }

    int n = sizeof(arr) / sizeof(arr[0]);

    //printArray(arr, n);
    cout << endl;
    odin(arr, n);
    mnogo(arr2, n);

    return (0);
}