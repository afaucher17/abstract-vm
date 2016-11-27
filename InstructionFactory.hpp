#ifndef INSTRUCTIONFACTORY_HPP
# define INSTRUCTIONFACTORY_HPP
# include <string>
# include <sstream>
# include <iostream>
# include <list>
# include "Instruction.hpp"
# include "Token.hpp"

class InstructionFactory
{
	public:
		InstructionFactory( void );
		~InstructionFactory( void );
		std::list<Instruction>		*createInstructionList(std::list<Token> * tokens);

	private:
		Instruction::e_type		_checkInstructionType(Token token);
		eOperandType			_checkOperandType(Token token);
};

#endif /* INSTRUCTIONFACTORY_HPP */
