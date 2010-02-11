#!/bin/sh

# By convention, create an autogen.sh that 
# runs the right autotools in the right order. 

./cleanup.sh

aclocal -I m4
libtoolize --force
autoheader
automake --add-missing --copy --gnu --force-missing
autoconf

echo '

>> Run ./configure now!

'
