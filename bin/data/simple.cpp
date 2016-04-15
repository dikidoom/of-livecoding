extern "C" {
  // "C++" names (the default) are mangled, which makes them hard to use.
  // We can declare unmangled "C" names for our functions in here.
  float mydouble( float x );
};

float mydouble( float x ){
  return x * 2; // <------------ try changing these to 4, 0.1, 1.5 ...
};

// ... or we can add external name linkage to the function itself.
extern "C" float mytriple( float x ){
  return x * 3; // <------------ try changing these to 4, 0.1, 1.5 ...
};
