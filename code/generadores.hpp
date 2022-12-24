#include <math.h>
#include <iostream>
//Genera un número uniformemente distribuido en el
//intervalo [0,1) a partir de uno de los generadores
//disponibles en C. Lo utiliza el generador de demanda
double uniforme()
{
    int t = random();
    double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}

//Construye la tabla de búsqueda de
//tamaño n para la distribución de
//la demanda del apartado (a).
double* construye_prop_a(int n)
{
    int i;
    double* temp;
    if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador uniforme\n",stderr);
        exit(1);
    }
    temp[0] = 1.0/n;
    for (i=1;i<n;i++)
        temp[i] = temp[i-1]+1.0/n;
    return temp;
}
//Construye la tabla de búsqueda de
//tamaño n para la distribución de
//la demanda del apartado (b).
double* construye_prop_b(int n)
{
    int i, max;
    double* temp;
    if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n",stderr);
        exit(1);
    }
    max = (n+1)*n/2;
    temp[0] = 1.0/max;
    for (i=1;i<n;i++)
        temp[i] = temp[i-1]+(double)(i+1)/max;
    return temp;
}
//Construye la tabla de búsqueda de
//tamaño n para la distribución de
//la demanda del apartado (c).
double* construye_prop_c(int n)
{
    int i, max;
    double* temp;
    if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador triangular\n",stderr);
        exit(1);
    }
    max = n*n/4;
    temp[0] = 0.0;
    for (i=1;i<(n/2);i++)
        temp[i] = temp[i-1]+(double)i/max;
    for (i=(n/2);i<n;i++)
        temp[i] = temp[i-1]+(double)(n-i)/max;
    return temp;
}
// Genera un valor de la
// distribución de la demanda codificada en tabla, por el
// método de tablas de búsqueda.
// tama es el tamaño de la tabla, 100 en nuestro caso particular
int genera_demanda(double* tabla,int tama)
{
    int i;
    double u = uniforme();
    i = 0;
    while((i<tama) && (u>=tabla[i]))
        i++;
    // char h;
    //std::cin >> h;
    // std::cout << i << " = " << tabla[i-1] << " - " << tabla[i] << std::endl;

    return i;
}

/*
 * El programa principal debe también incluir lo siguiente:
  srand(time(NULL)); //Inicializa el generador de números pseudoaleatorios
  tablabdemanda = construye_prop_?(100); //Construye la tabla de búsqueda con ? sustituido por a, b ó c

//Las llamadas al generador de datos en el bucle del programa principal realmente deben hacerse mediante
demanda = genera_demanda(tablabdemanda,100) //Cada vez que se necesite un
                                            //valor del generador de demanda
*/
