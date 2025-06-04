#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// Función corregida: f(x) = 2x - 6cos(x)
long double f(long double x) {
    //return powl(2,x) - 6 * cosl(x);
    return cosl(x)- powl(x, 3);
}

// Derivada corregida: f'(x) = 2 + 6sin(x)
long double f_prime(long double x) {
    //return logl(2) * powl(2, x) + 6 * sinl(x);
    
    return -sinl(x) -3 * powl(x, 2);
}

int main() {
    long double p0, TOL, p;
    int IT;

    cout << fixed << setprecision(17);
    cerr << fixed << setprecision(17);

    // Encabezado modificado para coincidir con la imagen
    cout << "Método de Newton-Raphson\n"
         << "f(x) = 2*x - 6cos(x)\n\n";

    cout << "Ingrese la aproximación inicial p0: ";
    cin >> p0;
    cout << "Ingrese la tolerancia TOL: ";
    cin >> TOL;
    cout << "Ingrese el número máximo de iteraciones IT: ";
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

        p = p0 - fp0 / derivada;
        long double error = fabsl(p - p0);

        // Ajuste de formato numérico
        cout << "| " << setw(3) << i << " | " 
             << setw(22) << p0 << " | " 
             << setw(22) << fp0 << " | "
             << setw(22) << p << " | " 
             << setw(22) << f(p) << " | " 
             << setw(22) << error << " |\n";

        if (error < TOL) {
        	
			cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "\nMétodo exitoso después de " << i << " iteraciones.\n"
                 << "Solución aproximada: p_" << i << " = " << p << "\n"
                 << "Valor de la función: f(p) = " << f(p) << "\n"
                 << "f(p0)= " << setprecision(20) << fp0 << endl
                 << "f(p)= " << setprecision(20) << f(p) << endl
				 << "Error= " << setprecision(20) << error;
            return 0;
        }

        p0 = p;
        i++;
    }

    cout << "\nEl método fracasó después de " << IT << " iteraciones.\n";
    cout << "Solución aproximada: p_" << i << " = " << p << "\n"
        	<< "Valor de la función: f(p) = " << f(p) << "\n";
    return 0;
}
