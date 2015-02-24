#include <iostream>
#include "Token.hpp"

Token::Token( void ) : _value(""), _type(UNKNOWN)
{
	return ;
}

Token::Token( std::string const & value ) : _value(value), _type(UNKNOWN)
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

void						Token::setType( tokenType type )
{
	this->_type = type ;
	return ;
}

std::ostream &				operator<<(std::ostream & o, Token const & rhs)
{
	o << "{" << rhs.getValue() << "}" << std::endl;
	o << Token::tokenTypeName[rhs.getType()];
	return o;
}

const std::string	Token::tokenTypeName[] =
{
	"Unknown",
	"Left Parenthesis",
	"Right Parenthesis",
	"Operator",
	"Type",
	"Natural Value",
	"Floating Value",
	"Separator"
};
