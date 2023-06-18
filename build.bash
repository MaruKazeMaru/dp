ls | grep build > /dev/null
[ $? -eq 0 ] | mkdir build
cd build

gcc     -I../include -c ../src/city.c ../src/txtlist.c
gcc -lm -I../include -c ../src/dp_matching.c

ar rcs libcity.a city.o
ar rcs libtxtlist.a txtlist.o
ar rcs libdp_matching.a dp_matching.o

gcc -o main.out ../src/main.c -lcity -L. -ltxtlist -ldp_matching -I../include -lm