# Paralelización de código en c/c++

## Introducción

Para la paralelización de código se usará la herramienta **OpenMP**.

OpenMP es una API para escribir código en paralelo basado en el paradigma de programación de variables compartidas para ejecutar aplicaciones en paralelo en varios threads. Además es no automática, es decir, no extrae paralelismo implícito.

La API OpenMP comprende directivas del compilador, funciones de biblioteca y variables de entorno.

Se podría considerar estándar por el gran número de vendedores y fabricantes que lo han definido.

OpenMP también sirve para paralelizar código FORTRAN.

## Componentes de OpenMP

- Directivas: El prepocesador del compilador las sustituye por código.
- Funciones: Sirven entre otras para fijar y preguntar parámetros en tiempo de ejecución.
- Variables de entorno: Sirven para fijar parámetros antes de la ejecución (como el número de threads: `export OMP_NUM_THREADS=N`).

## Sintaxis

La sintaxis siempre será del tipo:

```c++
#pragma omp <nombrededirectiva> <cláusula> <newline>
```

- Las cláusulas son opcionales y especifican adicionalmente la acción o comportamiento.

- <newline\> es necesario y precede al bloque estructurado que engloba la directiva.

Por ejemplo:

```c++
#pragma omp parallel num_threads(8) if (N>20)
// El código siguiente se ejecuta en paralelo con 8 hebras si N>20
```

Para usar varias líneas de código se usa `\` para unirlas: 

```c++
#pragma omp parallel private (...) \
shared (...)
```

## Compilación

Para compilar usaremos el flag `fopenmp` o `openmp`, así se definirá `_OPENMP` en nuestro código y se tendrán en cuenta las directivas de OpenMP.

```bash
# Compilación para código c
gcc -fopenmp -O2 -std=c11 -Wall fichero.c -o ejecutable
# Compilación para código c++
g++ -fopenmp -O2 -std=c++11 -Wall fichero.cpp -o ejecutable
# Se puede usar -O3 en ambos casos, pero puede provocar errores.
# Se puede añadir el flag -march=native (tras -fopenmp)
# El estándar de c++ puede usarse también el 14.
```

Por ejemplo, el siguiente código en c comprueba si se ha compilado con `fopenmp` y en caso afirmativo paraleliza el bucle, si no, se ejecuta de forma secuencial.

```c++
#ifdef _OPENMP
	omp_set_num_threadas(nthread)
#endif
        
#pragma omp parallel for
for(i=0;i<n;i++)
    for(j=0;j<n;j++)
        // Código
```

## Directivas

### Parallel

```c
#pragma omp parallel
```

- Especifica qué cálculos se ejecutarán en paralelo. Se pasa de secuencial a paralelo.
- El thread master crea un conjunto de threads.
- Cada thread ejecuta el código incluido en la región.
- No reparte tareas entre threads.
- Se pueden anidar y usar otras directivas dentro de esta. (No se pueden usar otras directivas fuera de parallel).
- Tiene una barrera implícita al final (es decir, dado un punto no se sigu ejecutando hasta que todas las hebras han llegado a él).

```c
#include <stdio.h>
#ifdef _OPENMP
	#include <omp.h>
#else
	#define omp_get_thread_num() 0
#endif

main(){
    int ID;
    #pragma omp parallel private(ID)
    {
        ID = omp_get_thread_num(); //ID tiene el identificador de la hebra que la ejecuta.
        printf("Soy la hebra %d",ID);
    }
}
```

Para modificar el número de hebras que se lanzan se modificará en la terminal la variable `OMP_NUM_THREADS`, es recomendable no usar más hebras que procesadores físicos.

```bash
export OMP_NUM_THREADS=4 #Se lanzarán 4 hebras al ejecutar el programa
```

Las hebras se enumeran de 0 hacia adelante, la hebra master siempre es la 0.

### for

- Implementa paralelismo de datos a nivel de bucle.
- Se tiene que conocer el número de iteraciones y se debe iterar sobre un entero.
- Solo sirve para bucles for.
- Se decide automáticamente la asignación de trabajo a hebras.
- Tiene una barrera implícita al final.

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]){
    int i;
    int n;
    if (argc < 2){
        fprintf(stderr,"\nError, falta numero de iteraciones\n");
        exit(-1);
    }
    n = atoi(argv[1]);
    #pragma omp parallel
    {
        #pragma omp for
        for (i=0; i<n; ++i)
            printf("Soy la hebra %d y ejecuto la iteracion %d",omp_get_thread_num(),i);
    }
    return 0;
}
```

### sections

- Implementa paralalelismo de tareas o a nivel de función.
- La asignación de tareas a threads concretos la hace automática.
- Tiene barrera implícita al final.
- Cada hebra ejecuta un section, no lo hacen a la vez.

```c
#include <stdio.h>
#include <omp.h>

void funcA(){
    printf("En funcA lo ejecuta el thread: %d",omp_get_thread_num());
}
void funcB(){
    printf("En funcB lo ejecuta el thread: %d",omp_get_thread_num());
}

int main(int argc, char**argv){
    #pragma omp parallel
    {
        #pragma omp sections
        	#pragma omp section
        		(void)funcA();
        	#pragma omp setion
        		(void)funcB();
    }
}
```

