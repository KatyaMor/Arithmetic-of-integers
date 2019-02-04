#include "LongNum.h"
#include <iostream>
#include<stdio.h> 
#include<assert.h>
#include <string>
#include <sstream>
#include <cmath>
#include<math.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <complex>
#define n_len 10
#define PI 3.14159265358979323846

using namespace std;
using std::string;

vector<int> LongNum::getLongNum()
{
	return nums;
}

int LongNum::getsize()
{
	return nums.size();
}

LongNum::LongNum()
{
	nums = vector<int>(1, 0);
}

LongNum::LongNum(string s)
{
	while (s.length() != 0)
	{
		nums.push_back(s[s.length() - 1] - '0');
		s.erase(s.length() - 1, s.length());
	}
}

LongNum::LongNum(const long long& n)
{
	long long x1 = n;
	while (x1 != 0) {
		nums.push_back(x1 % 10);
		x1 /= 10;
	}
}

LongNum::LongNum(const LongNum& other)
{
	operator = (other);
}

LongNum::LongNum(vector<int> n)
{
	nums = n;
}

LongNum& LongNum::operator = (const LongNum &other)
{
	nums = other.nums;
	return *this;
}

bool LongNum::operator==(LongNum other)
{
	if (nums.size() != other.nums.size()) return 0;
	else
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == other.nums[i])
				continue;
			else return 0;
		}
	return 1;
}

bool LongNum::operator!=(LongNum other)
{
	return !operator==(other);
}

bool LongNum::operator>=(LongNum other)
{
	return operator>(other) || operator==(other);
}

bool LongNum::operator<(LongNum other)
{
	return !operator>(other) && !operator==(other);
}

bool LongNum::operator<=(LongNum other)
{
	return operator<(other) || operator==(other);
}

bool LongNum::operator>(LongNum other)
{
	if ((*this).nums[(*this).nums.size() - 1] < 0 && (other.nums[other.nums.size() - 1] >= 0)) return 0;
	if ((*this).nums[(*this).nums.size() - 1] >= 0 && (other.nums[other.nums.size() - 1] < 0)) return 1;
	if ((*this).nums.size() > other.nums.size()) return 1;
	if ((*this).nums.size() < other.nums.size()) return 0;
	int i = (*this).nums.size() - 1;
	bool res = 0;
	while (i >= 0 && !res) {
		if ((*this).nums[i] > other.nums[i])
			res = 1;
		if ((*this).nums[i] < other.nums[i]) i = -1;
		i--;
	}
	return res;
}

void LongNum::write() const
{
	for (auto I = nums.end(); I != nums.begin(); )
		cout << *(--I);
}

LongNum LongNum::operator+( LongNum other)
{
	LongNum x = (*this);
	LongNum y = other;
	if (nums[nums.size() - 1] < 0) {
		if (other.nums[other.nums.size() - 1] < 0) {
			x.nums[x.nums.size() - 1] *= -1;
			y.nums[y.nums.size() - 1] *= -1;
			x = x + y;
			x.nums[x.nums.size() - 1] *= -1;
			return x;
		}
		x.nums[x.nums.size() - 1] *= -1;
		return y - x;
	}
	if (y.nums[y.nums.size() - 1] < 0) {
		y.nums[y.nums.size() - 1] *= -1;
		return x - y;
	}

	int n = max((*this).nums.size(), other.nums.size());
	string s;
	int k = 0;
	for (int i = 0; i <= n + 1; ++i)
		s += '0';
	LongNum res(s);
	if (x.nums.size() < y.nums.size())
		while (x.nums.size() != y.nums.size())
			x.nums.push_back(0);
	if (x.nums.size() > y.nums.size())
		while (y.nums.size() != x.nums.size())
			y.nums.push_back(0);

	for (int i = 0; i < n; i++) {
		int t = x.nums[i] + y.nums[i] + k;
		res.nums[i] = t % 10;
		k = t / 10;
	}
	res.nums[n] += k;
	int i = n + 1;
	while (res.nums[i] == 0 && i != 0) {
		res.nums.pop_back();
		i--;
	}

	return res;
}

