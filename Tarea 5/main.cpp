/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informaci?n y Ciencias de la Computaci?n
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Algoritmo de metodo secante para encontrar el valor aproximado a cero
Autor: Juan Enrique Samayoa Reyes
Fecha: 9 de marzo de 2025
*/

#define _USE_MATH_DEFINES  // Habilita constantes matemáticas como M_PI
#include <iostream>        // Librería para entrada y salida de datos
#include <cmath>           // Librería matemática para funciones como pow() y sqrt()
#include <iomanip>         // Librería para formatear la salida numérica
using namespace std;

//Se calcula la funcion solicitada
double f(double x){
	//Se define el valor de pi desde las contantes
    double pi = M_PI;
    double e = M_E;
    //Funcion del ejercicio 1
    //return (log((x*x) + 1) - exp(0.4 * x) * cos(x * pi));
    
    //Funcion ejercicio 2
    //return (pow(2, x) - (6 * cos(x)));
    
    return log(-x) - pow(e, x);
}

//Se calcula el valor de P segun la formula dada
double vp(double p0, double p1, double q1, double q0){
    return (p1 - ((q1 *(p1 - p0))/(q1 - q0))); 
}

//Inicia el programa principal
int main(int argc, char** argv) {
    
    // Parámetros de entrada
    double fp, p, p0, p1, q0, q1, err, TOL = 0.0000000001; //0.0000000001;
    int IT = 100, i = 2;  // Agregado i=2 según el algoritmo
    
    //Mostramos el metodo y la funcion
    cout << "Metodo de la secante" << endl;
    cout << "f(x) = pow(2, x) - (6 * cos(x)) = 0" << endl << endl;
    
    // Solicitar el primer punto al usuario
    cout << "Ingrese el primer punto (p0): ";
    cin >> p0;
    
    //Solicitar el segundo punto al usuario
    cout << "Ingrese el segundo punto (p1): ";
    cin >> p1;
    //Se muestra la tolerancia en el programa
    cout << "Tolerancia: " << TOL << endl;
    //Se muestra el numero maximo de iteraciones
    cout << "Numero maximo de iteraciones: " << IT << endl << endl;
    
    // Línea separadora antes de la tabla
    cout << "==================================================================================================================" << endl;
    
    cout << "--- Ejecutando con p0 = " << p0 << " ---" << endl << endl;
    
    q0 = f(p0); //Se obtiene el valor de q0 ingresando el valor de p0 dentro de la funcion original
    q1 = f(p1); //Se obtiene el valor de q1 ingresando el valor de p1 dentro de la funcion original
    
    
    // Se imprime la cabecera de la tabla
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|   IT    |          p0         |          p1         |          q0         |          q1         |           p         |         f(p)        |        |p-p1|        |" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    
    do{
        // Calcular nueva aproximación
        p = vp(p0, p1, q1, q0); //se calcula P en base a los valores ya obtenidos
        fp = f(p);  // Cálculo de f(p)
        
        // Calcular error absoluto como |p-p1|
        err = abs(p - p1);
        
        // Imprimir fila de la tabla
        cout << "| " << right << setw(8) << i
             << "| " << setw(20) << fixed << setprecision(17) << p0 
             << "| " << setw(20) << p1 
             << "| " << setw(20) << q0 
             << "| " << setw(20) << q1 
             << "| " << setw(20) << p 
             << "| " << setw(20) << fp 
             << "| " << setw(20) << err << " |" << endl;
        
        //Calcular el error
        if(abs(p - p1) < TOL){
            // Línea separadora al final de la tabla
            cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "El metodo salio exitoso despues de " << i-1 << " iteraciones." << endl;
            cout << "Solucion aproximada: P_" << i << " = " << fixed << setprecision(12) << p << endl;
            cout << "Valor de la funcion: f(P)_" << i << " = " << fixed << setprecision(15) << fp << endl;
            return 0;
        }
        
        // Actualizar valores para la siguiente iteración
        p0 = p1;
        q0 = q1;
        p1 = p;
        q1 = fp;
        
        i++;  // Incrementar contador
        
    } while (i <= IT);  // Mientras la iteracion actual sea menor a la maxima seguira en el ciclo
    
    // Si llegamos aqui, el método falló mostrando el ultimo valor de P y f(p)
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "El metodo fallo despues de " << IT << " iteraciones." << endl;
    cout << "Ultima aproximacion: P_" << i-1 << " = " << fixed << setprecision(12) << p << endl;
    cout << "Valor de la funcion: f(P) = " << fixed << setprecision(15) << fp << endl;
    
    return 0;
}
