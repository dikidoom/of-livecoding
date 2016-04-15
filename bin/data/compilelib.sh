# !! outdated and kept for reference only !!

# shared library:
echo g++ -fPIC -shared mylib.cpp -o mylib.so

# main
echo g++ mymain.cpp -ldl -Wl,-rpath=. -o mymain

echo cp mylib.so ../libs
