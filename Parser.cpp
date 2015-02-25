
#include "Parser.hpp"

bool		Parser::parse(std::list<Token> * tokens)
{
	std::list<Token>::const_iterator	it = tokens->begin();

	try
	{
		if (!Parser::isInstr(&it))
			return false;
		while (it != tokens->end())
		{
			if (!Parser::isSeparator(&it) || !Parser::isInstr(&it))
				return false;
		}
	}
	catch (const ParserException & e)
	{
		std::cerr << e.what() << std::endl;
		// TODO : quitter le programme
	}
	catch ( ... )
	{
		std::cerr << "???" << std::endl;
		// TODO : panic
	}
}

bool		Parser::isInstr(std::list<Token>::const_iterator * ptr_it)
{
	if (Parser::isOperator(ptr_it))
	{
		++(*ptr_it);
		return true;
	}
	if (Parser::isValueOperator(ptr_it))
	{
		++(*ptr_it);
		return (Parser::isValue(ptr_it));
	}
	// TODO : exception : instruction (push | pop | dump | assert | add | sub | mul | div | mod | print | exit) expected
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
	if (Parser::isIntPrecision(ptr_it))
	{
		++(*ptr_it);
		return (Parser::isLeftParenthesis(ptr_it) || Parser::isNaturalValue(ptr_it) || Parser::isRightParenthesis(ptr_it));
	}
	if (Parser::isFloatPrecision(ptr_it))
	{
		++(*ptr_it);
		return (Parser::isLeftParenthesis(ptr_it) || Parser::isFloatingValue(ptr_it) || Parser::isRightParenthesis(ptr_it));
	}
	// TODO : exception : precision (int8 | int16 | int32 | float | double) expected
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
	if ((*(*ptr_it)).getType() == LPARENTHESIS)
	{
		++(*ptr_it);
		return true;
	}
	// TODO : exception : left parenthesis expected
	return false;
}

bool		Parser::isRightParenthesis(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == RPARENTHESIS)
	{
		++(*ptr_it);
		return true;
	}
	// TODO : exception : right parenthesis expected
	return false;
}

bool		Parser::isNaturalValue(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == NATURAL_VAL)
	{
		++(*ptr_it);
		return true;
	}
	// TODO : exception : natural value expected
	return false;
}

bool		Parser::isFloatingValue(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == FLOATING_VAL)
	{
		++(*ptr_it);
		return true;
	}
	// TODO : exception : floating value expected
	return false;
}

bool		Parser::isSeparator(std::list<Token>::const_iterator * ptr_it)
{
	if ((*(*ptr_it)).getType() == SEPARATOR)
	{
		++(*ptr_it);
		return true;
	}
	// TODO : exception : separator expected
	return false;
}