LongNum LongNum::operator-()
{
	LongNum nw, ol;
	ol = *this;
	nw = ol;
	nw.nums[nw.nums.size() - 1] = -nums[nw.nums.size() - 1];
	return nw;
}

LongNum LongNum::operator-(LongNum other)
{
	LongNum x = (*this);
	LongNum y = other;
	if (y.nums[y.nums.size() - 1] < 0) {
		if (x.nums[x.nums.size() - 1] > 0) {
			y.nums[y.nums.size() - 1] *= -1;
			return x + y;
		}
		y.nums[y.nums.size() - 1] *= -1;
		x.nums[x.nums.size() - 1] *= -1;
		return y - x;
	}
	if (x.nums[x.nums.size() - 1] < 0) {
		x.nums[x.nums.size() - 1] *= -1;
		x = y + x;
		x.nums[x.nums.size() - 1] *= -1;
		return x;
	}
	bool pos = true;

	if (other > (*this)) {
		y = (*this);
		x = other;
		pos = false;
	}

	int n = max((*this).nums.size(), other.nums.size());
	string s;
	int k = 0;
	for (int i = 0; i <= n + 1; ++i)
		s += '0';
	LongNum res(s);

	if (x.nums.size() < y.nums.size())
		while (x.nums.size() != y.nums.size())
			x.nums.push_back(0);
	if (x.nums.size() > y.nums.size())
		while (y.nums.size() != x.nums.size())
			y.nums.push_back(0);
	for (int i = 0; i < y.nums.size(); i++) {
		if (x.nums[i] < y.nums[i]) {
			x.nums[i + 1]--;
			x.nums[i] += 10;
		}
		res.nums[i] = x.nums[i] - y.nums[i];
	}
	int i = n + 1;
	while (res.nums[i] == 0 && i != 0) {
		res.nums.pop_back();
		i--;
	}

	if (pos == false) res.nums[res.nums.size() - 1] *= -1;
	return res;
}

LongNum LongNum::operator*(LongNum other)
{
	int m = max(nums.size(), other.nums.size());
	vector<int> res(m * 2);
	LongNum M2 = (*this), M1 = other;

	if (nums[nums.size() - 1] < 0) M2 = -(*this);
	if (other.nums[other.nums.size() - 1] < 0) M1 = -other;

	vector<int> x1 = M2.getLongNum();
	vector<int> x2 = M1.getLongNum();

	if (x1.size() < x2.size())
	{
		swap(x1, x2);
	}

	for (int i = 0; i < x2.size(); ++i) {
		for (int j = 0; j < x1.size(); ++j) {
			int tmp = 0;
			tmp += res[i + j] + x2[i] * x1[j];
			res[i + j] = tmp % 10;
			res[i + j + 1] += tmp / 10;
		}
	}
	while (res.size() > 1 && res.back() == 0)
		res.pop_back();
	LongNum M(res);
	if ((nums[nums.size() - 1] < 0) || (other.nums[other.nums.size() - 1] < 0)) return -M;
	else return M;
}

LongNum LongNum::operator*(long long x)
{
	int m = nums.size();
	vector<int> a = nums;
	vector<int> res(m);
	int r = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (i == a.size() - 1) {
			res[i] = a[i] * x + r;
			if (res[i] >= 10)
			{
				r = res[i] / 10;
				res[i] = res[i] % 10;
				res.push_back(r);
			}
		}
		else {
			res[i] = a[i] * x + r;
			r = res[i] / 10;
			res[i] = res[i] % 10;
		}
	}
	while (res.size() > 1 && res.back() == 0) res.pop_back();
	return res;
}

