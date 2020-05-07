//lab1
#include <iostream>
#include <omp.h>
using namespace std;


void odin() {
   long long d = 100000000;

   long long first = 0;
   long long second = 0;
   long long counter = 0;

   long long
       average = 0;

        double start_time = omp_get_wtime();
    cout << "===========================================******Odin*******==================================================" << endl;
    for (long long i = 0; i <= d; i++)
        first = first + i;

    cout << "Obshy kolichestva chisel =" << d << endl;
    cout << "summa obshy kolichestva chisel  =" << first << endl;
    average = first / d;
    cout << "pervy sredny arifmetichesky  =" << first / d << endl;

    for (long long c = average + 1; c <= d; c++) {
        second = second + c;
        counter++;
    }

    cout << "summa obshy kolichestva chisel 2 =" << second << endl;

    second = second / counter;

    cout << "Obshy kolichestva chisel 2 =" << counter << endl;
    cout << "Vtoroy sredny arifmetichesky = " << second << endl;
    cout << "Odno potochny time:" << omp_get_wtime() - start_time << endl;

}


void mnogo() {
    long long d = 100000000;
    long long  sum = 0;
    long long counter = 0;

    long long average = 0;
    double  start_time = omp_get_wtime();

    cout << "===========================================******Mnogo*******==================================================" << endl;

#pragma omp parallel for reduction(+:sum) private(counter) 
    for (long long i = 0; i <= d; i++) sum = sum + i;

    cout << "Obshy kolichestva chisel =" << d << endl;
    cout << "summa obshy kolichestva chisel  =" << sum << endl;
    average = sum / d;
    cout << "pervy sredny arifmetichesky  =" << average << endl;

    sum = 0;
#pragma omp for 
    for (long long x = average + 1; x <= d; x++) {
        sum = sum + x;
        counter++;
    }

    cout << "summa obshy kolichestva chisel 2 =" << sum << endl;
    sum = sum / counter;
 
    cout << "Obshy kolichestva chisel 2 =" << counter << endl;
    cout << "Vtoroy sredny arifmetichesky = " << sum << endl;
    cout << "Mnogo potochny time:" << omp_get_wtime() - start_time << endl;

}



int main() {

    odin();
    mnogo();

}