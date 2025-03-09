--TEST--
DuckDB connection test
--SKIPIF--
<?php
if (!extension_loaded('duckdb')) die('skip DuckDB extension not loaded');
?>
--FILE--
<?php
// Test in-memory connection
$conn = duckdb_connect();
var_dump($conn !== false);

// Test file-based connection
$db_file = __DIR__ . '/test.db';
$conn2 = duckdb_connect($db_file);
var_dump($conn2 !== false);

// Test disconnection
var_dump(duckdb_disconnect($conn));
var_dump(duckdb_disconnect($conn2));

// Clean up
@unlink($db_file);
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true) 