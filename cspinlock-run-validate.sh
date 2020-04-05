DIRECTORY=`dirname $0`
cd $DIRECTORY/genmc

autoreconf --install
./configure
make

echo "Validate cspinlock/main.c..."
./src/genmc -unroll=8 ../cspinlock/main.c
