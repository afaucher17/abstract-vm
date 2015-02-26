
#include "Analyzer.hpp"

Analyzer::AnalyzerException::AnalyzerException(std::string message, size_t line) : _message(message), _line(line)
{
	return ;
}

Analyzer::AnalyzerException::AnalyzerException(AnalyzerException const & src)
{
	*this = src;
	return ;
}

Analyzer::AnalyzerException::~AnalyzerException(void) throw()
{
	return ;
}

const char *					Analyzer::AnalyzerException::what() const throw()
{
	std::stringstream ss;

	ss << "Line " << this->_line << " : lexical error : " << this->_message;
	return ss.str().c_str();
}

Analyzer::AnalyzerException &	Analyzer::AnalyzerException::operator=(AnalyzerException const & rhs)
{
	this->_message = rhs._message;
	this->_line = rhs._line;
	return *this;
}

void			Analyzer::analyze(std::list<Token> * tokens)
{
	std::stringstream ss;
	f tab[] =
	{
		&Analyzer::_isLParenthesis,
		&Analyzer::_isRParenthesis,
		&Analyzer::_isOperator,
		&Analyzer::_isValueOperator,
		&Analyzer::_isIntPrecision,
		&Analyzer::_isFloatPrecision,
		&Analyzer::_isNaturalVal,
		&Analyzer::_isFloatingVal,
		&Analyzer::_isSeparator
	};
	for (std::list<Token>::iterator it = tokens->begin(); it != tokens->end(); ++it)
	{
		for (int i = 0; i < 9; i++)
		{
			if (tab[i](*it))
				break;
		}
		if ((*it).getType() == UNKNOWN)
		{
			ss << "unexpected token : ";
			ss << (*it).getValue();
			throw Analyzer::AnalyzerException(ss.str(), (*it).getLine());
		}
	}
	tokens->push_back(Token(END_OF_FILE, tokens->back().getLine()));
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
	for (int i = 0; i < 9; i++)
	{
		if (token.getValue().compare(operators[i]) == 0)
		{
			token.setType(OPERATOR);
			return true;
		}
	}
	return false;
}

bool			Analyzer::_isValueOperator(Token & token)
{
	for (int i = 0; i < 2; i++)
	{
		if (token.getValue().compare(value_operators[i]) == 0)
		{
			token.setType(VALUE_OPERATOR);
			return true;
		}
	}
	return false;
}

bool			Analyzer::_isIntPrecision(Token & token)
{
	for (int i = 0; i < 3; i++)
	{
		if (token.getValue().compare(int_precisions[i]) == 0)
		{
			token.setType(IPRECISION);
			return true;
		}
	}
	return false;
}

bool			Analyzer::_isFloatPrecision(Token & token)
{
	for (int i = 0; i < 2; i++)
	{
		if (token.getValue().compare(float_precisions[i]) == 0)
		{
			token.setType(FPRECISION);
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
	while (*str >= '0' && *str <= '9')
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
	while (*str >= '0' && *str <= '9')
	{
		str++;
		num = true;
	}
	if (!num) return false;
	num = false;
	if (*str == '.')
		str++;
	else return false;
	while (*str >= '0' && *str <= '9')
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



std::string Analyzer::operators[9] =
{
	"pop",
	"dump",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit",
};

std::string Analyzer::value_operators[2] =
{
	"push",
	"assert"
};

std::string Analyzer::int_precisions[3] =
{
	"int8",
	"int16",
	"int32",
};

std::string Analyzer::float_precisions[2] =
{
	"float",
	"double"
};
