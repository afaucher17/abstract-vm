
#include "Tokenizer.hpp"

void						Tokenizer::_addToken(size_t last_found, size_t found, std::string const & content, std::list<Token> * tokens)
{
	std::string				value;
	std::stringstream		ss;

	value = content.substr(last_found, found - last_found);
	if (value.compare("") != 0)
	{
		Token token(value);
		tokens->push_back(token);
	}
	if (content[found] == '\n' || content[found] == '(' || content[found] == ')')
	{
		ss << content[found];
		Token token(ss.str());
		tokens->push_back(token);
	}
}

size_t						Tokenizer::_findNotComment(size_t * last_found, std::string const & content)
{
	size_t found = content.find_first_of(" \n();", *last_found);
	if (found != std::string::npos && content[found] == ';')
	{
		found = content.find_first_of("\n", found);
		*last_found = found + 1;
		return Tokenizer::_findNotComment(last_found, content);
	}
	return found;
}

std::list<Token> *			Tokenizer::tokenize(std::string const & content)
{
	std::list<Token> *		tokens = new std::list<Token>;
	size_t					found = 0;
	size_t					last_found = 0;

	found = Tokenizer::_findNotComment(&last_found, content);
	while (found != std::string::npos)
	{
		Tokenizer::_addToken(last_found, found, content, tokens);
		last_found = found + 1;
		found = Tokenizer::_findNotComment(&last_found, content);
	}
	Tokenizer::_addToken(last_found, found, content, tokens);
	return tokens;
}
