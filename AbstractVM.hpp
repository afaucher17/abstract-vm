#ifndef ABSTRACTVM_HPP
# define ABSTRACTVM_HPP
# include <string>
# include <sstream>
# include <iostream>
# include <string>
# include "Tokenizer.hpp"
# include "InstructionFactory.hpp"
# include "Parser.hpp"
# include "Analyzer.hpp"

class AbstractVM
{
	public:
		class AbstractVMException : public std::exception
		{
		};
		class NoExitException : public AbstractVMException
		{
			virtual const char *	what() const throw();
		};
		AbstractVM( void );
		int				run(std::string const & program);
	private:
		void			_compute(std::list<Instruction> & instructions, std::list<const IOperand *> & stk);
};
#endif /* ABSTRACTVM_HPP */
