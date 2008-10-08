#Brock Palen brockp@umich.edu  
#Center for Advanced Computing
#http://cac.engin.umich.edu
#http://www.umich.edu/~brockp


#compilers/linkers
CC  = pgcc	        #C compiler
F90 = pgf90 		#f90 compiler

#flags for compilers/linkers
CFLAGS = -fastsse -DACML 
FFLAGS = -fastsse 
LDFLAGS = -lacml -pgf90libs -lpgftnrtl
FLDFLAGS = -lacml

#CFLAGS = -fast -DMKL -openmp -lmkl
#FFLAGS = -fast -openmp -lmkl

#blas header location and lib location,
#Not needed if in normal path
BLAS_INC = $(ACML_INC)
BLAS_LIB = $(ACML_LINK)
#BLAS_INC = /usr/caen/pgi-7.2/linux86-64/7.2-1/include
#BLAS_LIB = /usr/caen/pgi-7.2/linux86-64/7.2-1/lib

#HDF5 libs for dgesv example
HDF5_INC = 
HDF5_LIB = 
HDF5_LINKER =

#FFTW-3.x libs for fft example
#module load fftw/3.1.1-pgi
FFTW3_INC  = $(FFTW_INC)
FFTW3_LINK = $(FFTW_LINK)
FFTW3_LINKER = -lfftw3

#nothing should be changed below here


CAPPS = cdgemm acmlVersion mklVersion blasSpeeds cosfft

FAPPS = fdgemm

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
	-rm -rf *.o *mod *.h5 $(APPS) 

#make tar
tar:
	-tar -czvf ../cac-blas-code.tar.gz ../blas-code
#help
help:
	@echo ""
	@echo "Set of example source files from brockp@umich.edu"
	@echo ""
	@echo "make all		Build all examples (default)"
	@echo "make clean	Delete all executables and objects"
	@echo "make tar		Build tar of this directory"
	@echo "make fapps	Build all Fortran examples"
	@echo "make capps	Build all C examples"
	@echo ""
	@echo "make acmlVersion	Finds version of linked acml library"
	@echo "make mklVersion	Finds version of linked mkl library"
	@echo "make cdgemm	C version of DGEMM() AB=C"
	@echo "make fdgemm	F90 version of DGEMM() AB=C"
	@echo "make blasSpeeds	Compares performance of C vs BLAS"
	@echo "make cosfft	FFTW-3.x fft example"
	

#c version dgemm()
cdgemm: dgemm.c
	$(CC) $(CFLAGS) $(BLAS_INC) -o $@ $? $(BLAS_LIB) $(LDFLAGS)

#f90 version dgemm()
fdgemm: dgemm.F90
	$(F90) $(FFLAGS) -o $@ $? $(BLAS_LIB) $(FLDFLAGS)
#blas speed timings
blasSpeeds: blasSpeeds.c
	$(CC) -DBLAS1 -DBLAS2 -DBLAS3 $(CFLAGS) $(BLAS_INC) -o $@ $? $(BLAS_LIB) $(LDFLAGS)

#acml version information
acmlVersion: acmlVersion.c
	-$(CC) $(CFLAGS) $(BLAS_INC) -o $@ $? $(BLAS_LIB) $(LDFLAGS)
#mkl version information
mklVersion: mklVersion.c
	-$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS)
#fft of cos
cosfft: cosfft.c
	$(CC) $(CFLAGS) $(FFTW3_INC) -o $@ $? $(FFTW3_LINK) $(FFTW3_LINKER)
