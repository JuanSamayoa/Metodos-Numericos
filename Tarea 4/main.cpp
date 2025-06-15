#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// Funcion: f(x) = sen(x^3) - 3x^2 + 20x - 3
long double f(long double x) {
    return sinl(powl(x, 3)) - 3 * powl(x, 2) + 20 * x - 3;
}

// Derivada: f'(x) = 3x^2 * cos(x^3) - 6x + 20
long double f_prime(long double x) {
    return 3 * powl(x, 2) * cosl(powl(x, 3)) - 6 * x + 20;
}

int main() {
    long double p0, TOL, p;
    int IT;    cout << fixed << setprecision(17);
    cerr << fixed << setprecision(17);    // Encabezado modificado para coincidir con la imagen
    cout << "Metodo de Newton-Raphson\n"
         << "f(x) = sen(x^3) - 3x^2 + 20x - 3\n\n";

    cout << "Ingrese la aproximacion inicial p0: ";
    cin >> p0;
    cout << "Ingrese la tolerancia TOL: ";
    cin >> TOL;
    cout << "Ingrese el numero maximo de iteraciones IT: ";
    cin >> IT;

    // Ajuste de anchos de columna
 	cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|  IT |          p0            |          f(p0)         |            p           |          f(p)          |          |p-p1|        |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;

    int i = 1;
    while (i <= IT) {
        long double fp0 = f(p0);
        long double derivada = f_prime(p0);

        if (fabsl(derivada) < numeric_limits<long double>::epsilon()) {
            cerr << "\nError: Derivada cercana a cero.\n";
            return 1;
        }

        p = p0 - fp0 / derivada;        long double error = fabsl(p - p0);

        // Ajuste de formato numerico
        cout << "| " << setw(3) << i << " | " 
             << setw(22) << p0 << " | " 
             << setw(22) << fp0 << " | "
             << setw(22) << p << " | " 
             << setw(22) << f(p) << " | " 
             << setw(22) << error << " |\n";        if (error < TOL) {
        	
			cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "\nMetodo exitoso despues de " << i << " iteraciones.\n"
                 << "Solucion aproximada: p_" << i << " = " << p << "\n"
                 << "Valor de la funcion: f(p) = " << f(p) << "\n"
                 << "f(p0)= " << setprecision(30) << fp0 << endl
                 << "f(p)= " << setprecision(30) << f(p) << endl
				 << "Error= " << setprecision(30) << error;
            return 0;
        }

        p0 = p;
        i++;    }

    cout << "\nEl metodo fracaso despues de " << IT << " iteraciones.\n";
    cout << "Solucion aproximada: p_" << i << " = " << p << "\n"
        	<< "Valor de la funcion: f(p) = " << f(p) << "\n";
    return 0;
}
