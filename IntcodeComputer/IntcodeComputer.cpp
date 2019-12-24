#include "IntcodeParser.h"

using namespace std;

int main()
{
	IntcodeParser computer = IntcodeParser("C:\\Users\\Chris\\OneDrive\\Shared Folder\\Projects\\IntcodeComputer\\IntcodeComputer\\input");
	computer.runProgram();
	//computer.printVS();
	system("pause");
}