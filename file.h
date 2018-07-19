#pragma once
#include <iostream>
#include <sstream>
#include <vector> 
#include <fstream>
#include <unistd.h>  
#include <ostream>
#include <string>
#include <ctime>
#include <cstdlib>

std::string read(std::string filename);
bool write(std::string filename, std::string word);
std::string readline(std::string filename, int line);
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
std::string exec(const char* cmd);
std::string str_replacve(std::string dstPattern, std::string pattern, std::string str, int count = -1);
bool writenochear(std::string filename, std::string word);
bool writeline(std::string filename, std::string word);
std::string randstring();