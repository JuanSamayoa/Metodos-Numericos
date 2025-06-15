# Proyecto de Metodos Numericos

Este repositorio contiene implementaciones en C++ de los principales metodos numericos para resolver ecuaciones no lineales, sistemas de ecuaciones lineales y interpolacion polinomial, desarrollados para el curso de Metodos Numericos de la Universidad Mariano Galvez.

## Metodos implementados

### 1. Metodos para encontrar raices de ecuaciones no lineales
- **Biseccion (Tarea 2)**: Metodo de intervalo que divide sucesivamente el intervalo por la mitad hasta encontrar la raiz. Garantiza convergencia si la funcion es continua y cambia de signo en el intervalo.

- **Punto Fijo (Tarea 3)**: Transforma f(x) = 0 a x = g(x) e itera x_{k+1} = g(x_k) hasta convergencia. Requiere que |g'(x)| < 1 en el intervalo de convergencia.

- **Newton-Raphson (Tarea 4)**: Utiliza la derivada para aproximar la raiz mediante la formula x_{k+1} = x_k - f(x_k)/f'(x_k). Convergencia cuadratica pero requiere calcular la derivada.

- **Metodo Secante (Tarea 5)**: Aproxima la derivada usando dos puntos anteriores, evitando el calculo directo de f'(x). Formula: x_{k+1} = x_k - f(x_k)(x_k - x_{k-1})/(f(x_k) - f(x_{k-1})).

- **Regla Falsi (Tarea 7)**: Combina biseccion con interpolacion lineal. Mantiene el intervalo donde la funcion cambia de signo pero usa interpolacion para aproximar mejor la raiz.

- **Metodo de Muller (Tarea 6)**: Generaliza el metodo secante usando tres puntos para ajustar una parabola y encontrar sus raices. Puede encontrar raices complejas.

### 2. Metodos de interpolacion polinomial
- **Interpolacion de Lagrange (Tarea 8)**: Construye el polinomio interpolante usando la base de Lagrange. Formula: P(x) = Σ y_i * L_i(x) donde L_i(x) son los polinomios de Lagrange.

- **Diferencias Divididas (Tarea 9)**: Construye el polinomio de Newton usando diferencias divididas. Permite agregar puntos facilmente y reutilizar calculos previos.

- **Metodo de Neville (Tarea 10)**: Algoritmo recursivo para evaluar el polinomio interpolante en un punto especifico sin construir explicitamente el polinomio completo.

### 3. Metodos para sistemas de ecuaciones lineales
- **Eliminacion de Gauss (Tarea 12)**: Metodo directo que transforma el sistema a forma triangular superior mediante operaciones elementales, luego aplica sustitucion hacia atras.

- **Gauss-Jordan (Tarea 12)**: Extension del metodo de Gauss que reduce la matriz a forma escalonada reducida (identidad), obteniendo directamente la solucion.

- **Metodo de Jacobi (Tarea 12)**: Metodo iterativo que despeja cada variable y actualiza simultaneamente usando los valores de la iteracion anterior. Requiere diagonal dominante para convergencia.

- **Metodo de Gauss-Seidel (Tarea 13)**: Mejora del metodo de Jacobi que usa inmediatamente los valores actualizados en la misma iteracion, generalmente convergiendo mas rapido.

## Estructura del repositorio
- `Tarea 2` a `Tarea 13`: Cada carpeta contiene el codigo fuente (main.cpp), ejecutables, archivos .dev para abrir en Dev-C++ y documentacion del metodo correspondiente.
- `README.md`: Este archivo con descripciones detalladas de cada algoritmo.

## Caracteristicas de implementacion
- **Precision numerica**: La mayoria usa precision doble (double) o extendida (long double) para mayor exactitud.
- **Validacion de entrada**: Funciones robustas para leer datos numericos con manejo de errores.
- **Formato de salida**: Tablas organizadas que muestran el progreso iterativo de cada metodo.
- **Criterios de parada**: Tolerancia configurable y limite maximo de iteraciones.
- **Documentacion**: Comentarios explicativos en el codigo fuente.

## Creditos
- Autor principal: Juan Enrique Samayoa Reyes
- Universidad Mariano Galvez de Guatemala
- Curso: Metodos Numericos, 2025

---

**Nota:** Todos los programas han sido refactorizados para eliminar caracteres especiales, mejorar la legibilidad del codigo, validacion de entrada, formato de resultados y documentacion, siguiendo principios de codigo limpio y buenas practicas de programacion.