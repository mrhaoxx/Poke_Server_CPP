#include "file.h"
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

std::string read(std::string filename)
{
	std::string tmp;
	tmp = "data/" + filename;
	const char*f = tmp.c_str();
	std::string data;
	std::ifstream read(f);
	if (read)
	{
		read.open(f);
		std::stringstream buffer;
		buffer << read.rdbuf();
		std::string contents(buffer.str());
		std::cout << "[FILE][READ:" << filename << "] "<< contents<< std::endl;
		return contents;
	}
	else
	{ 
		std::cout << "[FILE][Non-existent: " << filename << " ] "<< std::endl;
	}
	return "";
}
bool write(std::string filename, std::string word)
{
	std::string tmp;
	tmp = "data/" + filename;
	const char*f = tmp.c_str();
	std::ofstream write;
	write.open(f, std::ios::out);
	write << word;
	write.close();
	//std::cout << "[FILE][WRITE:" << filename << "] " << word << std::endl;
	return true;
}
std::string readline(std::string filename,int line)
{
	std::string tmp;
	tmp = "data/" + filename;
	std::ifstream infile(tmp.c_str());
	std::string temp;
	for (int l=0;l<line;l++)
	{
		getline(infile, temp);
	}
	//std::cout << "[FILE][READLINE:" << filename << " "<< line << "] " << temp << std::endl;
	return temp;
}
std::string exec(const char* cmd) {
	FILE* pipe = popen(cmd, "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	std::string result = "";
	while (!feof(pipe)) {
		if (std::fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;
}

std::string str_replacve(std::string dstPattern, std::string pattern, std::string str, int count)
{
	std::string retStr = "";
	std::string::size_type pos;
	int i = 0, l_count = 0,szStr = (int)str.length();
	if (-1 == count) // replace all
		count = szStr;
	for (i = 0; i<szStr; i++)
	{
		if (std::string::npos == (pos = str.find(pattern, i)))  break;
		if ((int)pos < szStr)
		{
			retStr += str.substr(i, pos - i) + dstPattern;
			i = pos + pattern.length() - 1;
			if (++l_count >= count)
			{
				i++;
				break;
			}
		}
	}
	retStr += str.substr(i);
	return retStr;
}
bool writenochear(std::string filename, std::string word) {
	std::string tmp;
	tmp = "data/" + filename;
	const char*f = tmp.c_str();
	std::ofstream write;
	write.open(f, std::ios::app);
	write <<word+"|";
	write.close();
	//std::cout << "[FILE][WRITE:" << filename << "] " << word << std::endl;
	return true;
}
bool writeline(std::string filename, std::string word) {
	std::string tmp;
	tmp = "data/" + filename;
	const char*f = tmp.c_str();
	std::ofstream write;
	write.open(f, std::ios::app);
	write << "\n" + word;
	write.close();
	//std::cout << "[FILE][WRITE:" << filename << "] " << word << std::endl;
	return true;
}
std::string randstring()
{
	std::string buf;
	std::string tmp;
	srand(time(0));                         //产生随机化种子
	int k=5;                  //随机生成一个字符串的长度 
	for (int i = 1; i <= k; i++)
	{
		int x, s;                        //x表示这个字符的ascii码 ，s表示这个字符的大小写  
		s = rand() % 2;                     //随机使s为1或0，为1就是大写，为0就是小写 
		if (s == 1)                        //如果s=1 
			x = rand() % ('Z' - 'A' + 1) + 'A';       //将x赋为大写字母的ascii码 
		else
			x = rand() % ('z' - 'a' + 1) + 'a';       //如果s=0，x赋为小写字母的ascii码 
		tmp = (char)x;
		buf = buf + tmp;
	}
	return buf;
}