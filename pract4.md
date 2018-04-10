# Práctica 4

## Introducción a punteros
```cpp
int main(){
	int *p, x=9;
	cout << "El puntero p vale" << p << endl; //Muestra la dirección de memoria a la que apunta p, no sabemos que hay en esa dirección porque no está inicializado.
	cout << "El contenido del puntero es " << *p << endl;
}
```
p es un **puntero salvaje**, no está inicializado, apunta a un lugar aleatorio y no sabemos que contiene.
Los punteros no son inicializados a 0 por el compilador, hay que tener cuidado.

- Lo mejor que puede pasar es que haya _segmentation fault_
- Lo peor que puede pasar es que apunte a algo de mi programa, no dé errores y estemos cambiadno datos y propagando errores sin darnos cuenta.

**Para evitar esto siempre que declaremos un puntero debemos inicializarlo a 0/NULL**

```cpp
int main(){
	int *p=NULL, x=9; //sirve igual con 0 e vez de NULL
	cout << "El puntero p vale" << p << endl; //Muestra la dirección de memoria a la que apunta p, no sabemos que hay en esa dirección porque no está inicializado.
	if ( p != NULL)
		cout << "El contenido del puntero es " << *p << endl;
	else
		cerr << "El puntero no está inicializado" << endl; //cerr visualiza mensajes de error.
}
```

```cpp
int main(){
	int *p=NULL, x=9; //p no apunta a nada
	p=&x; //Ahora p apunta a x
	cout << "El puntero p vale" << p << endl; //Muestra la direccion de memoria
	cout << "El contenido del puntero es " << *p << endl; //Muestra el valor de p, en este caso x, osea 9
}
```

## Valgrind
Para que **Valgrind** nos muestra la línea de error debemos compilar con _-g_
Estudiemos los errores de Valgrind.

- Invalid read on line.... : Estamos accediendo a una dirección de memoria que no es nuestra.

```cpp
int main(){
	int *p=NULL, x=9; //p no apunta a nada
	p=new int(5); //Reservamos espacio para un entero que inicializamos a 5
	cout << "El puntero p vale" << p << endl; //Muestra la direccion de memoria
	cout << "El contenido del puntero es " << *p << endl; //Muestra el valor de p, en este caso 5.
	//Falta liberar la memoria!
}
```
Esto se usa para gestionar memoria dinámica.

- 4 Bytes in a block are definitely lost... new on line... : No se ha liberado la memoria reservada en el new de la línea...

```cpp
int main(){
	int *p=NULL, x=9; //p no apunta a nada
	p=new int(5); //Reservamos espacio para un entero que inicializamos a 5
	cout << "El puntero p vale" << p << endl; //Muestra la direccion de memoria
	cout << "El contenido del puntero es " << *p << endl; //Muestra el valor de p, en este caso 5.
	delete p;
}
```
**OJO: SI HACEMOS UN DELETE A UN PUNTERO SALVAJE ESTAMOS BORRANDO MEMORIA QUE NO ES NUESTRA**

```cpp
int main(){
	int *p=NULL, x=9; //p no apunta a nada
	p=new int(5); //Reservamos espacio para un entero que inicializamos a 5
	cout << "El puntero p vale" << p << endl; //Muestra la direccion de memoria
	cout << "El contenido del puntero es " << *p << endl; //Muestra el valor de p, en este caso 5.
	if (p != NULL)
		delete p; //Este puntero se ha vuelto salvaje
}
```
Al hacer un delete a puntero el puntero sigue apuntando al mismo sitio, no es NULL si no se especifica.
```cpp
int main(){
	int *p=NULL, x=9; //p no apunta a nada
	p=new int(5); //Reservamos espacio para un entero que inicializamos a 5
	cout << "El puntero p vale" << p << endl; //Muestra la direccion de memoria
	if ( p != NULL)
		cout << "El contenido del puntero es " << *p << endl; //Muestra el valor de p, en este caso 5.
	if (p != NULL){
		delete p;
		p = NULL;
	}
}
```
**AL DECLARAR UN PUNTERO SE PONE A NULL, AL BORRAR UN PUNTERO SE PONE A NULL, AL ACCEDER A UN PUNTERO SE COMPRUEBA SI ES NULL Y SI LO ES NI SE TOCA.**

```cpp
int main(){
	int *p=NULL, x=9; //p no apunta a nada
	p = new int[15]; //Reservamos espacio para quince enteros donde hay basura
	cout << "El puntero p vale" << p << endl; //Muestra la direccion de memoria
	if ( p != NULL)
		cout << "El contenido del puntero es " << *p << endl; //Muestra el valor de p, en este caso 5.
	if (p != NULL){
		delete[] p;
		p = NULL;
	}
}
```

- Invalid write of 4 Bytes on line.... : Estamos escribiendo en una zona de memoria que no es nuestra.