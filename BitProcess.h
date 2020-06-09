#pragma once

#include <string>
#include <memory>
#include "Core.h"

class BitProcess
{
private:
	//Lấy bit tại vị trị pos từ trái qua
	bool GetBit(const unsigned char memory, const unsigned int& pos);
	//Bật bit lên 1 tại pos từ trái qua
	void SetBitOne(unsigned char& memory, const unsigned int& pos);
	//Tắt bit xuống 0 tại pos từ trái qua
	void SetBitZero(unsigned char& memory, const unsigned int& pos);

public:
	//Chuẩn hoá chuỗi bit cho đủ 128 bits, nếu thiếu thì thêm bit 0 vào đầu, thừa thì cắt các bit ở cuối
	void StandardBits(std::string& bits, const unsigned int& numOfBits);

	//Get bit trên vùng nhớ unsigned char 16 bytes
	std::string GetBit(const unsigned char memmory[MAX_CELL]);

	//Set bit trên vùng nhớ unsigned char 16 bytes
	void SetBit(unsigned char memmory[MAX_CELL], std::string bits);

	//Đảo chuỗi bits
	void ReverseBits(std::string& bits);

public:
	//Cộng nhị phân 2 dãy bits
	std::string AddTwoBits(std::string bits1, std::string bits2);
	//Thực hiện trừ 2 dãy bits
	std::string SubtractTwoBits(std::string bits1, std::string bits2);
	//Thực hiện nhân nhị phân 2 dãy bits
	std::string MultiplyTwoBits(std::string bits1, std::string bits2);
	//Shift right một chuỗi 3 dãy bits
	void ShiftRightThreeBits(std::string& A, std::string& Q, char& Q_1);
	//Chia 2 dãy bit
	std::string DivideTwoBits(std::string bits1, std::string bits2);
	//Shift left một chuỗi 3 dãy bits
	void ShiftLeftTwoBits(std::string& A, std::string& Q);


private:
	BitProcess()
	{

	}

public:
	BitProcess(const BitProcess&) = delete;
	void operator=(const BitProcess&) = delete;

public:
	static std::unique_ptr<BitProcess>& Instance();

private:
	static std::unique_ptr<BitProcess> m_pInstance;
};