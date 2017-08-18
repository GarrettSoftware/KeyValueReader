FILENAMES="../license.txt \
           `ls ../include/*.h` \
           `ls ../src/*.h` \
           `ls ../src/*.cpp` \
           `ls ../examples/*.c` \
           `ls ../test/*.h` \
           `ls ../test/*.cpp`"

DATESTRING=`date +'%Y'`
DATESTRING="(c) 2016-$DATESTRING"


clear
echo " "
echo "This script checks for the correct date in the header"
echo "of source code.  $DATESTRING"
echo " "

echo "Files with wrong or missing headers"
for FILENAME in $FILENAMES; do
    grep -L "$DATESTRING" $FILENAME
done
echo " "

echo "Files with correct headers"
for FILENAME in $FILENAMES; do
    grep -l "$DATESTRING" $FILENAME
done
echo " "