### single

- Ejecuta un trozo secuencial por un solo thread.
- Cualquier thread puede ejecutar el código secuencial, pero solo lo hará este.
- Tiene barrera implícita al final.

```c
#include <stdio.h>
#include <omp.h>
int main(int argc, char** argv){
    int n = 9,i,a,b[n];
    for (i = 0; i < n; ++i)
        b[i] = -1;
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Introduce el valor de inicialización a");
            scanf("%d",&a);
            printf("Single ejecutada por el thread %d", omp_get_thread_num());
        }
        #pragma omp for
        for (i=0; i < n; ++i)
            b[i] = a
    }
    printf("Después de la región parallel: ")
    for (i=0; i <  n; ++i)
        printf("b[%d]=%d",i,b[i]);
    return 0;
}
```

### barrier

- Fija un punto en el código en el que todos los threads se esperan entre sí.

```c
#include <stlib.h>
#include <time.h>
#ifdef _OPENMP
	#include <omp.h>
#else
	#define omp_get_thread_num() 0
	#define omp_get_num_threads() 1
#endif

int main (int argc, char**argv){
    int tid;
    time_t t1,t2;
    
    #pragma omp parallel private(tid,t1,t2) //Hace privadas a cada hebra tid,t1 y t2
    {
        tid = omp_get_thread_num();
        if (tid < omp_get_num_threads/2)
            system("sleep 3");
        t1 = time(NULL);
        
        #pragma omp barrier
        
        t2 = time(NULL)-t1;
        printf("Tiempo=%d seg\n", t2);
    }
}
```

### critical

- Evita que varios threads accedan a variables compartidas a la vez, es decir, sirve para evitar condiciones de carrera (esto es, el resultado del programa depende del orden en el que se ejecuten las hebras).

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char **argv)   {
   int i, n=20, a[n],suma=0,sumalocal;
   if(argc < 2)     {
         fprintf(stderr,"\nFalta iteraciones\n"); exit(-1);
   } 
   n = atoi(argv[1]); if (n>20) n=20; 

   for (i=0; i<n; i++)    a[i] = i; 
 
#pragma omp parallel private(sumalocal)
{  sumalocal=0;
   #pragma omp for  schedule(static)
   for (i=0; i<n; i++)
   {   sumalocal += a[i];
       printf(" thread %d suma de a[%d]=%d sumalocal=%d \n",  omp_get_thread_num(),i,a[i],sumalocal);
   } 
   #pragma omp critical 
       suma = suma + sumalocal;
}  
   printf("Fuera de 'parallel' suma=%d\n",suma);
   return(0);
}
```

### atomic

- Es una alternativa a critical más eficiente, en especial operaciones +,-,*,/,&,^,|,<<,>>.

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)  {
   int i, n=20, a[n],suma=0,sumalocal;
   if(argc < 2)     {
      fprintf(stderr,"\nFalta iteraciones\n");
      exit(-1);
     }
   n = atoi(argv[1]); if (n>20) n=20; 

   for (i=0; i<n; i++)     a[i] = i; 
 
  #pragma omp parallel private(sumalocal)
  {  sumalocal=0;
     #pragma omp for  schedule(static)
     for (i=0; i<n; i++)
     {   sumalocal += a[i];
         printf(" thread %d suma de a[%d]=%d sumalocal=%d \n",  omp_get_thread_num(),i,a[i],sumalocal);
     } 
     #pragma omp atomic 
         suma += sumalocal;
  }  
  printf("Fuera de 'parallel' suma=%d\n",suma);
  return(0);
}
```

### master

- No tiene barrera implícita.
- Establece una sección en la que solo entra la hebra master, lo que es útil para recoger datos de las hebras hijas o hacer operaciones, introducir datos...

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char **argv)  {
   int i, n=20, tid, a[n],suma=0,sumalocal;
   if(argc < 2)     {
      fprintf(stderr,"\nFalta iteraciones\n");
      exit(-1);
     }
   n = atoi(argv[1]); if (n>20) n=20; 

   for (i=0; i<n; i++)   a[i] = i; 
 
  #pragma omp parallel private(sumalocal,tid)
  {  sumalocal=0;
     tid=omp_get_thread_num();
     #pragma omp for  schedule(static)
     for (i=0; i<n; i++)
     {    sumalocal += a[i];
           printf(" thread %d suma de a[%d]=%d sumalocal=%d \n",  tid,i,a[i],sumalocal);
     } 
     #pragma omp atomic 
          suma += sumalocal;
     #pragma omp barrier
     #pragma omp master
          printf("thread master=%d imprime suma=%d\n", tid,suma);
  }  
  return 0;
}
```

### Contracción de directivas ya vistas:

Las directivas for y sections se pueden condensar en una línea, lo cual facilita la legibilidad y también mejora las prestaciones.

```c
#pragma omp parallel
	#pragma omp for
//Estas dos líneas se condensan en:
#pragma omp parallel for
```

```c
#pragma omp parallel
	#pragma omp sections
//Estas dos líneas se condensan en:
#pragma omp parallel sections
```

