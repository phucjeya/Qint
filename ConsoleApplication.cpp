#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "ConsoleApplication.h"
#include <string>

std::string ConsoleApplication::StandardResult(Qint number, int base)
{
	switch (base)
	{
	case 10:
		return number.ToString();
		break;
	case 2:
		return number.DecToBin(true);
		break;
	case 16:
		return number.DecToHex();
		break;
	default:
		return number.ToString();
	}
}

std::string ConsoleApplication::ProcessOperator(Qint A, Qint B, std::string numA, std::string numB, std::string _operator, int base)
{
	if (_operator == "~")
	{
		return StandardResult(~A, base);
	}
	else if (_operator == "+")
	{
		return StandardResult(A + B, base);
	}
	else if (_operator == "-")
	{
		return StandardResult(A - B, base);
	}
	else if (_operator == "*")
	{
		return StandardResult(A * B, base);
	}
	else if (_operator == "/")
	{
		return StandardResult(A / B, base);
	}
	else if (_operator == "&")
	{
		return StandardResult(A & B, base);
	}
	else if (_operator == "|")
	{
		return StandardResult(A | B, base);
	}
	else if (_operator == "^")
	{
		return StandardResult(A ^ B, base);
	}
	else if (_operator == "<<")
	{
		int nums = stoi(numB);
		return StandardResult(A << nums, base);
	}
	else if (_operator == ">>")
	{
		int nums = stoi(numB);
		return StandardResult(A >> nums, base);
	}
	else if (_operator == "rol")
	{
		int nums = atoi(numA.c_str());
		return StandardResult(A.rol(nums), base);
	}
	else if (_operator == "ror")
	{
		int nums = atoi(numA.c_str());
		return StandardResult(A.ror(nums), base);
	}
	else if (_operator == "<")
	{
		return ((A < B )? "TRUE" : "FALSE");
	}
	else if (_operator == ">")
	{
		return ((A > B) ? "TRUE" : "FALSE");
	}
	else if (_operator == "<=")
	{
		return ((A <= B)? "TRUE" : "FALSE");
	}
	else if (_operator == ">=")
	{
		return ((A >= B)? "TRUE" : "FALSE");
	}
	else if (_operator == "==")
	{
		return ((A ==B) ? "TRUE" : "FALSE");
	}
}

