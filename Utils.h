#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>

//Utils được thiết kế dưới dạng Singleton class
class Utils
{
public:
	static std::unique_ptr<Utils>& Instance();

public:
	//Cộng 2 số nguyên lớn ở dạng chuỗi
	//Kết quả trả về là số nguyên lớn dạng chuỗi
	//exs: "23565432456754322356543245675432" + "24567543245676543456"
	std::string AddTwoIntString(std::string num1, std::string num2);

	//Chia số nguyên lớn cho 2
	//Trả về kết quả của phép chia là một số nguyên lớn dạng chuỗi
	//exs: "23565432456754322356543245675432" / "2"
	std::string DivideNumStringForTwo(std::string num);

	//Nhân số nguyên lớn dạng chuỗi với một số nguyên (int)
	//Kêt quả trả về một số nguyên lớn
	//exs: "1" * "24567543245676543456"
	std::string MultiplyNumStringWithOneDigit(std::string num1, int num2);

	//Nhân 2 số nguyên lớn dạng chuỗi với nhau
	//Kết quả trả về một số nguyên lớn dạng chuỗi
	//exs: "23565432456754322356543245675432" * "24567543245676543456"
	std::string MultiplyNumString(std::string num1, std::string num2);

	//Lũy thừa một số nguyên với số mũ
	//Trả về số nguyên lớn dạng chuỗi
	//exs: 2^72 = ? 
	std::string PowOneDigit(int factor, int exp);

	//Lũy thừa số 2 với mũ âm
	//Trả về số nguyên lớn dạng chuỗi
	//exs: 2^-72 = ? 
	std::string NegativePowTwo(unsigned int exp);

	//Cộng 2 số thực lớn ở dạng chuỗi
	//Kết quả trả về là số nguyên lớn dạng chuỗi
	//exs: "0.23565432456754322356543245675432" + "0.24567543245676543456"
	std::string AddTwoDecWithPoint(std::string num1, std::string num2);
public:

	//Thực hiện trừ hai số với nhau
	//Nhận vào số trừ và số bị trừ
	//Trả về kết quả của phép trừ
	std::string SubtractTwoSNumString(std::string num1, std::string num2);

public:

	//Nhân một thập phân với 2
	//Nhận vào một số thập phân
	//Trả ra kết quả đã nhân với 2 ở dạng chuỗi
	std::string MultiplyNumberWithTwo(std::string number);

public:
	//Đọc dữ liệu theo từng dòng và lưu vào vector tương ứng với các phần tử trong vector đó
	std::vector<std::string> ReadFile(std::string file_name_in);
	//Ghi dữ liệu xuất ra file theo từng dòng
	//void WriteFile(std::string file_name_out, std::vector<std::string> list);

private:
	Utils()
	{
	}

public:
	Utils(const Utils&) = delete;
	void operator=(const Utils&) = delete;

	//Tìm số lớn nhất giữa 2 chuỗi
	std::string FindMaxNumString(std::string num1, std::string num2);

private:
	static std::unique_ptr<Utils> m_pInstance;
};