// SumaParalela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>
#include <Windows.h>

#pragma comment(lib,"vcomp.lib")

using namespace std;

int sumar(int* a, int* b, int* res, int n) {
    int total_threads = 0;

#pragma omp parallel 
    {

#pragma omp master
        
        total_threads = omp_get_num_threads();
        int tid = omp_get_thread_num();
        int inicio = -1, fin = -1;

#pragma omp critical
        {
            cout << "El thread " << tid << "/" << total_threads << " esta en marcha. " << endl;
        }

#pragma omp for
        for (int i = 0; i < n; i++) {
            if (inicio == -1) inicio = i;
            res[i] = a[i] + b[i];
            fin = i;
        }

#pragma omp critical
        {
            cout << "El thread " << tid << " termin\xa2 su rango: [" << inicio << " - " << fin << "]" << endl;
        }

    }

    return total_threads;

}

void imprimeResultados(int* a, int* b, int* res, int n) {
    int limite = (n < 10) ? n : 10;

    cout << " Mostrando resultados (L\xa1mite : " << limite << "):" << endl;
    cout << "indice\tArrA\t+\ArrB\t=\tResultado" << endl;
    for (int i = 0; i < limite; i++) {
        cout << "[" << i << "]" << a[i] << " + " << b[i] << " = " << res[i] << endl;
    }

    if (n > 1000) cout << "... se omitieron los resulados del \xa1ndice 1000 al " << n -1 << ")" << endl;

}

int main()
{

    int n, num_threads;

    cout << "Suma en paralelo de 2 arreglos utilizando openMP" << endl;
    cout << "Ingrese el tama\xa4o de los areglos (n):";
    cin >> n;
    cout << "Ingrese el n\xa3mero de threads deseados:";
    cin >> num_threads;

    omp_set_num_threads(num_threads);

    int* A = new int[n];
    int* B = new int[n];
    int* R = new int[n];

    for (int i = 0; i < n; i++) {
        A[i] = rand() % n + 1;
        B[i] = rand() % n + 1;
    }

    double inicio = omp_get_wtime();
    int hilos_utilizados = sumar(A, B, R, n);
    double fin = omp_get_wtime();

    imprimeResultados(A, B, R, n);

    cout << "\n>>> Tiempo de ejecuci\xa2n: " << (fin - inicio) << " segundos." << endl;
    cout << "\n>>> N\xa3mero de threads utilizado: " << hilos_utilizados << endl;

    delete[] A; delete[] B; delete[] R;
    system("pause");
    return 0;
}


