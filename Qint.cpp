#include "Qint.h"
#include "Utils.h"
#include "Convert.h"
#include "BitProcess.h"


Qint::Qint()
	:_data{ 0 }
{
}

Qint::Qint(std::string numberOrBits, const bool& isBits)
{
	if (!isBits)
	{
		std::string bin = Convert::Instance()->CovertIntStringToBin(numberOrBits, MAX_CELL * BITS_OF_CELL);
		BitProcess::Instance()->SetBit(_data, bin);
	}
	else
	{
		if (numberOrBits.length() != MAX_CELL * BITS_OF_CELL)
		{
			BitProcess::Instance()->StandardBits(numberOrBits, 1 + NUM_OF_EXPONENT_BITS + NUM_OF_SIGNIFICANT_BITS);
		}
		BitProcess::Instance()->SetBit(_data, numberOrBits);
	}
}

Qint::Qint(const Qint& other):_data{ 0 }
{

	if (this == &other) {
		return;
	}

	for (int i = 0; i < MAX_CELL; i++) {
		_data[i] = other._data[i];
	}
}

Qint::~Qint()
{
	memset(_data, 0, MAX_CELL);
}

std::string Qint::ToString() const
{
	const std::string bits = BitProcess::Instance()->GetBit(_data);
	const std::string bigIntNumber = Convert::Instance()->ConvertBinToIntString(bits);
	return bigIntNumber;
}

void Qint::ScanQInt(std::string num)
{
	std::string bin = Convert::Instance()->CovertIntStringToBin(num, MAX_CELL * BITS_OF_CELL);
	BitProcess::Instance()->SetBit(_data, bin); // chuyển string sang char
}

void Qint::PrintQInt() const
{
	const std::string bits = BitProcess::Instance()->GetBit(_data);
	const std::string bigIntNumber = Convert::Instance()->ConvertBinToIntString(bits);
	std::cout << bigIntNumber;
}

bool* Qint::DecToBin() const // Check binary trước khi xuất ra output.txt
{
	bool* result = new bool[MAX_CELL * BITS_OF_CELL];
	std::string bits = BitProcess::Instance()->GetBit(this->_data);
	for (unsigned int i = 0; i < bits.length(); i++)
	{
		if (bits[i] == '1')
		{
			result[i] = true;
		}
		else
		{
			result[i] = false;
		}
	}

	return result;
}

std::string Qint::DecToBin(bool isStr) const
{
	const std::string bits = BitProcess::Instance()->GetBit(this->_data);
	return bits;
}

Qint Qint::BinToDec(std::string bits)
{
	if (bits.length() != MAX_CELL * BITS_OF_CELL)
	{
		BitProcess::Instance()->StandardBits(bits, MAX_CELL * BITS_OF_CELL);
	}

	const std::string numberInStr = Convert::Instance()->ConvertBinToIntString(bits);

	Qint newQInt = Qint(numberInStr);
	return newQInt;
}

Qint Qint::HexToDec(std::string hex)
{
	std::string bits = Convert::Instance()->ConvertHexToBin(hex);
	Qint result(bits, true);

	return result;
}

std::string Qint::DecToHex() const
{
	std::string bits = BitProcess::Instance()->GetBit(_data);
	std::string result = Convert::Instance()->ConvertBinToHex(bits);

	return result;
}

Qint Qint::operator+(const Qint& other) const
{
	std::string bits1 = BitProcess::Instance()->GetBit(_data);
	std::string bits2 = BitProcess::Instance()->GetBit(other._data);
	std::string addedBits = BitProcess::Instance()->AddTwoBits(bits1, bits2);
	std::string numValue = Convert::Instance()->ConvertBinToIntString(addedBits);

	Qint result(numValue);
	return result;
}

Qint Qint::operator-(const Qint& other) const
{
	std::string bits1 = BitProcess::Instance()->GetBit(this->_data);
	std::string bits2 = BitProcess::Instance()->GetBit(other._data);

	Convert::Instance()->ConvertBitsToTwoComplement(bits2, true);
	std::string addedBits = BitProcess::Instance()->AddTwoBits(bits1, bits2);

	Qint result(addedBits, true);
	return result;
}

Qint Qint::operator*(const Qint& other) const
{
	auto bits1 = BitProcess::Instance()->GetBit(_data);
	auto bits2 = BitProcess::Instance()->GetBit(other._data);

	auto result = BitProcess::Instance()->MultiplyTwoBits(bits1, bits2);
	return Qint(result, true);
}

Qint Qint::operator/(const Qint& other) const
{
	auto bits1 = BitProcess::Instance()->GetBit(_data);
	auto bits2 = BitProcess::Instance()->GetBit(other._data);
	std::string bitZero = "0";
	BitProcess::Instance()->StandardBits(bitZero, MAX_CELL * BITS_OF_CELL);
	if (BitProcess::Instance()->GetBit(other._data) == bitZero)
	{
		throw "Divisor can't be Zero";
	}

	auto result = BitProcess::Instance()->DivideTwoBits(bits1, bits2);
	return Qint(result, true);
}

