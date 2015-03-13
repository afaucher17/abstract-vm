#ifndef FILEMANAGER_HPP
# define FILEMANAGER_HPP
# include <string>
# include <sstream>
# include <iostream>
# include <fstream>

class FileManager
{
	public:
		class FileManagerException : public std::exception
		{
			public:
			virtual char const *	what() const throw();
		};
		std::string const		openFile(const char * filename);
		std::string const		getFile();
};
#endif /* FILEMANAGER_HPP */
