extern "C" {
  int mydouble( int x ); // does this name my double, or an 'external' double?
};

int mydouble( int x ){
  return x * 20;
};
