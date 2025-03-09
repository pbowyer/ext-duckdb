# DuckDB Extension Tests

This directory contains PHP test files (.phpt) for testing the DuckDB extension functionality.

## Running Tests

### Running All Tests

To run all tests in this directory:

```bash
make test TESTS=tests/*.phpt
```

### Running Individual Tests

To run specific test files:

```bash
make test TESTS="tests/001-connect.phpt"
# Or multiple specific tests:
make test TESTS="tests/001-connect.phpt tests/002-basic-query.phpt"
```

## Test Files Overview

1. `001-connect.phpt`
   - Tests basic connection functionality
   - In-memory database connection
   - File-based database connection
   - Connection disconnection

2. `002-basic-query.phpt`
   - Tests basic SQL operations
   - CREATE TABLE
   - INSERT data
   - SELECT data
   - Result format validation

3. `003-data-types.phpt`
   - Tests all supported DuckDB data types:
     - BOOLEAN
     - TINYINT
     - SMALLINT
     - INTEGER
     - BIGINT
     - FLOAT
     - DOUBLE
     - VARCHAR
     - Arrays (INTEGER[])
   - Data type conversion between DuckDB and PHP

4. `004-error-handling.phpt`
   - Tests error conditions
   - Invalid connection attempts
   - Invalid SQL syntax
   - Non-existent table queries
   - Invalid resource types
   - Type error handling

## Test Structure

Each .phpt test file contains:
- `--TEST--`: Test description
- `--SKIPIF--`: Conditions under which to skip the test
- `--FILE--`: The actual test code
- `--EXPECT--`: Expected output from the test

## Requirements

- PHP development environment
- DuckDB extension compiled and installed
- PHP test framework (part of PHP development tools)

## Common Issues

1. If tests are skipped with "DuckDB extension not loaded":
   - Ensure the extension is properly compiled
   - Check if the extension is enabled in your php.ini
   - Verify with `php -m | grep duckdb`

2. If you see permission errors:
   - Ensure you have write permissions in the test directory
   - Check if the process can create temporary files 