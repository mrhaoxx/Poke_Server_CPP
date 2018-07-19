#pragma once
#include <string>
#include <string.h>
#include <map>
#include <iostream>
#include <stdlib.h>
#include "user.h"
#include "file.h"
#define FUHAO "*"
class distribute {
public:
	std::string ip;
	std::string input(std::string input);
	user u;
	int mode = 0;
	bool fresh_mode = true;
	int wait;

};
