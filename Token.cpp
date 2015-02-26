#include <iostream>
#include "Token.hpp"

Token::Token( void ) : _value(""), _type(UNKNOWN), _line(0)
{
	return ;
}

Token::Token( tokenType type , size_t line ) : _value(""), _type(type), _line(line)
{
	return ;
}

Token::Token( std::string const & value, size_t line) : _value(value), _type(UNKNOWN), _line(line)
{
	return ;
}

Token::Token( Token const & src )
{
	*this = src;
	return ;
}

Token::~Token( void )
{
	return ;
}

Token &						Token::operator=(Token const & rhs)
{
	this->_value = rhs._value;
	this->_type = rhs._type;
	this->_line = rhs._line;
	return *this;
}

std::string					Token::getValue( void ) const
{
	return this->_value;
}

tokenType					Token::getType( void ) const
{
	return this->_type;
}

std::string					Token::toString( void ) const
{
	std::stringstream ss;

	ss << "";
	if (this->_type == END_OF_FILE)
		ss << "end of file";
	else if (this->_value.compare("\n") == 0)
		ss << "end of line";
	else if (this->_value.compare("") != 0)
		ss << this->_value;
	return ss.str();
}

size_t						Token::getLine( void ) const
{
	return this->_line;
}

void						Token::setType( tokenType type )
{
	this->_type = type ;
	return ;
}

std::ostream &				operator<<(std::ostream & o, Token const & rhs)
{
	o << "{" << rhs.getValue() << "}" << std::endl;
	o << "Line: " << rhs.getLine() << std::endl;
	o << Token::tokenTypeName[rhs.getType()];
	return o;
}

const std::string	Token::tokenTypeName[] =
{
	"Unknown",
	"Left Parenthesis",
	"Right Parenthesis",
	"Operator",
	"Value Operator",
	"Int Precision",
	"Floating Precision",
	"Natural Value",
	"Floating Value",
	"Separator",
	"End of File",
};
