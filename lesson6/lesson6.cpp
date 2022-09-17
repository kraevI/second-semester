#include <iostream>
#include <iomanip>
#include <cmath>

double const pi = 3.1415926535897932384626433832795028841971;

using namespace std;

float naive_mean(float psi[], float pdf[], float dv, unsigned int size) {
	float sum = 0.f;
	for (unsigned idx = 0; idx < size; idx++)
		sum += psi[idx] * pdf[idx];
	return dv * sum;
}

float rec_sum(float f[], unsigned int size) {
	if (size > 1) {
		float* f_1 = new float[size / 2];
		float* f_2 = new float[size - size / 2];
		for (unsigned i = 0; i < size; i++) {
			if (i < size / 2) {
				f_1[i] = f[i];
			}
			else {
				f_2[i - size / 2] = f[i];
			}
		}
		float sum = rec_sum(f_1, size / 2) + rec_sum(f_2, size - size / 2);
		delete[] f_1;
		delete[] f_2;
		return sum;
	}
	else {
		return f[0];
	}
}

float mean_rec(float psi[], float pdf[], float dv, unsigned int size) {
	float* f = new float[size];
	for (unsigned i = 0; i < size; i++) {
		f[i] = psi[i] * pdf[i];
	}
	float sum = rec_sum(f, size);
	delete[] f;
	return sum * dv;
}

float neighbour_mean(float psi[], float pdf[], float dv, unsigned int size) {
	float* f = new float[size];
	for (unsigned i = 0; i < size; i++)
		f[i] = psi[i] * pdf[i];

	for (unsigned int k = 2; unsigned int(k / 2) < size; k = k * 2) {
		unsigned i = 0;
		while (i < size) {
			if (i + k / 2 < size)
				f[i] += f[i + k / 2];
			i += k;
		}
	}

	float s = f[0] * dv;
	delete[] f;
	return s;
}

float mean_kahan(float psi[], float pdf[], float dv, unsigned int size) {
	float sum = 0, c = 0;
	float* f = new float[size];
	for (unsigned i = 0; i < size; i++)
		f[i] = psi[i] * pdf[i];

	for (unsigned i = 0; i < size; i++) {
		float y = f[i] - c;
		float z = sum + y;
		c = (z - sum) - y;
		sum = z;
	}

	delete[] f;
	return sum * dv;
}

/*void split(double x, double& x_h, double& x_l) {
	double c = static_cast<double>((1ul << 11) + 1ul);
	x_h = (c * x) + (x - (c * x));
	x_l = x - x_h;
}*/

/*void fused_multiply_add(double a, double b, double& s, double& t) {
	double a_high, a_low, b_high, b_low;
	split(a, a_high, a_low);
	split(b, b_high, b_low);
	s = a * b;
	t = -s + a_high * b_high;
	t += a_high * b_low;
	t += a_low * b_high;
	t += a_low * b_low;

	std::cout << t;
}

float mean_with_fma(float psi[], float pdf[], float dv, unsigned size) {
	double mpl, t;
	float sum = 0, c = 0;
	float* f = new float[size];
	for (unsigned i = 0; i < size; i++) {
		fused_multiply_add(psi[i], pdf[i], mpl, t);
		f[i] = mpl;
		c += t;
	}

	for (int i = 0; i < size; i++) {
		float y = f[i] - c;
		float z = sum + y;
		c = (z - sum) - y;
		sum = z;
	}

	delete[] f;
	return sum * dv;
}*/

double mean_with_double(double psi[], double pdf[], double dv, unsigned int size) {
	double sum = 0.l;
	for (unsigned idx = 0; idx < size; idx++)
		sum += psi[idx] * pdf[idx];
	return dv * sum;
}

int main() {
	fmaf();
	for (double T = 0.00001; T < 100; T *= 10) {
		unsigned int n = 10000000;
		float* psi = new float[n];
		float* pdf = new float[n];
		float  dv = 0.00001, limit = n * dv / 2;
		for (int i = 0; i < n; i++) { // 1/np.sqrt(T*np.pi) * exp(-x**2/T)
			pdf[i] = exp(-(i * dv - limit) * (i * dv - limit) / T) / (sqrt(T * pi));
			psi[i] = abs(i * dv - limit);
		}

		double* psi_d = new double[n];
		double* pdf_d = new double[n];
		double T_d = T, dv_d = dv, limit_d = n * dv_d / 2;
		for (int i = 0; i < n; i++) {
			pdf_d[i] = exp(-(i * dv_d - limit_d) * (i * dv_d - limit_d) / T) / (sqrt(T * pi));
			psi_d[i] = abs(i * dv_d - limit_d);
		}

		cout << "T = " << T << endl;
		cout << setprecision(8) << scientific; //у float точность порядка 8 значащих десятичных цифр после запятой
		cout << "naive sum:     " << naive_mean(psi, pdf, dv, n) << endl;
		cout << "reccurent sum: " << mean_rec(psi, pdf, dv, n) << endl;
		cout << "neighbour sum: " << neighbour_mean(psi, pdf, dv, n) << endl;
		cout << "Kahan sum:     " << mean_kahan(psi, pdf, dv, n) << endl;
		//cout << "sum with fma:  " << mean_with_fma(psi, pdf, dv, n) << endl;
		cout << "double:        " << mean_with_double(psi_d, pdf_d, dv_d, n) << endl;

		cout << setprecision(16);//у double точность порядка 16 значащих десятичных цифр после запятой
		cout << "real mean:     " << (sqrt(T / pi)) << endl << endl;
		delete[] psi;
		delete[] pdf;
		delete[] psi_d;
		delete[] pdf_d;
	}
	return 0;
}