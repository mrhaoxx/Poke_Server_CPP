#include "user.h"
#include <iostream>
std::string user::maketoken() {
	write(this->name + ".token", "lost");
	std::time_t result = std::time(nullptr);
	std::asctime(std::localtime(&result));
	std::string tokenpassnomh5 = (this->name + this->password + this->ip + std::to_string(result) + "PokeTOKEN");
	token=MD5(tokenpassnomh5).toString();
	write(this->name + ".token", token);
	//writeline(this->name + ".token", std::to_string(result));
	return token;
}
bool user::tokenlogin(std::string username, std::string tokenlogin) {
	std::cout << username << "-" << tokenlogin << std::endl;
	if (read(username + ".token") == "")return false;
	//std::cout << "1";
	if (read(username + ".token") == "lost")return false;
	//std::cout << "2";
	this->logged = true;
	if (readline(username + ".token", 1) == tokenlogin) {
		//std::cout << "4";
		this->name = username;
		return true;
	}
}

bool user::reg(std::string username, std::string password)
{
	if (read(username) == "")
	{
		std::string tmp;
		tmp = username + "\n" + password;
		write(username, tmp);
		this->name = username;
		this->password = password;
		std::cout << "[USER][REG] " << username << std::endl;
		logged = true;
		this->maketoken();
		return true;
	}
	else
	{
		return false;
	}
}
bool user::login(std::string username, std::string password)
{
	if (readline(username, 2) == password && readline(username, 1) == username)
	{
		std::cout << "[USER][LOGIN] " << username << std::endl;
		this->name = username;
		this->password = password;
		logged = true;
		this->maketoken();
		return true;
	}
	else
	{
		return false;
	}
}