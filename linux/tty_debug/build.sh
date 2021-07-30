
BUILD_DIR="mybuild"

rm -rf ${BUILD_DIR}
mkdir ${BUILD_DIR}

cd ${BUILD_DIR}
cmake ..
make