LongNum  LongNum::operator/(long long x)
{
	if (x == 0) throw ("division by zero!!!");
	int len = nums.size();
	vector<int> res(len);
	int r = 0;
	for (int i = nums.size() - 1; i >= 0; i--)
	{
		int cur = 10 * r + nums[i];
		res[i] = cur / x;
		r = cur % x;
	}
	while (res.size() > 1 && res.back() == 0) res.pop_back();
	LongNum res1(res);
	return res1;
}

LongNum LongNum::operator/(LongNum other)
{
	if (other == LongNum("0"))
		throw ("division by zero!!!");
	LongNum x = (*this);
	LongNum y = other;

	if (x.nums[x.nums.size() - 1] < 0) {
		if (y.nums[y.nums.size() - 1] < 0) {
			x.nums[x.nums.size() - 1] *= -1;
			y.nums[y.nums.size() - 1] *= -1;
			return x / y;
		}
		x.nums[x.nums.size() - 1] *= -1;
		x = x / y;
		x.nums[x.nums.size() - 1] *= -1;
		return x;
	}
	if (y.nums[y.nums.size() - 1] < 0) {
		y.nums[y.nums.size() - 1] *= -1;
		x = x / y;
		x.nums[x.nums.size() - 1] *= -1;
		return x;
	}

	LongNum res("0"), z("1");
	int k = 0;

	while (!(y > x))
	{
		y = y + y;
		z = z + z;
		++k;
	}
	while (k)
	{
		y = y / 2;
		z = z / 2;
		--k;
		while (!(y > x))
		{
			x = x - y;
			res = res + z;
		}
	}
	return res;
}

LongNum LongNum::operator% (LongNum other)
{
	LongNum a;
	a = (*this);
	LongNum b;
	b = other;
	LongNum res;
	res = a - (a / b)*b;
	return res;
}

LongNum LongNum::evaluation(LongNum x1, LongNum x0, int m)
{//Evaluating for Toom-3 multiplication
	LongNum res;
	res = x0 + x1*m + (*this)*(m*m);
	return res;
}

