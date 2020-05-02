#include "stdio.h"
#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <random>
#include <omp.h>
using namespace std;

#define m 7
#define k m*3


void Prim1()
{

	int path[10000] = { 0 }; //В этот массив будут записываться вершины, по которым составиться путь
	int path_index = 1;
	int u, v, n, i, j, current = 0;
	int visited[m], min = 999, mincost = 0;
	int cost[m][m];

	for (int i = 0; i < m; i++)
	{
		visited[i] = 0;
		for (int j = 0; j < m; j++)
		{
			cost[i][j] = 0;
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i == j)
			{
				cost[i][j] = 0;
				continue;
			}


			if (cost[i][j] == 0)
			{
				random_device rd; // only used once to initialise (seed) engine
				mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
				uniform_int_distribution<int> uni(0, 15); // guaranteed unbiased
				cost[i][j] = uni(rng);
				cost[j][i] = cost[i][j];
				if (cost[i][j] == 0)
				{
					cost[i][j] = 999;
					cost[j][i] = 999;
				}

			}
		}
	}



	n = m;

	double start_time = omp_get_wtime();

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (cost[i][j] == 0)
				cost[i][j] = 999;
		}
	visited[0] = 1;
	cout << "\n";

	while (current < n)
	{
		int i = current;
		for (j = 0; j < n; j++)
		{

			if (cost[i][j] < min)
			{
				if (visited[j] == 0)
				{
					min = cost[i][j];
					u = i;
					v = j;
				}
			}
		}

		if (visited[u] == 0 || visited[v] == 0)
		{
			path[path_index] = v;
			path_index++;
			current = v;
			mincost += min;
			visited[v] = 1;
		}
		else
			current = 999;

		min = 999;
		cost[u][v] = cost[v][u] = 999;
	}

	cout << endl << "Алгоритм Прима один поток:" << omp_get_wtime() - start_time;

	//cout << "\n";

	//cout << " —> ";
	//for (int i = 0;i < n;i++)
	//{
	// cout << path[i];
	// if (i < n - 1) cout << " —> ";
	//}

	//cout << "\n Минимальная стоимость " << mincost;

}

void Prim2()
{

	int path[10000] = { 0 }; //В этот массив будут записываться вершины, по которым составиться путь
	int path_index = 1;
	int u, v, n, i, j, current = 0;
	int visited[m], min = 999, mincost = 0;
	int cost[m][m];

	for (int i = 0; i < m; i++)
	{
		visited[i] = 0;
		for (int j = 0; j < m; j++)
		{
			cost[i][j] = 0;
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i == j)
			{
				cost[i][j] = 0;
				continue;
			}


			if (cost[i][j] == 0)
			{
				random_device rd; // only used once to initialise (seed) engine
				mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
				uniform_int_distribution<int> uni(0, 15); // guaranteed unbiased
				cost[i][j] = uni(rng);
				cost[j][i] = cost[i][j];
				if (cost[i][j] == 0)
				{
					cost[i][j] = 999;
					cost[j][i] = 999;
				}

			}
		}
	}



	n = m;

	double start_time = omp_get_wtime();






	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (cost[i][j] == 0)
				cost[i][j] = 999;
		}
	visited[0] = 1;
	cout << "\n";

	while (current < n)
	{
		int i = current;
		int gmin = 99999;
#pragma omp parallel num_threads(2)
		{
#pragma omp for
			for (j = 0; j < n; j++)
			{

				if (cost[i][j] < min)
				{
					if (visited[j] == 0)
					{
						min = cost[i][j];
						u = i;
						v = j;
					}
				}
			}

#pragma omp critical
			{
				if (min < gmin)
					gmin = min;
			}
		}

		min = gmin;
		if (visited[u] == 0 || visited[v] == 0)
		{
			path[path_index] = v;
			path_index++;
			current = v;
			mincost += min;
			visited[v] = 1;
		}
		else
			current = 999;

		min = 999;
		cost[u][v] = cost[v][u] = 999;
	}

	cout << endl << "Алгоритм Прима многопоток:" << omp_get_wtime() - start_time;

	/*cout << "\n";

	cout << " —> ";
	for (int i = 0;i < n;i++)
	{
	cout << path[i];
	if (i < n - 1) cout << " —> ";
	}

	cout << "\n Минимальная стоимость " << mincost;*/

}

#define V 200

void dijkstra(int graph[V][V], int src)
{
	double start_time = omp_get_wtime();

	int dist[V];
	bool sptSet[V];

	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++)
	{
		int min = INT_MAX, min_index;

		for (int v = 0; v < V; v++)
		{

			if (sptSet[v] == false && dist[v] <= min)
				min = dist[v], min_index = v;
		}

		int u = min_index;

		sptSet[u] = true;

		for (int v = 0; v < V; v++)
		{
			if (!sptSet[v] && graph[u][v] && dist[u]
				!= INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
		}

	}

	cout << endl << "Алгоритм дейкстры один поток:" << omp_get_wtime() - start_time;

	//printf(" \n Минмальная дистанция со всех точке до графа 1 \n");
	//for (int i = 0; i < V; i++)
	// printf("C %d до 0 = %d\n", i, dist[i]);
}

void dijkstraM(int graph[V][V], int src)
{
	double start_time = omp_get_wtime();

	int dist[V];
	bool sptSet[V];

	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++)
	{
		int min = INT_MAX, min_index;
		int gmin = 99999;
		int gindex;
#pragma omp parallel num_threads(2)
		{
#pragma omp for
			for (int v = 0; v < V; v++)
			{

				if (sptSet[v] == false && dist[v] <= min)
					min = dist[v], min_index = v;
			}

#pragma omp critical
			{
				if (min < gmin)
				{
					gmin = min;
					gindex = min_index;
				}

			}
		}

		int u = gindex;

		sptSet[u] = true;

		for (int v = 0; v < V; v++)
		{
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
		}

	}

	cout << endl << "Алгоритм дейкстры много поток:" << omp_get_wtime() - start_time;

	//printf(" \n Минмальная дистанция со всех точке до графа 1 \n");
	//for (int i = 0; i < V; i++)
	// printf("C %d до 0 = %d\n", i, dist[i]);
}


int main() {
	setlocale(LC_ALL, "Russian");

	Prim1();
	Prim2();

	return 0;
}