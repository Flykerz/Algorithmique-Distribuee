//La commande MPI_Wtime() renvoie un nombre de type double contenant le temps en
//        secondes qui s'est écoulé depuis un instant xe (mais, sans autre information, arbitraire).
//Utilisez cette commande pour mesurer le nombre de secondes qui s'est écoulé entre la n de
//MPI_Init et MPI_Finalize pour chacun des processus. Achez cette durée juste avant l'appel
//de MPI_Finalize.
//Compilez et lancez votre programme avec 4 processus.
//An d'envoyer ou de recevoir des messages d'un processus à l'autre, on utilisera les commandes MPI_Send et MPI_Recv :
//MPI_Send(buffer,k,MPI_Type,destination_id,balise,MPI_COMM_WORLD);
//Ici, buffer est un pointeur sur les données à envoyer, k est le nombre de données envoyées,
//MPI_Type est le type des données envoyées (pour des nombres entiers, MPI_INT, pour des
//nombres de type double, MPI_DOUBLE, ...). En outre, l'entier destination_id est l'identi-
//cateur du processus auquel les données doivent être envoyées et l'entier balise permet de
//diérentier diérents types de messages.
//MPI_Recv(buffer,k,MPI_Type,origine_id,balise,MPI_COMM_WORLD,&status);
//Ici, les trois premiers arguments et le quatrième sont de même type que pour la commande précédente. L'entier origine_id est l'identicateur du processus duquel les données sont reçues.
//L'argument status de type MPI_Status permet au système de donner des détails supplémentaires sur le message reçu.

//mpicc -Wall Exercice2.c -o Exercice2
//mpirun -np 4 ./Exercice2

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    double start_time, end_time;

    MPI_Init(&argc, &argv); // Initialisation de MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtention de l'identifiant du processus
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtention du nombre total de processus

    start_time = MPI_Wtime(); // Mesure du temps au début de l'exécution

    printf("Hello from process %d of %d\n", rank, size);

    // Exemple d'envoi et de réception de messages entre les processus
    if (rank == 0) {
        int data = 42;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        int received_data;
        MPI_Recv(&received_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data: %d\n", received_data);
    }

    end_time = MPI_Wtime(); // Mesure du temps juste avant MPI_Finalize
    printf("Time elapsed for process %d: %f seconds\n", rank, end_time - start_time);

    MPI_Finalize(); // Finalisation de MPI

    return 0;
}
