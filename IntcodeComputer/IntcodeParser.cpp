#pragma once
#include "IntcodeParser.h"

void IntcodeParser::readFile(std::string fn) {
	ifs.open(fn, std::ios::in);
	if (ifs.is_open()) std::cout << "File opened." << std::endl;
	char c;
	long accum = 0;
	long neg = 1;
	while (ifs.get(c)) {
		if (c == ',' || ifs.peek() == EOF) {
			vs.push_back(neg*accum);
			accum = 0;
			neg = 1;
		}
		else if (c == '-') {
			neg = -1;
		}
		else {
			accum = 10 * accum + (c - '0');
		}
	}
	ifs.close();
}

void IntcodeParser::add(long c, long b, long a) {
	vs[a] = b + c;
	ip += 4;
}

void IntcodeParser::mul(long c, long b, long a) {
	vs[a] = b * c;
	ip += 4;
}

void IntcodeParser::inp(long pos) {
	std::cout << "in: ";
	std::cin >> vs[pos];
	ip += 2;
}

void IntcodeParser::outp(long pos) {
	std::cout << vs[pos] << std::endl;
	ip += 2;
}

void IntcodeParser::jit(long c, long b)
{
	ip = c ? b : ip + 3;
}

void IntcodeParser::jif(long c, long b)
{
	ip = c == 0 ? b : ip + 3;
}

void IntcodeParser::lt(long c, long b, long a)
{
	vs[a] = (c < b ? 1 : 0);
	ip += 4;
}

void IntcodeParser::eq(long c, long b, long a)
{
	vs[a] = (c == b ? 1 : 0);
	ip += 4;
}

IntcodeParser::IntcodeParser(std::string fn) { readFile(fn); }
	
void IntcodeParser::runProgram() {
	ip = 0;
	while (ip < vs.size())
	{
		long code = vs[ip];
		if (code == 99) break;
		long command = code % 100;
		long mode_c = code / 100 % 10;
		long mode_b = code / 1000 % 10;
		long mode_a = code / 10000 % 10;
		switch (command)
		{
		case 1:
			add((mode_c ? vs[ip + 1] : vs[vs[ip + 1]]), (mode_b ? vs[ip + 2] : vs[vs[ip + 2]]), vs[ip + 3]);
			break;
		case 2:
			mul((mode_c ? vs[ip + 1] : vs[vs[ip + 1]]), (mode_b ? vs[ip + 2] : vs[vs[ip + 2]]), vs[ip + 3]);
			break;
		case 3:
			inp(vs[ip+1]);
			break;
		case 4:
			outp(vs[ip+1]);
			break;
		case 5:
			jit((mode_c ? vs[ip + 1] : vs[vs[ip + 1]]), (mode_b ? vs[ip + 2] : vs[vs[ip + 2]]));
			break;
		case 6:
			jif((mode_c ? vs[ip + 1] : vs[vs[ip + 1]]), (mode_b ? vs[ip + 2] : vs[vs[ip + 2]]));
			break;
		case 7:
			lt((mode_c ? vs[ip + 1] : vs[vs[ip + 1]]), (mode_b ? vs[ip + 2] : vs[vs[ip + 2]]), vs[ip + 3]);
			break;
		case 8:
			eq((mode_c ? vs[ip + 1] : vs[vs[ip + 1]]), (mode_b ? vs[ip + 2] : vs[vs[ip + 2]]), vs[ip + 3]);
			break;
		default:
			std::cout << "Got a bad command: " << command << std::endl;
			ip = vs.size();
			break;
		}
	}
}

void IntcodeParser::printVS() {
	for (size_t i = 0; i < vs.size(); i++)
	{

		std::cout << vs[i] << std::endl;

	}
}