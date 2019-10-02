
# Tema 2: Punteros

## Tipo de dato Puntero


### Definición

La memoria dinámica permite crear variables del tamaño necesario en tiempo de ejecución, para esto usaremos los punteros.
Un **puntero** es un tipo de dato que contiene la dirección de memoria de otro dato.
Si el puntero tiene una dirección nula (`0`) , el puntero no apunta a ningún dato concreto. En C se podía usar tanto `0` como `NULL` (no lo vamos a usar) o `nullptr` que es nuevo de C++11.
Para declararlo:
```cpp
<tipoalquepuedeapuntar> *<identificador>
```
Un puntero guarda la dirección de memoria donde empieza la dirección de la variable a la que apunta o referencia.
Se declara la variable y luego el puntero.
Todos los punteros ocupan el mismo espacio. La memoria se reserva para el puntero (32 o 64 bits), no para el dato al que apuntan en sí.

**!** Cuidado al declarar varios punteros:
```cpp
int* ptr, ptr2;  // ptr es puntero, ptr2 es entero.
int* ptr, ptr2;  // lo mismo
int* ptr, *ptr2; // Ambos punteros
```


### Operaciones

- `&`: Hace un AND (multiplicar) bit a bit. Sirve para esconder mensajes en imágenes, por ejemplo. Devuelve la dirección de la variable (un puntero). No sirve para expresiones, debe ser una única variable.
```cpp
&<var> 
```
```cpp
int i = 5, *ptri;
ptri = &i;
```
- `*`: Devuelve el dato al que apunta un puntero.
```cpp
*<puntero>
```
```cpp
char c, *ptrc;
ptrc = &c;
*ptrc = 'A';
// Hace a c valer A.
```
- Inicialización: Conviene inicializar los punteros con el puntero nulo 0.
```cpp
// Le asignamos la dirección nula (único valor literal que puedo asignarle directamente).
int *ptri = 0;
int *ptri = nullptr;
int *ptri = NULL;
// Hay varias formas de asignar el puntero nulo, 
// pero se recomienda ser consistente y usar siempre la misma.
```

También podemos hacer que nuestro puntero apunte a una variable, siempre de su mismo tipo.
```cpp
int a;
int *ptri = &a;
```

- Asignación entre punteros: Sólo puede ser entre punteros del mismo tipo.
```cpp
int a = 7;
int *p1 = &a;
char *p2 = &a; // Esto no se puede hacer, a es entero y p2 apunta a un char a menos que usemos *p2 = reinterpret_cast<char*>(&a)
int *p3 = *p2; // Esto sí es válido ya que son del mismo tipo
```
- Relacionales: <,>,<=,>=,!=,==: Compara números enteros.
	- p1 == p2 : Comprueba si ambos punteros apuntan al mismo dato.
	- \*p1 == \*p2 : Comprueba si el contenido al que apunta p1 es el mismo que al que apunta p2.
	- <,>,<=,>= Permite conocer la posición relativa de un dato respecto a otro en la memoria. Esto es útil cuando los punteros están apuntando a datos del mismo array.
- Aritméticos: +,-,++,-\-,,+=,-= : Tiene sentido cuando estamos a puntando a datos del array. Al sumarle 1, apunta a la siguiente dirección de memoria del array.
```cpp
int v[5] = {2,6,3,5,3};
int *p;
p = &v[2];
cout << p[1]; // Escribe 5, ya que p apunta a 3, el siguiente es 5.
p+=2; // Ahora p apunta dos posiciones más adelante, es decir, al último 3.
p = &v[2];
q = &v[4];
q-p // Devuelve 2. Los punteros se pueden restar pero no pueden sumar punteros.
```


### Punteros y arrays

Al declarar un array, realmente se crea un puntero constante (siempre apunta a la misma dirección de memoria) que apunta a la primera posición de ese array. Si un array se llama `v`, entonces `v` es equivalente a `&(v[0])`. `v[0]` equivale a `*(&v[0])`.
Podemos usar arrays con la sintaxis de punteros.
```cpp
int v[5] = [2,6,3,5,3};
cout << *v << endl; // Escribe 2
cout << *(v+2) << endl; // Escribe 3
```
También podemos usar punteros como arrays.
```cpp
int v[5] = [2,6,3,5,3};
int *p;
p = &(v[1]);
cout << *p << endl; // Escribe 6
p = v+2,
cout << *p << endl; // Escribe 3
p++;
cout << *p << endl; // Escribe 5
p = &(v[3])-2;
cout << p[0] << p[2] << endl; // Escribe 6 5
```

