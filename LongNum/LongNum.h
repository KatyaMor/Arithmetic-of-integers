#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "math.h"
#include <complex>

using namespace std;

class LongNum
{
protected:
	vector<int> nums;

public:
	
	LongNum();
	LongNum(const long long&);
	LongNum(vector<int>);
	LongNum(const LongNum&);
	LongNum(string s);

	vector<int> getLongNum();
	int getsize();
	void write()const;
	LongNum operator-();
	LongNum operator+(LongNum);
	LongNum operator-(LongNum);
	LongNum operator*(LongNum);
	LongNum operator/(LongNum);
	LongNum operator*(long long);
	LongNum operator/(long long);
	LongNum operator%(LongNum);
	LongNum& operator = (const LongNum &other);
	bool operator==(LongNum);
	bool operator>=(LongNum);
	bool operator<=(LongNum);
	bool operator!=(LongNum);
	bool operator<(LongNum);
	bool operator>(LongNum);

	void fft(vector<complex<double>>&, bool);
	LongNum Strassen(LongNum);

	LongNum inverse(LongNum);
	LongNum chinese_remainder(vector<LongNum>, vector<LongNum>);
	LongNum Shoenhage(LongNum);
	 
	LongNum karatsuba(LongNum);

	LongNum evaluation(LongNum, LongNum, int);
	LongNum Toom3(LongNum);

	LongNum Random();
	LongNum power(LongNum, LongNum);

	bool prime_Lemman();

	LongNum to_power(LongNum);

	bool prime_RabinMiller();
};