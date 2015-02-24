
#include "Analyzer.hpp"

void			Analyzer::analyze(std::list<Token> * tokens)
{
	f tab[] =
	{
		&Analyzer::_isLParenthesis,
		&Analyzer::_isRParenthesis,
		&Analyzer::_isOperator,
		&Analyzer::_isType,
		&Analyzer::_isNaturalVal,
		&Analyzer::_isFloatingVal,
		&Analyzer::_isSeparator
	};
	for (std::list<Token>::iterator it = tokens->begin(); it != tokens->end(); ++it)
	{
		for (int i = 0; i < 7; i++)
		{
			if (tab[i](*it))
				break;
		}
		/* TODO : throw exception if UNKNOWN */
	}
}

bool			Analyzer::_isLParenthesis(Token & token)
{
	if (token.getValue().compare("(") == 0)	{
		token.setType(LPARENTHESIS);
		return true;
	}
	return false;
}

bool			Analyzer::_isRParenthesis(Token & token)
{
	if (token.getValue().compare(")") == 0)
	{
		token.setType(RPARENTHESIS);
		return true;
	}
	return false;
}

bool			Analyzer::_isOperator(Token & token)
{
	for (int i = 0; i < 11; i++)
	{
		if (token.getValue().compare(operators[i]) == 0)
		{
			token.setType(OPERATOR);
			return true;
		}
	}
	return false;
}

bool			Analyzer::_isType(Token & token)
{
	for (int i = 0; i < 5; i++)
	{
		if (token.getValue().compare(types[i]) == 0)
		{
			token.setType(TYPE);
			return true;
		}
	}
	return false;
}

bool				Analyzer::_isNaturalVal(Token & token)
{
	const char		*str = token.getValue().c_str();
	bool			num = false;

	if (*str == '-')
		str++;
	while (*str > '0' && *str < '9')
	{
		str++;
		num = true;
	}
	if (num && *str == '\0')
	{
		token.setType(NATURAL_VAL);
		return true;
	}
	return false;
}

bool				Analyzer::_isFloatingVal(Token & token)
{
	const char		*str = token.getValue().c_str();
	bool			num = false;

	if (*str == '-')
		str++;
	while (*str > '0' && *str < '9')
	{
		str++;
		num = true;
	}
	if (!num) return false;
	num = false;
	if (*str == '.')
		str++;
	else return false;
	while (*str > '0' && *str < '9')
	{
		str++;
		num = true;
	}
	if (num && *str == '\0')
	{
		token.setType(FLOATING_VAL);
		return true;
	}
	return false;
}

bool			Analyzer::_isSeparator(Token & token)
{
	if (token.getValue().compare("\n") == 0)
	{
		token.setType(SEPARATOR);
		return true;
	}
	return false;
}


std::string Analyzer::operators[11] =
{
	"push",
	"pop",
	"dump",
	"assert",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit",
};

std::string Analyzer::types[5] =
{
	"int8",
	"int16",
	"int32",
	"float",
	"double",
};
