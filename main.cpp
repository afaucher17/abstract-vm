#include "Tokenizer.hpp"
#include "Token.hpp"
#include "Analyzer.hpp"
#include <fstream>

int main()
{
	std::ifstream	myfile;
	std::string	line;
	std::stringstream ss;
	myfile.open("exemple.avm");
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			ss << line << std::endl;
		}
		myfile.close();
	}
	else std::cout << "Unable to open file" << std::endl;
	std::cout << ss.str();
	std::list<Token> *		tokens = Tokenizer::tokenize(ss.str());

	for (std::list<Token>::iterator it = tokens->begin(); it != tokens->end(); ++it)
	{
		std::cout << "{" << (*it).getValue() << "}" << std::endl;
	}
	Analyzer::analyze(tokens);
	for (std::list<Token>::iterator it = tokens->begin(); it != tokens->end(); ++it)
	{
		std::cout << *it << std::endl;
	}
return (0);
}
