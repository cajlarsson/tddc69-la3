/*
 * expression-test-0.cc
 *
 * Test av defaultkonstruktor, kopieringskonstruktor, empty(), evaluate(),
 * och get_postfix().
 */
#include "Expression.h"
#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
   Expression e1;  // Defaultkonstruktor

   if (e1.empty())
      cout << "Tomt uttryck!\n";
   else
      cout << "e1.evaluate() = " << e1.evaluate() << '\n';

   cout << "e1.get_postfix() = " << e1.get_postfix() << '\n';

   cout << boolalpha << "e1.empty() = " << e1.empty() << "\n\n";

   Expression e2(e1);  // Kopieringskonstruktor

   try
   {
      cout << "e2.evaluate() = " << e2.evaluate() << '\n';
   }
   catch (const exception& e)
   {
      cout << "Undantag fångat: " << e.what() << '\n';
   }

   cout << "e2.get_postfix() = " << e2.get_postfix() << '\n';
   cout << "e2.empty() = " << e2.empty() << "\n\n";
   
   e2.swap(e1);

   // Fler tester kräver implementering av Expression_Tree-klasserna.

   return 0;
}
