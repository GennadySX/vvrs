#include <iostream>
#include <omp.h>
using namespace std;

void odin( ) {
    int d = 1000;
    int average, first, counter = 0;
    double start_time = omp_get_wtime(), second = 0;

    for (int i = 0; i <= d; i++)
        first = first + i;

    cout << "size first numbers =" << d << endl;
    cout << "first filled number =" << first << endl;
    average = first / d;

    for (int i = average + 1; i <= d; i++) {
        second = second + i;
        counter++;
    }

    second = second / counter;

    cout << "first average  =" << average << endl;
    cout << "size second numbers =" << counter << endl;
    cout << "second average  = " << second << endl;
    cout << "Potok 1:" << omp_get_wtime() - start_time<< endl;
    cout << "=============================================================================================" << endl;

}


void mnogo() {
    int d = 1000;
    int average, first, counter = 0;
    double start_time = omp_get_wtime(), second = 0;

    for (int i = 0; i <= d; i++)
        first = first + i;

    cout << "size first numbers =" << d << endl;
    cout << "first filled number =" << first << endl;
    average = first / d;


    for (int i = average + 1; i <= d; i++) {
        second = second + i;
        counter++;


        second = second / counter;

    }

    cout << "first average  =" << average << endl;
    cout << "size second numbers =" << counter << endl;
    cout << "second average  = " << second << endl;
    cout << "Potok dynamic:" << omp_get_wtime() - start_time;

}


int main() {
    int n =10000;
    int n2 =10000;
    // cout << "Vvedite chislo :\t "<<endl;
    //cin >> n;



    odin();
    mnogo();


}