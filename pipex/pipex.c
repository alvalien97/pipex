#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd;
    int stdout_copy;
    pid_t pid;

    char *args[3];

    args[0] = "ls";   // El nombre del programa a ejecutar
    args[1] = "-l";   // El argumento que se pasa al comando ls (listar en formato largo)
    args[2] = NULL;   // El arreglo de argumentos debe terminar con NULL

// Guardar el descriptor del stdout original
    stdout_copy = dup(STDOUT_FILENO);

// Abrir el archivo 'example.txt' en modo escritura, creando el archivo si no existe
    fd = open("example.txt", O_WRONLY | O_CREAT, 0644);

// Comprobar apertura del archivo
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }

// Redirigir la salida estándar (stdout) al descriptor de archivo de 'example.txt'
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("Error al redirigir stdout");
        close(fd);
        return 1;
    }

// Imprimir al archivo, que va a 'example.txt' ahora
    printf("This is printed in example.txt!\n");
// asegura que cualquier contenido pendiente del buffer de stdout se vacíe y se escriba 
// en el archivo o terminal, dependiendo de si se ha redirigido o no la salida estándar
    fflush(stdout);

// Restaurar la salida estándar a la terminal
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdout_copy);

// Cerrar el descriptor de archivo de 'example.txt' después de la impresión
    close(fd);

 // Ahora esta información se imprimirá en la terminal
    printf("Información que se muestra en la terminal:\n");

// Verificar permisos del archivo 'example.txt'
    if (access("example.txt", R_OK) != -1)
        printf("Tengo permiso de lectura\n");
    else
        printf("No tengo permiso de lectura\n");

    if (access("example.txt", W_OK) != -1)
        printf("Tengo permiso de escritura\n");
    else
        printf("No tengo permiso de escritura\n");

    if (access("example.txt", X_OK) != -1)
        printf("Tengo permiso de ejecución\n");
    else
        printf("No tengo permiso de ejecución\n");

    if (access("example.txt", F_OK) != -1)
        printf("El archivo existe\n");
    else
        printf("El archivo no existe\n");

    fflush(stdout);

    printf("\nFORK:\n");
//Aqui dulico el pid que declare con un fork asi que ya tengo un padre y un hijo
    pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
//Esto se va imprimir 2 veces porque se ejecuta una vez para e proceso hijo y
//otra para el padre ya que el al duplicarlo el programa se ejecuta en dos espacios
//de memoria distintos.
	if (pid == 0)
		printf("This is the child process. (pid: %d)\n\n", getpid());
	else
		printf("This is the parent process. (pid: %d)\n", getpid());

    fflush(stdout);

    // Llamada a execve() para ejecutar el comando 'ls -l'
    if (execve("/bin/ls", args, NULL) == -1)
        perror("Error al ejecutar execve");

        printf("Ya se ha ejecutado exceve perrón\n");

    fflush(stdout);

    return (0);
}
