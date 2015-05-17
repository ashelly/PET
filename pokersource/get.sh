svn co http://svn.gna.org/svn/pokersource/trunk/poker-eval source
sed 's/AM_CONFIG_HEADER/AC_CONFIG_HEADERS/' <source/configure.ac >tmp.ac
cp tmp.ac source/configure.ac
rm tmp.ac
cd source
libtoolize
autoreconf --install
./configure
make
cd ..