LongNum LongNum::Toom3(LongNum other)
{
	vector<int> x = nums;
	vector<int> y = other.nums;
	if (max(x.size(), y.size()) <= n_len) 
	{
		return (*this)*other;
	}
	//Part that makes longNums%3==0 and equal sizes
	if (x.size() < y.size())
	{
		int forY = y.size();
		int i = 0;
		if ((y.size() % 3) != 0)
		{
			y.push_back(0);
			++i;
		}
		y.resize(forY + i);

		do {
			x.push_back(0);
		} while (x.size() != y.size());
		x.resize(y.size());
	}
	if (y.size() < x.size())
	{
		int forX = x.size();
		int j = 0;
		if ((x.size() % 3) != 0)
		{
			x.push_back(0);
			++j;
		}
		x.resize(forX + j);

		do {
			y.push_back(0);
		} while (y.size() != x.size());
		y.resize(x.size());
	}
	if (y.size() == x.size()) {
		int c = 0;
		int sizeXY = x.size();
		while ((x.size() % 3) != 0)
		{
			x.push_back(0);
			y.push_back(0);
			++c;
		};
		x.resize(sizeXY + c);
		y.resize(sizeXY + c);
	}

	int len = x.size();
	vector<int> res(2 * len);
	int k = len / 3;

	//Splitting
	vector<int> x_2 = { x.begin() + 2 * k, x.end() };
	vector<int> x_1 = { x.begin() + k, x.begin() + 2 * k };
	vector<int> x_0 = { x.begin(), x.begin() + k };
	vector<int> y_2 = { y.begin() + 2 * k, y.end() };
	vector<int> y_1 = { y.begin() + k, y.begin() + 2 * k };
	vector<int> y_0 = { y.begin(), y.begin() + k };
	LongNum x2(x_2), x1(x_1), x0(x_0), y2(y_2), y1(y_1), y0(y_0);

	//Evaluating and Pointwise multiplication
	LongNum R0, R1, R2, R3, R4;
	R0 = (x2.evaluation(x1, x0, 0))*(y2.evaluation(y1, y0, 0));
	R1 = (x2.evaluation(x1, x0, 1))*(y2.evaluation(y1, y0, 1));
	R2 = (x2.evaluation(x1, x0, 2))*(y2.evaluation(y1, y0, 2));
	R3 = (x2.evaluation(x1, x0, 3))*(y2.evaluation(y1, y0, 3));
	R4 = (x2.evaluation(x1, x0, 4))*(y2.evaluation(y1, y0, 4));

	//Interpolation
	// 1  0  0   0   0    R0
	// 1  1  1   1   1    R1
	// 1  2  4   8   16   R2
	// 1  3  9   27  81   R3
	// 1  4  16  64  256  R4

	R1 = R1 - R0;
	R2 = R2 - R0;
	R3 = R3 - R0;
	R4 = R4 - R0;

	// 1  0  0   0   0    R0
	// 0  1  1   1   1    R1
	// 0  2  4   8   16   R2
	// 0  3  9   27  81   R3
	// 0  4  16  64  256  R4

	R2 = R2 - R1 * 2;
	R3 = R3 - R1 * 3;
	R4 = R4 - R1 * 4;

	// 1  0  0   0   0    R0
	// 0  1  1   1   1    R1
	// 0  0  2   6   14   R2
	// 0  0  6   24  78   R3
	// 0  0  12  60  252  R4

	R3 = R3 - R2 * 3;
	R4 = R4 - R2 * 6;

	// 1  0  0   0   0    R0
	// 0  1  1   1   1    R1
	// 0  0  2   6   14   R2
	// 0  0  0   6   36   R3
	// 0  0  0   24  168  R4

	R4 = R4 - R3 * 4;

	// 1  0  0   0   0    R0
	// 0  1  1   1   1    R1
	// 0  0  2   6   14   R2
	// 0  0  0   6   36   R3
	// 0  0  0   0   24   R4

	R4 = R4 / 24;
	R3 = R3 / 6;
	R2 = R2 / 2;

	// 1  0  0   0   0    R0
	// 0  1  1   1   1    R1
	// 0  0  1   3   7    R2
	// 0  0  0   1   6    R3
	// 0  0  0   0   1    R4

	R3 = R3 - R4 * 6;
	R2 = R2 - R4 * 7;
	R1 = R1 - R4;

	// 1  0  0   0   0    R0
	// 0  1  1   1   0    R1
	// 0  0  1   3   0    R2
	// 0  0  0   1   0    R3
	// 0  0  0   0   1    R4

	R2 = R2 - R3 * 3;
	R1 = R1 - R3;

	// 1  0  0   0   0    R0
	// 0  1  1   0   0    R1
	// 0  0  1   0   0    R2
	// 0  0  0   1   0    R3
	// 0  0  0   0   1    R4

	R1 = R1 - R2;

	// 1  0  0   0   0    R0
	// 0  1  0   0   0    R1
	// 0  0  1   0   0    R2
	// 0  0  0   1   0    R3
	// 0  0  0   0   1    R4

	//Recomposition
	R4.nums.insert(R4.nums.begin(), 4 * k, 0);
	R3.nums.insert(R3.nums.begin(), 3 * k, 0);
	R2.nums.insert(R2.nums.begin(), 2 * k, 0);
	R1.nums.insert(R1.nums.begin(), k, 0);

	LongNum res1(res);
	res1 = R4 + R3 + R2 + R1 + R0;
	return res1;

}

