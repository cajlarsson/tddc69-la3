#
# Makefile för kalkylatorn, kompilering med GNU GCC (g++)
#
# Filkataloger där olika delar av programvaran finns.
EXPRESSION = ../Expression

# Kompilator och flaggor som påverkar kompilering, inkludering, etc. 
# Lägg till '-g' i CCFLAGS om kompilering för avlusning ska göras.
CCC = g++
CCFLAGS  += -std=c++98 -pedantic -Wall -Wextra -g
CPPFLAGS += -I$(EXPRESSION)

# Gemensamma objektmoduler
LIBS = Calculator.o Expression.o Expression_Tree.o expression_utils.o 

# Objektkodsmoduler som ingår i den kompletta kalkylatorn
OBJECTS = kalkylator.o $(LIBS) 

# Objektkodsmoduler som ingår i test1
TEST_OBJECTS_1 = expression-tree-test-0.o $(LIBS) 

# Objektkodsmoduler som ingår i test2
TEST_OBJECTS_2 = expression-tree-test.o $(LIBS) 

# Huvudmål - skapas med kommandot 'make' eller 'make kalkylator'
kalkylator: $(OBJECTS) Makefile
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -o kalkylator $(OBJECTS)

# Testprogram 1 - Körs med kommandot 'make test1'
test1: $(TEST_OBJECTS_1) Makefile
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -o test1 $(TEST_OBJECTS_1)
	./test1

# Testprogram 2 - Körs med kommandot 'make test2'
test2: $(TEST_OBJECTS_2) Makefile
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -o test2 $(TEST_OBJECTS_2)
	./test2

# Körmål - körs med 'make run' bygger kalkylatorn och kör den
run: kalkylator
	./kalkylator

# Kör dessa mål även om inget har uppdaterats
.PHONY: run test1 test2

# Delmål
kalkylator.o: kalkylator.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c kalkylator.cc

Calculator.o: Calculator.h Calculator.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Calculator.cc

Expression.o: $(EXPRESSION)/Expression.h $(EXPRESSION)/Expression.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(EXPRESSION)/Expression.cc

Expression_Tree.o: $(EXPRESSION)/Expression_Tree.h $(EXPRESSION)/Expression_Tree.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(EXPRESSION)/Expression_Tree.cc

expression_utils.o: $(EXPRESSION)/expression_utils.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(EXPRESSION)/expression_utils.cc

expression-tree-test-0.o: $(EXPRESSION)/expression-tree-test-0.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(EXPRESSION)/expression-tree-test-0.cc

expression-tree-test.o: $(EXPRESSION)/expression-tree-test.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(EXPRESSION)/expression-tree-test.cc

# 'make clean' tar bort objektkodsfiler och 'core'
clean:
	@ \rm -rf *.o core

# 'make zap' tar också bort det körbara programmet och reservkopior (filer
# som slutar med tecknet '~')
zap: clean
	@ \rm -rf kalkylator test1 test2 *~

