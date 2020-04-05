DIRECTORY=`dirname $0`

cd $DIRECTORY
git submodule init
git submodule update

cd genmc
autoreconf --install
./configure
make -j 4

echo "Validate cspinlock/main.c..."
./src/genmc -unroll=8 ../cspinlock/main.c
