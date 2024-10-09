#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define N 6

int main(int argc, char** argv) {
    int rank, size;
    char vector[N][100];
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 3) {
        if (rank == 0) {
            printf("Este programa necesita exactamente 3 procesadores.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        strcpy(vector[0], "cadena_0");
        strcpy(vector[1], "cadena_1");
        strcpy(vector[2], "cadena_2");
        strcpy(vector[3], "cadena_3");
        strcpy(vector[4], "cadena_4");
        strcpy(vector[5], "cadena_5");

        MPI_Send(vector, N * 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vector, N * 100, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
    }

    if (rank == 1) {
        MPI_Recv(vector, N * 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Procesador 1 - posiciones pares:\n");
        for (i = 0; i < N; i += 2) {
            printf("%s\n", vector[i]);
        }
    }

    if (rank == 2) {
        MPI_Recv(vector, N * 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Procesador 2 - posiciones impares:\n");
        for (i = 1; i < N; i += 2) {
            printf("%s\n", vector[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
