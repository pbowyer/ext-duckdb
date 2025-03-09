--TEST--
DuckDB data types test
--SKIPIF--
<?php
if (!extension_loaded('duckdb')) die('skip DuckDB extension not loaded');
?>
--FILE--
<?php
$conn = duckdb_connect();

// Create table with different data types
$create_sql = "CREATE TABLE type_test (
    bool_col BOOLEAN,
    tinyint_col TINYINT,
    smallint_col SMALLINT,
    int_col INTEGER,
    bigint_col BIGINT,
    float_col FLOAT,
    double_col DOUBLE,
    varchar_col VARCHAR,
    list_col INTEGER[]
)";

$result = duckdb_query($conn, $create_sql);
var_dump($result !== false);

// Insert test data
$insert_sql = "INSERT INTO type_test VALUES (
    true,
    127,
    32767,
    2147483647,
    9223372036854775807,
    3.14,
    3.141592653589793,
    'Hello World',
    [1, 2, 3]
)";

$result = duckdb_query($conn, $insert_sql);
var_dump($result !== false);

// Query and check data types
$result = duckdb_query($conn, "SELECT * FROM type_test");
var_dump($result);

// Clean up
duckdb_query($conn, "DROP TABLE type_test");
duckdb_disconnect($conn);
?>
--EXPECT--
bool(true)
bool(true)
array(1) {
  [0]=>
  array(9) {
    ["bool_col"]=>
    bool(true)
    ["tinyint_col"]=>
    int(127)
    ["smallint_col"]=>
    int(32767)
    ["int_col"]=>
    int(2147483647)
    ["bigint_col"]=>
    int(9223372036854775807)
    ["float_col"]=>
    float(3.14)
    ["double_col"]=>
    float(3.141592653589793)
    ["varchar_col"]=>
    string(11) "Hello World"
    ["list_col"]=>
    array(3) {
      [0]=>
      int(1)
      [1]=>
      int(2)
      [2]=>
      int(3)
    }
  }
} 