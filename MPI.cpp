#include <iostream>
#include <fstream>
#include <mpi.h>
#include <string>


int main(int argc, char* argv[]) {
    // инициализация MPI
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // считываем размер массива N с клавиатуры или из файла
    int N;
    if (rank == 0) {
        std::cout << "Enter the size of the array: ";
        std::cin >> N;
        // в этом случае мы считываем N с клавиатуры
        // но можно также считывать N из файла, например:
        // std::ifstream fin("input.txt");
        // fin >> N;
    }

    // рассылаем размер массива всем процессам
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // выделяем память под массив
    int* arr = new int[N];

    // считываем массив с клавиатуры или из файла
    for (int i = 0; i < N; i++)
        arr[i] = -5 + rand() % ((5 + 1) + 5 );;

    // рассылаем массив всем процессам
    MPI_Bcast(arr, N, MPI_INT, 0, MPI_COMM_WORLD);
    // разбиваем массив на части для каждого процесса
    int local_size = N / size;
    int* local_arr = new int[local_size];
    MPI_Scatter(arr, local_size, MPI_INT, local_arr, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // вычисляем результат для каждого процесса
    int local_result = 1;
    for (int i = 0; i < local_size; i++) {
        if (local_arr[i] < 0) {
            local_result *= local_arr[i];
        }
    }

    // собираем результаты всех процессов
    int global_result;
    MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
        // сохраняем результаты вычислений в файл
        std::ofstream fout;
    fout.open(std::to_string(rank) + ".txt");
    fout << "Process number: " << rank << std::endl;
    fout << "Data size: " << local_size << std::endl;
    fout << "Data: ";
    for (int i = 0; i < local_size; i++) {
        fout << local_arr[i] << " ";
    }
    fout << std::endl;
    fout << "Result: " << local_result << std::endl;
    fout.close();

    // главный процесс сохраняет общий результат вычислений
    if (rank == 0) {
        std::ofstream fout;
        fout.open("result.txt");
        fout << "Processes number: " << size << std::endl;
        fout << "Result: " << global_result << std::endl;
        fout.close();
    }

    // освобождаем память
    delete[] arr;
    delete[] local_arr;

    // завершаем работу MPI
    MPI_Finalize();

    return 0;
}