#pragma once

#include <string>
#include "Utils.h"

//Lớp Convert thiết kế dưới dạng Singleton
class Convert
{
public:
	//Chuyển đổi một chuỗi bit sang mã hex
	//Nhận vào chuỗi bits
	//Trả về chuỗi hex
	std::string ConvertBinToHex(std::string bits);

	//Chuyển đổi một chuỗi hex sang bin
	//Nhận vào chuỗi hex
	//Trả về chuỗi bits
	std::string ConvertHexToBin(std::string hex);

	//Chuyển dổi dãy bits sang dạng bù 2
	//Nhận vào tham chiếu của dãy bits cần chuyển
	void ConvertBitsToTwoComplement(std::string& bits, bool sign);

	//Chuyển đổi một số nguyên hệ 10 sang chuỗi nhị nhân
	//Nhận vào số nguyên định dạng chuỗi
	//Trả về chuỗi chứa các bit ở dạng bù 2
	std::string CovertIntStringToBin(std::string num, unsigned int numOfBits);

	//Chuyển đổi một chuỗi bit sang số nguyên
	//Nhận vào chuỗi bit
	//Trả về số nguyên dạng chuỗi
	std::string ConvertBinToIntString(std::string bits);
private:
	//Chuyển phần thập phân dạng decimal qua binary
	//Nhận vào phần thập phân, 1 tham chiếu để đếm bao nhiêu bit 0 trước bit 1 đầu tiên của phần thập phân, tham 
	//chiếu thứ 2 xác định phần nguyên trước đó khác 0 hay không.
	//Trả về dang binary dạng chuỗi
	std::string ConvertDecPartToBin(std::string decPart, unsigned int& countBitsBeforeOne, const bool& isIntPartDiffZero);
private:
	Convert()
	{
	}

public:
	Convert(const Convert&) = delete;
	void operator=(const Convert&) = delete;

public:
	static std::unique_ptr<Convert>& Instance();

public :void DeleteZero(std::string &s);

private:
	static std::unique_ptr<Convert> m_pInstance;
};