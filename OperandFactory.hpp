#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP
# include <string>
# include <sstream>
# include <iostream>
# include "IOperand.hpp"

class OperandFactory
{
	class OperandOverflowException : public std::exception
	{
		virtual const char *		what() const throw();
	};
	class OperandUnderflowException : public std::exception
	{
		virtual const char *		what() const throw();
	};

	public:
		IOperand const *	createOperand( eOperandType type, std::string const & value ) const;
	private:
		IOperand const *	createInt8( std::string const & value ) const;
		IOperand const *	createInt16( std::string const & value ) const;
		IOperand const *	createInt32( std::string const & value ) const;
		IOperand const *	createFloat( std::string const & value ) const;
		IOperand const *	createDouble( std::string const & value ) const;
};
#endif /* OPERANDFACTORY_HPP */
