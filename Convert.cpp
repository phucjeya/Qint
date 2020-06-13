#include "Convert.h"
#include <algorithm>

#include "Convert.h"
#include "Utils.h"
#include "BitProcess.h"
#include "Core.h"

std::unique_ptr<Convert> Convert::m_pInstance(nullptr);

std::string Convert::CovertIntStringToBin(std::string num, unsigned int numOfBits)
{
	std::string result;
	unsigned int index = 0;
	bool negative = num[0] == '-';

	while (num != "0")
	{
		result += std::to_string((num[num.length() - 1] - '0') % 2); // trả vệ hệ 16 
		num = Utils::Instance()->DivideNumStringForTwo(num);
	}

	std::reverse(result.begin(), result.end());

	BitProcess::Instance()->StandardBits(result, numOfBits);

	if (negative)
	{
		ConvertBitsToTwoComplement(result, true);
	}

	return result;
}

std::string Convert::ConvertBinToIntString(std::string bits)
{
	int index = 0;
	std::string decResult = "0";
	int length = bits.length();
	bool isNegativeNumber = bits[0] == '1';

	//Nếu kết quả phép chuyển là số âm chuyển về bit của số dương để thực hiện tính toán nhanh hơn
	if (isNegativeNumber)
	{
		ConvertBitsToTwoComplement(bits, true);
	}

	bool sign = false;

	while (index < length)
	{
		int exp = length - 1 - index;
		if (bits[index] == '1') {
			if (bits[index] == '1' && index == 0)
			{
				sign = true; //Sau khi đảo chuyển từ bù 2 về dạng nhị phân bình thường vẫn còn bit dấu thì lưu giá trị cờ
				index++;
				continue;
			}
			else
			{
				decResult = Utils::Instance()->AddTwoIntString(decResult, Utils::Instance()->PowOneDigit(2, exp));
			}
		}

		index++;
	}

	if (sign)
	{
		decResult = Utils::Instance()->SubtractTwoSNumString(decResult, Utils::Instance()->PowOneDigit(2, 127));
		//Trường hợp số nhỏ nhất -2^127
	}
	else if (isNegativeNumber)
	{
		decResult.insert(0, "-");
	}

	return decResult;

}

