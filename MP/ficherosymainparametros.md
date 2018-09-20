# Apuntes 16/04, repaso
## Introducción
- El error más común es no pasar correctamente los parámetros por valor y por referencia (constante y no).
- El estándar que se sigue en clase es el de 98, esto es, deberíamos usar el compilador de estándar del 98.
- El error de ignorar funciones de cstring hace referencia a que es importante trabajar con cstrings, y saber diferenciar _cstring_ de _string_
	- _cstring_ requeire terminador y el espacio para él, es estática.
	- _string_ no requiere terminador y es dinámica. 
- Queda mal entregar funciones comentadas.

## cstring
```cpp
char micadena[tamano]
```
¡Se pueden leer con cin!
```cpp
cin >> micadena;
```
Y el cin añade él por sí mismo el terminador (\0).
estos son el único tipo de vector que se pueden leer con _cin_ y no hace falta un _for_ para leer componente a componente. Si metemos la cadena carácter a carácter y no ponemos el terminador al mostrarlo va a buscar por toda la memoria hasta encontrar un terminador y provocará violación de memoria.
También es el único vector que se puede inicializar de golpe y tam bién añade el terminador por sí solo.
```cpp
char micadena[10] ="Ana";
``` 
Además se puede escribir de golpe.
```cpp
cout << micadena;
```
Con los cstring no se puede copiar una cadena en la otra.
```cpp
s1=s2; //No se puede
```
Para ello se usan funciones:
```cpp
strcpy(s1,s2);
```
Se pueden coiar cstrings en string de forma normal (como arrriba), pero para copiar un string a cstring se hace así:
```cpp
strcoy(s1, s2._str()); //No sé si es _ o .
```

## Acceso a ficheros de texto
Al introducir varios datos a la vez (separados por espacio, y luego sarle a enter) se crea un flujo de datos, se ejecutan entonces los cin y van cogiéndolos de cin en cin parando en los espacios o en carácteres que no le correspondan.
Un flujo de datos no siempre se lee bien, si se da esto hay que ver si se dan errores porque si se ha dado el resto de flujo es impredecible.

Con la redirección de entrada solo podemos usar un fichero, por eso hace falta aprender a leer y escribir en ficheros.

Utilizaremos flujos de datos asociados a ficheros.
```cpp
#include <fstream>
```

```cpp
ifstream entrada; //Declaro la variable
entrada.open("datos.dat") //Abro el archivo, indicando la ruta a partir de l binario
entrada>> n; //como cin
entrada >> d; //como cin
entrada.close() //Cierro el fichero.
```
Si el fichero se abre y no se cierra:
- Como profesor el mundo se acaba y explota todo, no es bueno.
- Como programador, al ser c++ al acabar la función en la que está o el programa terminar se cierra automáticamente.
Para comprobar que el fichero del que se lee existe y funciona:
```cpp
ifstream entrada; //Declaro la variable
entrada.open("datos.dat") //Abro el archivo, indicando la ruta a partir de l binario
if (entrada){ //es un puntero, si apunta a algun sitio no es 0, y sera true, si es null sera 0 y sera false.
	entrada>> n; //como cin
	entrada >> d; //como cin
	entrada.close() //Cierro el fichero.
}
else
	cerr << "ERROR en la apertura del fichero" << endl;
return 0;
```

Si faltan datos en la lectura en el fichero, también se arreglara así:

```cpp
ifstream entrada; //Declaro la variable
entrada.open("datos.dat") //Abro el archivo, indicando la ruta a partir de l binario
if (entrada){ //es un puntero, si apunta a algun sitio no es 0, y sera true, si es null sera 0 y sera false.
	entrada>> n; //como cin
	entrada >> d; //como cin
	if (entrada)
		cout << //variables.
	else
		cerr << "ERROR en la lectura del fichero" << endl;
	enntrada.close()
}
else
	cerr << "ERROR en la apertura del fichero" << endl;
return 0;
```

La escritura funciona de maner análoga.
```cpp
ofstream salida;
```

## Parámetros del main
```cpp
int main (int nargs, char * args[]){
	return 0;
}
```
Donde _nargs_ es el número de argumentos y args contiene los argumentos que se han pasado. _args[0]_ es el nombre del binario.

```cpp
int main (int nargs, char * args[]){
	cout << "Soy el programa " << args[0] << endl;
	if (nargs > 1)
		for (int i = 1; i < nargs, i++)
			cout << "Soy amigo de " << args[1] << endl;
	else
		cout << "No tengo amigos" << endl;
	return 0;
}
```
## Práctica a entregar.
Se construirá sobre la práctica anterior y se copiará lac lase anterior y se construirá otra nueva.
El idioma ruso dará un error que hay que solventar.
El método más complicado será añadir de fichero.

