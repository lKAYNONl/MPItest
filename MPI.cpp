// MPI.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "mpi.h"
#include <iostream>

int main(int argc, char** argv)
{
    const int MAX = 20;
    int rank, size;
    int n, ibeg, iend;

    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    n = (MAX - 1) / size + 1;
    ibeg = rank * n + 1;
    iend = (rank + 1) * n;
    for (int i = ibeg; i <= ((iend > MAX) ? MAX : iend); i++)
    {
        printf("Process: %d, %d^2=%d\n", rank, i, i * i);
    }

    //// Размер массива
    //const int N = 15;
    //// Массив с элементами
    //int data[N];
    //// Заполняем массив случайными числами
    //for (int i = 0; i < N; i++)
    //{
    //    data[i] = -10 + rand() % ((10 + 1) +10);;
    //    printf("Process: %d\n",data[i]);

    //}
    //    

    //// Произведение отрицательных элементов
    //int local_product = 1;
    //// Разбиваем массив на части и распределяем по процессам
    //for (int i = rank; i < N; i += size)
    //    if (data[i] < 0)
    //    {
    //        local_product *= data[i];
    //        printf("Process: %d, *%d=%d\n", rank, data[i], local_product);
    //    
    //    }
    //        

    //// Собираем результаты от всех процессов
    //int global_product;
    //MPI_Reduce(&local_product, &global_product, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    //if (rank == 0)
    //    std::cout << "Global product: " << global_product << std::endl;

    MPI_Finalize();
    return 0;
}


//int main(int argc, char** argv)
//{
//	const int MAX = 200;
//	int rank, size;
//	int n, ibeg, iend;
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	n = (MAX - 1) / size + 1;
//	ibeg = rank * n + 1;
//	iend = (rank + 1) * n;
//	for (int i = ibeg; i <= ((iend > MAX) ? MAX : iend); i++)
//	{
//		printf("Process: %d, %d^2=%d\n", rank, i, i * i);
//	}
//
//	MPI_Finalize();
//
//	return 0;
//}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
