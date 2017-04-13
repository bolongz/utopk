EXE = utopk
DEFINES = -g -ggdb
MYINCDIR = ./src/include
INCDIR =  -I$(MYINCDIR)
CC = g++ -std=c++11  -Wall
OPTFLAG= -O3 
CFLAGS = $(OPTFLAG)  $(INCDIR)
COMPILE = $(CC) $(CFLAGS) -c


OBJS= tuple.o state.o engine.o utopk.o ukrank.o caller.o test.o \
	   indenpukrank.o indenputopk.o


SUB=$(OBJS:%.o=obj/%.o)

ALL: $(EXE)

$(EXE): $(SUB)
	@$(CC) $(CFLAGS) -o  $(EXE) $(SUB)
	@echo linking $(@F)...
obj/%.o: src/%.cpp
	@$(COMPILE) -o  $@  $< $(MYINCLDIR)
	@echo compiling $(@F)...
clean:
	\rm -f ./obj/*.o  utopk
