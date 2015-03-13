#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP
# include <string>
# include <sstream>
# include <iostream>
# include <exception>
# include <limits>
# include <cstdlib>
# include <cmath>
# include "IOperand.hpp"
# include "Int8.hpp"
# include "Int16.hpp"
# include "Int32.hpp"
# include "Float.hpp"
# include "Double.hpp"

class OperandFactory
{
	public:
		class OperandException : public std::exception
		{
		};
		class OperandOverflowException : public OperandException
		{
			public:
				virtual const char *	what() const throw();
		};
		class OperandUnderflowException : public OperandException
		{
			public:
				virtual const char *	what() const throw();
		};

		OperandFactory( void );
		~OperandFactory( void );
		IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	private:
		IOperand const *	_createInt8( std::string const & value ) const;
		IOperand const *	_createInt16( std::string const & value ) const;
		IOperand const *	_createInt32( std::string const & value ) const;
		IOperand const *	_createFloat( std::string const & value ) const;
		IOperand const *	_createDouble( std::string const & value ) const;
		OperandFactory(OperandFactory const & src);
		OperandFactory &	operator=(OperandFactory const & rhs);
};
typedef IOperand const * (OperandFactory::*of)(std::string const & value) const;
#endif /* OPERANDFACTORY_HPP */
