/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informacion y Ciencias de la Computacion
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Algoritmo de Regla Falsi
Autor: Juan Enrique Samayoa Reyes
Fecha: 30 de marzo de 2025
*/
#define _USE_MATH_DEFINES // Habilita constantes matematicas como M_PI
#include <iostream>       // Libreria para entrada y salida de datos
#include <cmath>          // Libreria matematica para funciones como pow() y sqrt()
#include <iomanip>        // Libreria para formatear la salida numerica
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
double f(double x)
{
    // Se define el valor de pi desde las constantes
    double pi = M_PI;
    double e = M_E;

    // Inciso A
    // return pow(x, 3) - (2 * pow(x, 2)) - 5;

    // Inciso B
    // return x - cos(x);

    // Inciso C
    // return pow(x, 3) - 3 * pow(x, 2) - 1;

    // Inciso D
    //return (5* pow(x, 3)) - (8* pow(x,2)) - (19*x)+16;
    return (-0.01 * pow(x, 3)) + (2.5 * x) + 4.5;
}

int main(int argc, char **argv)
{
    // ENTRADA: aproximaciones iniciales p0, p1; tolerancia TOL; numero maximo de iteraciones N0
    double p0, p1, p, TOL;
    int N0;

    // Mostramos el metodo y la funcion
    cout << "Metodo de Regla Falsi (Falsa Posicion)" << endl;
    // cout << "f(x) = x^3 - 2x^2 - 5 = 0" << endl<< endl;
    // cout << "f(x) = x - cos(x) = 0" << endl<< endl;
    // cout << "f(x) = x^3 - 3x^2 - 1 = 0" << endl<< endl;
    cout << "f(x) = x - 0.8 -0.2 * sin(x) = 0" << endl
         << endl;

    // Solicitar datos de entrada
    cout << "Ingrese el primer punto (p0): ";
    cin >> p0;
    cout << "Ingrese el segundo punto (p1): ";
    cin >> p1;
    cout << "Ingrese la tolerancia (TOL): ";
    cin >> TOL;
    cout << "Ingrese el numero maximo de iteraciones (N0): ";
    cin >> N0;
    cout << endl;

    // Se inicializa el contador en 2
    int i = 2;

    // Se calculan los valores de la funcion en los puntos iniciales
    double q0 = f(p0);
    double q1 = f(p1);

    // Configurar la precision para todos los numeros flotantes
    cout << fixed << setprecision(15);

    // Imprimir encabezados de la tabla
    cout << setw(20) << "Iteracion" << "|" << setw(25) << "p" << "|" << setw(25) << "f(p)" << "|" << setw(25) << "Error" << "|" << endl;
    cout << string(97, '-') << endl;

    // Entramos en el ciclo while
    while (i <= N0)
    {
        // Calculamos el nuevo punto p
        p = p1 - q1 * (p1 - p0) / (q1 - q0);
        double q = f(p);

        // Imprimimos la informacion de la iteracion actual
        cout << setw(20) << i << "|" << setw(25) << p << "|"
             << setw(25) << q << "|" << setw(25) << abs(p - p1) << "|" << endl;

        // Si el error es menor a la tolerancia, imprimimos la solucion y terminamos
        if (abs(p - p1) < TOL)
        {
            cout << string(97, '-') << endl;
            cout << "Procedimiento exitoso." << endl;
            cout << "Solucion aproximada p = " << p << endl;
            cout << "f(p) = " << q << endl;
            cout << "Numero de iteraciones: " << i << endl;
            return 0;
        }

        // Incrementamos el contador y calculamos el nuevo valor de la funcion
        i++;
        q = f(p);

        // Si el producto de q y q1 es negativo, actualizamos p0 y q0
        if (q * q1 < 0)
        {
            p0 = p1;
            q0 = q1;
        }

        // Actualizamos p1 y q1
        p1 = p;
        q1 = q;
    }

    // Imprimimos el mensaje de que el metodo fallo
    cout << string(97, '-') << endl;
    cout << "El metodo fallo despues de " << N0 << " iteraciones." << endl;
    cout << "Procedimiento no exitoso." << endl;
    cout << "Ultima solucion aproximada p = " << p << endl;
    cout << "Ultimo valor de f(p) = " << f(p) << endl;
    return 1;
}
