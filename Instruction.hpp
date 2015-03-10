#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP
# include <string>
# include <sstream>
# include <iostream>
# include <cstring>
# include <cstdlib>
# include <list>
# include "OperandFactory.hpp"

class Instruction
{
	public:
		class InstructionException : public std::exception
		{
		};
		class EmptyStackException : public InstructionException
		{
			public:
				virtual const char *	what() const throw();
		};
		class AssertException : public InstructionException
		{
			public:
				virtual const char *	what() const throw();
		};
		class NotEnoughValuesException : public InstructionException
		{
			public:
				virtual const char *	what() const throw();
		};
		enum e_type
		{
			PUSH = 0,
			POP = 1,
			DUMP = 2,
			ASSERT = 3,
			ADD = 4,
			SUB = 5,
			MUL = 6,
			DIV = 7,
			MOD = 8,
			PRINT = 9,
			EXIT = 10
		};
		Instruction( e_type type, size_t line );
		Instruction( e_type type, size_t line, std::string value, eOperandType otype );
		Instruction(Instruction const & src);
		~Instruction( void );
		Instruction &	operator=(Instruction const & rhs);
		bool			execute_fun(std::list<const IOperand *> & stk) const;

	private:
		e_type			_type;
		size_t			_line;
		std::string		_value;
		eOperandType	_otype;

		Instruction( void );
		bool		_push(std::list<const IOperand *> & stk) const;
		bool		_pop(std::list<const IOperand *> & stk) const;
		bool		_dump(std::list<const IOperand *> & stk) const;
		bool		_assert(std::list<const IOperand *> & stk) const;
		bool		_add(std::list<const IOperand *> & stk) const;
		bool		_sub(std::list<const IOperand *> & stk) const;
		bool		_mul(std::list<const IOperand *> & stk) const;
		bool		_div(std::list<const IOperand *> & stk) const;
		bool		_mod(std::list<const IOperand *> & stk) const;
		bool		_print(std::list<const IOperand *> & stk) const;
		bool		_exit(std::list<const IOperand *> & stk) const;
};

typedef	bool (Instruction::*fun) (std::list<const IOperand *> & stk) const;
#endif /* INSTRUCTION_HPP */
