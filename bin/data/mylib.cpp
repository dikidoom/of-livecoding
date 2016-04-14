extern "C" {
  // "C++" names (the default) are mangled, which makes them hard to use.
  // We can declare unmangled "C" names for our functions in here.
  // int mydouble( int x );
};

extern "C" int mydouble( int x ){
  return x * 2;
};

extern "C" void bla( ){
  //printf( "Shit." );
};
