#include "Instruction.hpp"

const char *		Instruction::PopEmptyStackException::what() const throw()
{
	return ("Pop on empty stack");
}

const char *		Instruction::AssertEmptyStackException::what() const throw()
{
	return ("Assert on empty stack");
}

const char  *		Instruction::PrintEmptyStackException::what() const throw()
{
	return ("Print on empty stack");
}

const char *		Instruction::EmptyStackException::what() const throw()
{
	return ("The stack is empty.");
}

const char *		Instruction::AssertException::what() const throw()
{
	return ("The asserted value is not the one expected.");
}

const char *		Instruction::NotEnoughValuesException::what() const throw()
{
	return ("Not enough values in the stack");
}

const char *		Instruction::PrintNotCharException::what() const throw()
{
	return ("The value on top on the stack is not an Int8");
}

Instruction::Instruction( e_type type, size_t line ) : _type(type), _line(line)
{
	return ;
}

Instruction::Instruction( e_type type, size_t line, std::string value, eOperandType otype ) : _type(type), _line(line), _value(value), _otype(otype)
{
	return ;
}

Instruction::Instruction( Instruction const & src )
{
	*this = src;
	return ;
}

Instruction::~Instruction( void )
{
	return ;
}

Instruction &		Instruction::operator=( Instruction const & rhs )
{
	this->_type = rhs._type;
	this->_line = rhs._line;
	this->_value = rhs._value;
	this->_otype = rhs._otype;
	return *this;
}

bool				Instruction::execute_fun(std::list<const IOperand *> & stk) const
{
	fun tab[] =
	{
		&Instruction::_push,
		&Instruction::_pop,
		&Instruction::_dump,
		&Instruction::_assert,
		&Instruction::_add,
		&Instruction::_sub,
		&Instruction::_mul,
		&Instruction::_div,
		&Instruction::_mod,
		&Instruction::_print,
		&Instruction::_exit
	};
	bool res = false;
	try {
		res = (this->*tab[this->_type])(stk);
		return (res);
	}
	catch (const InstructionException & e)
	{
		std::cerr << "Line " << this->_line << " : Error : " << e.what() << std::endl;
		throw;
	}
	catch (const OperandFactory::OperandException & e)
	{
		std::cerr << "Line " << this->_line << " : Error : " << e.what() << std::endl;
		throw;
	}
	catch (const Calculator::CalculatorException & e)
	{
		std::cerr << "Line " << this->_line << " : Error : " << e.what() << std::endl;
		throw;
	}
}

bool				Instruction::_push(std::list<const IOperand *> & stk) const
{
	OperandFactory			of;

	stk.push_front(of.createOperand(this->_otype, this->_value));
	return (false);
}

bool				Instruction::_pop(std::list<const IOperand *> & stk) const
{
	const IOperand *		op;

	if (stk.empty())
		throw PopEmptyStackException();
	op = (*stk.begin());
	stk.pop_front();
	delete op;
	return (false);
}

bool				Instruction::_dump(std::list<const IOperand *> & stk) const
{
	std::list<const IOperand *>::const_iterator it;

	for (it = stk.begin(); it != stk.end(); ++it)
		std::cout << (*it)->toString() << std::endl;
	return (false);
}

bool				Instruction::_assert(std::list<const IOperand *> & stk) const
{
	OperandFactory			of;
	const IOperand *		op1;
	const IOperand *		op2;

	if (stk.empty())
		throw AssertEmptyStackException();
	op1 = of.createOperand(this->_otype, this->_value);
	op2 = (*stk.begin());
	if (op1->getType() != op2->getType() || op1->toString().compare(op2->toString()) != 0)
		throw AssertException();
	return (false);
}

bool				Instruction::_add(std::list<const IOperand *> & stk) const
{
	const IOperand *		op1;
	const IOperand *		op2;

	if (stk.empty())
		throw EmptyStackException();
	if (stk.size() < 2)
		throw NotEnoughValuesException();
	op1 = (*stk.begin());
	stk.pop_front();
	op2 = (*stk.begin());
	stk.pop_front();
	stk.push_front(*op2 + *op1);
	delete op1;
	delete op2;
	return (false);
}

bool				Instruction::_sub(std::list<const IOperand *> & stk) const
{
	const IOperand *		op1;
	const IOperand *		op2;

	if (stk.empty())
		throw EmptyStackException();
	if (stk.size() < 2)
		throw NotEnoughValuesException();
	op1 = (*stk.begin());
	stk.pop_front();
	op2 = (*stk.begin());
	stk.pop_front();
	stk.push_front(*op2 - *op1);
	delete op1;
	delete op2;
	return (false);
}

bool				Instruction::_mul(std::list<const IOperand *> & stk) const
{
	const IOperand *		op1;
	const IOperand *		op2;

	if (stk.empty())
		throw EmptyStackException();
	if (stk.size() < 2)
		throw NotEnoughValuesException();
	op1 = (*stk.begin());
	stk.pop_front();
	op2 = (*stk.begin());
	stk.pop_front();
	stk.push_front(*op2 * *op1);
	delete op1;
	delete op2;
	return (false);
}

bool				Instruction::_div(std::list<const IOperand *> & stk) const
{
	const IOperand *		op1;
	const IOperand *		op2;

	if (stk.empty())
		throw EmptyStackException();
	if (stk.size() < 2)
		throw NotEnoughValuesException();
	op1 = (*stk.begin());
	stk.pop_front();
	op2 = (*stk.begin());
	stk.pop_front();
	stk.push_front(*op2 / *op1);
	delete op1;
	delete op2;
	return (false);
}

bool				Instruction::_mod(std::list<const IOperand *> & stk) const
{
	const IOperand *		op1;
	const IOperand *		op2;

	if (stk.empty())
		throw EmptyStackException();
	if (stk.size() < 2)
		throw NotEnoughValuesException();
	op1 = (*stk.begin());
	stk.pop_front();
	op2 = (*stk.begin());
	stk.pop_front();
	stk.push_front(*op2 % *op1);
	delete op1;
	delete op2;
	return (false);
}

bool				Instruction::_print(std::list<const IOperand *> & stk) const
{
	OperandFactory			of;
	const IOperand *		op1;

	if (stk.empty())
		throw EmptyStackException();
	op1 = (*stk.begin());
	if (op1->getType() == INT8)
		throw PrintNotCharException();
	std::cout << static_cast<char>(std::atoi(op1->toString().c_str())) << std::endl;
	return (false);
}

bool				Instruction::_exit(std::list<const IOperand *> & stk) const
{
	static_cast<void>(stk);
	return (true);
}
