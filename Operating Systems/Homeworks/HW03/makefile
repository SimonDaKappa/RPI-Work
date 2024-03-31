
build: hw03.c
	gcc -Wall -o hw03.o hw03.c -pthread -lm
debug: hw03.c
	gcc -g -Wall -Werror -Wextra -D DEBUG -o hw03.o hw03.c -pthread -lm
nothread: hw03.c
	gcc -Wall -Werror -D NO_PARALLEL -o hw03.o hw03.c -lm	
nothreaddebug: hw03.c
	gcc -g -Wall -Werror -Wextra -D DEBUG -D NO_PARALLEL -o hw03.o hw03.c -lm
buildtest: hw03_test.c
	gcc -Wall -o hw03.o hw03_test.c -pthread -lm
buildtestdebug: hw03_test.c
	gcc -g -Wall -Werror -Wextra -D DEBUG -o hw03.o hw03_test.c -pthread -lm