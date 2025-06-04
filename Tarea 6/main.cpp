/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informacion y Ciencias de la Computacion
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Algoritmo de Muller
Autor: Juan Enrique Samayoa Reyes
Fecha: 23 de marzo de 2025
*/
#define _USE_MATH_DEFINES // Habilita constantes matematicas como M_PI
#include <iostream>       // Libreria para entrada y salida de datos
#include <cmath>          // Libreria matematica para funciones como pow() y sqrt()
#include <iomanip>        // Libreria para formatear la salida numerica
using namespace std;

// Funcion f(x) que queremos encontrar sus raices
double f(double x)
{
    return ((9/11)* pow(x,3)) - ((11/2)* x) +2;
}

int main(int argc, char **argv)
{
    // ENTRADA: aproximaciones iniciales p0, p1, p2; tolerancia TOL; numero maximo de iteraciones N0
    double p0, p1, p2, TOL;
    int N0;

    // Mostramos el metodo y la funcion
    cout << "Metodo de Muller" << endl;
    cout << "f(x) = x^4 + x^3 + 3x^2 + 2x + 2 = 0" << endl
         << endl;

    // Solicitar datos de entrada
    cout << "Ingrese el primer punto (p0): ";
    cin >> p0;
    cout << "Ingrese el segundo punto (p1): ";
    cin >> p1;
    cout << "Ingrese el tercer punto (p2): ";
    cin >> p2;
    cout << "Ingrese la tolerancia (TOL): ";
    cin >> TOL;
    cout << "Ingrese el numero maximo de iteraciones (N0): ";
    cin >> N0;
    cout << endl;

    // Configurar la precision para todos los numeros flotantes
    cout << fixed << setprecision(16);

    // Imprimir encabezados de la tabla
    cout << setw(10) << "i" << "|"
         << setw(25) << "h1" << "|"
         << setw(25) << "h2" << "|"
         << setw(25) << "d" << "|"
         << setw(25) << "p" << "|"
         << setw(25) << "f(p)" << "|"
         << setw(25) << "|p-p2|" << "|" << endl;
    cout << string(160, '-') << endl;

    // Step 1: Set i = 3
    int i = 3;

    do
    {
        // Step 1: Calcular h1, h2, s1, s2, d
        double h1 = p1 - p0;
        double h2 = p2 - p1;
        double s1 = (f(p1) - f(p0)) / h1;
        double s2 = (f(p2) - f(p1)) / h2;
        double d = (s2 - s1) / (h2 + h1);

        // Step 3: Calcular b y D
        double b = s2 + h2 * d;
        double D = sqrt(pow(b, 2) - 4 * f(p2) * d);

        // Step 4: Determinar E
        double E;
        if (abs(b - D) < abs(b + D))
        {
            E = b + D;
        }
        else
        {
            E = b - D;
        }

        // Step 5: Calcular h y p
        double h = -2 * f(p2) / E;
        double p = p2 + h;

        // Imprimir información de la iteración actual
        cout << setw(10) << i << "|"
             << setw(25) << h1 << "|"
             << setw(25) << h2 << "|"
             << setw(25) << d << "|"
             << setw(25) << p << "|"
             << setw(25) << f(p) << "|"
             << setw(25) << abs(h) << "|" << endl;

        // Step 6: Verificar convergencia
        if (abs(h) < TOL)
        {
            cout << string(160, '-') << endl;
            cout << "Procedimiento exitoso." << endl;
            cout << "Solucion aproximada p = " << p << endl;
            cout << "f(p) = " << f(p) << endl;
            cout << "Numero de iteraciones: " << i - 2 << endl;
            return 0;
        }

        // Step 7: Preparar para siguiente iteracion
        p0 = p1;
        p1 = p2;
        p2 = p;
        i++;

    } while (i <= N0);

    // Step 8: El método falló
    cout << string(160, '-') << endl;
    cout << "El metodo fallo despues de " << N0 << " iteraciones." << endl;
    cout << "Ultima solucion aproximada p = " << p2 << endl;
    cout << "f(p) = " << f(p2) << endl;
    return 1;
}

/*
CONCLUSION:
La implementacion del metodo de Muller nos permitio comprender como encontrar raices de ecuaciones
no lineales utilizando interpolacion cuadratica. A diferencia de otros metodos, este utiliza tres
puntos iniciales para generar una mejor aproximacion. Se observo que el metodo puede converger
rapidamente cuando los puntos iniciales estan cerca de la raiz y la funcion es bien comportada
en esa region.
*/
