#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_duckdb.h"
#include "duckdb.h"

// Argument information for DuckDB functions
ZEND_BEGIN_ARG_INFO_EX(arginfo_duckdb_connect, 0, 0, 0)
    ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_duckdb_disconnect, 0, 0, 1)
    ZEND_ARG_INFO(0, connection)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_duckdb_query, 0, 0, 2)
    ZEND_ARG_INFO(0, connection)
    ZEND_ARG_INFO(0, query)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_duckdb_close, 0, 0, 1)
    ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()

ZEND_DECLARE_MODULE_GLOBALS(duckdb)

// Resource type IDs
int le_duckdb_db;
int le_duckdb_conn;
int le_duckdb_result;

// Resource type names
#define le_duckdb_db_name "DuckDB Database"
#define le_duckdb_conn_name "DuckDB Connection"
#define le_duckdb_result_name "DuckDB Result"

// Add this structure definition after the resource type definitions
typedef struct {
    duckdb_database db;
    duckdb_connection conn;
} php_duckdb_conn;

// Function entries
static const zend_function_entry duckdb_functions[] = {
    PHP_FE(duckdb_connect, arginfo_duckdb_connect)
    PHP_FE(duckdb_disconnect, arginfo_duckdb_disconnect)
    PHP_FE(duckdb_query, arginfo_duckdb_query)
    PHP_FE(duckdb_close, arginfo_duckdb_close)
    PHP_FE_END
};

// Module entry
zend_module_entry duckdb_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_DUCKDB_EXTNAME,
    duckdb_functions,
    PHP_MINIT(duckdb),
    PHP_MSHUTDOWN(duckdb),
    PHP_RINIT(duckdb),
    PHP_RSHUTDOWN(duckdb),
    PHP_MINFO(duckdb),
    PHP_DUCKDB_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_DUCKDB
ZEND_GET_MODULE(duckdb)
#endif

// Resource destructors
void duckdb_db_dtor(zend_resource *rsrc) {
    duckdb_database *db = (duckdb_database *)rsrc->ptr;
    if (db) {
        duckdb_close(db);
    }
}

void duckdb_conn_dtor(zend_resource *rsrc) {
    php_duckdb_conn *conn_wrapper = (php_duckdb_conn *)rsrc->ptr;
    if (conn_wrapper) {
        duckdb_disconnect(&conn_wrapper->conn);
        duckdb_close(&conn_wrapper->db);
        efree(conn_wrapper);
        rsrc->ptr = NULL;
    }
}

void duckdb_result_dtor(zend_resource *rsrc) {
    duckdb_result *result = (duckdb_result *)rsrc->ptr;
    if (result) {
        duckdb_destroy_result(result);
    }
}

