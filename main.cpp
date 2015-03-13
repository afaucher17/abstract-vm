#include <fstream>
#include "AbstractVM.hpp"
#include "FileManager.hpp"

int main(int argc, char **argv)
{
	FileManager		fm;
	AbstractVM		avm;
	std::string		file;

	try
	{
		if (argc > 1)
			file = fm.openFile(argv[1]);
		else
			file = fm.getFile();
	}
	catch (const FileManager::FileManagerException & e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
		return (0);
	}
	return (avm.run(file));
}