std::string ConsoleApplication::ProcessQint(std::string inputString)
{
	std::vector<std::string> UnaryOperator = { "~","rol","ror" };
	std::vector<std::string> BinaryOperator = { "+"," - ","*","/","<",">","<=",">=","==","&","|","^","<<",">>" };

	int OperatorType = 0;
	int ArgumentCount = 1;

	//Đếm số lượng tham số
	for (unsigned int i = 0; i < inputString.length(); i++)
	{
		if (inputString[i] == ' ')
			ArgumentCount++;
	}
	//Tìm Toán tử 1 ngôi trong chuỗi
	for (unsigned int i = 0; i < UnaryOperator.size(); i++)
	{
		if (inputString.find(UnaryOperator[i], 0) != std::string::npos)
		{
			OperatorType = 1;
			break;
		}
	}
	//Tìm Toán tử 2 ngôi trong chuỗi
	if (OperatorType == 0)
	{
		for (unsigned int i = 0; i < BinaryOperator.size(); i++)
		{
			if (inputString.find(BinaryOperator[i], 0) != std::string::npos)
			{
				OperatorType = 2;
				break;
			}
		}
	}

	std::string p1, p2, _operator, num1, num2;
	std::stringstream ss;

	ss << inputString;
	ss >> p1;

	//Kiểm tra có chỉ thị p2 hay không
	if (ArgumentCount - OperatorType == 3)
		ss >> p2;
	else
		p2 = p1;

	//Kiểu tra toán tử
	_operator = "";
	switch (OperatorType)
	{
	case 0:	//Không có toán tử
		ss >> num1;
		break;
	case 1: //Toán tử 1 ngôi
		ss >> _operator >> num1;
		break;
	case 2:	//Toán tử 2 ngôi
		ss >> num1 >> _operator >> num2;
		break;
	}


	//Trường hợp không có toán tử, thực hiện chuyển đổi giữa các toán hạng
	int base1 = std::atoi(p1.c_str());
	int base2 = std::atoi(p2.c_str());

	if (_operator == "")
	{
		if ((base1 == 2) && (base2 == 16))
		{
			Qint A;
			std::string Hex = Convert::Instance()->ConvertBinToHex(num1);
			A.DeleteZero(Hex);
			return Hex;
			std::cout << std::endl;
		}
		else if ((base1 == 2) && (base2 == 10))
		{
			Qint A;
			return (A.BinToDec(num1)).ToString();
			std::cout << std::endl;
		}
		else if ((base1 == 10) && (base2 == 16))
		{
			Qint A(num1);
			std::string Hex = A.DecToHex();
			return Hex;
			std::cout << std::endl;
		}
		else if ((base1 == 10) && (base2 == 2))
		{
			Qint A(num1);
			std::string bits = A.DecToBin(true);
			A.DeleteZero(bits);
			return bits;
			std::cout << std::endl;
		}
		else if ((base1 == 16) && (base2 == 2))
		{
			std::string Bin = Convert::Instance()->ConvertHexToBin(num1);
			Qint A;
			A.DeleteZero(Bin);
			return Bin;
		}
		else if ((base1 == 16) && (base2 == 10))
		{
			Qint A;
			return (A.HexToDec(num1)).ToString();
		}
		else if ((base1 == 10) && (base2 == 10))
		{
			Qint A(num1);
			std::string bits = A.DecToBin(true);
			Qint B;
			return (A.BinToDec(bits)).ToString();
			//std::cout << std::endl;
		}
		else if ((base1 == 2) && (base2 == 2))
		{
			std::string Bin = Convert::Instance()->ConvertHexToBin(Convert::Instance()->ConvertBinToHex(num1));
			Qint A;
			A.DeleteZero(Bin);
			return Bin;
		}
		else if ((base1 == 16) && (base2 == 16))
		{
			std::string Bin = Convert::Instance()->ConvertHexToBin(num1);
			Qint A;
			std::string Hex = Convert::Instance()->ConvertBinToHex(Bin);
			return Hex;
			std::cout << std::endl;
		}
	}

	//Trường hợp có toán tử, xử lí các toán hạng với toán tử
	if (base1 == base2)
	{
		switch (base1)
		{
		case 2:
		{
			Qint A;
			Qint B;

			A = Qint::BinToDec(num1);
			B = Qint::BinToDec(num2);

			return ProcessOperator(A, B, num1, num2, _operator, base1);
		}
		break;
		case 10:
		{
			if (OperatorType == 2) {
				Qint A(num1);
				Qint B(num2);
				return ProcessOperator(A, B, num1, num2, _operator, base1);
			}
			else
			{
				Qint A(num1);
				Qint B(num1);
				return ProcessOperator(A, B, num1, num2, _operator, base1);
			}
		}
		break;
		case 16:
		{
			Qint A = Qint::HexToDec(num1);
			Qint B = Qint::HexToDec(num2);
			return ProcessOperator(A, B, num1, num2, _operator, base1);
		}
		break;
		}
	}
}



void ConsoleApplication::Run(std::string fileIn, std::string fileOut, std::string type)
{
	std::vector<std::string> list = Utils::Instance()->ReadFile(fileIn);

	std::ofstream fout;
	fout.open(fileOut, std::ios_base::out);

	if (fout.fail() == true)
		std::cout << "File is inavailable!\n";
	else
	{
		if (type == "1")
		{
			for (unsigned int i = 0; i <= list.size() - 1; i++)
			{
				fout << ProcessQint(list[i]) << "\n";
			}
		}

	}

	fout.close();
}

