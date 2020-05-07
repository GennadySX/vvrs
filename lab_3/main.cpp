#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include<conio.h>
#include <stdlib.h>
using namespace std;

#define DIM 10000

void init(void);
void delete_(int);

struct prims {
    int(*edge)[DIM] = new int[DIM][DIM];

    int dim; int U[DIM];
    int total_minDist;
    int counts;
};

struct prims prim;
struct prims prim2;


void odin(int rebro) {
    cout << "===========================================******OdinPotochny*******==================================================" << endl;

    int j, k, i;
    prim.dim = rebro;
    //переменная, которая содержит текущее максимальное расстояние

    int minDist;
    int newElem;
    //переменная, которая содержит следующий узел

    prim.total_minDist = 0;
    prim.counts = 0;


    srand(time(NULL));

    for (i = 0; i < prim.dim; ++i) {
        for (j = 0; j < prim.dim; j++) {
            //std::cin >> (prim.edge[i][j]);
            prim.edge[i][j] = rand() % (0, 100) + 0;
        }
    }

    cout << "Random konets" << endl;
    //инициализация данных
    init();
    double start_time = omp_get_wtime();

    //Рассчитиваем для всех узлов
    for (k = 0; k < prim.dim - 1; k++)
    {
        minDist = 1000;
        //для каждого узла в минимальном охватывающем дереве
        for (i = 0; i < prim.counts; i++)

            for (j = 0; j < prim.dim; j++) {
                //найдем минимальную ширину
                if (prim.edge[prim.U[i]][j] > minDist || prim.edge[prim.U[i]][j] == 0) {
                    continue;
                }
                else {
                    minDist = prim.edge[prim.U[i]][j];
                    newElem = j;
                }
            }

        //Складываем локальный minDist на total_minDist
        prim.total_minDist += minDist;
        //Присвоем слд элемент узла в U 
        prim.U[i] = newElem;
        //Субструктура элементов столбца, в которой новый узло
        delete_(newElem);
        //Увеличиваем узлов, которые они находятся в счетчике
        prim.counts++;
    }


    cout << "time: " << omp_get_wtime() - start_time << "\n\n";
}


void mnogo(int rebro) {
    prim2.dim = rebro;
    prim2.total_minDist = 0;
    prim2.counts = 0;


    cout << "===========================================******MnogoPotochny*******==================================================" << endl;

    int j, k, i, minDist, newElem;
    double start_time;

    for (i = 0; i < prim2.dim; ++i) 
        for (j = 0; j < prim2.dim; j++) {
            //std::cin >> (prim.edge[i][j]);
            prim2.edge[i][j] = rand() % (0, 100) + 0;
        }

    cout << "Random konets" << endl;

    init();

     start_time = omp_get_wtime();

    for (k = 0; k < prim2.dim - 1; k++)

    {
        minDist = 1000;
        for (i = 0; i < prim.counts; i++)

#pragma omp parallel num_threads(4)
#pragma omp for 
            for (j = 0; j < prim2.dim; j++) {
                if (prim2.edge[prim2.U[i]][j] > minDist || prim2.edge[prim2.U[i]][j] == 0) {
                    continue;
                }
                else {
                    minDist = prim2.edge[prim2.U[i]][j];
                    newElem = j;
                }
            }

        prim2.total_minDist += minDist;
        prim2.U[i] = newElem;
        delete_(newElem);
        prim2.counts++;
    }
    cout << "time: " << omp_get_wtime() - start_time << "\n\n";
}



int main() {
    //Установливаем временные рандомизация для уникальные число
    srand(time(NULL));

    int rebro; 
    cout << "Vvedite chislo rebra: ";
    cin >> rebro;

    cout << endl;

    mnogo(rebro);
    odin(rebro);

    return 0;
}

void init(void) {

    int i, j;

    prim.total_minDist = 0;
    prim.counts = 0;

    //инициализация U установите
    for (i = 0; i < prim.dim; i++) prim.U[i] = -1;

    //хранение первого узла в наборе U
    prim.U[0] = 0;
    //удаление первого узла
    delete_(prim.U[0]);
    //увеличение на единицу числа узлов, находящихся внутри набора U
    prim.counts++;
}

void delete_(int next_element)
{
    int k;
    for (k = 0; k < prim.dim; k++) prim.edge[k][next_element] = 0;
}




