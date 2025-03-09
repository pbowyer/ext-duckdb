#ifndef PHP_DUCKDB_H
#define PHP_DUCKDB_H 1

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "duckdb.h"

#define PHP_DUCKDB_VERSION "1.0.0"
#define PHP_DUCKDB_EXTNAME "duckdb"

// Forward declare the module entry
extern zend_module_entry duckdb_module_entry;
#define phpext_duckdb_ptr &duckdb_module_entry

// Resource type for DuckDB database connections
extern int le_duckdb_db;
extern int le_duckdb_conn;
extern int le_duckdb_result;

// DuckDB resource handlers
PHP_MINIT_FUNCTION(duckdb);
PHP_MSHUTDOWN_FUNCTION(duckdb);
PHP_RINIT_FUNCTION(duckdb);
PHP_RSHUTDOWN_FUNCTION(duckdb);
PHP_MINFO_FUNCTION(duckdb);

// DuckDB functions
PHP_FUNCTION(duckdb_connect);
PHP_FUNCTION(duckdb_disconnect);
PHP_FUNCTION(duckdb_query);
PHP_FUNCTION(duckdb_close);

// Resource destructors
void duckdb_db_dtor(zend_resource *rsrc);
void duckdb_conn_dtor(zend_resource *rsrc);
void duckdb_result_dtor(zend_resource *rsrc);

ZEND_BEGIN_MODULE_GLOBALS(duckdb)
    char *default_db_path;
ZEND_END_MODULE_GLOBALS(duckdb)

#ifdef ZTS
#define DUCKDB_G(v) TSRMG(duckdb_globals_id, zend_duckdb_globals *, v)
#else
#define DUCKDB_G(v) (duckdb_globals.v)
#endif

#endif /* PHP_DUCKDB_H */