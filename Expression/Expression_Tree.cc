/*
 * Expression_Tree.cc
 */
#include "Expression_Tree.h"
#include <limits>     // Tillfälligt, för numeric_limits
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

// Gör separata definitioner för för Expression_Tree-klasserna här.

// STUBBAR:
/*
double Expression_Tree::evaluate() const
{
	return numeric_limits<double>::infinity();
}

std::string Expression_Tree::get_postfix() const
{
	return string();
}

std::string Expression_Tree::str() const
{
	return string();
}

Expression_Tree* Expression_Tree::clone() const
{
	return 0;
}

*/
std::string Operator::get_postfix() const
{
	return left->get_postfix()+" " + right->get_postfix()+ " " + str();
}

Operator::Operator(void* left, void* right)
{
	this->left = (Expression_Tree*)left;
	this->right = (Expression_Tree*)right;
}

double Plus::evaluate() const
{
	return left->evaluate() + right->evaluate();
}

std::string Plus::str() const
{
	return "+";
}

Expression_Tree* Plus::clone() const 
{
	return new Plus( left->clone(),right->clone());
}

double Minus::evaluate() const
{
	return left->evaluate() - right->evaluate();
}

std::string Minus::str() const
{
	return "-";
}

Expression_Tree* Minus::clone() const 
{
	return new Minus( left->clone(),right->clone());
}

double Times::evaluate() const
{
	return left->evaluate() * right->evaluate();
}

std::string Times::str() const
{
	return "*";
}

Expression_Tree* Times::clone() const 
{
	return new Times( left->clone(),right->clone());
}

double Divide::evaluate() const
{
	return left->evaluate() / right->evaluate();
}

std::string Divide::str() const
{
	return "/";
}

Expression_Tree* Divide::clone() const 
{
	return new Divide( left->clone(),right->clone());
}
 
double Power::evaluate() const
{
	double x = left->evaluate();

	if (x == 0.0)
		return 1.0;
	else
		return pow(x, right->evaluate());
}

std::string Power::str() const
{
	return "^";
}

Expression_Tree* Power::clone() const 
{
	return new Power( left->clone(),right->clone());
}

Operator::~Operator()
{
	delete right;
	delete left;
}

Integer::Integer(int integer)
{
	this->integer = integer;
}

double Integer::evaluate() const
{
	return integer;
}

std::string Integer::str() const
{
	std::ostringstream stream ;
	stream << integer;
	return stream.str();
}

std::string Integer::get_postfix() const
{
	return str();
}

Expression_Tree* Integer::clone() const
{
	return new Integer(integer);
}

Real::Real(double real)
{
	this->real = real;
}

double Real::evaluate() const
{
	return real;
}

std::string Real::str() const
{
	std::ostringstream stream;
	stream<< real;
	return stream.str();
}

std::string Real::get_postfix() const
{
	return str();
}

Expression_Tree* Real::clone() const
{
	return new Real(real);
}
