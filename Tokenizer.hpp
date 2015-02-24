#ifndef TOKENIZER_HPP
# define TOKENIZER_HPP
# include <iostream>
# include <sstream>
# include <list>
# include "Token.hpp"

class Tokenizer
{
	public:
		static std::list<Token>	*		tokenize(std::string const & content);

	private:
		static void						_addToken(size_t last_found, size_t found, std::string const & content, std::list<Token> * tokens);
		static size_t					_findNotComment(size_t  * last_found, std::string const & content);
		Tokenizer( void );
		Tokenizer(Tokenizer const & src);
		~Tokenizer( void );
		Tokenizer &						operator=(Tokenizer const & rhs);
};

#endif /* TOKENIZER_HPP */
