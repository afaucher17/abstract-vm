#include "Tokenizer.hpp"
#include "Token.hpp"
#include "Analyzer.hpp"
#include "Parser.hpp"
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
	std::list<Token> *		tokens = Tokenizer::tokenize(ss.str());
	try
	{
		Analyzer::analyze(tokens);
		Parser::parse(tokens);
		// TODO : Transform into exec
		// TODO : Exec
	}
	catch (const Parser::ParserException & e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (const Analyzer::AnalyzerException & e)
	{
		std::cout << e.what() << std::endl;
	}
	// TODO : Catch transorm exec error
	// TODO : Catch exec error
	return (0);
}
