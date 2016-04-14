# shared library:
g++ -fPIC -shared mylib.cpp -o mylib.so

# main
g++ mymain.cpp -ldl -Wl,-rpath=. -o mymain

cp mylib.so ../libs
