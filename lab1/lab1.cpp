#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

// 1. Создание массива размера vertical_size x horizontal_size x 2, заполнение нулями. Функция вывода таблицы.
const int vertical_size = 12;
const int horizontal_size = 15;
int crystal[vertical_size][horizontal_size][3] = { 0 };

void crystal_output() {
    for (int i = 0; i < vertical_size; ++i) {
        for (int j = 0; j < horizontal_size; ++j)
            std::cout << crystal[i][j][0] << " " << crystal[i][j][1] << "\t";
        std::cout << "\n";
    }
    std::cout << "\n";
}

// 2. Заполнение нужного процента от всех ячеек элементами вида [1, 1, 0], что значит [дислокация, активна, ещё не сдвигалась на этом шаге].
const unsigned int percentage_of_dislocation = 5;
unsigned int real_percentage = 0;
void initial_filling_of_the_crystal(const unsigned int &percentage, unsigned int &real_percentage) {
    for (int i = 0; i < vertical_size; ++i)
        for (int j = 0; j < horizontal_size; ++j) {
            unsigned int indicator = 1 + rand() % (100 - 1 + 1);
            if (indicator <= percentage) {
                real_percentage += 1;
                crystal[i][j][0] = { 1 };
                crystal[i][j][1] = { 1 };
                crystal[i][j][2] = { 0 };
            }
        }
    std::cout << "Real percentage: " << real_percentage * 100 / (vertical_size * horizontal_size) << "\n";
}

// 3. Функция, со счётчиком активных дислокаций, проверяющяя соседние клетки.
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

// 4. Функция, передвигающая в сторону по параметру, если место не занято.
void move() {
    for (int i = 0; i < vertical_size; ++i)
        for (int j = 0; j < horizontal_size; ++j)
            if (crystal[i][j][1] == 1 && crystal[i][j][2] == 0) {
                unsigned int direction = 1 + rand() % (4 - 1 + 1);
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
                else {
                    std::swap(crystal[i][j], crystal[i][j - 1]);
                    crystal[i][j - 1][2] = { 1 };
                }
            }
    for (int i = 0; i < vertical_size; ++i)
        for (int j = 0; j < horizontal_size; ++j) crystal[i][j][2] = 0;
}

// 5. Главная часть.
int main() {

    srand(time(NULL));
    
    std::cout << "Empty crystal:" << "\n";
    crystal_output();
    std::cout << "Initial filling. ";
    initial_filling_of_the_crystal(percentage_of_dislocation, real_percentage);
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
    std::ofstream stat_out("task2_stat.txt", std::ios_base::app);
    stat_out << "Crystal size: " << vertical_size << " * " << horizontal_size << " ; ";
    stat_out << "real percentage: " << real_percentage * 100 / (vertical_size * horizontal_size) << " ; ";
    stat_out << "total number of steps: " << step_number << "\n";
    stat_out.close();

    return 0;
}