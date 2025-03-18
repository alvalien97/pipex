#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
	int fd[2]; //Array para los dos extremos de la tuberia lectura y escritura
	pid_t pid; //Variable para almacenar el PID del proceso hijo
	char buffer[13]; //BUFFER para almacenar el mansaje leido
//Empieza el pipe
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork(); //duplico
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) //si es el hijo
	{
		close(fd[0]); // Cerrar el extremo de lectura de la tubería
		write(fd[1], "Hello parent!", 13); // Escribir mensaje en el extremo de escritura
		close(fd[1]); // Cerrar el extremo de escritura
		exit(EXIT_SUCCESS);
	}
	else //si es el padre
	{
        int file = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (file == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(file);

    if (unlink("example.txt") == 0)
        printf("File successfully deleted\n");
    else
        printf("Error deleting file\n");

		close(fd[1]); //Cerrar el extremo de escritura de la tubería
		read(fd[0], buffer, 13); //Leer mensaje desde el extremo de lectura
		close(fd[0]); //Cerrar el extremo de lectura
		printf("Message from child: '%s'\n", buffer); //Imprimir el mensaje recibido
		exit(EXIT_SUCCESS); //esta linea hay que ponerla pero si el programa continua
        //hay que quitarla porque sino termina el programa
	} //el padre lee el mensaje que su hijo escrbio en la tuberia

    //fflush(stdout);

    return (0);
}