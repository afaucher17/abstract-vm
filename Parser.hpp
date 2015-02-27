#ifndef PARSER_HPP
# define PARSER_HPP
# include <string>
# include <iostream>
# include <sstream>
# include <list>
# include <exception>
# include "Token.hpp"

class Parser
{
	public:
		class ParserException : public std::exception
		{
			public:
				ParserException(std::string message, size_t line);
				ParserException(ParserException const & src);
				~ParserException(void) throw ();
				virtual const char *	what() const throw();
				ParserException &		operator=(ParserException const & rhs);
			private:
				std::string		_message;
				size_t			_line;
				ParserException(void);
		};
		static bool		parse(std::list<Token> * tokens);

	private:
		static bool		isInstr(std::list<Token>::const_iterator * ptr_it);
		static bool		isValue(std::list<Token>::const_iterator * ptr_it);
		static bool		isSeparator(std::list<Token>::const_iterator * ptr_it);
		static bool		isIntPrecision(std::list<Token>::const_iterator * ptr_it);
		static bool		isFloatPrecision(std::list<Token>::const_iterator * ptr_it);
		static bool		isRightParenthesis(std::list<Token>::const_iterator * ptr_it);
		static bool		isLeftParenthesis(std::list<Token>::const_iterator * ptr_it);
		static bool		isNaturalValue(std::list<Token>::const_iterator * ptr_it);
		static bool		isFloatingValue(std::list<Token>::const_iterator * ptr_it);
		static bool		isValueOperator(std::list<Token>::const_iterator * ptr_it);
		static bool		isOperator(std::list<Token>::const_iterator * ptr_it);
};

#endif /* PARSER_HPP */
