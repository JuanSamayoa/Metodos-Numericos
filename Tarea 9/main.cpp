/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informacion y Ciencias de la Computacion
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Algoritmo de Metodo de Diferencias Divididas
Autor: Juan Enrique Samayoa Reyes
Fecha: 13 de abril de 2025
*/

#include <iostream> // Para entrada y salida estandar
#include <vector>   // Para el uso de vectores dinamicos
#include <iomanip>  // Para formatear la salida de datos en tablas
#include <cmath>    // Para funciones matematicas
#include <sstream>  // Para formatear números menores a 0.0001 o mayores a 10000.0

using namespace std;

// Función auxiliar para formatear números
string formatearNumero(double valor, int precision = 5) {
    stringstream ss;
    
    // Si el valor es muy pequeño o muy grande, usar notación científica
    if (abs(valor) < 0.0001 || abs(valor) > 10000.0) {
        ss << scientific << setprecision(precision) << valor;
    } else {
        ss << fixed << setprecision(precision) << valor;
    }
    return ss.str();
}

int main() {
    // Entrada de datos
    int n;
    cout << "Ingrese la cantidad de datos (n): ";
    cin >> n;

    vector<double> x(n), fx(n); // Vectores para almacenar los puntos (xi, f(xi))
    cout << "Ingrese los valores de x y f(x):\n";
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "]: ";
        cin >> x[i];
        cout << "f(x)[" << i << "]: ";
        cin >> fx[i];
    }

    double xint;
    cout << "\nIngrese el valor a interpolar (xint): ";
    cin >> xint;

    // Crear la matriz para las diferencias divididas
    vector<vector<double>> T(n, vector<double>(n, 0.0));
    
    // Inicializar la primera columna con los valores de f(x)
    for (int i = 0; i < n; i++) {
        T[i][0] = fx[i];
    }

    // Calcular las diferencias divididas para las columnas restantes
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            T[i][j] = (T[i + 1][j - 1] - T[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
    
    // Mostrar la tabla de diferencias divididas con diagonal de arriba hacia abajo
    cout << "\n+------------------------------------------------------+" << endl;
    cout << "|           TABLA DE DIFERENCIAS DIVIDIDAS             |" << endl;
    cout << "+----------+";
    
    for (int j = 0; j < n; j++) {
        cout << "---------------+";
    }
    cout << endl;
    
    cout << "|    x     |";
    for (int j = 0; j < n; j++) {
        if (j == 0) {
            cout << "     f(x)     |";
        } else {
            cout << "   f[" << j << "](x)    |";
        }
    }
    cout << endl;
    
    cout << "+----------+";
    for (int j = 0; j < n; j++) {
        cout << "---------------+";
    }
    cout << endl;
    
    // Mostrar los datos con diagonal de arriba hacia abajo
    for (int i = 0; i < n; i++) {
        cout << "| " << setw(8) << formatearNumero(x[i], 4) << " |";
        
        // Primera columna (valores de f(x))
        cout << " " << setw(13) << formatearNumero(T[i][0], 5) << " |";
        
        // Columnas de diferencias divididas (estructura diagonal hacia abajo)
        for (int j = 1; j <= i; j++) {
            cout << " " << setw(13) << formatearNumero(T[i-j][j], 5) << " |";
        }
        
        // Completar la fila con espacios vacíos
        for (int j = i+1; j < n; j++) {
            cout << "               |";
        }
        cout << endl;
    }
    
    cout << "+----------+";
    for (int j = 0; j < n; j++) {
        cout << "---------------+";
    }
    cout << endl;
    
    // Calcular el valor interpolado
    double fxint = T[0][0]; // Primer termino del polinomio (f(x0))
    for (int i = 1; i < n; i++) {
        double p = 1.0; // Producto acumulado de (xint - x0)(xint - x1)...
        for (int j = 0; j < i; j++) {
            p *= (xint - x[j]);
        }
        fxint += T[0][i] * p; // Sumar el termino correspondiente
    }
    
    // Mostrar el resultado final simplificado
    cout << "\n+------------------------------------------------------+" << endl;
    cout << "|                RESULTADO FINAL                       |" << endl;
    cout << "+------------------------------------------------------+" << endl;
    cout << "| Valor de x = " << setw(8) << fixed << setprecision(4) << xint 
         << "                                |" << endl;
    cout << "| Valor interpolado f(" << setw(4) << fixed << setprecision(2) << xint << ") = " 
         << setw(11) << formatearNumero(fxint, 5) << "              |" << endl;
    cout << "+------------------------------------------------------+" << endl;

    return 0;
}