Por ejemplo, para recorrer los elementos de un array mediante punteros:
```cpp
int v[10] = {3,5,2,7,6,7,5,1,2,5};
int *p=v;
for (int i=0; i<10; i++)
	cout << *(p++) << endl;
```
O bien:
```cpp
int v[10] = {3,5,2,7,6,7,5,1,2,5};
for (int *p=v; p<v+10; p++)
	cout << *p << endl;
```


### Punteros y cadenas

Una cadena de caracteres es un array constante de `char` (carácter) con tamaño su longitud más uno, pues su último carácter es siempre `\0`, el llamado carácter nulo o marca de fin de cadena. Es considerado un `const char*`. Por ejemplo calculando la longitud de una cadena:

```cpp
const char *cadena = "Hola"; // Tamaño 5
const char *p; // p puntero a caracter constante, p es modificable
int i = 0;
for (p=cadena;*p!='\0';p++)
	++i;
cout << "Longitud: " << i << endl;
```

A continuación este ejemplo escribe `Hola Adios` y luego `Adios`, normalmente escribiría la dirección de memoria a la que apunta, pero muestra por pantalla el contenido ya que está apuntando a una cadena de `char` (esto pasa siempre, es una excepción). Si pusiéramos `*cadena` sólo mostraría la primera h, ya que apunta a la primera letra. Si quisiéramos que mostrara la dirección de memoria pondríamos (`char *`) cadena.

```cpp
const char *cadena = "Hola Adiós";
cout << "Original: " << cadena << endl;
cout << "Sin la primera palabra: " << cadena+5 << endl;
```

Si lo declaramos con corchetes se puede cambiar un carácter, si se declara como puntero no se pueden modificar caracteres ya que está apuntando a caracteres constantes. (Nótese que declaramos la cadena como `const char`)


### Punteros y struct o class

También pueden apuntar a structs o class.
Un puntero apunta al primer dato del struct o clase de ese clase y se accede a sus datos como `(*puntero).dato` y a métodos como `(*puntero).método()`.

Podemos usar el operador `->` para acceder a datos miembros `(*p).miembro` o `p->miembro`.
Una clase puede tener punteros como miembros, pueden apuntar a otro dato de la misma clase que estamos definiendo, por ejemplo en el caso de una clase persona, un puntero que apunta a su pareja. Pueden dereferenciarse varios punteros (si un puntero apunta a otro puntero es válido usar esto:)
```cpp
ptr->pareja->nombre // El puntero accede a otro puntero que accede al nombre.
```


### Punteros y funciones

Un puntero puede ser un parámetro de funciones, es similar al paso por referencia.
También podemos modificar un puntero pasando por referencia el puntero:
```cpp
void funcion (int *p) // Pasa puntero como argumento.
void funcion (int* & p) // Pasa puntero como argumento POR REFERENCIA
int* double (int x) // Devuelve un puntero.
```

No se pueden devolver punteros a una variable local a la función, ya que la variable se destruye al acabar la función.


### Punteros a Punteros

Es posible que un puntero apunte a otro, y repetir esto todas las veces que se quiera, creando una especie de cadena:

```cpp
int a = 5;
int *p;  // Puntero a entero.
int **q; // Puntero a puntero a entero.
p = &a;
q = &p; // Para acceder al valor de a sirve a, *p, **q
```
Esto es útil, por ejemplo, para declarar matrices dinámicas (usamos un puntero a un array de punteros que actúan como arrays).


### Punteros y const

Tenemos el dato al que apunta el puntero y el puntero, para definir constantes:
```cpp
double *p; 			// Ninguno constante
const double *p; 		// El dato apuntado es constante
double const *p; 		// El dato apuntado es constante
double *const p=<valor>; 	// El puntero es constante
const double *const p; 		// Ambos son constantes
double const *const p; 		// Ambos son constantes
```
Un puntero a dato no constante no puede apuntar a un dato constante (permitiría cambiar el valor de una constante mediante el puntero).

Podemos llamar a una función que espera un puntero a dato constante con un puntero a dato no constante.


### Arrays de punteros

Es un array cuyos elementos son punteros:
```cpp
int* arrayPunts[4];
int a=5, b=7, c=3, d=2;
arrayPunts[0]=&a;
arrayPunts[1]=&b;
arrayPunts[2]=&c;
arrayPunts[3]=&d;
for (int i = 0; i<4; i++){
	cout << *arrayPunts[i] << " "; // Imprime 5 7 3 2
}
cout << endl;
``` 
Por ejemplo, para ordenar un array sin modificar el array se crea un array de punteros con tantos punteros como el array a ordenar, donde cada puntero apunta al valor de su misma posición y se ordenan los punteros en lugar de los valores.
Podemos tener un array de punteros a cadenas tipo C (`cstring`).
```cpp
const char*  constpalosBaraja[4]={"Oros","Copas", "Espadas", "Bastos"};
cput << "Palos de la Baraja: ";
for (int i = 0; i<4; i++)
	cout << oalosBaraja[i] << " ";
cout << endl;
```


