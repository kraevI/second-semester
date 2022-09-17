#include <iostream>

//одна точка выхода, править

const unsigned int arraysize = 42;
int array[arraysize];

int linear_search(int n, int array[], int &counter) {
    for (int i = 0; i < arraysize; i++) {
        if (array[i] == n) {
            return i;
        }
        if (i == arraysize - 1) return -1;
        counter = counter + 1;
    }

}

int binary_search(int n, int array[], int &counter) {
    bool flag = false;
    int l = 0;
    int r = arraysize-1;
    int mid;

    while ((l <= r) && (flag != true)) {
        mid = (l + r) / 2;

        if (array[mid] == n) flag = true;
        if (array[mid] > n) r = mid - 1;
        else l = mid + 1;
        counter = counter + 1;
    }

    if (flag) return mid;
    else return -1;
}

int main() {
    for (int i = 0; i < arraysize; i++) {
        array[i] = i;
        std::cout << array[i] << " ";
    }
    std::cout << "\n";

    int n; int counter1 = 1; int counter2 = 1;
    std::cin >> n;

    std::cout << "linear search: number " << linear_search(n, array, counter1) << " steps " << counter1 << "\n";
    std::cout << "binare search: number " << binary_search(n, array, counter2) << " steps " << counter2;
}