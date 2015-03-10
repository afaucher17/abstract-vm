
#include "InstructionFactory.hpp"

InstructionFactory::InstructionFactory( void )
{
	return ;
}

InstructionFactory::~InstructionFactory( void )
{
	return ;
}

Instruction::e_type						InstructionFactory::_checkInstructionType(Token token)
{
	std::string							tab[] =
	{
		"push",
		"pop",
		"dump",
		"assert",
		"add",
		"sub",
		"mul",
		"div",
		"mod",
		"print",
		"exit"
	};
	for (int i = 0; i < 11; i++)
	{
		if (token.getValue().compare(tab[i]) == 0)
			return static_cast<Instruction::e_type>(i);
	}
	return static_cast<Instruction::e_type>(0);
}

eOperandType							InstructionFactory::_checkOperandType(Token token)
{
	std::string							tab[] =
	{
		"int8",
		"int16",
		"int32",
		"float",
		"double"
	};
	for (int i = 0; i < 5; i++)
	{
		if (token.getValue().compare(tab[i]) == 0)
			return static_cast<eOperandType>(i);
	}
	std::cout << "problem" << std::endl;
	return static_cast<eOperandType>(0);
}

std::list<Instruction>					*InstructionFactory::createInstructionList(std::list<Token> * tokens)
{
	std::list<Instruction> *			instructions = new std::list<Instruction>();
	std::list<Token>::const_iterator	it;
	Token								inst;
	Token								otype;

	for (it = tokens->begin(); it != tokens->end(); ++it)
	{
		if ((*it).getType() == OPERATOR)
			instructions->push_back(Instruction(this->_checkInstructionType((*it)), (*it).getLine()));
		if ((*it).getType() == VALUE_OPERATOR)
		{
			inst = (*it);
			++it;
			otype = (*it);
			++it;
			++it;
			instructions->push_back(Instruction(this->_checkInstructionType(inst), inst.getLine(), (*it).getValue(), this->_checkOperandType(otype)));
		}
	}
	return (instructions);
}
