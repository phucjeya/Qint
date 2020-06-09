#pragma once

#include <iostream>
#include <string>

class Qint
{
private:
	unsigned char _data[16];

public:
	Qint();
	Qint(std::string numberOrBits, const bool& isBits = false);
	Qint(const Qint& other);
	~Qint();

public:
	std::string ToString() const;

	//Nhập số QInt
	void ScanQInt(std::string num);

	//In số QInt ra màn hình
	void PrintQInt() const;

	//Chuyển đổi thập phân sang nhị phân
	//Trả về mảng bit ở dạng bool
	bool* DecToBin() const;

	//Chuyển đổi thập phân sang nhị phân
	//Trả về mảng bit ở dạng string
	std::string DecToBin(bool isStr = true) const;

	//Chuyển đổi nhị phân sang thập phân
	//Trả về một số nguyên lớn
	static Qint BinToDec(std::string bits);

	//Chuyển đổi thập lục phân sang thập phân
	//Trả về một số nguyên lớn
	static Qint HexToDec(std::string hex);

	//Chuyển đổi thập phân sang thập lục phân
	//Trả về mảng kí tự của hệ thập lục phân 
	std::string DecToHex() const;

public:
	//+ operator
	Qint operator+(const Qint&) const;
	//- operator
	Qint operator-(const Qint& other) const;
	//* operator
	Qint operator*(const Qint& other) const;
	//div operator
	Qint operator/(const Qint& other) const;

	Qint& operator=(const std::string& number);

public:
	//++ operator: ++Qint
	Qint& operator++();
	//++ operator: Qint++ 
	Qint operator++(const int);
	//-- operator: --Qint
	Qint& operator--();
	//-- operator: Qint--
	Qint operator--(const int);

public:
	//boolean operator
	const bool operator==(const Qint& other) const;
	const bool operator!=(const Qint& other) const;
	const bool operator>(const Qint& other) const;
	const bool operator>=(const Qint& other) const;
	const bool operator<(const Qint& other) const;
	const bool operator<=(const Qint& other) const;

public:
	//bitwise operator
	Qint operator<<(const int n);
	Qint operator>>(const int n);
	Qint rol(const int n);
	Qint ror(const int n);

	Qint operator&(const Qint& other) const;
	Qint operator|(const Qint& other) const;
	Qint operator^(const Qint& other) const;
	Qint operator~();
	Qint& operator=(const Qint& other);

public:
	friend std::ostream& operator<<(std::ostream& os, const Qint& dt);
	friend std::istream& operator>>(std::istream& is, Qint& dt);
};