### Main con argumentos.

Ahora declararemos el main como:
```cpp
int main ( char* argv[], int argc)
```
Esto sirve para que al ejecutar un programa pasándole ficheros por la terminal, el nombre de estos ficheros se guarde en el array que recibe como parámetro main.
`argv` es un array de cadenas de C.
`argv[0]` es el nombre del ejecutable, `argv[1]` es el primer fichero que recibe y así sucesivamente.
`argc` almacena el tamaño del array.


### Manejo de archivos con `fstream`.

Para leer datos de un fichero se usa una variable de tipo ifstream, perteneciente a la biblioteca `fstream`.
```cpp
#include<fstream> // Para el manejo de archivos

//...

int entero;
ifstream flujo; 	// Declaramos el objeto que "almacenará" el archivo y nos permite enviar datos 
flujo.open(argv[1]); 	// Abrimos el archivo
flujo >> entero; 	// Enviamos datos al archivo
```


### Punteros a funciones

Es un puntero que contiene la dirección de memoria de una función. Estos punteros se pueden pasar como parámetro a otra función o ser devuelto o hacer un array de punteros a funciones, asignarlos a otras variables o se usan para ejecutar la función a la que apuntan.
Al darle un valor, se le da como valor el nombre de una función.
```cpp
bool ( *comparar )( int, int)
// Comparar es un puntero que puede apuntar a cualquier función que reciba como parametros dos enteros y devuelva un booleano.
// Si no se usan los paréntesis en *comparar estaríamos declarando una función que devuelve un puntero a bool y recibe dos enteros.
(*comparar)(valor1,valor2); // Accede a la función
```
Son útiles para, por ejemplo, con una sola función hacer una función que ordene un array de mayor a menor o de menor a mayor.


### Errores comunes con punteros

- Asignar punteros a distinto tipo (puntero entero que intenta apuntar a puntero a carácter).
- Usar punteros no inicializados (salvajes).
- Asignar valores al puntero y no a la variable.


## Gestión de memoria dinámica


### Estructura de la memoria

Un SO divide la memoria en varias partes:

