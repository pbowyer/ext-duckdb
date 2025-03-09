--TEST--
DuckDB basic query test
--SKIPIF--
<?php
if (!extension_loaded('duckdb')) die('skip DuckDB extension not loaded');
?>
--FILE--
<?php
$conn = duckdb_connect();

// Test CREATE TABLE
$result = duckdb_query($conn, "CREATE TABLE test (id INTEGER, name VARCHAR)");
var_dump($result !== false);

// Test INSERT
$result = duckdb_query($conn, "INSERT INTO test VALUES (1, 'Alice'), (2, 'Bob')");
var_dump($result !== false);

// Test SELECT
$result = duckdb_query($conn, "SELECT * FROM test ORDER BY id");
var_dump($result);

// Clean up
duckdb_query($conn, "DROP TABLE test");
duckdb_disconnect($conn);
?>
--EXPECT--
bool(true)
bool(true)
array(2) {
  [0]=>
  array(2) {
    ["id"]=>
    int(1)
    ["name"]=>
    string(5) "Alice"
  }
  [1]=>
  array(2) {
    ["id"]=>
    int(2)
    ["name"]=>
    string(3) "Bob"
  }
} 