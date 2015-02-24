#ifndef ANALYZER_HPP
# define ANALYZER_HPP
# include <string>
# include <sstream>
# include <iostream>
# include <list>
# include "Token.hpp"


class Analyzer
{
	public:
		static void		analyze(std::list<Token> * tokens);
		static bool		_isLParenthesis(Token & token);
		static bool		_isRParenthesis(Token & token);
		static bool		_isOperator(Token & token);
		static bool		_isType(Token & token);
		static bool		_isNaturalVal(Token & token);
		static bool		_isFloatingVal(Token & token);
		static bool		_isSeparator(Token & token);

	private:
		Analyzer( void );
		Analyzer(Analyzer const & src);
		~Analyzer( void );
		Analyzer &	operator=(Analyzer const & rhs);
		static std::string operators[11];
		static std::string types[5];
};
typedef bool (*f)(Token & token);

#endif /* ANALYZER_HPP */
