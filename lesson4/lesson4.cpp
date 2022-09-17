/*стек, куча, неинициализированная память (статич.), инициализ (глоб перем и тд), текст. стек и куча - динамическая память.
  автоматическая (стек), статическая, куча
  автомат: переменные, которые объявляются внутри блоков (приписка automatic опускается)
  статические существуют все время жизни программы, инициализируются static, определяются один раз, могут быть использованы как счетчики. при объявлении
инициализируются нулями, является глобальной переменной с ограниченной областью видимости
  в куче выделяется память по запросу.
  для вывода адреса ячейки памяти a: cout << &a. для сохранения адреса int *ptr_a = &a - указатель. разыменовывание int val_a = *prt_a. 
  операции с указателями: сложение работает поадресно смещая на число бит ячеек. умножения и деления нет.
  выделение динамической памяти: 
    int a = new int(10);
    delete a;
    array = new char[20];
    delete [] array;
*/

/*Контрольная когда-то. Темы: циклы, функции, массивы, указатели, сортировки.
*/

#include <iostream>
#include <time.h>

int fact(int N)
{
    if (N < 0) // если пользователь ввел отрицательное число
        return 0; // возвращаем ноль
    if (N == 0) // если пользователь ввел ноль,
        return 1; // возвращаем факториал от нуля - не удивляйтесь, но это 1 =)
    else // Во всех остальных случаях
        return N * fact(N - 1); // делаем рекурсию.
}

/* глупая функция, не ломающая программу почему-то, будучи зацикленной
int foo() {
    int b = 5;
    double *array = new double[40];
    std::cout << array << "\n";
    return b;
}
*/

const unsigned int size = 17;
int array[size] = { 0 };


void qsort(int* array, int size) {
    int l = 0;
    int r = size - 1;
    int mid = array[size / 2];

    do {
        while (array[l] < mid) l++;
        while (array[r] > mid) r--;

        if (l <= r) {
            int tmp = array[l];
            array[l] = array[r];
            array[r] = tmp;

            l++;
            r--;
        }
        for (int i = 0; i < size; i++) std::cout << array[i] << " ";
        std::cout << "\n";

    } while (l <= r);

    if (r > 0) qsort(array, r + 1);
    if (l < size) qsort(&array[l], size - l);
}

void FixHeap(int* array, unsigned int root,unsigned int key,unsigned int bound) {
    //*list - ссылка на первый элемент массива, root - номер корня пирамиды, key - ключ, bound - правая граница
    //здесь и в следующей функции везде в обращении к элементам массива прописано -1 к индексу - это адаптация к нумерации массива с нулевого элемента
    int vacant = root;
    while (2 * vacant <= bound) {
        unsigned int largerChild = 2 * vacant;
        if ((largerChild < bound) && (array[largerChild + 1 - 1] > array[largerChild - 1])) largerChild = largerChild + 1;

        if (key > array[largerChild - 1]) break;
        else {
            array[vacant - 1] = array[largerChild - 1];
            vacant = largerChild;
        }
    }
    array[vacant - 1] = key;
}

void HeapSort(int* array, int size) {
    for (unsigned int i = size / 2; i >= 1; i--) FixHeap(array, i, array[i - 1], size);
    for (unsigned int i = size; i >= 2; i--) {
        unsigned int max = array[1 - 1];
        FixHeap(array, 1, array[i - 1], i - 1);
        array[i - 1] = max;
    }
    for (int i = 0; i < size; i++) std::cout << array[i] << " ";
    std::cout << "\n";
}




int main() {

    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = 1 + rand() % (20 - 1 + 1);
        std::cout << array[i] << " ";
    }

    std::cout << "\n";

    qsort(array, size);

    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }

    //HeapSort(array, size);

    return 0;
}

