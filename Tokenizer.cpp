
#include "Tokenizer.hpp"

void						Tokenizer::_addToken(size_t last_found, size_t found, size_t * line, std::string const & content, std::list<Token> * tokens)
{
	std::string				value;
	std::stringstream		ss;

	value = content.substr(last_found, found - last_found);
	if (value.compare("") != 0)
	{
		Token token(value, *line);
		tokens->push_back(token);
	}
	if (content[found] == '\n' || content[found] == '(' || content[found] == ')')
	{
		ss << content[found];
		Token token(ss.str(), *line);
		tokens->push_back(token);
		if (content[found] == '\n')
			(*line)++;
	}
}

size_t						Tokenizer::_findNotComment(size_t * last_found, size_t * line, std::string const & content)
{
	size_t found = content.find_first_of(" \n();", *last_found);
	if (found != std::string::npos && content[found] == ';')
	{
		found = content.find_first_of("\n", found);
		if (found == std::string::npos)
		{
			*last_found = found;
			return found;
		}
		*last_found = found + 1;
		(*line)++;
		return Tokenizer::_findNotComment(last_found, line, content);
	}
	return found;
}

std::list<Token> *			Tokenizer::tokenize(std::string const & content)
{
	std::list<Token> *		tokens = new std::list<Token>;
	size_t					found = 0;
	size_t					last_found = 0;
	size_t					line = 0;

	found = Tokenizer::_findNotComment(&last_found, &line, content);
	while (found != std::string::npos)
	{
		Tokenizer::_addToken(last_found, found, &line, content, tokens);
		last_found = found + 1;
		found = Tokenizer::_findNotComment(&last_found, &line, content);
	}
	if (last_found != std::string::npos)
		Tokenizer::_addToken(last_found, found, &line, content, tokens);
	return tokens;
}
