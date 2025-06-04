/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informacion y Ciencias de la Computacion
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Algoritmo de resolucion de sistemas lineales por el metodo de Jacobi
Autor: Juan Enrique Samayoa Reyes
Fecha: 18 de abril de 2025
*/

#include <iostream>  // para entrada/salida por consola
#include <vector>    // para manejo de vectores (A, b, x0, x)
#include <cmath>     // para fabs
#include <iomanip>   // para setprecision
#include <limits>  // Permite usar numeric_limits<streamsize> para limpiar y descartar entradas invalidas
#include <sstream>  // para parsing de linea completa

using namespace std;

// Funcion para leer un valor numerico con prompt y validacion
void leerValor(const string &mensaje, double &valor) {
    while (true) {
        cout << mensaje;
        if (cin >> valor) break;
        cerr << "Entrada invalida. Intente de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Funcion para leer matriz A en una sola linea por fila
void leerMatriz(vector<vector<double>> &A, int n) {
    string linea;
    for (int i = 0; i < n; ++i) {
        while (true) {
            cout << "Ingrese coeficientes de la fila " << i+1 << " (separadas por espacios): ";
            getline(cin, linea);
            if (linea.empty()) getline(cin, linea);  // descartar newline previo
            istringstream iss(linea);
            bool ok = true;
            double valor;
            for (int j = 0; j < n; ++j) {
                if (!(iss >> valor)) { ok = false; break; }
                A[i][j] = valor;
            }
            if (ok) break;
            cerr << "Entrada invalida. Intente de nuevo.\n";
        }
    }
}

// Funcion para leer vector
void leerVector(vector<double> &v, int n, const string &nombre) {
    cout << "Ingrese valores de " << nombre << ":\n";
    for (int i = 0; i < n; ++i) {
        leerValor(nombre + "[" + to_string(i+1) + "] = ", v[i]);
    }
}

// Verificar que A tenga diagonal distinta de cero y dominio diagonal
bool verificarMatriz(const vector<vector<double>> &A, int n) {
    return true;  // Validacion de diagonal omitida: siempre se asume matriz correcta
}

// Funcion para leer un valor entero con prompt y validacion
void leerEntero(const string &mensaje, int &valor) {
    while (true) {
        cout << mensaje;
        if (cin >> valor) break;
        cerr << "Entrada invalida. Intente de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    int n;
    do {
        cout << "Numero de ecuaciones/incognitas [3-6]: ";
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
    } while (n < 3 || n > 6);

    vector<vector<double>> A(n, vector<double>(n));
    leerMatriz(A, n);
    if (!verificarMatriz(A, n)) return 1;

    vector<double> b(n), x0(n), x(n);
    leerVector(b, n, "b");
    leerVector(x0, n, "x0 (aproximacion inicial)");

    double tol;
    int N;
    leerValor("Tolerancia TOL: ", tol);
    leerEntero("Maximo de iteraciones N: ", N);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer antes de leer lineas

    int k = 1;
    // Mostrar encabezado de tabla
    vector<string> nombres = {"x", "y", "z", "u", "v", "w"};
    cout << "+---------";
    for (int i = 0; i < n; ++i) cout << "+------------";
    cout << "+------------+\n";
    cout << "| Iteracion";
    for (int i = 0; i < n; ++i) cout << " | " << setw(10) << nombres[i];
    cout << " |   Error   |\n";
    cout << "+---------";
    for (int i = 0; i < n; ++i) cout << "+------------";
    cout << "+------------+\n";
    // Iteraciones de Jacobi
    while (k <= N) {
        // Calculo de nuevas aproximaciones
        for (int i = 0; i < n; ++i) {
            double suma = b[i];
            for (int j = 0; j < n; ++j) {
                if (j != i) suma -= A[i][j] * x0[j];
            }
            x[i] = suma / A[i][i];
        }
        // Calcular error maximo |x - x0|
        double maxDiff = 0;
        for (int i = 0; i < n; ++i) {
            maxDiff = max(maxDiff, fabs(x[i] - x0[i]));
        }
        // Mostrar iteracion en formato tabla
        cout << "| " << setw(8) << k;
        for (int i = 0; i < n; ++i) cout << " | " << setw(10) << fixed << setprecision(6) << x[i];
        cout << " | " << setw(10) << fixed << setprecision(6) << maxDiff << " |\n";
        cout << "+---------";
        for (int i = 0; i < n; ++i) cout << "+------------";
        cout << "+------------+\n";
        // Verificar convergencia
        if (maxDiff < tol) {
            cout << "\nConvergio en " << k << " iteraciones.\n";
            break;
        }
        // Preparar siguiente iteracion
        x0 = x;
        k++;
    }
    if (k > N) {
        cout << "\nSupero el numero maximo de iteraciones (" << N << ").\n";
    }
    // Mostrar resultado final
    cout << "\nSolucion aproximada:\n";
    for (int i = 0; i < n; ++i) {
        cout << "x" << i+1 << " = " << fixed << setprecision(6) << x[i] << "\n";
    }
    return 0;
}
