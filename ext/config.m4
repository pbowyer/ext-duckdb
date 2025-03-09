PHP_ARG_WITH([duckdb],
  [for DuckDB support],
  [AS_HELP_STRING([--with-duckdb=DIR],
    [Include DuckDB support. DIR is the DuckDB source directory])])

if test "$PHP_DUCKDB" != "no"; then
  # Check for DuckDB header files in the specified directory
  AC_MSG_CHECKING([for DuckDB files in $PHP_DUCKDB])
  
  if test ! -r "$PHP_DUCKDB/duckdb.h"; then
    AC_MSG_ERROR([DuckDB header files not found in $PHP_DUCKDB. Please specify the correct DuckDB source directory.])
  fi
  
  AC_MSG_RESULT([found])
  
  # Add DuckDB include path
  PHP_ADD_INCLUDE($PHP_DUCKDB)
  
  # Add DuckDB library path and link against it
  LIBNAME=duckdb
  LIBSYMBOL=duckdb_open
  
  # Add necessary flags
  PHP_CHECK_LIBRARY([duckdb], [duckdb_open],
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHP_DUCKDB, DUCKDB_SHARED_LIBADD)
    AC_DEFINE(HAVE_DUCKDBLIB,1,[ ])
  ],[
    AC_MSG_ERROR([DuckDB library not found in $PHP_DUCKDB. Please build DuckDB first.])
  ],[
    -L$PHP_DUCKDB
  ])
  
  PHP_SUBST(DUCKDB_SHARED_LIBADD)
  
  # Define source files
  PHP_NEW_EXTENSION(duckdb, duckdb.c, $ext_shared)
fi