/*
 * expression-tree-test-0.cc
 *
 * Test av abstrakthet, konstruktorer, kopiering, evaluate(), get_postfix()
 * och str().
 */
#include "Expression_Tree.h"
#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
   // Ska inte vara möjligt - dessa klasser ska vara abstrakta.
   // Expression_Tree* t1 = new Expression_Tree;
   // Expression_Tree* t2 = new Operator(0, 0);
   // Expression_Tree* t3 = new Operand;

   Plus* p1 = new Plus(0, 0);
   Plus* p2 = new Plus(0, 0);

   // Ska inte vara möjligt att skapa och kopiera på dessa sätt.
   // Plus  p0;                   // Defaultkonstruktor
   // Plus  p3(*p1);              // Kopieringskonstruktor
   // *p1 = *p2;                  // Kopieringstilldelning

   Expression_Tree* t1 = new Plus(new Integer(7), new Real(3.14));

   try
   {
      cout << "t1->evaluate() = " << t1->evaluate() << '\n';
   }
   catch (const exception& e)
   {
      cout << "Undantag fångat: " << e.what() << '\n';
   }

   cout << "t1->get_postfix() = " << t1->get_postfix() << '\n';
   cout << "t1->str() = " << t1->str() << "\n\n";

   Expression_Tree* t2 = t1->clone();

   try
   {
      cout << "t2->evaluate() = " << t2->evaluate() << '\n';
   }
   catch (const exception& e)
   {
      cout << "Undantag fångat: " << e.what() << '\n';
   }
   cout << "t2->get_postfix() = " << t2->get_postfix() << '\n';
   cout << "t2->str() = " << t2->str() << "\n\n";

   return 0;
}
