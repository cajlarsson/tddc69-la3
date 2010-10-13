/*
 * expression_utils.cc
 */
#include "Expression.h"
#include "Expression_Tree.h"
#include "expression_utils.h"
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <map>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
   // Anonym namnrymd begränsar användningen av medlemmarna till denna fil
   using std::vector;
   using std::map;
   using std::make_pair;
   using std::string;

   // Underlag för att skapa prioritetstabellerna, mm. Högre värde inom
   // input_prio respektive stack_prio anger inbördes prioritetsordning.
   // Högre värde i input_prio jämfört med motsvarande position i stack_prio
   // innebär högerassociativitet, det motsatta vänsterassociativitet.
   const char* ops[]        = { "^", "*", "/", "+", "-" };
   const int   input_prio[] = {  6,   3,   3,   1,   1  };
   const int   stack_prio[] = {  5,   4,   4,   2,   2  };
   const int   n_tokens = sizeof ops / sizeof (char*);
   const int   n_ops    = n_tokens;

   // Tillåtna operatorer. Används av infix_to_postfix() och make_expression_tree().
   const vector<string> operators(ops, ops + n_ops);

   // Teckenuppsättningar för operander. Används av make_expression_tree().
   const string digit("0123456789");
   const string integer_char(digit);
   const string real_char(digit + '.');
   const string operand_char(digit + '.');

   // Prioritetstabeller. Används av infix_to_postfix().
   typedef map<string, int> priority_table;

   // Funktion för att initiera en prioritetstabell, givet de tillåtna operatorerna, deras
   // prioritieter (inkommandeprioritet eller stackprioritet, beroende på vilken tabell som
   // ska skapas) och antalet operatorer.
   priority_table init_priority_table(const char* op[], const int* prio, const int n_tokens)
   {
      priority_table pm;

      for (int i = 0; i < n_tokens; ++i)
      {
	 pm.insert(make_pair(string(op[i]), prio[i]));
      }

      return pm;
   }

   // Prioritetstabellerna, en för inkommandeprioritet och en för stackprioritet.
   const priority_table input_priority = init_priority_table(ops, input_prio, n_tokens);
   const priority_table stack_priority = init_priority_table(ops, stack_prio, n_tokens);

} // namespace

/*
 * infix_to_postfix()
 */
std::string infix_to_postfix(const std::string& infix)
{
   using std::stack;
   using std::string;
   using std::istringstream;
   using std::find;

   stack<string> operator_stack;
   string        token;
   string        previous_token = "";
   bool          last_was_operand = false;
   int           paren_count = 0;
   istringstream is(infix);
   string        postfix;
   
   while (is >> token)
   {
      if (find(operators.begin(), operators.end(), token) != operators.end())
      {
	 if (! last_was_operand || postfix.empty() || previous_token == "(")
	 {
	    throw infix_error("operator där operand förväntades"); 
	 }

	 while (! operator_stack.empty() && operator_stack.top() != ")" &&
		input_priority.find(token)->second <= 
		stack_priority.find(operator_stack.top())->second)
	 {
	    postfix += operator_stack.top() + ' ';
	    operator_stack.pop();
	 }
	 operator_stack.push(token);
	 last_was_operand = false;
      }
      else if (token == "(")
      {
	 operator_stack.push(token);
	 ++paren_count;
      }
      else if (token == ")")
      {
	 if (paren_count == 0)
	 {
	    throw infix_error("vänsterparentes saknas");
	 }

	 if (previous_token == "(" && ! postfix.empty())
	 {
	    throw infix_error("tom parentes");
	 }

	 while (! operator_stack.empty() && operator_stack.top() != "(")
	 {
	    postfix += operator_stack.top() + ' ';
	    operator_stack.pop();
	 }
	 operator_stack.pop();
	 --paren_count;
      }
      else if (token.find_first_not_of(operand_char) == string::npos)
      {
	 if (last_was_operand || previous_token == ")")
	 {
	    throw infix_error("operand där operator förväntades"); 
	 }
	 postfix += token + ' '; 
	 last_was_operand = true;
      }
      else
      {
	 throw infix_error("otillåten symbol"); 
      }

      previous_token = token;
   }

   if ((! last_was_operand) && (! postfix.empty()))
   {
      throw infix_error("operator avslutar"); 
   }

   if (paren_count > 0)
   {
      throw infix_error("högerparentes saknas"); 
   }

   while (! operator_stack.empty())
   {
      postfix += operator_stack.top() + ' ';
      operator_stack.pop();
   }

   if (! postfix.empty())
   {
      postfix.erase(postfix.size() - 1);
   }

   return postfix;
}

/*
 * make_expression()
 */
Expression make_expression(const std::string& postfix)
{
   return Expression(make_expression_tree(postfix));
}

/*
 * make_expression_tree()
 */
Expression_Tree* make_expression_tree(const std::string& postfix)
{
   using std::stack;
   using std::string;
   using std::istringstream;
   using std::find;

   stack<Expression_Tree*> tree_stack;
   string                  token;
   istringstream           is(postfix); 

   while (is >> token)
   {
      if (find(operators.begin(), operators.end(), token) != operators.end())
      {
         // Operator
	 Expression_Tree* rhs = tree_stack.top();
	 tree_stack.pop();
	 Expression_Tree* lhs = tree_stack.top();
	 tree_stack.pop();

	 if (token == "^") 
         {
	    tree_stack.push(new Power(lhs, rhs));
         }
	 else if (token == "*") 
         {
	    tree_stack.push(new Times(lhs, rhs));
         }
	 else if (token == "/") 
	 {
	    tree_stack.push(new Divide(lhs, rhs));
	 }
 	 else if (token == "+") 
         {
	    tree_stack.push(new Plus(lhs, rhs));
         }
	 else if (token == "-") 
         {
	    tree_stack.push(new Minus(lhs, rhs));
         }
      }
      else
      {
	 // Operand
	 if (token.find_first_not_of(integer_char) == string::npos)
	 {
	    tree_stack.push(new Integer(atoi(token.c_str())));
	 }
	 else if (token.find_first_not_of(real_char) == string::npos)
	 {
	    tree_stack.push(new Real(atof(token.c_str())));
	 }
      }
   }

   if (tree_stack.empty())
   {
      throw postfix_error();
   }

   if (tree_stack.size() > 1)
   {
      while (! tree_stack.empty())
      {
	 delete tree_stack.top();
	 tree_stack.pop();
      }
      throw postfix_error();
   }

   // One tree on stack, give it to the Expression object, the stack vanishes.
   return tree_stack.top();
}
