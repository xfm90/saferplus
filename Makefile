
OBJS = utils.o tbl.o modular.o safer.o

INCLUDES = types.h tbl.h operations.h modular.h safer.h

TARGETS = saferenc saferdec

CC = gcc 

##baseline
#CFLAGS = -O0 -ansi 
## Mac
CFLAGS = -O3 -ansi 
## Tests 1-4
#CFLAGS = -O3 -ansi -mtune=core2 -march=core2 

#TEST to be defined as make cmd line argument (used in other script)

all: ${TARGETS}

saferenc: safer_enc_dec.c ${OBJS} ${INCLUDES}
	${CC} $(CFLAGS) -DSAFERENC $(TEST) -o $@ $< ${OBJS} 

saferdec: safer_enc_dec.c ${OBJS} ${INCLUDES}
	${CC} $(CFLAGS) -DSAFERDEC $(TEST) -o $@ $< ${OBJS} 

.c.o:
	$(CC) -c $(CFLAGS) $(TEST) -o $@ $<

clean:
	-rm -f ${OBJS} ${TARGETS} *~
	-cd files && make clean
