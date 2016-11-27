
#include "Parser.hpp"

const char *					Parser::InstructionException::what() const throw()
{
	return ("Instruction exception : instruction 'push | pop | dump | assert | add | sub | mul | div | print | exit' expected, got ");
}

const char *					Parser::PrecisionException::what() const throw()
{
	return ("Precision exception : precision 'int8 | int16 | int32 | float | double' expected, got ");
}

const char *					Parser::LeftParenthesisException::what() const throw()
{
	return ("Left Parenthesis exception : '(' expected, got ");
}

const char *					Parser::RightParenthesisException::what() const throw()
{
	return ("Right Parenthesis exception : ')' expected, got ");
}

const char *					Parser::NaturalValueException::what() const throw()
{
	return ("Natural Value exception : '[-]?[0..9]+' expected, got ");
}

const char *					Parser::FloatingValueException::what() const throw()
{
	return ("Floating Value exception : '[-]?[0..9]+.[0..9]+' expected, got ");
}

const char *					Parser::SeparatorException::what() const throw()
{
	return ("Separator exception : '\\n' expected, got ");
}

bool		Parser::parse(std::list<Token> * tokens)
{
	std::list<Token>::const_iterator	it = tokens->begin();

	try
	{
		while ((*it).getType() == SEPARATOR)
			++it;
		if (!Parser::isInstr(&it))
			return false;
		while ((*it).getType() != END_OF_FILE)
		{
			if (!Parser::isSeparator(&it) || !Parser::isInstr(&it))
				return false;
		}
	}
	catch (const ParserException & e)
	{
		std::cerr << "Line " << (*it).getLine() << " : Parse error : " << e.what() << (*it).toString() << std::endl;
		throw;
	}
	return true;
}

bool		Parser::isInstr(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == END_OF_FILE)
		return true;
	if (Parser::isOperator(ptr_it))
		return true;
	if (Parser::isValueOperator(ptr_it))
		return (Parser::isValue(ptr_it));
	throw InstructionException();
}


bool		Parser::isOperator(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == OPERATOR)
	{
		++(*ptr_it);
		return true;
	}
	return false;
}


bool		Parser::isValueOperator(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == VALUE_OPERATOR)
	{
		++(*ptr_it);
		return true;
	}
	return false;
}

bool		Parser::isValue(std::list<Token>::const_iterator * ptr_it)
{
	if (Parser::isIntPrecision(ptr_it))
		return (Parser::isLeftParenthesis(ptr_it) && Parser::isNaturalValue(ptr_it) && Parser::isRightParenthesis(ptr_it));
	if (Parser::isFloatPrecision(ptr_it))
		return (Parser::isLeftParenthesis(ptr_it) && Parser::isFloatingValue(ptr_it) && Parser::isRightParenthesis(ptr_it));
	throw PrecisionException();
}

bool		Parser::isIntPrecision(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == IPRECISION)
	{
		++(*ptr_it);
		return true;
	}
	return false;
}

bool		Parser::isFloatPrecision(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == FPRECISION)
	{
		++(*ptr_it);
		return true;
	}
	return false;
}

bool		Parser::isLeftParenthesis(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == LPARENTHESIS)
	{
		++(*ptr_it);
		return true;
	}
	throw LeftParenthesisException();
}

bool		Parser::isRightParenthesis(std::list<Token>::const_iterator * ptr_it)
{
	std::stringstream ss;

	if ((*(*ptr_it)).getType() == RPARENTHESIS)
	{
		++(*ptr_it);
		return true;
	}
	throw RightParenthesisException();
}

bool		Parser::isNaturalValue(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == NATURAL_VAL)
	{
		++(*ptr_it);
		return true;
	}
	throw NaturalValueException();
}

bool		Parser::isFloatingValue(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == FLOATING_VAL)
	{
		++(*ptr_it);
		return true;
	}
	throw FloatingValueException();
}

bool		Parser::isSeparator(std::list<Token>::const_iterator * ptr_it)
{
	size_t				i = 0;
	while ((*(*ptr_it)).getType() == SEPARATOR)
	{
		++(*ptr_it);
		i++;
	}
	if (i > 0)
		return true;
	throw SeparatorException();
}
