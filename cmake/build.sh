OUTPUT=obj

if [ -d ${OUTPUT} ]; then
	rm -rf ${OUTPUT}
fi
mkdir ${OUTPUT}

cp main.c ${OUTPUT}
cp CMakeLists.txt ${OUTPUT}
cp include.cmake ${OUTPUT}
cp test_so.c ${OUTPUT}

cd ${OUTPUT}
cmake .
make
