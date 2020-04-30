python binder/generate/run.py
if errorlevel 1 exit 1

mkdir build
cd build

cmake .. -G "Ninja" ^
    -DCMAKE_BUILD_TYPE="Release" ^
    -DENABLE_SMESH=OFF ^
    -DENABLE_NETGEN=OFF ^
    -DPTHREAD_INCLUDE_DIRS:FILEPATH="%LIBRARY_PREFIX%/include"
if errorlevel 1 exit 1

ninja -j2
if errorlevel 1 exit 1

ninja install
if errorlevel 1 exit 1

cd ..
python setup.py install
