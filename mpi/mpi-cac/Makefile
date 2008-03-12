#Brock Palen brockp@umich.edu  
#Center for Advanced Computing
#http://cac.engin.umich.edu


#compilers/linkers
CC  = mpicc	        #mpi C compiler
F90 = mpif90 		#mpi f90 compiler

#flags for compilers/linkers
CFLAGS = -fastsse  -Minfo -Mneginfo
FFLAGS = -fastsse  -Minfo -Mneginfo


#nothing should be changed below here


CAPPS = chello cdeadlock no-cdeadlock cpi

FAPPS = fhello fdeadlock no-fdeadlock fpi

#all apps
APPS = $(CAPPS) $(FAPPS)

#build everything
all: $(APPS)

#build only fortran examples
fapps: $(FAPPS)

#build only C apps
capps: $(CAPPS)

#kill everything start over
clean:
	-rm -rf *.o *mod $(APPS)

#c version helloworld.c
chello: helloworld.c
	$(CC) $(CFLAGS) -o $@ $?

#f90 version helloworld.f90
fhello: helloworld.f90
	$(F90) $(FFLAGS) -o $@ $?

#c version of deadlock.c with deadlock
cdeadlock: deadlock.c
	$(CC) $(CFLAGS) -DSIZE=120 -o $@ $?

#c version with  no deadlock 
no-cdeadlock: deadlock.c
	$(CC) $(CFLAGS) -DSIZE=119 -o $@ $?

#f90 version deadlock.c with deadlock
fdeadlock: deadlock.F90
	$(F90) $(FFLAGS) -DSIZE=120 -o $@ $?

#f90 version with no deadlock
no-fdeadlock: deadlock.F90
	$(F90) $(FFLAGS) -DSIZE=119 -o $@ $?

#c version of calculate pi
cpi: cpi.c
	$(CC) $(CFLAGS) -o $@ $?

#f90 version of calculate pi
fpi: fpi.f90
	$(F90) $(FFLAGS) -o $@ $?
