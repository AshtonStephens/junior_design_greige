# Makefile
#
# Purpose: to compile logistic regression alg
# By: Ashton Stephens
# Date : 03/06/18
#

IDIRS	  = ./
SERIAL_RX = FRSKY
SERIAL_TX = SEND7 

# # # # # # # # # # # # # # # # 
# This is where you keep your .h files

CC 	= clang++
IFLAGS  = $(patsubst %,-I%,$(IDIRS))
CFLAGS  = -g -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)
LDFLAGS = 
DBFLAGS = -g -DDEBUG
LDLIBS  = -lrt -lpthread -lm
RM_OBJS = && rm *.o

PROTOCALLS = $(SERIAL_RX) $(SERIAL_TX)
DEF_FLAGS = $(patsubst %,-D%,$(PROTOCALLS))

%.o: %.cpp
	$(CC) $(DEF_FLAGS) $(CFLAGS) -c -o $@ $<

%.o.test: %.cpp
	$(CC) $(DEF_FLAGS) $(DBFLAGS) $(CFLAGS) -c -o $*.o $<


# # # # # # # # # # # # # # # # 
# stuff you might have to change 
# 	|	|	|
# 	V	V	V

EXECUTABLES    = main

MAIN_INCLUDES  = regression2.o

#
# # # # # # # # # # # # # # # # 

main: $(MAIN_INCLUDES)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(RM_OBJS) 
main_test: $(patsubst %,%.test,$(MAIN_INCLUDES))
	$(CC) $(LDFLAGS) -o $@ $(MAIN_INCLUDES) $(LDLIBS) $(RM_OBJS)

times: $(TIMES_INCLUDES)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(RM_OBJS) 
times_test: $(patsubst %,%.test,$(TIMES_INCLUDES))
	$(CC) $(LDFLAGS) -o $@ $(TIMES_INCLUDES) $(LDLIBS) $(RM_OBJS)

clean: 
	rm *~ *.swp *.o $(EXECUTABLES) \
	    $(patsubst %,%_test,$(EXECUTABLES))\
	    2> /dev/null; true

