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
 * run() �r huvudfunktionen f�r kalkylatorn. Skriver f�rst ut hur man anv�nder
 * kalkylatorn. L�ser sedan sedan in ett kommando i taget och utf�r det.
 */
void
Calculator::
run()
{
   cout << "V�lkommen till Kalkylatorn!\n\n";
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
   cout << "  B     Ber�kna aktuellt uttryck\n";
   cout << "  P     Visa aktuellt uttryck som postfix\n";
   cout << "  M     Mata in ett nytt uttryck\n";
   cout << "  S     Avsluta kalkylatorn\n";
}

/**
 * get_command() l�ser ett kommando fr�n standardstr�mmen cin. Ett tecken 
 * l�ses, g�rs om till versal och lagras i medlemmen command_, f�r vidare
 * behandling av andra operationer. Ingen kontroll g�rs om det skrivits 
 * mer, i s� fall skr�p, p� kommandoraden.
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
 * tillh�r den till�tna kommandorepertoraren och returnerar antingen true
 * (giltigt kommando) eller false (ogiltigt kommando).
 */
bool
Calculator::
valid_command()
{
   if (valid_command_.find(command_) == string::npos)
   {
      cout << "Otill�tet kommando: " << command_ << "\n";
      return false;
   }
   return true;
}

/**
 * execute_command() utf�r kommandot som finns i medlemmen command_. Kommandot
 * f�ruts�tts ha kontrollerats med valid_command() och �r ett giltigt kommando.
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
      cout << "Kalkylatorn avlutas, v�lkommen �ter!\n";
   else if (command_ == 'M')
      read_expression(cin);
   else
      cout << "Detta ska inte h�nda!\n";
}

/**
 * read_expression() l�ser ett infixuttryck fr�n instr�mmen is och genererar
 * ett motsvarande uttryckstr�d. infix_to_postfix() anv�nds f�r att omvandla
 * det l�sta infixuttrycket till ett motsvarande postfixuttryck. postfixuttrycket
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
