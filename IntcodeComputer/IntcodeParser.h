#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class IntcodeParser
{
	size_t ip;
	std::vector<long> vs;
	std::ifstream ifs;
	void readFile(std::string fn);
	void add(long c, long b, long a);
	void mul(long c, long b, long a);
	void inp(long pos);
	void outp(long pos);
	void jit(long c, long b);
	void jif(long c, long b);
	void lt(long c, long b, long a);
	void eq(long c, long b, long a);
	
public:
	IntcodeParser(std::string fn);
	void runProgram();
	void printVS();
};

