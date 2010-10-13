/*
 * Expression.h
 */
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "Expression_Tree.h"
#include <stdexcept>
#include <string>

/**
 * expression_error kastas om fel inträffar i en Expression-operation.
 */
class expression_error : public std::runtime_error
{
   public:
      explicit expression_error(const std::string& what_arg = "")
	 : std::runtime_error(what_arg) {}
};

/**
 * Expression
 */
class Expression
{
public:
      // En hel del viktiga saker kvar att tänka på, även i detta givna ...
	Expression();
	Expression(Expression_Tree* );
	Expression(const Expression& exp);
	Expression operator= (Expression exp);
	double      evaluate() const;
	std::string get_postfix() const;
	bool        empty() const;
	void        swap(Expression&);
private:
	Expression_Tree *tree;
};

#endif
