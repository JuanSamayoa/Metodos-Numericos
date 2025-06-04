/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informacion y Ciencias de la Computacion
1er Semestre 2025
Curso: Metodos Numericos
Descripcion: Algoritmo de resolucion de sistemas lineales por el metodo de Gauss-Seidel
Autor: Juan Enrique Samayoa Reyes
Fecha: 25 de abril de 2025
*/

#include <iostream> // entrada/salida por consola (cin, cout, cerr)
#include <vector>		// contenedores dinamicos para matrices y vectores
#include <limits>		// numeric_limits para limpiar buffer y validar entradas
#include <cmath>		// funciones matematicas como fabs y sqrt
#include <iomanip>	// manipuladores de formato (setprecision, fixed)

using namespace std;

// Leer un entero con validacion de rango minimo
int leerEntero(const string &msg, int minV = 1)
{
	int v;
	while (true)
	{
		cout << msg;
		if (cin >> v && v >= minV)
			break;
		cerr << "Entrada invalida. Intente de nuevo.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return v;
}

// Leer un numero de punto flotante con validacion
// Utilizada para entradas de coeficientes y tolerancia
double leerDouble(const string &msg)
{
	double v;
	while (true)
	{
		cout << msg;
		if (cin >> v)
			break;
		cerr << "Entrada invalida. Intente de nuevo.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return v;
}

// Leer matriz cuadrada A de tamano n x n
vector<vector<double>> leerMatriz(int n)
{
	vector<vector<double>> A(n, vector<double>(n));
	for (int i = 0; i < n; ++i)
	{
		cout << "Fila " << i + 1 << " de A (" << n << " valores): ";
		for (int j = 0; j < n; ++j)
		{
			A[i][j] = leerDouble("");
		}
	}
	return A;
}

// Leer vector de tamano n con etiqueta 'name'
vector<double> leerVector(int n, const string &name)
{
	vector<double> v(n);
	for (int i = 0; i < n; ++i)
	{
		v[i] = leerDouble(name + "[" + to_string(i + 1) + "] = ");
	}
	return v;
}

// -------------------------------------------------------------
// Funcion: gaussSeidel
// Implementa el metodo iterativo de Gauss-Seidel para resolver Ax = b
// Parametros:
//  A   - matriz de coeficientes (n x n)
//  b   - vector de terminos independientes (n)
//  x   - vector con aproximacion inicial; al final contiene la solucion
//  tol - tolerancia para el criterio de convergencia
//  IT  - numero maximo de iteraciones permitidas
// Retorna true si converge antes de IT, false en caso contrario
// -------------------------------------------------------------
bool gaussSeidel(const vector<vector<double>> &A, const vector<double> &b, vector<double> &x, double tol, int IT)
{
	int n = A.size();
	// Iteraciones principales
	for (int k = 1; k <= IT; ++k)
	{
		double maxDiff = 0.0; // para medir cambio maximo en esta iteracion
		// Actualizar cada componente x[i]
		for (int i = 0; i < n; ++i)
		{
			double suma = b[i];
			// Restar contribuciones de las otras variables
			for (int j = 0; j < n; ++j)
			{
				if (j != i)
					suma -= A[i][j] * x[j];
			}
			double xi = suma / A[i][i];
			// Actualizar diferencia maxima
			maxDiff = max(maxDiff, fabs(xi - x[i]));
			x[i] = xi; // asignar nuevo valor
		}
		// Mostrar proceso de calculo: valores de x en esta iteracion
		cout << "Iteracion " << k << ": ";
		for (int j = 0; j < n; ++j)
		{
			cout << "x" << (j + 1) << "=" << x[j] << " ";
		}
		cout << '\n';
		// Criterio de convergencia: variacion menor a la tolerancia
		if (maxDiff < tol)
		{
			cout << "\nConvergio en " << k << " iteraciones.\n";
			return true;
		}
	}
// No convergio en IT iteraciones
	cout << "\nSe excedio el numero maximo de iteraciones.\n";
	return false;
}

int main()
{
	// Leer tamaño del sistema
	int n = leerEntero("Numero de ecuaciones/incognitas (n>=1): ", 1);

	// Lectura de datos: matriz A, vector b y aproximacion inicial x0
	auto A = leerMatriz(n);
	auto b = leerVector(n, "b");
	vector<double> x0 = leerVector(n, "x0 (aprox inicio)");

	// Parametros de control
	double tol = leerDouble("Tolerancia TOL: ");
	int IT = leerEntero("Maximo de iteraciones IT: ", 1);

	// Configurar formato de salida
	cout << fixed << setprecision(10);
	// Separador entre datos ingresados y procesamiento
	cout << "\n-----------------------------------------\n";

	// Ejecutar metodo y mostrar resultado
	bool ok = gaussSeidel(A, b, x0, tol, IT);
	cout << "\nSolucion aproximada:\n";
	for (int i = 0; i < n; ++i)
	{
		cout << "x" << i + 1 << " = " << x0[i] << "\n";
	}
	return 0;
}