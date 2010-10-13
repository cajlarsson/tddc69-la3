/*
 * Expression.cc
 */
#include "Expression.h"
#include <limits>     // Tillfälligt, för numeric_limits
#include <stdexcept>
#include <string>
using namespace std;

// Gör separata definitioner för för Expression-klassen här.

// STUBBAR!

Expression::Expression(Expression_Tree* tree) 
{
	this->tree = tree;
}

Expression::Expression()
{
	tree = NULL;
}

Expression::Expression(const Expression& exp)
{
	this->tree = exp.tree->clone();
}
Expression Expression::operator=(Expression exp)
{
	exp.swap(*this);
	return *this;
}

double Expression::evaluate() const
{
	return tree->evaluate();
}

std::string Expression::get_postfix() const
{
	return tree->get_postfix();
}

bool Expression::empty() const
{
	return (tree == NULL);
}

void Expression::swap(Expression& exp)
{
	if (this->tree != exp.tree)
	{
		Expression_Tree *temp = this->tree;
		this->tree = exp.tree;
		exp.tree = temp;
	}
}

void swap(Expression& exp1, Expression& exp2)
{
	exp1.swap(exp2);
}

