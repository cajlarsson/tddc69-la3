/*
 * Expression_Tree.h
 */
#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include <stdexcept>
#include <string>
#include <cmath>

/**
 * expression_tree_error kastas om fel intr�ffar i en Expression_Tree-operation.
 */
class expression_tree_error : public std::runtime_error
{
   public:
      explicit expression_tree_error(const std::string& what_arg = "")
	 : std::runtime_error(what_arg) {}
};

/**
 * Expression_Tree - abstrakt basklass f�r alla tr�dnodklasser.
 */
class Expression_Tree
{
public:
      // En hel del viktiga saker kvar att t�nka p�, �ven i detta givna ...
	virtual double evaluate() const =0;
	virtual std::string get_postfix() const =0;
	virtual std::string str() const = 0;
	virtual Expression_Tree* clone() const =0;
};

// Definiera subklasserna till Expression_Tree h�r.

// F�LJANDE DEFINITIONER �R ENBART F�R ATT DET GIVNA PROGRAMMET SKA KOMPILERA,
// N�RMARE BEST�MT FUNKTIONEN make_expression(), SOM SKAPAR OBJEKT AV DESSA 
// TYPER. ERS�TT MED HELT NYA DEFINITIONER, I STIL MED Expression_Tree OVAN.
// Expression_Tree SKA INTE VARA DIREKT BASKLASS TILL DESSA KLASSER. DEFINIERA
// OM DESSA SOM FULLFJ�DRADE KLASSER! 

class Operator : public Expression_Tree
{
protected:
	Expression_Tree *right;
	Expression_Tree *left;
public:
	Operator (void* left, void* right);
	virtual double evaluate() const = 0;
	virtual std::string str() const = 0;
	virtual Expression_Tree* clone() const = 0;
	std::string get_postfix() const;
	~Operator();
};

class Operand : public Expression_Tree
{
public:
	virtual double evaluate() const = 0;
	virtual std::string str() const = 0;
	virtual Expression_Tree* clone() const = 0;
};


class Plus : public Operator
{
public:
Plus(void* left, void* right) : Operator(left,right){};
	double evaluate() const;
	std::string str() const;
	Expression_Tree* clone() const;
};

class Minus : public Operator
{
public:
Minus(void* left, void* right) : Operator(left,right){};
	double evaluate() const;
	std::string str() const;
	Expression_Tree* clone() const;
};

class Times : public Operator
{
public:
Times(void* left, void* right) : Operator(left,right){};
	double evaluate() const;
	std::string str() const;
	Expression_Tree* clone() const;
};

class Divide : public Operator
{
public:
Divide(void* left, void* right) : Operator(left,right){};
	double evaluate() const;
	std::string str() const;
	Expression_Tree* clone() const;
};

class Power : public Operator
{
public:
Power(void* left, void* right) : Operator(left,right){};
	double evaluate() const;
	std::string str() const;
	Expression_Tree* clone() const;
};
 
class Integer : public Operand
{
private:
	int integer;
public:
	Integer(int integer);
	double evaluate() const;
	std::string str() const;
	Expression_Tree* clone() const;
	std::string get_postfix() const;
};

class Real : public Operand
{
private:
	double real;
public:
	Real(double real);
	double evaluate() const;
	std::string str() const;
	Expression_Tree* clone() const;
	std::string get_postfix() const;
};



//struct Plus    : Expression_Tree { Plus(void*, void*) {} };
//struct Minus   : Expression_Tree { Minus(void*, void*) {} };
//struct Times   : Expression_Tree { Times(void*, void*) {} };
//struct Divide  : Expression_Tree { Divide(void*, void*) {} };
//struct Power   : Expression_Tree { Power(void*, void*) {} };
//struct Integer : Expression_Tree { Integer(int) {} };
//struct Real    : Expression_Tree { Real(double) {} };

#endif
