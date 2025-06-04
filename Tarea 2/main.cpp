/*
Universidad Mariano Galvez de Guatemala
Centro Universitario el Naranjo
Ingenieria en Sistemas de Informaci�n y Ciencias de la Computaci�n
1er Semestre 2025
Curso: M�todos Num�ricos
Descripci�n:
Autor: Juan Enrique Samayoa Reyes
Fecha: 15 de febrero de 2025
*/

#define _USE_MATH_DEFINES //Parte de CMATH para incluir constantes

#include <iostream> //Librer�a para poder obtener entradas/salidas dentro del sistema
#include <cmath> //Librer�a para incluir potencias, raices, valor absoluto, entre otras funciones matem�ticas
#include <iomanip> //Librer�a para poder incluir decimales de precisi�n, en este caso son 15 decimales

using namespace std;

double func(double x) {
	//Constante de euler
    double e = M_E;
    
    //Inciso a
	//return (pow(x, -x) - x);
    
    //Inciso B, problema 1
	//return (x - pow(2, -x));
	
	//Inciso B, problema 2
	//return (pow(e, x) - pow(x, 2) + (3 * x) - 2);
	
	//Inciso B, problema 3
	//return ((2 * x) * cos(x) - pow((x + 1), 2));
	
	//Inciso B, problema 4
	//return (x * cos(x) - pow((2 * x), 2) + (3 * x) - 1);
	
	//return pow(e, x) - pow(x, 2) + 3*x - 2;
	//return cos(x) - pow(x, 3);
	return pow(e, -pow(x, 2)) - x +1.37;
}

int main() {
	/*Definicion de variables; a -> Punto A del intervalo; b -> Punto B del intervalo;
	p -> Punto intermedio entre A y B;
	fa -> Valor de la funci�n en el punto A;
	fp -> Valor de la funci�n en el punto P;
	TOL -> Valor de la tolerancia m�xima para el calculo de |(b - a) / 2)|;
	i -> Valor de las iteraciones, en numero entero;
	IT -> N�mero m�ximo de iteraciones que debe realizar el sistema.
	*/
    double a, b, p, fa, fp, TOL = 0.000000000000001 /*0.0000000001*/;
    int i = 0, IT = 100;

	//Se imprime la funcion inicial, esto se cambia manualmente.
	cout << "f(x) = 2x * cos(x) - pow((x + 1), 2) = 0 \n\n";

	//Se solicitan los intervalos de la funcion desde el punto A al punto B.
    cout << "Ingrese el intervalo A: ";
    cin >> a;
    cout << "Ingrese el intervalo B: ";
    cin >> b;

	//Se hace validaci�n de los intervalos para no crear una contradiccion o mal calculo del punto en X.
	if (b < a || a > b){
		cout << "El punto A debe ser menor al punto B.";
		return 0;
	}
	
	//Se muestra en la pantalla la tolerancia m�nima del numero en la funci�n y el m�ximo de iteraciones a realizar.
	cout << "La tolerancia es de: " << TOL;
	cout << "\nMaximo de iteraciones: " << IT;
	
    fa = func(a); //Se asigna el valor de A en la funci�n a la variable fa.

	//Se crea la cabecera de la tabla.
    cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
    cout << "| Iteracion |         pA         |         pB        |         pP          |           fp       |        error       |\n";
    cout << "----------------------------------------------------------------------------------------------------------------------\n";

	//Empieza el ciclo do
    do {
    	//Se calcula el punto P a partir de la bisecci�n entre el punto A y el punto B
        p = (a + b) / 2;
        
        //Se calcula en base a la funci�n f(x) sobre el punto P.
        fp = func(p);
        
        //Se calcula el error con el valor absoluto de "(b - a) / 2".
        double err = abs((b - a) / 2);

		//Se imprime en la tabla los valores de i, punto A, punto B, punto P, f(p), y el error cometido
		//Se fija un width por variable de 9 para las iteraciones y 18 para los valores, asi se muestra correctamente
        cout << "| " << setw(9) << i + 1
            << " | " << setw(18) << fixed << setprecision(15) << a //Se determina una precisi�n de 15 d�gitos a todos los n�meros siguientes
            << " | " << setw(18) << b
            << " | " << setw(18) << p
            << " | " << setw(18) << fp
            << " | " << setw(18) << err << " |\n";


		/*
		Si el error cometido es menor al valor absoluto de (b-a)/2, se termina el ciclo,
		� si el punto P es exactamente cero (0).
		*/
        if (p == 0 || abs((b - a) / 2) < TOL) {
        	//Muestra en pantalla que fue un �xito en la ejecuci�n y termina la ejecuci�n del programa
            cout << "-------------------------------------------------------------------------------------------------------------------\n";
            cout << "El metodo salio exitoso despues de " << i + 1 << " iteraciones.\n";
            cout << "con P_" << i + 1 << " = " << setw(15) << p << " y\n";
            cout << "f(p)_" << i + 1 << " = " << setw(15) << fp ;
            return 0;
        }

        i++; //Se incrementa el valor de la iteraci�n si a�n no ha cumplido con la tolerancia requerida.


		/* Se calcula si el resultado de f(a) * f(p) es un numero positivo o negativo,
		Si es positivo, el punto P se vuelve el punto A, y f(p) se vuelve f(a)
		siendo la bisecci�n del lado derecho a utilizar.
		Si el n�mero es negativo, se utiliza la bisecci�n del lado izquierdo y el punto P se vuelve punto B.
		*/
        if ((fa * fp) > 0) {
            a = p;
            fa = fp;
        } else {
            b = p;
        }

    } while (i < IT); //Mientras que el numero de iteraci�n sera menor al m�ximo, seguir� realizando la tarea

	//Si el n�mero de iteraciones supera el m�ximo sin haber conseguido la tolerancia, saldr� del ciclo y el m�todo fallar�
    cout << "---------------------------------------------------------------------------------------------------------------------\n";
    cout << "El metodo fracaso despu�s de " << i << " iteraciones.\n";
    cout << "con P_i =  " << setw(15) << p << " y\n";
    cout << "f(p)_i =" << setw(15) << fp << "\n";
	
	//Finalizar� el sistema despu�s de haber fracasado
    return 0;
}
