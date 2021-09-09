#pragma once
#include<cmath>
#include<iostream>

const double PI = 2 * acos(0.0);

using std::cout;
using std::cin;
using std::endl;

class complex {
public:
	double re, im, r, theta;

	//constructor
	complex() {
		re = im = r = theta = 0;
	};
	complex(double a, double b = 0, int mode = 0) {
		if (mode == 0) {
			re = a;
			im = b;
			set1();
		}
		else if (1) {
			r = a;
			theta = b;
			set2();
		}
	};
	complex(const complex &c) {
		re = c.re;
		im = c.im;
		set1();
	}

	void show(int mode = 0) {
		if (mode == 0)
			cout << (std::abs(re) > MyPrecision ? re : 0) << std::showpos << (std::abs(im) > MyPrecision ? im : 0) << 'i' << std::noshowpos;
		else
			cout << r << " * exp{ i * " << theta << " }";
	}

	//overload
	complex operator=(const complex &c) {
		re = c.re;
		im = c.im;
		set1();
		return *this;
	};
	complex operator+(const complex &c) const {
		return complex(re + c.re, im + c.im);
	};
	complex operator-(const complex &c) const {
		return complex(re - c.re, im - c.im);
	};
	complex operator*(const complex &c) const {
		return complex(re * c.re - im * c.im, re * c.im + im * c.re);
	};
	complex pow(const double &n) const {
		return complex(r, n * theta, 1);
	}
	complex operator/(const double &c) const {
		return complex(re / c, im / c);
	};

	//friend
	friend std::ostream& operator<<(std::ostream& os, const complex &a);

private:
	const double MyPrecision = 1e-6;
	void set1() {
		r = std::sqrt(re * re + im * im);
		theta = std::atan(im / re);
	}
	void set2() {
		re = r * std::cos(theta);
		im = r * std::sin(theta);
	}
};

std::ostream& operator<<(std::ostream& os, complex &a) {
	a.show();
	return os;
}
