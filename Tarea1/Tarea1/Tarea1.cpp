// Tarea1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <omp.h>

int arregloA[1000], arregloB[1000], arregloC[1000];

using namespace std;

void mostrar(int cantidad) {
    int i = 0;
    cout << "> Arreglo A: [";
    for (int i = 0; i < cantidad; i++) {
        cout << "[" << arregloA[i] << "]";
    }
    cout << "]";
    cout << endl;
    cout << "> Arreglo B:";
    for (int i = 0; i < cantidad; i++) {
        cout << "[" << arregloB[i] << "]";
    }
    cout << "]";
    cout << endl;
    cout << "> Arreglo C:";
    for (int i = 0; i < cantidad; i++) {
        cout << "[" << arregloC[i] << "]";
    }
    cout << "]";
    cout << endl;
}

void sumar(int cantidad) {
    // Creamos una variable para almacenar la suma realizada por cada hilo
    int suma_por_hilo[2] = { 0, 0 }; // Suponemos 2 hilos para este ejemplo

    // Hacemos el bucle paralelo usando OpenMP con 2 hilos
    #pragma omp parallel for num_threads(2)
    for (int i = 0; i < cantidad; i++) {
        int id_hilo = omp_get_thread_num(); // Obtener el ID del hilo
        arregloC[i] = arregloA[i] + arregloB[i];
        suma_por_hilo[id_hilo] += arregloC[i]; // Acumular la suma realizada por este hilo

        // Imprimir qué índice procesó el hilo
    #pragma omp critical
        cout << "Hilo " << id_hilo << " procesó índice " << i
            << " (Suma: " << arregloA[i] << " + " << arregloB[i]
            << " = " << arregloC[i] << ")" << endl;
    }
}

void aleatorio(int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        arregloA[i] = rand() % 101;
        arregloB[i] = rand() % 101;
        arregloC[i] = 0;
    }
}

int main()
{
    int cantidad;
    cout << "Ingrese el numero de registro que quiere ingresar:";
    cin >> cantidad;
    aleatorio(cantidad);
    sumar(cantidad);
    mostrar(cantidad);
}
