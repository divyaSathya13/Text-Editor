a.out: DSprojectUtils.o DSprojectMain.o
	gcc DSprojectUtils.o DSprojectMain.o

DSprojectUtils.o: DSprojectUtils.c DSproject.h
	gcc -c DSprojectUtils.c

DSprojectMain.o: DSprojectMain.c DSproject.h
	gcc -c DSprojectMain.c


