/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informacion y Ciencias de la Computacion
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Algoritmo de Interpolacion de Lagrange
Autor: Juan Enrique Samayoa Reyes
Fecha: 6 de abril de 2025
*/

#include <iostream>       // Libreria para entrada y salida de datos
#include <iomanip>        // Libreria para formatear la salida numerica
#include <vector>         // Libreria para manejar vectores
using namespace std;

int main(int argc, char **argv)
{
	// Se inicializan las variables de entrada
	int n; // Cantidad de puntos
	double z; // Punto a evaluar 

	// Mostramos el metodo
	cout << "Metodo de Interpolacion de Lagrange" << endl << endl;

	// Solicitar datos de entrada
	cout << "Ingrese la cantidad de puntos (n): ";
	cin >> n;

	// Se crean los vectores para almacenar los puntos
	vector<double> x(n);  // Vector para valores x
	vector<double> y(n);  // Vector para valores y (f(x))

	// Solicitar los puntos (xi, yi)
	cout << "\nIngrese los puntos (x,y):" << endl;
	for(int i = 0; i < n; i++) {
		cout << "x[" << i << "]: ";
		cin >> x[i];
		cout << "y[" << i << "]: ";
		cin >> y[i];
	}

	// Solicitar el punto de evaluacion
	cout << "\nIngrese el punto a evaluar (z): ";
	cin >> z;

	// Configurar la precision para todos los numeros flotantes
	cout << fixed << setprecision(15);

	// Mostrar tabla de datos ingresados
	cout << "\nPuntos ingresados:" << endl;
	cout << setw(20) << "xi" << "|" << setw(20) << "yi" << "|" << endl;
	cout << string(42, '-') << endl;
	for(int i = 0; i < n; i++) {
		cout << setw(20) << x[i] << "|" << setw(20) << y[i] << "|" << endl;
	}
	cout << string(42, '-') << endl;

	// Inicializar acumulador para el polinomio de Lagrange
	double valor = 0;

	// Calcular el polinomio de Lagrange
	for(int i = 0; i < n; i++) {
			// Inicializar el termino Li(x)
		double v = y[i];
		
		// Calcular el producto para Li(x)
		for(int j = 0; j < n; j++) {
			// Si i es diferente a j
			if(i != j) {
				// Multiplicar por (x - xj)/(xi - xj)
				v = v * (z - x[j]) / (x[i] - x[j]);
			}
		}
		// Sumar el termino al resultado
		valor += v;
	}

	// Mostrar resultados
	cout << "\nResultados:" << endl;
	cout << "Punto de evaluacion z = " << z << endl;
	cout << "Valor interpolado P(" << z << ") = " << valor << endl;

	return 0;
}

/*
CONCLUSION:
La implementacion del metodo de Lagrange nos permitio comprender como realizar interpolacion
polinomial utilizando los polinomios base de Lagrange. Est0e metodo es especialmente util
cuando necesitamos encontrar un valor aproximado de una funcion conociendo solo algunos de
sus puntos, sin necesidad de conocer la funcion explicita. La implementacion demuestra como
cada termino del polinomio se construye como un producto de factores que se anulan en todos
los puntos excepto en uno, lo que garantiza que el polinomio pase exactamente por todos los
puntos dados.
*/
