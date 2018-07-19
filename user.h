#pragma once
#include <string>
#include "file.h"
#include <ctime>
#include "md5.h"
class user {
public:
	std::string name="undefine";
	std::string password="";
	std::string token;
	std::string maketoken();
	bool tokenlogin(std::string username,std::string tokenlogin);
	bool reg(std::string username, std::string password);
	bool login(std::string username, std::string password);
	bool logged = false;
	std::string ip;
};