// Module initialization
PHP_MINIT_FUNCTION(duckdb) {
    le_duckdb_db = zend_register_list_destructors_ex(duckdb_db_dtor, NULL, le_duckdb_db_name, module_number);
    le_duckdb_conn = zend_register_list_destructors_ex(duckdb_conn_dtor, NULL, le_duckdb_conn_name, module_number);
    le_duckdb_result = zend_register_list_destructors_ex(duckdb_result_dtor, NULL, le_duckdb_result_name, module_number);
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(duckdb) {
    return SUCCESS;
}

PHP_RINIT_FUNCTION(duckdb) {
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(duckdb) {
    return SUCCESS;
}

PHP_MINFO_FUNCTION(duckdb) {
    php_info_print_table_start();
    php_info_print_table_header(2, "DuckDB support", "enabled");
    php_info_print_table_row(2, "DuckDB extension version", PHP_DUCKDB_VERSION);
    php_info_print_table_end();
}

// DuckDB functions implementation
PHP_FUNCTION(duckdb_connect) {
    char *path = NULL;
    size_t path_len = 0;
    
    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_STRING(path, path_len)
    ZEND_PARSE_PARAMETERS_END();

    php_duckdb_conn *conn_wrapper = emalloc(sizeof(php_duckdb_conn));
    
    if (duckdb_open(path ? path : ":memory:", &conn_wrapper->db) == DuckDBError) {
        php_error_docref(NULL, E_WARNING, "Failed to open DuckDB database: %s", path ? path : ":memory:");
        efree(conn_wrapper);
        RETURN_FALSE;
    }

    if (duckdb_connect(conn_wrapper->db, &conn_wrapper->conn) == DuckDBError) {
        php_error_docref(NULL, E_WARNING, "Failed to create DuckDB connection");
        duckdb_close(&conn_wrapper->db);
        efree(conn_wrapper);
        RETURN_FALSE;
    }

    // Register only the connection wrapper resource
    RETURN_RES(zend_register_resource(conn_wrapper, le_duckdb_conn));
}

PHP_FUNCTION(duckdb_disconnect) {
    zval *conn_resource;
    duckdb_connection *conn;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_RESOURCE(conn_resource)
    ZEND_PARSE_PARAMETERS_END();

    if ((conn = (duckdb_connection *)zend_fetch_resource(Z_RES_P(conn_resource), le_duckdb_conn_name, le_duckdb_conn)) == NULL) {
        RETURN_FALSE;
    }

    // Just delete the resource - the destructor will handle disconnecting
    zend_list_delete(Z_RES_P(conn_resource));
    RETURN_TRUE;
}

PHP_FUNCTION(duckdb_query) {
    zval *conn_resource;
    char *query;
    size_t query_len;
    php_duckdb_conn *conn_wrapper;
    duckdb_result result;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_RESOURCE(conn_resource)
        Z_PARAM_STRING(query, query_len)
    ZEND_PARSE_PARAMETERS_END();

    if ((conn_wrapper = (php_duckdb_conn *)zend_fetch_resource(Z_RES_P(conn_resource), le_duckdb_conn_name, le_duckdb_conn)) == NULL) {
        RETURN_FALSE;
    }

    if (duckdb_query(conn_wrapper->conn, query, &result) == DuckDBError) {
        const char *error_msg = duckdb_result_error(&result);
        if (error_msg) {
            php_error_docref(NULL, E_WARNING, "DuckDB query failed: %s", error_msg);
        } else {
            php_error_docref(NULL, E_WARNING, "DuckDB query failed");
        }
        duckdb_destroy_result(&result);
        RETURN_FALSE;
    }

    // Create result array
    array_init(return_value);

    // Get column count and names
    idx_t column_count = duckdb_column_count(&result);
    idx_t row_count = duckdb_row_count(&result);
    
    // Process all rows
    for (idx_t row = 0; row < row_count; row++) {
        zval row_array;
        array_init(&row_array);
        
        for (idx_t col = 0; col < column_count; col++) {
            const char *col_name = duckdb_column_name(&result, col);
            zval value;
            
            // Get value based on column type
            duckdb_type col_type = duckdb_column_type(&result, col);
            switch (col_type) {
                case DUCKDB_TYPE_BOOLEAN:
                    ZVAL_BOOL(&value, duckdb_value_boolean(&result, col, row));
                    break;
                case DUCKDB_TYPE_TINYINT:
                    ZVAL_LONG(&value, duckdb_value_int8(&result, col, row));
                    break;
                case DUCKDB_TYPE_SMALLINT:
                    ZVAL_LONG(&value, duckdb_value_int16(&result, col, row));
                    break;
                case DUCKDB_TYPE_INTEGER:
                    ZVAL_LONG(&value, duckdb_value_int32(&result, col, row));
                    break;
                case DUCKDB_TYPE_BIGINT:
                    ZVAL_LONG(&value, duckdb_value_int64(&result, col, row));
                    break;
                case DUCKDB_TYPE_FLOAT:
                    ZVAL_DOUBLE(&value, duckdb_value_float(&result, col, row));
                    break;
                case DUCKDB_TYPE_DOUBLE:
                    ZVAL_DOUBLE(&value, duckdb_value_double(&result, col, row));
                    break;
                case DUCKDB_TYPE_VARCHAR:
                    {
                        char *str_val = duckdb_value_varchar(&result, col, row);
                        if (str_val) {
                            ZVAL_STRING(&value, str_val);
                            duckdb_free(str_val);
                        } else {
                            ZVAL_NULL(&value);
                        }
                    }
                    break;
                default:
                    ZVAL_NULL(&value);
                    break;
            }
            
            add_assoc_zval(&row_array, col_name, &value);
        }
        add_next_index_zval(return_value, &row_array);
    }
    
    duckdb_destroy_result(&result);
}

PHP_FUNCTION(duckdb_close) {
    zval *db_resource;
    duckdb_database *db;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_RESOURCE(db_resource)
    ZEND_PARSE_PARAMETERS_END();

    if ((db = (duckdb_database *)zend_fetch_resource(Z_RES_P(db_resource), le_duckdb_db_name, le_duckdb_db)) == NULL) {
        RETURN_FALSE;
    }

    zend_list_close(Z_RES_P(db_resource));
    RETURN_TRUE;
}