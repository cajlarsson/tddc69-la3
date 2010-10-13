/*
 * Calculator.cc
 */
#include "Expression.h"
#include "expression_utils.h"
#include "Calculator.h"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

const string Calculator::valid_command_("?HBPMS");

/**
 * run() är huvudfunktionen för kalkylatorn. Skriver först ut hur man använder
 * kalkylatorn. Läser sedan sedan in ett kommando i taget och utför det.
 */
void
Calculator::
run()
{
   cout << "Välkommen till Kalkylatorn!\n\n";
   print_help();

   for (;;) // "for ever"
   {
      try
      {
	 do
	 {
	    get_command();
	    if (valid_command()) execute_command();
	 }
	 while (command_ != 'S');

	 break; // for
      }
      catch (const exception& e)
      {
	 cout << e.what() << "\n";
      }
   }
}

/**
 * print_help() skriver ut kommandorepertoaren.
 */
void
Calculator::
print_help()
{
   cout << "  H, ?  Skriv ut denna information\n";
   cout << "  B     Beräkna aktuellt uttryck\n";
   cout << "  P     Visa aktuellt uttryck som postfix\n";
   cout << "  M     Mata in ett nytt uttryck\n";
   cout << "  S     Avsluta kalkylatorn\n";
}

/**
 * get_command() läser ett kommando från standardströmmen cin. Ett tecken 
 * läses, görs om till versal och lagras i medlemmen command_, för vidare
 * behandling av andra operationer. Ingen kontroll görs om det skrivits 
 * mer, i så fall skräp, på kommandoraden.
 */
void
Calculator::
get_command()
{
   cout << ">> ";
   cin >> command_;
   command_ = toupper(command_);
}

/**
 * valid_command() kontrollerar om kommandot som finns i medlemmen command_
 * tillhör den tillåtna kommandorepertoraren och returnerar antingen true
 * (giltigt kommando) eller false (ogiltigt kommando).
 */
bool
Calculator::
valid_command()
{
   if (valid_command_.find(command_) == string::npos)
   {
      cout << "Otillåtet kommando: " << command_ << "\n";
      return false;
   }
   return true;
}

/**
 * execute_command() utför kommandot som finns i medlemmen command_. Kommandot
 * förutsätts ha kontrollerats med valid_command() och är ett giltigt kommando.
 */
void
Calculator::
execute_command()
{
   if (command_ == 'H' || command_ == '?')
      print_help();
   else if (command_ == 'B')
      cout << current_expression_.evaluate() << "\n";
   else if (command_ == 'P')
      cout << current_expression_.get_postfix() << "\n";
   else if (command_ == 'S')
      cout << "Kalkylatorn avlutas, välkommen åter!\n";
   else if (command_ == 'M')
      read_expression(cin);
   else
      cout << "Detta ska inte hända!\n";
}

/**
 * read_expression() läser ett infixuttryck från inströmmen is och genererar
 * ett motsvarande uttrycksträd. infix_to_postfix() används för att omvandla
 * det lästa infixuttrycket till ett motsvarande postfixuttryck. postfixuttrycket
 * ges sedan till funktionen make_expression() som returnerar ett objekt av
 * typen Expression, vilket lagras som  aktuellt uttryck i current_expression_.
 */
void
Calculator::
read_expression(istream& is)
{
   string infix;

   is >> ws;

   if (getline(is, infix))
   {
      current_expression_ = make_expression(infix_to_postfix(infix));
   }
   else
   {
      cout << "Felaktig inmatning!\n";
   }
}
