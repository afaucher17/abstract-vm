
#include "Parser.hpp"

Parser::ParserException::ParserException(std::string message, size_t line) : _message(message), _line(line)
{
	return ;
}

Parser::ParserException::ParserException(ParserException const & src)
{
	*this = src;
	return ;
}

Parser::ParserException::~ParserException(void) throw()
{
	return ;
}

const char *					Parser::ParserException::what() const throw()
{
	std::stringstream ss;

	ss << "Line " << this->_line << " : syntax error : " << this->_message;
	return ss.str().c_str();
}

Parser::ParserException &		Parser::ParserException::operator=(ParserException const & rhs)
{
	this->_message = rhs._message;
	this->_line = rhs._line;
	return *this;
}

bool		Parser::parse(std::list<Token> * tokens)
{
	std::list<Token>::const_iterator	it = tokens->begin();

	while ((*it).getType() == SEPARATOR)
		++it;
	if (!Parser::isInstr(&it))
		return false;
	while ((*it).getType() != END_OF_FILE)
	{
		if (!Parser::isSeparator(&it) || !Parser::isInstr(&it))
			return false;
	}
	return true;
}

bool		Parser::isInstr(std::list<Token>::const_iterator * ptr_it)
{
	std::stringstream ss;

	if ((*(*ptr_it)).getType() == END_OF_FILE)
		return true;
	if (Parser::isOperator(ptr_it))
		return true;
	if (Parser::isValueOperator(ptr_it))
		return (Parser::isValue(ptr_it));
	ss << "instruction { push | pop | dump | assert | add | sub | mul | div | print | exit } expected, got ";
	ss << (*(*ptr_it)).toString();
	throw Parser::ParserException(ss.str(), (*(*ptr_it)).getLine());
	return false;
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
	std::stringstream ss;

	if (Parser::isIntPrecision(ptr_it))
		return (Parser::isLeftParenthesis(ptr_it) && Parser::isNaturalValue(ptr_it) && Parser::isRightParenthesis(ptr_it));
	if (Parser::isFloatPrecision(ptr_it))
		return (Parser::isLeftParenthesis(ptr_it) && Parser::isFloatingValue(ptr_it) && Parser::isRightParenthesis(ptr_it));
	ss << "precision {int8 | int 16 | int32 | float | double} expected, got ";
	ss << (*(*ptr_it)).toString();
	throw Parser::ParserException(ss.str(), (*(*ptr_it)).getLine());
	return false;
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
	std::stringstream ss;

	if ((*(*ptr_it)).getType() == LPARENTHESIS)
	{
		++(*ptr_it);
		return true;
	}
	ss << "left parenthesis expected, got ";
	ss << (*(*ptr_it)).toString();
	throw Parser::ParserException(ss.str(), (*(*ptr_it)).getLine());
	return false;
}

bool		Parser::isRightParenthesis(std::list<Token>::const_iterator * ptr_it)
{
	std::stringstream ss;

	if ((*(*ptr_it)).getType() == RPARENTHESIS)
	{
		++(*ptr_it);
		return true;
	}
	ss << "right parenthesis expected, got ";
	ss << (*(*ptr_it)).toString();
	throw Parser::ParserException(ss.str(), (*(*ptr_it)).getLine());
	return false;
}

bool		Parser::isNaturalValue(std::list<Token>::const_iterator * ptr_it)
{
	std::stringstream ss;

	if ((*(*ptr_it)).getType() == NATURAL_VAL)
	{
		++(*ptr_it);
		return true;
	}
	ss << "natural value expected, got ";
	ss << (*(*ptr_it)).toString();
	throw Parser::ParserException(ss.str(), (*(*ptr_it)).getLine());
	return false;
}

bool		Parser::isFloatingValue(std::list<Token>::const_iterator * ptr_it)
{
	std::stringstream ss;

	if ((*(*ptr_it)).getType() == FLOATING_VAL)
	{
		++(*ptr_it);
		return true;
	}
	ss << "floating value expected, got ";
	ss << (*(*ptr_it)).toString();
	throw Parser::ParserException(ss.str(), (*(*ptr_it)).getLine());
	return false;
}

bool		Parser::isSeparator(std::list<Token>::const_iterator * ptr_it)
{
	std::stringstream	ss;
	size_t				i = 0;

	while ((*(*ptr_it)).getType() == SEPARATOR)
	{
		++(*ptr_it);
		i++;
	}
	if (i > 0)
		return true;
	ss << "separator expected, got ";
	ss << (*(*ptr_it)).toString();
	throw Parser::ParserException(ss.str(), (*(*ptr_it)).getLine());
	return false;
}
