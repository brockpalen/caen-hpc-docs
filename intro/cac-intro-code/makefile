default: c_examples f_examples
#for IBM SP
#F90=mpxlf90
#F_OP=
#CC=mpcc
#C_OP=

#For Cray T3e
#F90=f90
#CC=cc
#F_OP= -f free
#C_OP= 

#DEC alpha settings
#F90=f90
#F_OP=-O4 -free -lmpi -lfmpi
#CC=cc
#C_OP= -O4 -lm -lmpi

#LINUX SETTINGS
F90=mpif90
F_OP=-fastsse
CC=mpicc
C_OP= -fastsse

FEXE= f_ex00 f_ex01 f_ex02 f_ex03 f_ex04 f_ex05 f_ex06 f_ex07 f_ex08 f_ex09 f_ex10 f_ex11
CEXE=  c_ex01 c_ex02 c_ex03 c_ex04 c_ex05 c_ex06 c_ex07 c_ex08 c_ex09 c_ex10 c_ex11
c_examples: $(CEXE)
f_examples:	$(FEXE)
both: c_examples f_examples

c_ex01:c_ex01.c
	$(CC) $(C_OP) -o c_ex01 c_ex01.c

c_ex02:c_ex02.c
	$(CC) $(C_OP) -o c_ex02 c_ex02.c

c_ex03:c_ex03.c
	$(CC) $(C_OP) -o c_ex03 c_ex03.c

c_ex04:c_ex04.c
	$(CC) $(C_OP) -o c_ex04 c_ex04.c

c_ex05:c_ex05.c
	$(CC) $(C_OP) -o c_ex05 c_ex05.c

c_ex06:c_ex06.c
	$(CC) $(C_OP) -o c_ex06 c_ex06.c

c_ex07:c_ex07.c
	$(CC) $(C_OP) -o c_ex07 c_ex07.c

c_ex08:c_ex08.c
	$(CC) $(C_OP) -o c_ex08 c_ex08.c

c_ex09:c_ex09.c
	$(CC) $(C_OP) -o c_ex09 c_ex09.c

c_ex10:c_ex10.c
	$(CC) $(C_OP) -o c_ex10 c_ex10.c

c_ex11:c_ex11.c
	$(CC) $(C_OP) -o c_ex11 c_ex11.c


mpi.o: mpi.f90
	$(F90) $(F_OP) -c  mpi.f90 

f_ex00:f_ex00.f90 mpi.o
	$(F90) $(F_OP) -o f_ex00 f_ex00.f90 mpi.o 

f_ex01:f_ex01.f90 mpi.o
	$(F90) $(F_OP) -o f_ex01 f_ex01.f90 mpi.o 

f_ex02:f_ex02.f90 mpi.o
	$(F90) $(F_OP) -o f_ex02 f_ex02.f90 mpi.o 

f_ex03:f_ex03.f90 mpi.o
	$(F90) $(F_OP) -o f_ex03 f_ex03.f90 mpi.o 

f_ex04:f_ex04.f90 mpi.o
	$(F90) $(F_OP) -o f_ex04 f_ex04.f90 mpi.o 

f_ex05:f_ex05.f90 mpi.o
	$(F90) $(F_OP) -o f_ex05 f_ex05.f90 mpi.o 

f_ex06:f_ex06.f90 mpi.o
	$(F90) $(F_OP) -o f_ex06 f_ex06.f90 mpi.o 

f_ex07:f_ex07.f90
	$(F90) $(F_OP) -o f_ex07 f_ex07.f90  mpi.o

f_ex08:f_ex08.f90
	$(F90) $(F_OP) -o f_ex08 f_ex08.f90  mpi.o

f_ex09:f_ex09.f90
	$(F90) $(F_OP) -o f_ex09 f_ex09.f90  mpi.o

f_ex10:f_ex10.f90
	$(F90) $(F_OP) -o f_ex10 f_ex10.f90 mpi.o

f_ex11:f_ex11.f90
	$(F90) $(F_OP) -o f_ex11 f_ex11.f90  mpi.o


clean:
	/bin/rm -f $(CEXE) $(FEXE) *mod *o
	
FSCR= f_ex00.f90 f_ex01.f90 f_ex02.f90 f_ex03.f90 f_ex04.f90 f_ex05.f90\
      f_ex06.f90 f_ex07.f90 f_ex08.f90 f_ex09.f90 f_ex10.f90 com_split.f90\
      mpi.f90 f_ex11.f90
CSRC= c_ex00.c c_ex01.c c_ex02.c c_ex03.c c_ex04.c c_ex05.c\
      c_ex06.c c_ex07.c c_ex08.c c_ex09.c c_ex10.c com_split.c\
      c_ex11.c
REST= readme run makefile

tar:
	/bin/tar -cf new_ex.tar $(FSCR) $(CSRC) $(REST)
	
