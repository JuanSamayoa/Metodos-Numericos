/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informaci?n y Ciencias de la Computaci?n
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Algoritmo de punto fijo para encontrar el valor deseado
Autor: Juan Enrique Samayoa Reyes
Fecha: 23 de febrero de 2025
*/

#define _USE_MATH_DEFINES  // Habilita constantes matemáticas como M_PI
#include <iostream>        // Librería para entrada y salida de datos
#include <cmath>           // Librería matemática para funciones como pow() y sqrt()
#include <iomanip>        // Librería para formatear la salida numérica

using namespace std;

// Función g(x) utilizada en el método de punto fijo
double g(double x) {
	/*Problema 1*/
	//return pow(3 * x * x + 3, 0.25);; // g(x) = raíz cuarta de (3x² + 3)
	
	/*Problema 2*/
    // Se calcula el valor de g(x) = sqrt((7 - (1/3)x^5) / 5)
    //double valor = (7 - (1.0 / 3.0) * pow(x, 5)) / 5;
    
    // Validación para evitar la raíz de un número negativo (lo que generaría NaN)
    /*if (valor < 0) {
        return NAN; // Devuelve NaN si el valor dentro de sqrt() es negativo
    }
    return sqrt(valor); // Devuelve la raíz cuadrada si el valor es válido*/
    
    return (pow(3+ 3*x*x*x, 0.25));
}

// Función f(x) para verificar la convergencia de la raíz
double f(double x) {
	/*Problema 1*/
	//return pow(x, 4) - 3 * pow(x, 2) - 3;
	
	/*Problema 2*/	
    //return (1.0 / 3.0) * pow(x, 5) + 5 * pow(x, 2) - 7; // Retorna el valor de la función f(x)
    
    return ((pow(x, 4))- (3 * pow(x, 3)) - 3);
}

// Método de Punto Fijo para encontrar una raíz aproximada
void metodoPuntoFijo(double p0, double TOL, int IT) {
    double p; // Variable para almacenar la nueva aproximación de la raíz
    int i = 1; // Contador de iteraciones

    // Encabezado de la tabla de iteraciones
    cout << "\n-----------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "| Iteracion |          p0           |          p            |        g(p0)         |        f(p0)         |  Error absoluto  |  Error relativo  |\n";
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------\n";

    do {
        p = g(p0); // Calcula g(p0)
        
        // Si p es NaN, significa que g(p0) intentó calcular sqrt() de un número negativo
        if (isnan(p)) {
            cout << "-------------------------------------------------------------------------------------------------------------------------------------------------\n";
            cout << "El metodo fracaso: g(p0) intento calcular la raiz de un numero negativo.\n";
            cout << "Ultima aproximacion: P_i = " << fixed << setprecision(15) << p0 << "\n";
            return; // Termina la ejecución del método
        }

        double f_p0 = f(p0); // Evalúa f(p0)
        double err_abs = abs((p - p0) / p); // Calcula el error absoluto
        double err_rel = abs(p - p0); // Calcula el error relativo

        // Imprime la iteración en la tabla
        cout << "| " << setw(9) << i
             << " | " << setw(21) << fixed << setprecision(15) << p0
             << " | " << setw(21) << fixed << setprecision(15) << p
             << " | " << setw(21) << fixed << setprecision(15) << g(p0)
             << " | " << setw(21) << fixed << setprecision(15) << f_p0
             << " | " << setw(16) << fixed << setprecision(15) << err_abs
             << " | " << setw(16) << fixed << setprecision(15) << err_rel
             << " |\n";

        // Verifica si la tolerancia se cumple y detiene el método
        if (err_rel < TOL) {
            cout << "-------------------------------------------------------------------------------------------------------------------------------------------------\n";
            cout << "El metodo salio exitoso despues de " << i << " iteraciones.\n";
            cout << "Solucion aproximada: P_" << i << " = " << fixed << setprecision(15) << p << "\n";
            cout << "g(p0) = " << g(p0);
            
            return;
        }

        p0 = p; // Actualiza p0 con el nuevo valor
        i++; // Incrementa la iteración
    } while (i < IT);

    // Si se alcanza el número máximo de iteraciones sin convergencia
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "El metodo fracaso despues de " << i << " iteraciones.\n";
    cout << "Ultima aproximacion: P_i = " << fixed << setprecision(15) << p0 << "\n";
}

// Función principal
int main() {
    double tolerancias[] = {1e-10}; // Arreglo con los valores de tolerancia a evaluar
    double valores_p0[] = {2.55}; // Valores iniciales p0 para probar
    int IT = 100; // Número máximo de iteraciones permitidas
    
    // Mensajes iniciales de presentación del problema
    cout << "Metodo de punto fijo\n";
    cout << "f(x) = pow(x, 4) - 3 * pow(x, 2) - 3\n";
    cout << "g(x) = raíz cuarta de (3x² + 3)\n";

    // Itera sobre las tolerancias
    for (double TOL : tolerancias) {
        cout << "\n==================================================================================================";
        cout << "\nEjecutando con tolerancia: " << TOL << "\n";
        cout << "==================================================================================================\n";

        // Itera sobre los valores iniciales p0
        for (double p0 : valores_p0) {
            cout << "\n\n### Ejecutando con p0 = " << p0 << " ###\n";
            metodoPuntoFijo(p0, TOL, IT); // Llama al método de punto fijo
        }
    }
    return 0; // Finaliza la ejecución del programa
}
