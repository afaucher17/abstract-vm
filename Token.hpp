#ifndef TOKEN_HPP
# define TOKEN_HPP
# include <string>
# include <sstream>

enum		tokenType {
	UNKNOWN = 0,
	LPARENTHESIS,
	RPARENTHESIS,
	OPERATOR,
	VALUE_OPERATOR,
	IPRECISION,
	FPRECISION,
	NATURAL_VAL,
	FLOATING_VAL,
	SEPARATOR,
	END_OF_FILE
};


class Token
{
	public:
		Token( void );
		Token( tokenType type , size_t line);
		Token( std::string const & value, size_t line);
		Token(Token const & src);
		~Token( void );
		Token &					operator=(Token const & rhs);
		const static std::string tokenTypeName[];
		std::string				getValue( void ) const;
		tokenType				getType( void ) const;
		std::string				toString( void ) const;
		size_t					getLine( void ) const;
		void					setType( tokenType type );

	private:
		std::string				_value;
		tokenType				_type;
		size_t					_line;

};

std::ostream &					operator<<(std::ostream & o, Token const & rhs);

#endif /* TOKEN_HPP */
