#include "distribute.h"
#include <unistd.h>

std::string distribute::input(std::string input)
{
	if (fresh_mode)
	{
		mode = 0;
	}
	if (input == "FUHAO")
	{
		return FUHAO;
	}
	std::vector<std::string> data;
	SplitString(input, data, FUHAO);
	if (!u.logged)
	{
		if (data[0] == "login")
		{
			//sleep(3);
			mode = 1;
		}
		else if (data[0] == "reg")
		{
			mode = 2;
		}
		else if (data[0] == "token")
		{
			mode = 8;
		}
	}
	else
	{
		if (data[0] == "chat_data")
		{
			mode = 3;
		}
		if (data[0] == "system")
		{
			mode = 4;
		}
		if (data[0] == "chat_send")
		{
			mode = 5;
		}
		if (data[0] == "chat_num")
		{
			mode = 6;
		}
		if (data[0] == "musicplaylist163")
		{
			mode = 7;
		}	
		if (data[0] == "musicplaylistadd163")
		{
			mode = 9;
		}
		if (data[0] == "musicplaylistclear163")
		{
			mode = 10;
		}
		if (data[0] == "needhelpadndgetid")
		{
			mode = 11;
		}
		if (data[0] == "needhelpcheckothershelpyou")
		{
			mode = 12;
		}
		if (data[0] == "helpcommandchannel")
		{
			mode = 13;
		}
		if (data[0] == "helpothersrequestid")
		{
			mode = 14;
		}
	}
	switch (mode)
	{
	case 1:
		if (data.size() == 3)
		{
			if (u.login(data[1], data[2]))
			{
				return u.token;
			}
			else
			{
				return "Error";
			}
		}
		else
		{
			return "Error";
		}
	case 2:
		if (data.size() == 3)
		{
			if (u.reg(data[1], data[2]))
			{
				return u.token;
			}
			else
			{
				return "Error";
			}
		}
		else
		{
			return "Error";
		}
	case 3:
	{
		if (data.size() == 2)
		{
			//return "233";
			std::string linetmp, tmp;
			std::vector<std::string> t;
			int fromstart= atoi(data[1].c_str());
			SplitString(read("chat/chat_data"), t, "|");
			//while (t[line])
			if (atoi(data[1].c_str()) > (int)t.size())
			{
				return "SIZEERROR";
			}
			else
			{
				while (fromstart < t.size())
				{
					fromstart++;
					tmp =tmp+"$"+t[fromstart-1];
				}
			}
			return std::to_string(t.size())+ tmp;
		}
		else
		{
			return "SIZEERROR";
		}
	}
	case 4:
	{
		if (data.size() == 2)
		{
			std::string tmp;
			tmp = str_replacve(" ", "#", data[1]);
			tmp = "cd data&&" + tmp + "> .systemlog" + u.name;
			system(tmp.c_str());
			tmp = read(".systemlog" + u.name);
			if (tmp == "") {
				tmp = "Error Command";
			}
			return tmp;
		}
		else
		{
			return "SIZEERROR";
		}
	}
	case 5:
	{
		if (data.size() >= 2)
		{
			std::string tmp;
			int size = (int)data.size()-1;
			if (size == 1)
			{
				writenochear("chat/chat_data", u.name + "#" + data[1]);
				return "ok";
			}
			for (int x = 1; x < size; x++)
			{
				tmp =tmp+FUHAO+ data[x];
			}
			writenochear("chat/chat_data", u.name + "#" + tmp);
			//write("chat/chat_num", std::to_string(atoi(read("chat/chat_num").c_str())+1));
			return "ok";
		}
		else
		{
			return "SIZEERROR";
		}
	}
	case 6:
	{
		if (data.size() == 1)
		{
			if (read("chat/lock") == "")
			{
				system("mkdir data/chat");
				write("chat/chat_data", "a#1|nb#2|c#3|");
				write("chat/lock", "done");
				//write("chat/chat_num", "0");
			}
			std::string linetmp, tmp;
			std::vector<std::string> t;
			SplitString(read("chat/chat_data"), t, "|");
			return std::to_string(t.size());
		}
		else
		{
			return "SIZEERROR";
		}
	}
	case 7:
		if (data.size() == 1)
		{
			if (read("musiclists/musiclist") == "")
			{
				return "empty";
			}
			return read("musiclists/musiclist");
		}
		else
		{
			return "SIZEERROR";
		}
	case 8:
		if (data.size() == 3) {
			if (u.tokenlogin(data[1], data[2]))
			{
				return "success";
			}
			else
			{
				return "failed";
			}
		}
		else
		{
			return "SIZEERROR";
		}
	case 9:
		if (data.size() == 2)
		{
			if (read("musiclists/musiclist")=="")
			{
				write("musiclists/musiclist", data[1]);
			}
			else
			{
				write("musiclists/musiclist", read("musiclists/musiclist")+"$" + data[1]);
			}
			return "ok";
		}
		else
		{
			return "SIZEERROR";
		}
	case 10:
		if (data.size() == 1)
		{
			write("musiclists/musiclist", "");
			return "ok";
		}
		else
		{
			return "SIZEERROR";
		}
	case 11:
		if (data.size() == 1)
		{
			id = randstring();
			write("help/" + id, "wait");
			return id;
		}
		else
		{
			return "SIZEERROR";
		}
	case 12:
		if (data.size() == 1)
		{			
			return read("help/" + id);
		}			
		else
		{
			return "SIZEERROR";
		}
	case 14:
		if (data.size() == 2)
		{
			if (read("help/" + data[1]) == "wait")
			{
				write("help/" + data[1], "requested");
				oid = data[1];
				return "ok";
			}
			else
			{
				return "wrong";
			}
		}
		else
		{
			return "SIZEERROR";
		}
	default:
		return "Error";
	}
}