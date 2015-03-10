#include "Tokenizer.hpp"
#include "Token.hpp"
#include "Analyzer.hpp"
#include "Parser.hpp"
#include <fstream>
#include "InstructionFactory.hpp"

int main()
{
	std::ifstream	myfile;
	std::string	line;
	std::stringstream ss;
	std::list<Instruction>::const_iterator it;
	bool		exit = false;
	myfile.open("exemple.avm");
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			ss << line << std::endl;
		}
		myfile.close();
	}
	else std::cerr << "Unable to open file" << std::endl;
	std::list<Token> *		tokens = Tokenizer::tokenize(ss.str());
	try
	{
		Analyzer::analyze(tokens);
		Parser::parse(tokens);
		InstructionFactory insf;
		std::list<Instruction> * instructions = insf.createInstructionList(tokens);
		std::list<const IOperand *>	stk;
		for (it = instructions->begin(); it != instructions->end(); ++it)
		{
			if (!exit && (*it).execute_fun(stk))
				exit = true;
		}
		if (!exit)
			std::cerr << "Program ended without exit command." << std::endl;
	}
	catch (const Parser::ParserException & e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const Analyzer::AnalyzerException & e)
	{
		std::cerr << e.what() << std::endl;
	}
	/*catch (const Instruction::InstructionException & e)
	{
		std::cerr <<  e.what() << std::endl;
	}
	catch (const OperandFactory::OperandException & e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const Calculator::FloatingPointException & e)
	{
		std::cerr << e.what() << std::endl;
	}*/
	return (0);
}
