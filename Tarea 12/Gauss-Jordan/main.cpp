/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informacion y Ciencias de la Computacion
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Resolucion de sistemas lineales por el metodo de Gauss-Jordan
Autor: Juan Enrique Samayoa Reyes
Fecha: 18 de abril de 2025
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

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

// Metodo de Gauss-Jordan con pivoteo parcial
vector<double> gaussJordan(vector<vector<double>> A) {
    int n = A.size();
    for (int k = 0; k < n; ++k) {
        // Seleccion de pivote: fila con mayor valor absoluto en columna k
        int pivote = k;
        for (int i = k + 1; i < n; ++i) {
            if (fabs(A[i][k]) > fabs(A[pivote][k])) pivote = i;
        }
        // Intercambiar filas si es necesario
        if (pivote != k) {
            swap(A[k], A[pivote]);
            cout << "\nIntercambio fila " << k+1 << " con fila " << pivote+1 << ":\n";
            imprimirMatriz(A);
        }
        // Normalizar fila k para que pivote sea 1
        double div = A[k][k];
        for (int j = k; j <= n; ++j) A[k][j] /= div;
        cout << "\nNormalizando fila " << k+1 << " (dividiendo por " << div << "):\n";
        imprimirMatriz(A);
        // Eliminar en todas las filas i != k el elemento en columna k
        for (int i = 0; i < n; ++i) {
            if (i == k) continue;
            double factor = A[i][k];
            for (int j = k; j <= n; ++j) A[i][j] -= factor * A[k][j];
            cout << "\nEliminando elemento (fila " << i+1 << ", col " << k+1 << ") usando factor=" << factor << ":\n";
            imprimirMatriz(A);
        }
    }
    // Extraer solucion (ultima columna)
    vector<double> x(n);
    for (int i = 0; i < n; ++i) x[i] = A[i][n];
    return x;
}

int main() {
    int n;
    cout << "Ingrese numero de ecuaciones (3-6): "; cin >> n;
    if (n < 3 || n > 6) {
        cerr << "Error: numero de ecuaciones debe estar entre 3 y 6.\n";
        return 1;
    }
    // Leer matriz aumentada (n filas, n+1 columnas)
    vector<vector<double>> A(n, vector<double>(n+1));
    cout << "Ingrese la matriz aumentada (cada fila con " << n+1 << " valores):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Fila " << i+1 << ": ";
        for (int j = 0; j <= n; ++j) cin >> A[i][j];
    }
    // Mostrar matriz inicial
    cout << "\nMatriz inicial:\n";
    imprimirMatriz(A);
    // Ejecutar Gauss-Jordan
    vector<double> sol = gaussJordan(A);
    // Mostrar solucion
    cout << "\nSolucion del sistema:\n";
    for (int i = 0; i < n; ++i) cout << "x" << i+1 << " = " << sol[i] << "\n";
    return 0;
}
