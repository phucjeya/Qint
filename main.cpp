#include "ConsoleApplication.h"

using namespace std;
//int main(int argc, char** argv)
//{
//	std::string fileIn, fileOut, type;
//	if (argc < 4)
//	{
//		std::cout << "invalid data!";
//	}
//	else
//	{
//		fileIn = std::string("input");
//		fileOut = std::string("output");
//		type = std::string(".txt");
//
//		ConsoleApplication* app = new ConsoleApplication;
//		app->Run(fileIn, fileOut, type);
//		delete app;
//	}
//
//	return 0;
//}

int main(int argc, char** argv) {
	std::string filein, fileout, type;
	filein = std::string("q.txt");
	fileout = std::string("output.txt");
	type = std::string("1");
	ConsoleApplication* app = new ConsoleApplication;
	app->Run(filein, fileout, type);
	delete app;
	return 0;
	// dòng 51,69 bị sai
	/*std::string fileIn, fileOut, type;

	if (argc < 3)
	{
		std::cout << "Khong hop le";
	}

	fileIn = string(argv[1]);
	fileOut = std::string(argv[2]);

	ConsoleApplication* app = new ConsoleApplication;
	app->Run(fileIn, fileOut, "1");
	delete app;
	return 0;*/
}