/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informacion y Ciencias de la Computacion
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Algoritmo de resolución de sistemas lineales por el metodo de Gauss
Autor: Juan Enrique Samayoa Reyes
Fecha: 18 de abril de 2025
*/

#include <iostream>  // para operaciones de entrada/salida por consola
#include <vector>    // para usar contenedores vectoriales (matrices)
#include <cmath>     // para funciones matematicas (fabs, pow, etc.)
#include <iomanip>   // para manipuladores de formato (setprecision, setw)

using namespace std;

// Programa para resolver sistemas lineales (3-6 ecuaciones) usando el metodo de Gauss
// Muestra paso a paso la transformacion de la matriz aumentada

// Funcion para imprimir la matriz aumentada con formato
void imprimirMatriz(const vector<vector<double>>& M) {
    int filas = M.size(), cols = M[0].size();
    cout << fixed << setprecision(4);
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(10) << M[i][j] << " ";
        }
        cout << "\n";
    }
}

// Eliminacion Gaussiana con pivoteo parcial
vector<double> gaussEliminacion(vector<vector<double>> A) {
    int n = A.size();
    // Paso 1: Eliminacion hacia adelante (de convertir en triangular superior)
    for (int k = 0; k < n; ++k) {
        // Seleccionar fila pivote: buscar el mayor valor absoluto en la columna k
        int pivote = k;
        for (int i = k + 1; i < n; ++i)
            if (fabs(A[i][k]) > fabs(A[pivote][k]))
                pivote = i;
        // Si el pivote no esta en la fila k, intercambiar filas
        if (pivote != k) {
            // Swap para mejorar estabilidad numerica
            swap(A[k], A[pivote]);
            cout << "\nIntercambio fila " << k+1 << " con fila " << pivote+1 << ":\n";
            imprimirMatriz(A);
        }
        // Anulacion: eliminar elementos debajo del pivote en la columna k
        for (int i = k + 1; i < n; ++i) {
            double factor = A[i][k] / A[k][k];  // factor para hacer cero A[i][k]
            for (int j = k; j <= n; ++j)
                A[i][j] -= factor * A[k][j];
            cout << "\nEliminando (fila " << i+1 << ", col " << k+1 << ") factor=" << factor << ":\n";
            imprimirMatriz(A);
        }
    }
    // Paso 2: Sustitucion regresiva
    vector<double> x(n);
    for (int i = n-1; i >= 0; --i) {
        double suma = A[i][n];
        for (int j = i+1; j < n; ++j) suma -= A[i][j] * x[j];
        x[i] = suma / A[i][i];
    }
    return x;
}

int main() {
    int n;
    cout << "Ingrese numero de ecuaciones (3-6): "; cin >> n;
    if (n < 3 || n > 6) {
        cerr << "Error: numero de ecuaciones debe estar entre 3 y 6.\n";
        return 1;
    }
    vector<vector<double>> A(n, vector<double>(n+1));
    cout << "Ingrese matriz aumentada (fila con "<<n+1<<" valores):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Fila "<<i+1<<": ";
        for (int j = 0; j <= n; ++j) cin >> A[i][j];
    }
    cout << "\nMatriz inicial:\n"; imprimirMatriz(A);
    vector<double> sol = gaussEliminacion(A);
    cout << "\nSolucion del sistema:\n";
    for (int i = 0; i < n; ++i) cout << "x"<<i+1<<" = "<<sol[i]<<"\n";
    return 0;
}