/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informacion y Ciencias de la Computacion
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Algoritmo de Interpolacion de Neville
Autor: Juan Enrique Samayoa Reyes
Fecha: 13 de abril de 2025
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <sstream>

using namespace std;

// Devuelve una representacion en cadena de un double en notacion cientifica y con la precision indicada
string formatearNumero(double valor, int precision = 15) {
    ostringstream ss;
    if (abs(valor) < 0.0001 || abs(valor) > 10000.0) {
        ss << scientific << setprecision(precision) << valor;
    } else {
        ss << fixed << setprecision(precision) << valor;
    }
    return ss.str();
}

// Calcula el ancho necesario para una celda en notacion cientifica segun la precision
int calcularAnchoCelda(int precision) {
    // Ejemplo: -1.234567890123456e+308 (signo, digito, punto, decimales, e, signo, 3 digitos de exponente)
    // 1 (signo) + 1 (digito) + 1 (punto) + precision + 2 (e+) + 3 (expo) = precision + 8
    // Se suma extra para margen visual
    return precision + 12;
}

int main(int argc, char** argv) {
    int n;
    cout << "Metodo de Interpolacion de Neville" << endl;
    cout << "Ingrese la cantidad de puntos de referencia (n): ";
    cin >> n;

    vector<double> x(n), y(n);
    // Solicita al usuario los puntos de referencia para la interpolacion
    for (int i = 0; i < n; ++i) {
        cout << "x[" << i << "]: ";
        cin >> x[i];
        cout << "y[" << i << "]: ";
        cin >> y[i];
    }

    int m;
    cout << "Ingrese la cantidad de valores a interpolar: ";
    cin >> m;
    vector<double> xint(m);
    for (int i = 0; i < m; ++i) {
        cout << "xint[" << i << "]: ";
        cin >> xint[i];
    }

    const int precision = 15;
    const int anchoCelda = calcularAnchoCelda(precision);

    // Procesa cada valor a interpolar usando el metodo de Neville
    for (int k = 0; k < m; ++k) {
        // Matriz Q para el metodo de Neville
        vector<vector<double>> Q(n, vector<double>(n, 0.0));
        // Inicializa la primera columna con los valores de y
        for (int i = 0; i < n; ++i) {
            Q[i][0] = y[i];
        }
        // Algoritmo de Neville para calcular la interpolacion
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= i; ++j) {
                double num = (xint[k] - x[i - j]) * Q[i][j - 1] - (xint[k] - x[i]) * Q[i - 1][j - 1];
                double den = x[i] - x[i - j];
                Q[i][j] = num / den;
            }
        }
        // Imprime la matriz Q como tabla ASCII alineada
        cout << "\n+";
        for (int j = 0; j < n; ++j) cout << string(anchoCelda, '-') << "+";
        cout << "\n|";
        for (int j = 0; j < n; ++j) {
            string header = "    Q[" + to_string(j) + "]";
            cout << setw(anchoCelda) << left << header << "|";
        }
        cout << "\n+";
        for (int j = 0; j < n; ++j) cout << string(anchoCelda, '-') << "+";
        cout << endl;
        for (int i = 0; i < n; ++i) {
            cout << "|";
            for (int j = 0; j <= i; ++j) {
                cout << setw(anchoCelda) << scientific << setprecision(precision) << Q[i][j] << "|";
            }
            for (int j = i + 1; j < n; ++j) {
                cout << setw(anchoCelda) << " " << "|";
            }
            cout << endl;
        }
        cout << "+";
        for (int j = 0; j < n; ++j) cout << string(anchoCelda, '-') << "+";
        cout << endl;
        // Imprime el resultado para xint[k]
        cout << "\nInterpolacion en el punto x = " << fixed << setprecision(precision) << xint[k] << ": ";
        cout << scientific << setprecision(precision) << Q[n - 1][n - 1] << endl;
    }
    return 0;
}
