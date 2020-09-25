make

if [ $# -gt 0 ]
then
	echo
	echo
	echo
	echo

	cp target/Release/linux/x86_64/Readelf/Readelf file/Readelf
	echo Copied Successfully
fi

echo
echo
echo
echo
echo Program Output:
echo
target/Release/linux/x86_64/Readelf/Readelf