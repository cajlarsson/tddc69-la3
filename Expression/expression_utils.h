/*
 * expression_utils.h
 *
 * Hj�lpfunktioner f�r behandling av uttryck.
 */
#ifndef EXPRESSIONUTILS_H
#define EXPRESSIONUTILS_H
#include "Expression.h"
#include <stdexcept>
#include <string>

/*
 * Omvandling av infixuttryck till postfixuttryck. Om fel uppt�cks
 * kastas infix_error.
 */
class infix_error : public std::runtime_error
{
   public:
      explicit infix_error(const std::string& whar_arg = std::string()) 
	 : std::runtime_error(whar_arg) {}
};

/**
 * infix_to_postfix() tar en str�ng med ett infixuttryck som argument och
 * returnerasr en str�ng med motsvarande postfixuttryck.
 */
std::string infix_to_postfix(const std::string& infix);

/*
 * Generering av uttryckstr�d fr�n postfix. Om fel uppt�cks kastas 
 * postfix_error.
 */
class postfix_error : public std::runtime_error
{
   public:
      explicit postfix_error(const std::string& whar_arg = std::string()) 
	 : std::runtime_error(whar_arg) {}
};

/**
 * make_expression() tar en str�ng med ett postfixuttryck som argument,
 * anropar make_expression_tree() f�r att skapa motsvarande uttryckstr�d
 * och returnerar ett Expression-objekt med uttryckstr�det som intern 
 * representation.
 */
Expression make_expression(const std::string& postfix);

/**
 * make_expression_tree() tar en str�ng med ett postfixuttryck som argument,
 * skapar ett uttryckstr�d och returnerar det.
 */
Expression_Tree* make_expression_tree(const std::string& postfix);

#endif