std::string Convert::ConvertDecPartToBin(std::string decPart, unsigned int& countBitsBeforeOne, const bool& isIntPartDiffZero = true)
{
	//Xử lí số "0123" -> "123"
	unsigned int firstPosDecPartNotOfZero = decPart.find_first_not_of('0', 0);

	int countFirstZero = firstPosDecPartNotOfZero;
	if (firstPosDecPartNotOfZero == -1)
	{
		return "0";
	}
	decPart = decPart.substr(firstPosDecPartNotOfZero, decPart.length() - firstPosDecPartNotOfZero);

	unsigned int lengthDecPartAtFirstTime = decPart.length();

	std::string num = "1";
	num = num.insert(1, lengthDecPartAtFirstTime + countFirstZero, '0');

	std::string result;

	if (isIntPartDiffZero)
	{
		int index = 0;
		while (index < NUM_OF_SIGNIFICANT_BITS)
		{
			decPart = Utils::Instance()->MultiplyNumStringWithOneDigit(decPart, 2);
			if (decPart.length() < lengthDecPartAtFirstTime + countFirstZero + 1)
			{
				result.append(1, '0');
			}
			else
			{
				result.append(1, '1');

				if (decPart == num)
				{
					break;
				}

				decPart.erase(0, 1);
				firstPosDecPartNotOfZero = decPart.find_first_not_of('0', 0);

				if (firstPosDecPartNotOfZero > 0)
				{
					decPart = decPart.substr(firstPosDecPartNotOfZero, decPart.length() - firstPosDecPartNotOfZero);
				}
			}
			index++;
		}
		return result;
	}
	else
	{
		bool isOne = false;
		unsigned int firstPosOne = -1;
		unsigned int countBitsAfterOne = 0;
		while (!isOne && countBitsBeforeOne < MAX_EXPONENT + NUM_OF_SIGNIFICANT_BITS)
		{
			decPart = Utils::Instance()->MultiplyNumStringWithOneDigit(decPart, 2);
			if (decPart.length() < lengthDecPartAtFirstTime + countFirstZero + 1)
			{
				countBitsBeforeOne++;
			}
			else
			{
				result.append(1, '1');
				unsigned int firstPosOne = countBitsBeforeOne;
				isOne = true;

				if (decPart == num)
				{
					return result;
				}

				decPart.erase(0, 1);
				firstPosDecPartNotOfZero = decPart.find_first_not_of('0', 0);
				if (firstPosDecPartNotOfZero > 0)
				{
					decPart = decPart.substr(firstPosDecPartNotOfZero, decPart.length() - firstPosDecPartNotOfZero);
				}
			}
		}

		while (countBitsAfterOne < NUM_OF_SIGNIFICANT_BITS - 1 && countBitsBeforeOne < MAX_EXPONENT + NUM_OF_SIGNIFICANT_BITS)
		{
			decPart = Utils::Instance()->MultiplyNumStringWithOneDigit(decPart, 2);
			if (decPart.length() < lengthDecPartAtFirstTime + countFirstZero + 1)
			{
				result.append(1, '0');
			}
			else
			{
				result.append(1, '1');

				if (decPart == num)
				{
					break;
				}

				decPart.erase(0, 1);
				firstPosDecPartNotOfZero = decPart.find_first_not_of('0', 0);
				if (firstPosDecPartNotOfZero > 0)
				{
					decPart = decPart.substr(firstPosDecPartNotOfZero, decPart.length() - firstPosDecPartNotOfZero);
				}
			}
			countBitsAfterOne++;
		}
		return result;
	}
}
void Convert::ConvertBitsToTwoComplement(std::string& bits, bool sign)
{
	if (sign)
	{
		BitProcess::Instance()->ReverseBits(bits);
		bits = BitProcess::Instance()->AddTwoBits(bits, "1");
	}
}

std::string Convert::ConvertHexToBin(std::string hex)
{
	std::string result = "";
	std::map<std::string, std::string> mapBinToHex = {
	{"0", "0000"},
	{"1", "0001"},
	{"2", "0010"},
	{"3", "0011"},
	{"4", "0100"},
	{"5", "0101"},
	{"6", "0110"},
	{"7", "0111"},
	{"8", "1000"},
	{"9", "1001"},
	{"A", "1010"},
	{"B", "1011"},
	{"C", "1100"},
	{"D", "1101"},
	{"E", "1110"},
	{"F", "1111"}
	};

	for (unsigned int i = 0; i < hex.length(); i++)
	{
		result += mapBinToHex[hex.substr(i, 1)];
	}

	//BitProcess::Instance()->StandardBits(result, MAX_CELL * BITS_OF_CELL);
	return result;
}

std::string Convert::ConvertBinToHex(std::string bits)
{
	std::string result = "";
	std::map<std::string, std::string> mapBinToHex = {
	{"0000","0"},
	{"0001","1"},
	{"0010","2"},
	{"0011","3"},
	{"0100","4"},
	{"0101","5"},
	{"0110","6"},
	{"0111","7"},
	{"1000","8"},
	{"1001","9"},
	{"1010","A"},
	{"1011","B"},
	{"1100","C"},
	{"1101","D"},
	{"1110","E"},
	{"1111","F"}
	};

	BitProcess::Instance()->StandardBits(bits, MAX_CELL * BITS_OF_CELL);

	for (int i = 0; i < bits.length(); i += 4)
	{
		result += mapBinToHex[bits.substr(i, 4)];
	}
	
	DeleteZero(result);
	return result;
}

std::unique_ptr<Convert>& Convert::Instance()
{
	if (m_pInstance.get() == nullptr)
	{
		m_pInstance.reset(new Convert());
	}
	return m_pInstance;
}
void Convert::DeleteZero(std::string &s)
{
	int count = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '0')
		{
			count++;
		}
		else break;
	}
	s.erase(s.begin(), s.begin() + count);
}