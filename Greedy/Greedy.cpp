#include <iostream>
#include <algorithm>
using namespace std;

//A
/*int main()
{
    int size, number;
    cin >> size >> number;
    int* list = new int[number];

    for (int i = 0; i < number; i++) {
        cin >> list[i];
    }

    sort(list, list + number);

    int sum = 0;
    int answer = 0;

    for (int i = 0; i < number; i++) {
        if (sum + list[i] <= size) {
            answer += 1;
            sum += list[i];
        }
        else break;
    }

    cout << answer;

    return 0;
}*/

//B
/*int main() {
    int distance, range_of_travel, number_of_gas_stations;
    cin >> distance;
    cin >> range_of_travel;
    cin >> number_of_gas_stations;

    int* map = new int[number_of_gas_stations + 2];
    map[0] = 0;
    for (int i = 1; i < number_of_gas_stations + 1; i++) {
        cin >> map[i];
    }
    map[number_of_gas_stations + 1] = distance;

    int A = 0, old_A = 0, answer = 0, maximum = 0;

    while (A != distance) {
        for (int i = 0; i < number_of_gas_stations + 2; i++) {
            if (map[i] - A <= range_of_travel) maximum = i;
        }
        A = map[maximum];
        if (A == old_A) {
            answer = 0;
            A = distance;
        }
        else {
            old_A = A;
            answer += 1;
        }
    }

    cout << answer - 1;

    return 0;
}*/

//C
/*int main() {
    int number;
    cin >> number;
    int** list = new int*[number];
    for (int i = 0; i < number; i++) {
        list[i] = new int[2];
    }

    for (int i = 0; i < number; i++) {
        cin >> list[i][0] >> list[i][1];
    }

    int answer = 0;
    int l = 1;
    for (int i = 0; i < number; i++) {
        if (list[i][0] >= l) {
            answer += 1;
            l = list[i][1];
        }
    }

    cout << answer;

    return 0;
}*/

//D
/*long long gcd(long long a,long long b) {
    if ((a == 0) || (b == 0)) return int(max(a, b));
    else {
        if (a > b) return gcd(a % b, b);
        return gcd(a, b % a);
    }
}

struct denom_array_t {
    int* array; 
    int size;
};

struct denom_array_t egyptian_fractions(int a, int b) {
    int* array = new int[30];
    long long int x = a, y = b, h;
    int size = 1;
    int g = gcd(x, y);
    if (g != 1) {
        x = x / g;
        y = y / g;
    }
    while (x != 1) {
        cout << 1 << " " << (y + x - 1) / x << "\n";
        h = x;
        x = ((-y) % x + x) % x;
        y = y * ((y + h - 1) / h);
        int g = gcd(x, y);
        if (g != 0) {
            x = x / g;
            y = y / g;
        }
        size += 1;
    }
    cout << 1 << " " << y << "\n";  
    denom_array_t answer;
    answer.array = array;
    answer.size = size;
    return answer;
}

int main() {
    long long int x, y;
    cin >> x >> y;
    
    denom_array_t answer = egyptian_fractions(x, y);
    cout << answer.array << " " << answer.size;

    return 0;
}*/