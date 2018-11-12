// Alumna: Ana Buendía Ruiz-Azuaga

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdbool.h>



//    DESACTIVAR BUFFER

setvbuf(stdout, NULL,_IONBF, 0);


//    ESTRUCTURA BÁSICA DEL MAIN
    int main(int argc, char* argv[]){
        if (argc != JAJA){
            perror("Numero de argumentos invalido\n");
            exit(EXIT_FAILURE);
        }

        //Cosas

        exit(EXIT_SUCCESS);
    }


//   SEÑALES
//Función que se invoca para manejar las señales
void manejadorsignal(int signum){
    printf("El valor de la suma es: %d\n", contador);
    kill(0, SIGKILL); //Envía la señal a todos los procesos de su grupo
	exit(EXIT_FAILURE);
}

    struct sigaction sa;
	sa.sa_handler = sa_handler_SIGPIPE;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if(sigaction(13, &sa, NULL)<0){
		perror("Error en sigaction.\n");
		exit(EXIT_FAILURE);
	}

	signal(SIGNAL,FUNCION)


//  CERROJOS

    struct flock cerrojo;
	cerrojo.l_type = F_RDLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;
	if(fcntl(fd, F_SETLK, &cerrojo) < 0){
        perror("Error en fcntl\n");
        exit(EXIT_FAILURE);
	}

	cerrojo.l_type = F_UNLCK;
    if(fcntl(fd, F_SETLK, &cerrojo) < 0){
        perror("Error en fcntl\n");
        exit(EXIT_FAILURE);
	}


//  RECORRER DIRECTORIO

//Macro para comprobar los permisos. Tener permisos de ejecución para grupos y otros equivale a tener los permisos 011
#define criterio(mode) (((mode) & 011) == 011)


void recorrerDir(char *path, int *n, int *tam) {

	struct stat atributos;
	DIR *direct;
	struct dirent *dir;
	char nombre[256];

	direct = opendir(path);

	if(direct == NULL) {
		printf("Error al abrir el directorio\n");
		exit(-1);
	}

	dir = readdir(direct);

	while(dir != NULL) {
		//Comprobamos que la entrada que vamos a leer del directorio, no es ni el propio directorio ni el directorio padre
		if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
			//Guardamos la ruta de la entrada
			sprintf(nombre,"%s/%s",path,dir->d_name);
			//Guardamos los atributos de la entrada
			if(stat(nombre, &atributos) < 0) {
				printf("\nError al acceder a los atributos de %s\n", nombre);
				exit(-1);
			}

			//Si es un archivo y tiene los permisos, incrementamos el contador y sumamos su tamaño a la variable que lleva el tamaño
			if(S_ISREG(atributos.st_mode) && criterio(atributos.st_mode)) {
				//Imprimos el nombre del archivo y su número de inodo
				printf("%s %ld \n\n", nombre, atributos.st_ino);
				(*n)++;
				//El tamaño del archivo se encuentra almacenadi en su estructura stat atributos, en el campo st_size
				(*tam) += (int) atributos.st_size;
			}
			//Si no es regular, miramos si es directorio para llamar de nuevo la función. Sino, no hacemos nada más
			else if(S_ISDIR(atributos.st_mode)) {
				//LLamamos de nuevo a la función recursivamente
				recorrerDir(nombre,n,tam);
			}
		}

		//Leemos la siguiente entrada para la próxima iteracción
		dir = readdir(direct);
		}

	closedir(direct);
}


//  COMPROBAR SI ES REGULAR Y PERMISOS

if(S_ISREG(atributos.st_mode) && (((atributos.st_mode) & 011) == 011)) {
				// Cosas
}


//  PROYECTAR EN MEMORIA

            memoria = (char *)mmap(0, atributos.st_size, PROT_READ, MAP_SHARED, fdarch, 0);
			if(memoria == MAP_FAILED){
				perror("Error al proyectar\n");
				exit(EXIT_FAILURE);
			}

			close(fdarch);

			printf("%s:\n\n%s\n\n", archivo, memoria);
			if(munmap(memoria, atributos.st_size)<0){
				perror("Error al liberar proyección.\n");
				exit(EXIT_FAILURE);
			}


//  ESCRIBIR LEER DE FIFO CON HIJOS

//Creo FIFO
	umask(0);
	mkfifo("ARCHFIFO", 0666);

	if((fd = open("ARCHFIFO", O_WRONLY, 0666))<0){
			perror("Error en open\n");
			exit(EXIT_FAILURE);
		}
    if(write(fd, lectura->d_name, strlen(lectura->d_name)+1)<strlen(lectura->d_name)+1){
					perror("Error en write");
					exit(EXIT_FAILURE);
				}
    if((fd = open("ARCHFIFO", O_RDONLY, 0666))<0){
			perror("Error en open\n");
			exit(EXIT_FAILURE);
		}

    while(read(fd, &ch, sizeof(char))>0){
        archivo[0]=ch;
			int i=1;

			//Leemos nombre de archivp
			while(ch != '\0' && read(fd, &ch, sizeof(char))>0){
				archivo[i]=ch;
				i++;
			}
    }

    close(fd);
    unlink("ARCHFIFO");



//  ESCRIBIR LEER DE PIPE CON HIJOS

//Análogo a FIFO con fd[0] para lectura y fd[1] para escritura.


//  DUP Y DUP2

if(dup2(fd[1],STDOUT_FILENO) < 0){
    perror("Error en dup2\n");
    exit(EXIT_FAILURE);
}
