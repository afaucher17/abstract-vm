#ifndef TOKEN_HPP
# define TOKEN_HPP
# include <string>

enum		tokenType {
	UNKNOWN = 0,
	LPARENTHESIS,
	RPARENTHESIS,
	OPERATOR,
	TYPE,
	NATURAL_VAL,
	FLOATING_VAL,
	SEPARATOR
};


class Token
{
	public:
		Token( void );
		Token( std::string const & value );
		Token(Token const & src);
		~Token( void );
		Token &					operator=(Token const & rhs);
		const static std::string tokenTypeName[];
		std::string				getValue( void ) const;
		tokenType				getType( void ) const;
		void					setType( tokenType type );

	private:
		std::string				_value;
		tokenType				_type;

};

std::ostream &					operator<<(std::ostream & o, Token const & rhs);

#endif /* TOKEN_HPP */
