
#include <stdio.h>
#include <iostream> 
#include <stdlib.h>  
#include <time.h>
#include <cmath>
#include <omp.h>  
#include <windows.h>
#include <string> 
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	int n;
	int N;
	int* a;
	bool fail = false;

	do {
		fail = false;
		cout << "Введите размер массива = ";
		cin >> N;
		if (cin.fail() || N <= 0) {
			cout << "Вы ввели не верное число, ввелите число больше нуля" << endl;
			fail = true;
		}
		cin.clear();
		cin.ignore();
	} while (fail);

	do {
		fail = false;
		cout << "Введите кол-во потоков = ";
		cin >> n;
		if (cin.fail() || n <= 0) {
			cout << "Вы ввели не верное число, ввелите число больше нуля" << endl;
			fail = true;
		}
		cin.clear();
		cin.ignore();
	} while (fail);
	a = new int[N];

	for (int i = 0; i < N; i++) {
		a[i] = 100 + rand() % 10000000;
	}

	double time = omp_get_wtime();
	omp_set_dynamic(false);
	omp_set_num_threads(n);

	long unsigned int sum1 = 0;
	long unsigned int sum = 0;

#pragma omp parallel firstprivate(sum) shared(sum1) 
	{
		sum = 0;

#pragma omp for
		for (int i = 0; i < N; i++)
		{
		
				sum += sqrt(a[i]);
			
		}
#pragma omp critical
		{
			sum1 += sum;
		}
	}
	cout << "Значение выражения с потоками = " << sum1 << "\n";
	time = omp_get_wtime() - time;
	cout << "Время вычислений = " << time << "\n";


	time = omp_get_wtime();

	sum1 = 0;

#pragma omp parallel for reduction (+: sum1)  

	for (int i = 0; i < N; i++)
	{
		
			sum1 += sqrt(a[i]);
		
	}

	time = omp_get_wtime() - time;

	cout << "Значение выражения с потоками через редукцию = " << sum1 << "\n";
	cout << "Время вычислений = " << time << "\n";


	time = omp_get_wtime();

	sum1 = 0;

	for (int i = 0; i < N; i++)
	{
		
		
		sum1 += sqrt(a[i]);
		
	}

	time = omp_get_wtime() - time;
	cout << "Значение выражения без потоков = " << sum1 << "\n";
	cout << "Время вычислений = " << time << "\n";


	system("pause");
	return 0;
}



