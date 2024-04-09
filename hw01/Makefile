# build the executable files
build:
	mpicc -o a.out PPD_PA1_B0829002_1.c
	mpicc -o b.out PPD_PA1_B0829002_2.c
	mpicc -o c.out PPD_PA1_B0829002_3.c

# run the executable files with 5 processes, which is the homework requirement
run:
	mpirun -n 5 ./a.out
	mpirun -n 5 ./b.out
	mpirun -n 5 ./c.out

# clean the executable files
clean:
	rm -f a.out b.out c.out 
	rm -r a.out.dSYM b.out.dSYM c.out.dSYM