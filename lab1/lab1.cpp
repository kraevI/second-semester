#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

// Задание параметров кристалла. Создание массива размера vertical_size x horizontal_size x 3, заполнение нулями. Функция вывода таблицы.
const unsigned int vertical_size = 12;
const unsigned int horizontal_size = 15;
int crystal[vertical_size][horizontal_size][3] = { 0 };

void crystal_output() {
    for (int i = 0; i < vertical_size; ++i) {
        for (int j = 0; j < horizontal_size; ++j)
            std::cout << crystal[i][j][0] << " " << crystal[i][j][1] << "\t";
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Функция заполнения нужного процента от всех ячеек элементами вида [1, 1, 0], что значит [дислокация, активна, ещё не сдвигалась на этом шаге].
const unsigned int percentage_of_dislocation = 20;
void initial_filling_of_the_crystal(const unsigned int &percentage) {
    unsigned int counter = 0;
    while (counter < percentage * (vertical_size * horizontal_size) / 100) {
        unsigned int i = 0 + rand() % (vertical_size - 1 - 0 + 1);
        unsigned int j = 0 + rand() % (horizontal_size - 1 - 0 + 1);
        if (crystal[i][j][0] != 1) {
            crystal[i][j][0] = { 1 };
            crystal[i][j][1] = { 1 };
            crystal[i][j][2] = { 0 };
            counter += 1;
        }
    }

    std::cout << "Real percentage: " << percentage << "\n";
}

void initial_filling_of_the_crystal() {
    unsigned int i = 0 + rand() % (vertical_size - 1 - 0 + 1);
    unsigned int j = 0 + rand() % (horizontal_size - 1 - 0 + 1);
    crystal[i][j][0] = { 1 };
    crystal[i][j][1] = { 1 };
    crystal[i][j][2] = { 0 };
}

// Функция, со счётчиком активных дислокаций, проверяющяя соседние клетки.
int checking_neighbors() {
    unsigned int counter = 0;
    for (int i = 0; i < vertical_size; ++i)
        for (int j = 0; j < horizontal_size; ++j) 
            if (crystal[i][j][1] == 1) {
                if (i == 0 || i == vertical_size - 1 || j == 0 || j == horizontal_size - 1) {
                    crystal[i][j][1] = 0;
                }
                else if (crystal[i + 1][j][0] == 1 || crystal[i - 1][j][0] == 1 || crystal[i][j + 1][0] == 1 || crystal[i][j - 1][0] == 1) {
                    crystal[i][j][1] = 0;
                }
                else counter += 1;
            }
    return counter;
}

int checking_neighbors_for_limiting_case() {
    unsigned int counter = 0;
    for (int i = 0; i < vertical_size; ++i)
        for (int j = 0; j < horizontal_size; ++j)
            if (crystal[i][j][1] == 1) {
                if (j == 0 || j == horizontal_size - 1) {
                    crystal[i][j][1] = 0;
                }
                else if (crystal[i][j + 1][0] == 1 || crystal[i][j - 1][0] == 1) {
                    crystal[i][j][1] = 0;
                }
                else counter += 1;
            }
    return counter;
}

// Функция, передвигающая в сторону по параметру, если место не занято.
void move() {
    for (int i = 0; i < vertical_size; ++i)
        for (int j = 0; j < horizontal_size; ++j)
            if (crystal[i][j][1] == 1 && crystal[i][j][2] == 0) {
                unsigned int direction = 1 + rand() % (5 - 1 + 1);
                if (direction == 1) {
                    std::swap(crystal[i][j], crystal[i - 1][j]);
                    crystal[i - 1][j][2] = { 1 };
                }
                else if (direction == 2) {
                    std::swap(crystal[i][j], crystal[i][j + 1]);
                    crystal[i][j + 1][2] = { 1 };
                }
                else if (direction == 3) {
                    std::swap(crystal[i][j], crystal[i + 1][j]);
                    crystal[i + 1][j][2] = { 1 };
                }
                else if (direction == 4) {
                    std::swap(crystal[i][j], crystal[i][j - 1]);
                    crystal[i][j - 1][2] = { 1 };
                }
                else crystal[i][j][2] = { 1 };
            }
    for (int i = 0; i < vertical_size; ++i)
        for (int j = 0; j < horizontal_size; ++j) crystal[i][j][2] = 0;
}

void move_for_limiting_case() {
    for (int i = 0; i < vertical_size; ++i)
        for (int j = 0; j < horizontal_size; ++j)
            if (crystal[i][j][1] == 1 && crystal[i][j][2] == 0) {
                unsigned int direction = 1 + rand() % (3 - 1 + 1);
                if (direction == 1) {
                    std::swap(crystal[i][j], crystal[i][j + 1]);
                    crystal[i][j + 1][2] = { 1 };
                }
                else if (direction == 2) {
                    std::swap(crystal[i][j], crystal[i][j - 1]);
                    crystal[i][j - 1][2] = { 1 };
                }
                else crystal[i][j][2] = 1;
            }
    for (int i = 0; i < vertical_size; ++i)
        for (int j = 0; j < horizontal_size; ++j) crystal[i][j][2] = 0;
}

// Функция, проводящая один эксперимент.
void one_full_run(const unsigned int &percentage_of_dislocation) {

    // Первоначальное заполнение кристалла.
    std::cout << "Empty crystal:" << "\n";
    crystal_output();
    std::cout << "Initial filling. ";
    initial_filling_of_the_crystal(percentage_of_dislocation);
    std::cout << "Crystal:" << "\n";
    crystal_output();

    unsigned int flag = checking_neighbors();
    unsigned int step_number = 0;
    while (flag > 0) {
        std::cout << "Step number: " << step_number << "  Active dislocations: " << flag << "\n";
        std::cout << "Crystal after freezing:" << "\n";
        crystal_output();
        move();
        std::cout << "Crystal after moving:" << "\n";
        crystal_output();
        flag = checking_neighbors();
        step_number += 1;
    }

    std::cout << "All dislocations are stationary. Total number of steps: " << step_number << "\n";
    crystal_output();

    //Вывод в файл информации о запуске.
    std::ofstream stat_out("task3_B_stat.txt", std::ios_base::app);
    stat_out << "Crystal size: " << vertical_size << " * " << horizontal_size << " ; ";
    stat_out << "percentage: " << percentage_of_dislocation << " ; ";
    stat_out << "total number of steps: " << step_number << "\n";
    stat_out.close();
}


int main() {

    srand(time(NULL));

    for (int i = 1; i <= 1; i++) {
        one_full_run(percentage_of_dislocation);
        for (int i = 0; i < vertical_size; ++i)
            for (int j = 0; j < horizontal_size; ++j) {
                crystal[i][j][0] = { 0 };
                crystal[i][j][1] = { 0 };
                crystal[i][j][2] = { 0 };
            }
    }

    return 0;
}