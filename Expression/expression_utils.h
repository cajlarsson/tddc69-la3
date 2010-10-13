/*
 * expression_utils.h
 *
 * Hjälpfunktioner för behandling av uttryck.
 */
#ifndef EXPRESSIONUTILS_H
#define EXPRESSIONUTILS_H
#include "Expression.h"
#include <stdexcept>
#include <string>

/*
 * Omvandling av infixuttryck till postfixuttryck. Om fel upptäcks
 * kastas infix_error.
 */
class infix_error : public std::runtime_error
{
   public:
      explicit infix_error(const std::string& whar_arg = std::string()) 
	 : std::runtime_error(whar_arg) {}
};

/**
 * infix_to_postfix() tar en sträng med ett infixuttryck som argument och
 * returnerasr en sträng med motsvarande postfixuttryck.
 */
std::string infix_to_postfix(const std::string& infix);

/*
 * Generering av uttrycksträd från postfix. Om fel upptäcks kastas 
 * postfix_error.
 */
class postfix_error : public std::runtime_error
{
   public:
      explicit postfix_error(const std::string& whar_arg = std::string()) 
	 : std::runtime_error(whar_arg) {}
};

/**
 * make_expression() tar en sträng med ett postfixuttryck som argument,
 * anropar make_expression_tree() för att skapa motsvarande uttrycksträd
 * och returnerar ett Expression-objekt med uttrycksträdet som intern 
 * representation.
 */
Expression make_expression(const std::string& postfix);

/**
 * make_expression_tree() tar en sträng med ett postfixuttryck som argument,
 * skapar ett uttrycksträd och returnerar det.
 */
Expression_Tree* make_expression_tree(const std::string& postfix);

#endif