- Segmento de código: Donde está el código del programa.
- Memoria estática: Memoria reservada antes de ejecutar un programa (es fija) donde se guardan las variables globales y las `static` (Locales a una función: solo se le asigna el valor inicializador una vez (la primera que se entra; A una clase en `public`: es como una variable global de la clase, es la misma para todos los objetos).
- Pila: Aquí se guardan las variables locales de las funciones. por cada función se reserva un _entorno de programa_.
- El _heap_: Se reservan y liberan trozos según las necesidades, esta es la única zona que maneja el programador. Sirve para crear nuevas variables o variables con tamaño indeterminado.


### Gestión dinámica de la memoria

- Se pide al SO un trozo de la memoria (tamaño). Para ello usamos la palabra reservada `new`.
- El SO comprueba si hay suficiente espacio libre en el _heap_.
- Si hay espacio suficiente, el SO devuelve la posición de memoria donde se ha reservado y marca la zona como ocupada.
- La ubicación de la memoria se almacena en una variable estática o local puntero.
```cpp
int *p2;
p2 = new int[200]; // Almacena la direccion de memoria
```
- La zona de memoria reservada puede almacenar nuevas variables dinámicas que pueden almacenar la dirección de nuevas peticiones de reserva de memoria.
- Se libera la memoria dinámica que ya no necesitamos.

### Operador `new`
Reserva en el _heap_ memoria suficiente del tipo especificado.
```cpp
<tipo> *p;
p = new <tipo>;
```
Si no hay espacio suficiente para reservar esa memoria se provocaría una excepción y el programa termina.
```cpp
int *p;
p = new int;
*p = 10; // Se reserva memoria para un entero.
```

### Operador `delete`
Sirve para liberar la memoria que ya no es necesaria.
```cpp
delete puntero;
```
```cpp
int *p, q = 10;
p = new int; // Reservamos memoria
*p = q;

// Usamos p en las operaciones necesarias.

delete p; // Liberamos la memoria
```

### Objetos dinámicos compuestos

Se reservan `structs` y `class` de forma igual a datos simples.

- `new` reserva la memoria y llama al constructor de la clase para inicializar los objetos.
- `delete` llama al destructor de la clase y después libera la memoria de cada campo del objeto.
```cpp
class Estudiante {
	string nombre;
	int nAsignaturasMatricula;
	vector<int> codigosAsignaturasMatricula;
	public:
	Estudiante();
	Estudiante(string name);
	void setNombre(string nuevoNombre);
	string getNombre() const;
	void insertaAsignatura(int codigo);
	int getNumeroAsignaturas() const;
	int getCodigoAsignatura(int index) const;
	// Más métodos aquí
};

int main() {
	Estudiante* ramon;
	ramon=new Estudiante("Ramón Rodríguez Ramírez"); // Llama al constructor necesario de acuerdo a los parámetros que se le den.
	ramon->insertaAsignatura(302);
	ramon->insertaAsignatura(307);
	ramon->insertaAsignatura(205);
	// Más código aquí
	delete ramon;
}

```


### Arrays dinámicos

Usando arrays dinámicos podemos crear arrays justo del tamaño necesario y justo en el momento necesario y destruirlos después.
Para ello usaremos `[]` en los operadores usuales.
```cpp
<tipo> *p;
p = new <tipo> [numeroareservar]; // Num debe ser mayor que 0
delete[] p;
```
```cpp
// Programa donde se crea array dinámico (con un puntero que se trata como array)
int *v = 0, n;
cout << "Número de casillas: ";
cin >> n;
v = new int [n];

for (int i = 0;  i < n;  i++) {
	cout << "Valor en casilla " << i <<  ": ";
	cin >> v[i];
}
cout << endl;

for (int i = 0; i < n; i++)
	cout << "En la casilla " << i << " guardo: "<< v[i] << endl;

delete [] v;
v = 0;
```
```cpp
// Función para redimensionar un array dinámico.
void redimensionar (int *&v, int& tama, int aumento){
	if (tama+aumento > 0){
		int *v_ampliado = new int[tama+aumento];
		for (int i = 0; (i < tama) && (i < tama+aumento); i++)
			v_ampliado[i] = v[i];
		delete[] v;
		v = v_ampliado;
		tama = tama+aumento;
	}
}
```


### Arrays dinámicos de objetos

Funciona igual que con un tipo de dato nativo, salvo que se usa el constructor por defecto obligatoriamente al inicializar los datos de la memoria reservada.


### Clases que contienen dartos en memoria dinámica

Una clase puede contener punteros que se pueden a usar para almacenar datos en memoria dinámica.
Los constructores pueden reservar la memoria dinámica y el destructor elimina la memoria dinámica que contiene  un objeto. Obviamente se puede aumentar o disminuir la memoria reservada con otros métodos.


### Matrices dinámicas

Hay 3 formas distintas de declarar matrices dinámicas:

- Primera forma:
```cpp
// Creación de la matriz
int *m;
int nfil,ncol;
m = new int[nfil*ncol];
// Acceso al elemento fila (f),columna (c)
int a;
a = m[f*ncol+c];
// Liberación de la matriz
delete[] m;
```

- Segunda forma:
```cpp
// Creación de la matriz
int **m;
int nfil, ncol;
m = new int*[nfil];
for (int i=0; i<nfil;++i)
m[i] = new int[ncol];
// Acceso al elemento fila (f), columna (c)
int a;
a = m[f][c];
// Liberación de la matriz
for(int i=0;i<nfil;++i)
	delete[] m[i];
delete[] m;
```

- Tercera forma:
```cpp
// Creación de la matriz
int **m;
int nfil, ncol;
m = new int*[nfil];
m[0] = new int[nfil*ncol];
for (int i=1; i<nfil;++i)
m[i] = m[i-1]+ncol;

// Acceso al elemento fila (f), columna (c)
int a;
a = m[f][c];
// Liberación de la matriz
delete[] m[0];
delete[] m;
```


### Celdas enlazadas

En estas listas se pueden insertar datos en la posición que se quiera usando celdas enlazadas, donde cada una está en el heap y se usan punteros para enlazar a la celda siguiente.
Es obligatorio que en la última celda de la lista el puntero sea nulo (`0` o `nullptr`) para indicar el final.
```cpp
struct Celda{
	double dato;
	Celda* sig;
}
```
```cpp
#include <iostream>
using namespace std;

struct Celda{
	double dato;
	Celda* sig;
};

int main(){
	Celda* lista;
	double valor;
	lista = 0;
	cin >> valor;
	while(valor != 0.0){ // Creación de las celdas de la lista
		Celda* aux = new Celda;
		aux->dato = valor;
		aux->sig = lista;
		lista = aux;
		cin >> valor;
	}
	// Mostrar la lista en salida estandar de principio a fin
	aux = lista;
	while(aux != 0){
		cout << aux -> dato << " ";
		aux = aux->sig; // aux apunta a la siguiente celda
	}
	cout << endl;
	while (lista != 0) { // Destrucción de la lista
		Celda* aux = lista;
		lista = aux->sig;
		delete aux;
	}
}
```


_By Mapachana_
