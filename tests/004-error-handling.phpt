--TEST--
DuckDB error handling test
--SKIPIF--
<?php
if (!extension_loaded('duckdb')) die('skip DuckDB extension not loaded');
?>
--FILE--
<?php
// Test invalid connection
$invalid_conn = duckdb_connect('/invalid/path/to/db');
var_dump($invalid_conn);

// Test valid connection
$conn = duckdb_connect();
var_dump($conn !== false);

// Test invalid SQL syntax
$result = duckdb_query($conn, "SELEC * FROM non_existent_table");
var_dump($result);

// Test query on non-existent table
$result = duckdb_query($conn, "SELECT * FROM non_existent_table");
var_dump($result);

// Test invalid resource type
$invalid_resource = fopen('php://memory', 'r');
try {
    $result = duckdb_query($invalid_resource, "SELECT 1");
} catch (TypeError $e) {
    echo "Caught TypeError\n";
}

// Test disconnecting invalid connection
try {
    duckdb_disconnect($invalid_resource);
} catch (TypeError $e) {
    echo "Caught TypeError\n";
}

// Clean up
fclose($invalid_resource);
duckdb_disconnect($conn);
?>
--EXPECTF--
Warning: Failed to open DuckDB database: /invalid/path/to/db in %s on line %d
bool(false)
bool(true)
Warning: DuckDB query failed: Parser Error: syntax error at or near "SELEC" in %s on line %d
bool(false)
Warning: DuckDB query failed: Catalog Error: Table with name non_existent_table does not exist%s in %s on line %d
bool(false)
Caught TypeError
Caught TypeError 