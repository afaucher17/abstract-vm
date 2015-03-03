#ifndef CALCULATOR_HPP
# define CALCULATOR_HPP
# include <string>
# include <sstream>
# include <iostream>

class Calculator
{
	public:
		Calculator( void );
		Calculator(Calculator const & src);
		~Calculator( void );
		Calculator &	operator=(Calculator const & rhs);
		std::string	toString() const;

	private:
};

std::ostream &		operator<<(std::ostream & o, Calculator const & rhs);

#endif /* CALCULATOR_HPP */