LongNum LongNum::karatsuba(LongNum other)
{
	int len = max(nums.size(), other.nums.size());
	if (len <= n_len)
	{
		return (*this)*other;
	}
	vector<int> res(2 * len);
	vector<int> x = nums; 
	vector<int> y = other.nums;
	int m = other.nums.size();
	int n = nums.size();

	if (n < m)
	{
		while (x.size() != y.size())
			x.push_back(0);
		x.resize(other.nums.size());
	}
	if (m < n)
	{
		while (y.size() != x.size())
			y.push_back(0);
		y.resize(nums.size());
	}

	int k = (len / 2) + (len % 2);
	vector <int> a_ = { x.begin() + k,x.end() }; 
	vector <int> b_ = { x.begin(), x.begin() + k };
	vector <int> c_ = { y.begin() + k, y.end() };
	vector <int> d_ = { y.begin(), y.begin() + k };
	LongNum a(a_), b(b_), c(c_), d(d_);
	LongNum r(res);
	LongNum z0, z1, z2, z3;
	z0 = a.karatsuba(c);
	z1 = (a + b).karatsuba(c + d);
	z2 = b.karatsuba(d);
	z3 = z1 - z2 - z0;
	z0.nums.insert(z0.nums.begin(), 2 * k, 0); 
	z3.nums.insert(z3.nums.begin(), k, 0);
	r = (z0)+(z3)+(z2);
	return r;
}

LongNum LongNum::inverse(LongNum b)
{
	LongNum b0 = b, t, q, one("1"), null("0"), a = (*this);
	LongNum x0("0"), x1("1");
	if (b == one) return one;
	while (one < a) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < null)
		x1 = b0 + x1;
	return x1;
}

LongNum LongNum::chinese_remainder(vector <LongNum> n, vector <LongNum> a)
{
	LongNum p, prod("1"), sum("0");
	int i;
	for (i = 0; i < 6; i++) prod = prod * n[i];
	for (i = 0; i < 6; i++) {
		p = prod / n[i];
		sum = sum + (p.inverse(LongNum(n[i])) * p) * a[i];
	}
	sum = sum % prod;
	return sum;
}

LongNum LongNum::Shoenhage(LongNum other)
{
	LongNum a = *this, b = other;
	//longNum w1("7"), w2("11"), w3("13"), w4("17"), w5("23"), w6("3");
	LongNum w1("1300727"), w2("1313423"), w3("1327877"), w4("15487001"), w5("179423411"), w6("179426341");
	LongNum v1, v2, v3, v4, v5, v6, u1, u2, u3, u4, u5, u6, x1, x2, x3, x4, x5, x6;

	v1 = a % w1;
	v2 = a % w2;
	v3 = a % w3;
	v4 = a % w4;
	v5 = a % w5;
	v6 = a % w6;

	u1 = b % w1;
	u2 = b % w2;
	u3 = b % w3;
	u4 = b % w4;
	u5 = b % w5;
	u6 = b % w6;

	x1 = (v1 * u1) % w1;
	x2 = (v2 * u2) % w2;
	x3 = (v3 * u3) % w3;
	x4 = (v4 * u4) % w4;
	x5 = (v5 * u5) % w5;
	x6 = (v6 * u6) % w6;

	LongNum res;
	res = chinese_remainder({w1, w2, w3, w4, w5, w6}, {x1, x2, x3, x4, x5, x6});
	return res;
}

void LongNum::fft(vector<complex<double>>& a, bool invert) //Fast Fourier Transform
{

	int n = (int)a.size();
	if (n == 1)  return;

	vector<complex<double>> a0(n / 2), a1(n / 2);

	for (int i = 0, j = 0; i<n; i += 2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i + 1];
	}
	fft(a0, invert);
	fft(a1, invert);

	double ang = 2 * PI / n * (invert ? -1 : 1);
	complex<double> w(1), wn(cos(ang), sin(ang));
	for (int i = 0; i<n / 2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2, a[i + n / 2] /= 2;
		w *= wn;
	}
}

