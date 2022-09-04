SHELL	:=	sh

setup:
	mkdir execs
	cp src/* .

clean: 
	rm *_output.txt
	rm -rf execs/
	rm -rf *_sol
	rm -rf *_student
	rm mem.h mem_init.c mem_solution.c

all: AllocMultiple AllocSingle FreeSingle StressFree CoalLeft CoalRight Driver

alltests: test_AM1 test_AM2 test_AM3 test_AS1 test_AS2 test_FS test_SF test_CL test_CR test_D

AllocMultiple:
	gcc -g drivers/alloc_multiple.c mem_solution.c solution.c  mem_init.c -Wall -o AM
	mv AM execs/

AllocSingle:
	gcc -g drivers/alloc_single.c mem_solution.c solution.c  mem_init.c -Wall -o AS
	mv AS execs/

FreeSingle:
	gcc -g drivers/free_single.c mem_solution.c solution.c  mem_init.c -Wall -o FS
	mv FS execs/

CoalLeft:
	gcc -g drivers/coalesce_left.c mem_solution.c solution.c  mem_init.c -Wall -o CL
	mv CL execs/

CoalRight:
	gcc -g drivers/coalesce_right.c mem_solution.c solution.c  mem_init.c -Wall -o CR
	mv CR execs/

StressFree:
	gcc -g drivers/stress_free.c mem_solution.c solution.c  mem_init.c -Wall -o SF
	mv SF execs/

Driver:
	gcc -g drivers/driver_free.c mem_solution.c solution.c  mem_init.c -Wall -o D
	mv D execs/

test_AM1:
	execs/./AM 16 10 > AM1_output.txt

test_AM2:
	execs/./AM 8 10 > AM2_output.txt

test_AM3:
	execs/./AM 16 5 > AM3_output.txt

test_AS1:
	execs/./AS 32 > AS1_output.txt

test_AS2:
	execs/./AS 50 > AS2_output.txt

test_FS:
	execs/./FS 32 > FS_output.txt

test_SF:
	execs/./SF > SF_output.txt

test_CL:
	execs/./CL > CL_output.txt

test_CR:
	execs/./CR > CR_output.txt

test_D:
	execs/./D > D_output.txt


  
