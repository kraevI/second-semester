#include <iostream>
#include <cmath>

bool is_a_prime_number(int x) {
	bool R = 1;
	for (int i = 2; i <= x / 2; i++) {
		if (x % i == 0) {
			R = 0;
			break;
		}
	}
	return R;
}

bool is_a_palindrome(int &x) {
	int a;
	int y = x * 10;
	a = x % 10;
	while (x != 0) {
		x = x / 10;
		a = a * 10 + x % 10;
	}
	return y == a;
}

void checking_the_set_for_prime_and_palindrome(int n) {
	for (int i = 1; i <= n; i++) {
		int ai;
		using std::cout;
		std::cin >> ai;
		cout << is_a_prime_number(ai) << "\n";
		cout << is_a_palindrome(ai) << "\n";
	}
}

/*bool is_the_sequence_correct(int n) {
	char a, char b, bool R = 1;
	std::cin >> a;
	for (int i = 1; i <= n - 1; i++) {
		std::cin >> b;
		if (a == b) {
			R = 0;
			break;
		}
		a = b;
	}
	return R;
}*/

/*int upper_bound(int &x) {
	int i = 1;
	while (i > 0) {
		if (x / pow(10, i) == 0) return i;
		i++;
	}
}*/

void coup(int &x) {
	int a = 0;
	while (x > 0) {
		a = 10 * a + x % 10;
		x = x / 10;
	}
	x = a;
}

int main(){
	int n;
	std::cin >> n;

    //checking_the_set_for_prime_and_palindrome(n);

	//std::cout << is_the_sequence_correct(n);

	/*coup(n);
	std::cout << n;*/
}
