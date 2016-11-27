
#include "FileManager.hpp"

char const *			FileManager::FileManagerException::what() const throw()
{
	return ("Unable to open file.");
}
std::string const		FileManager::openFile(const char * filename)
{
	std::ifstream		myfile;
	std::string			line;
	std::stringstream	ss;

	myfile.open(filename);
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
			ss << line << std::endl;
		myfile.close();
	}
	else
		throw FileManagerException();
	return ss.str();
}

std::string const		FileManager::getFile()
{
	std::stringstream	ss;
	std::string			buff;

	std::getline(std::cin, buff);
	while (buff.compare(";;") != 0)
	{
		ss << buff << std::endl;
		std::getline(std::cin, buff);
	}
	return ss.str();
}