LongNum LongNum::Strassen(LongNum other)
{
	LongNum f = *this, s = other;
	vector<int> res;
	vector<complex<double>> ff(f.nums.begin(), f.nums.end()), fs(s.nums.begin(), s.nums.end());
	size_t n = 1;
	while (n < max(f.nums.size(), s.nums.size()))  n <<= 1;
	n <<= 1;
	fs.resize(n), ff.resize(n);

	fft(ff, false), fft(fs, false);
	for (size_t i = 0; i<n; ++i)
		ff[i] *= fs[i];
	fft(ff, true);

	res.resize(n);

	for (size_t i = 0; i<n; ++i)
		res[i] = int(ff[i].real() + 0.5);

	int carry = 0;
	for (size_t i = 0; i<n; ++i) {
		res[i] += carry;
		carry = res[i] / 10;
		res[i] %= 10;
	}
	while (res.size() > 1 && res.back() == 0)
		res.pop_back();
	return LongNum(res);
}

LongNum LongNum::Random()
{
	vector<int> a;
	bool r = true;
	while (r)
	{
		a.clear();
		for (int i = 0; i < this->nums.size(); i++)
		{
			if (i == 0)
			{
				int b = rand() % (this->nums[0] + 1);
				a.insert(a.begin(), b);
			}
			else
			{
				int c = rand() % 10;
				while (c == 0) c = rand() % 10;
				a.insert(a.begin(), c);
			}
		}
		if (LongNum(a) < *this)
		{
			r = false;
		}
		else r = true;
	}
	while (a.size() > 1 && a.back() == 0) a.pop_back();
	return LongNum(a);
}

LongNum LongNum::power(LongNum y, LongNum p)
{
	LongNum x1, y1, res;
	res = LongNum("1"); x1 = *this; y1 = y;

	while (y1 != LongNum("0"))
	{
		if (y1.nums[0] % 2 == 1)
		{
			res = (res * x1) % p;
		}
		y1 = y1 / 2;
		x1 = (x1 * x1) % p;
	}

	return res;
}

bool LongNum::prime_Lemman()
{
	LongNum lem, one("1");
	lem = *this;
	if (lem == LongNum("2")) return 1;
	if (lem == one || lem.nums[0] % 2 == 0) return 0;
	bool flag = 0;
	bool isOK = 1;
	for (int i = 0; i < 10 && isOK; i++)
	{
		LongNum check, a;
		a = lem.Random();
		//a.write(); cout << endl;
		check = a.power(((*this) - one) / 2, lem);
		if (check == one || check == (lem - one))
		{
			if (check == (lem - one)) flag = 1;
		}
		else isOK = 0;
	}
	return isOK && flag;
}
LongNum LongNum::to_power(LongNum other)
{
	LongNum n, m, i, null("0"), one("1");
	m = *this;
	n = one;
	i = other;
	while (null < i)
	{
		n = n.Toom3(m);
		i = i - one;
	}
	return n;
}

bool LongNum::prime_RabinMiller()
{
	LongNum n, null("0"), one("1"), two("2");
	n = *this;

	if (n == LongNum("2")) return true;
	if (n < two) return false;
	if (n == one || n.nums[0] % 2 == 0) return false;

	LongNum s, t, a, x, z;
	bool isOK = true;
	s = one;

	LongNum w = n - one;
	while (w.nums[0] % 2) 
	{
		s = s + one;
		w = w / 2;
	}

	t = (n - one) / two.to_power(s);

	int i = 0;
	while (isOK && i < 10)
	{
		a = n.Random();
		x = a.power(t, n);
		if (x == one || x == n - one) ++i;
		else
		{
			LongNum j("0");
			bool isOK2 = true;
			while (j < s - one && isOK2)
			{
				x = (x.Toom3(x)) % n;
				if (x == one) { isOK = false; isOK2 = false; }
				else if (x == n - one) {
					++i;
					isOK2 = false;
					break;
				};
				j = j + one;
			}
			if (isOK2) isOK = false;
		}
	}
	return isOK;
}