Qint& Qint::operator=(const std::string& number)
{
	*this = Qint(number);
	return *this;
}

//Qint& Qint::operator++()
//{
//	std::string bitsOfOne = "1";
//	BitProcess::Instance()->StandardBits(bitsOfOne, MAX_CELL * BITS_OF_CELL);
//	*this = Qint(BitProcess::Instance()->AddTwoBits(BitProcess::Instance()->GetBit(this->_data), bitsOfOne), true);
//	return *this;
//}
//
//Qint Qint::operator++(const int)
//{
//	Qint temp = *this;
//	std::string bitsOfOne = "1";
//	BitProcess::Instance()->StandardBits(bitsOfOne, MAX_CELL * BITS_OF_CELL);
//
//	*this = Qint(BitProcess::Instance()->AddTwoBits(BitProcess::Instance()->GetBit(_data), bitsOfOne), true);
//	return temp;
//}
//
//Qint& Qint::operator--()
//{
//	std::string bitsOfOne = "1";
//	BitProcess::Instance()->StandardBits(bitsOfOne, MAX_CELL * BITS_OF_CELL);
//	*this = Qint(BitProcess::Instance()->SubtractTwoBits(BitProcess::Instance()->GetBit(this->_data), bitsOfOne), true);
//	return *this;
//}
//
//Qint Qint::operator--(const int)
//{
//	Qint temp = *this;
//	std::string bitsOfOne = "1";
//	BitProcess::Instance()->StandardBits(bitsOfOne, MAX_CELL * BITS_OF_CELL);
//
//	*this = Qint(BitProcess::Instance()->SubtractTwoBits(BitProcess::Instance()->GetBit(_data), bitsOfOne), true);
//	return temp;
//}

const bool Qint::operator==(const Qint& other) const
{
	std::string allZeroBitsString = std::string(MAX_CELL * BITS_OF_CELL, '0');
	Qint comparedValue = (*this ^ other);	//Lấy kq XOR giữa số so sánh và số được so sánh Ra một số Qint

	std::string comparedValueBitsStr = BitProcess::Instance()->GetBit(comparedValue._data);

	bool flag = false; //Checking flag
	for (int i = 0; i < 128; i++) //Nếu kq XOR là 0 thì hai số bằng nhau và ngược lại
	{
		if (allZeroBitsString[i] != comparedValueBitsStr[i])
		{
			return flag;
		}
	}

	flag = true;
	return flag;
}

const bool Qint::operator!=(const Qint& other) const
{
	bool flag = false;

	if (*this == other)
	{
		return flag;
	}

	else flag = true;
	return flag;
}

const bool Qint::operator>(const Qint& other) const
{
	std::string otherBitsStr = BitProcess::Instance()->GetBit(other._data);//Chuyển sang dãy bit
	std::string thisBitsStr = BitProcess::Instance()->GetBit(this->_data);//Chuyển sang dãy bit
	bool flag = false;//Checking flag

	// a = b
	if (*this == other)
	{
		return flag;
	}

	// a < 0 and b > 0
	if (thisBitsStr[0] == '1' && otherBitsStr[0] == '0')
	{
		return flag;
	}
	// a > 0 and b < 0
	else if (thisBitsStr[0] == '0' && otherBitsStr[0] == '1')
	{
		flag = true;
		return flag;
	}

	// a > 0 and b > 0
	else if (thisBitsStr[0] == '0' && otherBitsStr[0] == '0')
	{
		int i = 1;
		do //So sánh bit giá trị bên trái nhất
		{
			if (thisBitsStr[i] == '1' && otherBitsStr[i] == '0') //a > b
			{
				flag = true;
				return flag;
			}
			else if (thisBitsStr[i] == '0' && otherBitsStr[i] == '1') //a < b
			{
				flag = false;
				return flag;
			}
			i++; //Xét bit kế tiếp
		} while (i < 128);
	}

	// a < 0 and b < 0
	else if (thisBitsStr[0] == '1' && otherBitsStr[0] == '1')
	{
		Convert::Instance()->ConvertBitsToTwoComplement(thisBitsStr, true);
		Convert::Instance()->ConvertBitsToTwoComplement(otherBitsStr, true);

		int i = 1;
		do	// So sánh ngược của TH so sánh 2 số dương		
		{
			if (thisBitsStr[i] == '1' && otherBitsStr[i] == '0')
			{
				flag = false;
				return flag;
			}
			else if (thisBitsStr[i] == '0' && otherBitsStr[i] == '1')
			{
				flag = true;
				return flag;
			}
			i++;
		} while (i < 128);
	}

	return flag;
}

