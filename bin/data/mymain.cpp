#include <dlfcn.h>
#include <iostream>

int main( void ){
  std::cout << "Hello World!\n";

  // opening
  std::cout << "Loading lib ...\n";
  void* handle = dlopen( "mylib.so", RTLD_LAZY );
  if( handle == NULL ){
    std::cout << "Error: " << dlerror();
    return 1;
  }

  // binding
  int(*mydouble)(int) = (int(*)(int)) dlsym( handle, "mydouble" );
  // ^                  ^
  // |                  -- explicit cast to same type (stop compiler warning/error)
  // -- function pointer of return type int and signature int
  std::cout << "Doubling 123: " << (*mydouble)(123) << "\n";

  // closing
  std::cout << "Closing lib ...\n";
  int close = dlclose( handle );
  if( close != 0 ){
    std::cout << "Error: " << dlerror();
    return 1;
  }
  return 0;
}
