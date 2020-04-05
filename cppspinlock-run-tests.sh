DIRECTORY=`dirname $0`
cd $DIRECTORY/cppspinlock
mkdir build
cd build
cmake ..
make && make test