const bool Qint::operator>=(const Qint& other) const
{
	bool flag = true;

	if (*this > other || *this == other)
	{
		return flag;
	}

	else flag = false;
	return flag;
}

const bool Qint::operator<(const Qint& other) const
{
	bool flag = false;

	if (*this >= other)
	{
		return flag;
	}

	else flag = true;

	return flag;
}

const bool Qint::operator<=(const Qint& other) const
{
	bool flag = false;
	if (*this > other)
	{
		return flag;
	}

	else flag = true;
	return flag;
}
// Dịch trái, phải 1 bit (sửa lại)
Qint Qint::operator<<(const int n)
{
	std::string bits = BitProcess::Instance()->GetBit(this->_data);
	bits += std::string(n, '0');
	bits.erase(0, n);// xóa bit dư

	Qint returnVal;
	BitProcess::Instance()->SetBit(returnVal._data, bits);
	return returnVal;
}

Qint Qint::operator>>(const int n)
{
	std::string bits = BitProcess::Instance()->GetBit(this->_data);

	if (bits.at(0) == '1')
	{
		bits.insert(0, std::string(n, '1'));
	}
	else
	{
		bits.insert(0, std::string(n, '0'));
	}

	bits.erase(bits.length() - n, n);

	Qint returnVal;
	BitProcess::Instance()->SetBit(returnVal._data, bits);
	return returnVal;
}
//xoay trái, phải  1 bit (sửa lại)
Qint Qint::rol(const int n)
{
	std::string bits = BitProcess::Instance()->GetBit(this->_data);
	std::string f = bits.substr(0, n);
	bits += f;
	bits.erase(0, n);

	Qint returnVal;
	BitProcess::Instance()->SetBit(returnVal._data, bits);
	return returnVal;
}

Qint Qint::ror(const int n)
{
	std::string bits = BitProcess::Instance()->GetBit(this->_data);
	std::string f = bits.substr(bits.length() - n, n);
	bits.insert(0, f);
	bits.erase(bits.length() - n, n);
	Qint returnVal;
	BitProcess::Instance()->SetBit(returnVal._data, bits);
	return returnVal;
}

Qint Qint::operator&(const Qint& other) const
{
	std::string bitsThis = BitProcess::Instance()->GetBit(this->_data);
	std::string bitsOther = BitProcess::Instance()->GetBit(other._data);
	std::string result;
	for (int i = 0; i < 128; i++)
	{
		if (bitsThis.at(i) == '1' && bitsOther.at(i) == '1')
		{
			result.append("1");
		}
		else {
			result.append("0");
		}
	}
	Qint returnVal;
	BitProcess::Instance()->SetBit(returnVal._data, result);
	return returnVal;
}

Qint Qint::operator|(const Qint& other) const
{
	std::string bitsThis = BitProcess::Instance()->GetBit(this->_data);
	std::string bitsOther = BitProcess::Instance()->GetBit(other._data);
	std::string result;
	for (int i = 0; i < 128; i++)
	{
		if (bitsThis.at(i) == '0' && bitsOther.at(i) == '0')
		{
			result.append("0");
		}
		else {
			result.append("1");
		}
	}

	Qint returnVal;
	BitProcess::Instance()->SetBit(returnVal._data, result);
	return returnVal;
}

Qint Qint::operator^(const Qint& other) const
{
	std::string bitsThis = BitProcess::Instance()->GetBit(this->_data);
	std::string bitsOther = BitProcess::Instance()->GetBit(other._data);
	std::string result;
	for (int i = 0; i < 128; i++)
	{
		if (bitsThis.at(i) == bitsOther.at(i))
		{
			result.append("0");
		}
		else
		{
			result.append("1");
		}
	}

	Qint returnVal;
	BitProcess::Instance()->SetBit(returnVal._data, result);
	return returnVal;
}

Qint Qint::operator~()
{
	std::string bitsThis = BitProcess::Instance()->GetBit(this->_data);
	std::string result;
	for (int i = 0; i < 128; i++)
	{
		if (bitsThis.at(i) == '0')
		{
			result.append("1");

		}
		else
		{
			result.append("0");
		}
	}
	Qint returnVal;
	BitProcess::Instance()->SetBit(returnVal._data, result);
	return returnVal;
}

std::ostream& operator<<(std::ostream& os, const Qint& dt)
{
	os << dt.ToString();
	return os;
}

std::istream& operator>>(std::istream& is, Qint& dt)
{
	std::string num;
	is >> num;
	dt.ScanQInt(num);
	return is;
}

Qint& Qint::operator=(const Qint& other) {

	if (this == &other) {
		return *this;
	}

	for (int i = 0; i < 16; i++) {
		_data[i] = other._data[i];
	}
	return *this;
}