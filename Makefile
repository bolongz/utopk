EXE = topk
DEFINES = -g -ggdb
MYINCDIR = ./src/include
INCDIR =  -I$(MYINCDIR)
CC = g++ -std=c++11  -Wall
OPTFLAG= -O3 
CFLAGS = $(OPTFLAG)  $(INCDIR)
COMPILE = $(CC) $(CFLAGS) -c

OBJS= tuple.o state.o engine.o utopk.o ukrank.o

SUB=$(OBJS:%.o=obj/%.o)

ALL: $(EXE)

$(EXE): $(SUB)
	$(CC) $(CFLAGS) -o  $(EXE) $(SUB)

obj/%.o: src/%.cpp src/include/%.h
	@$(COMPILE) -o  $@  $< $(MYINCLDIR)

clean:
	\rm -f ./obj/*.o  topk
