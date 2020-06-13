#pragma once
#include <string>

#include "Qint.h"

#include "Utils.h"
#include "Convert.h"

class ConsoleApplication
{
private:
	//Hàm chuẩn hóa về hệ cơ số đề bài yêu cầu sau khi xử lí với toán tử
	std::string StandardResult(Qint number, int base);
	//Hàm xử lí với các toán tử và trả về chuỗi kết quả string
	std::string ProcessOperator(Qint A, Qint B, std::string numA, std::string numB, std::string _operator, int base);
	//Xử lí với số nguyên lớn và trả kết quả về chuỗi string
	std::string ProcessQint(std::string inputString);


public:
	void Run(std::string fileIn, std::string fileOut, std::string type);
	
	
}; 