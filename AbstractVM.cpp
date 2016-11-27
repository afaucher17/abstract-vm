
#include "AbstractVM.hpp"

const char *	AbstractVM::NoExitException::what() const throw()
{
	return ("Program ended without exit command.");
}

AbstractVM::AbstractVM( void )
{
	return ;
}

void			AbstractVM::_compute(std::list<Instruction> & instructions, std::list<const IOperand *> & stk)
{
	std::list<Instruction>::const_iterator		it;
	bool										exit = false;

	try
	{
		for (it = instructions.begin(); it != instructions.end(); ++it)
		{
			if (!exit)
				exit |= (*it).execute_fun(stk);
		}
		if (!exit)
			throw NoExitException();
	}
	catch (const AbstractVMException & e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
		return ;
	}
}

int				AbstractVM::run(std::string const & program)
{
	std::list<Token> *							tokens = Tokenizer::tokenize(program);
	std::list<Instruction> *					instructions = NULL;
	std::list<const IOperand *>					stk;
	std::list<const IOperand *>::iterator		stk_it;

	try
	{
		Analyzer::analyze(tokens);
		Parser::parse(tokens);
		InstructionFactory	insf;
		instructions = insf.createInstructionList(tokens);
		this->_compute(*instructions, stk);
	}
	catch (const std::exception & e)
	{
	}
	delete tokens;
	delete instructions;
	for (stk_it = stk.begin(); stk_it != stk.end(); ++stk_it)
		delete(*stk_it);
	return (0);
}

