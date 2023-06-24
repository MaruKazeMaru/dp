ls | grep build > /dev/null
[ $? -eq 0 ] || mkdir build
cd build

ls | grep src > /dev/null
[ $? -eq 0 ] || mkdir src
cd src

gcc     -g -I../../include -c ../../src/city.c ../../src/txtlist.c
gcc -lm -g -I../../include -c ../../src/dp_matching.c

ar rcs libcity.a city.o
ar rcs libtxtlist.a txtlist.o
ar rcs libdp_matching.a dp_matching.o

gcc -o main.out ../../src/main.c -g -lcity -L. -ltxtlist -ldp_matching -I../../include -lm
