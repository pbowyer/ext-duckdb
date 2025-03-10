# This page contains the reference for DuckDB's C API.

> Deprecated The reference contains several deprecation notices. These concern methods whose long-term availability is not guaranteed as they may be removed in the future. That said, DuckDB's developers plan to carry out deprecations slowly as several of the deprecated methods do not yet have a fully functional alternative. Therefore, they will not removed before the alternative is available, and even then, there will be a grace period of a few minor versions before removing them. The reason that the methods are already deprecated in v1.0 is to denote that they are not part of the v1.0 stable API, which contains methods that are available long-term.

## API Reference Overview

### Open Connect

duckdb_instance_cache duckdb_create_instance_cache();

duckdb_state duckdb_get_or_create_from_cache(duckdb_instance_cache instance_cache, const char *path, duckdb_database *out_database, duckdb_config config, char **out_error);

void duckdb_destroy_instance_cache(duckdb_instance_cache *instance_cache);

duckdb_state duckdb_open(const char *path, duckdb_database *out_database);

duckdb_state duckdb_open_ext(const char *path, duckdb_database *out_database, duckdb_config config, char **out_error);

void duckdb_close(duckdb_database *database);

duckdb_state duckdb_connect(duckdb_database database, duckdb_connection *out_connection);

void duckdb_interrupt(duckdb_connection connection);

duckdb_query_progress_type duckdb_query_progress(duckdb_connection connection);

void duckdb_disconnect(duckdb_connection *connection);

const char *duckdb_library_version();

### Configuration

duckdb_state duckdb_create_config(duckdb_config *out_config);

size_t duckdb_config_count();

duckdb_state duckdb_get_config_flag(size_t index, const char **out_name, const char **out_description);

duckdb_state duckdb_set_config(duckdb_config config, const char *name, const char *option);

void duckdb_destroy_config(duckdb_config *config);

### Query Execution

duckdb_state duckdb_query(duckdb_connection connection, const char *query, duckdb_result *out_result);

void duckdb_destroy_result(duckdb_result *result);

const char *duckdb_column_name(duckdb_result *result, idx_t col);

duckdb_type duckdb_column_type(duckdb_result *result, idx_t col);

duckdb_statement_type duckdb_result_statement_type(duckdb_result result);

duckdb_logical_type duckdb_column_logical_type(duckdb_result *result, idx_t col);

idx_t duckdb_column_count(duckdb_result *result);

idx_t duckdb_row_count(duckdb_result *result);

idx_t duckdb_rows_changed(duckdb_result *result);

void *duckdb_column_data(duckdb_result *result, idx_t col);

bool *duckdb_nullmask_data(duckdb_result *result, idx_t col);

const char *duckdb_result_error(duckdb_result *result);

duckdb_error_type duckdb_result_error_type(duckdb_result *result);

### Result Functions

duckdb_data_chunk duckdb_result_get_chunk(duckdb_result result, idx_t chunk_index);

bool duckdb_result_is_streaming(duckdb_result result);

idx_t duckdb_result_chunk_count(duckdb_result result);

duckdb_result_type duckdb_result_return_type(duckdb_result result);

### Safe Fetch Functions

bool duckdb_value_boolean(duckdb_result *result, idx_t col, idx_t row);

int8_t duckdb_value_int8(duckdb_result *result, idx_t col, idx_t row);

int16_t duckdb_value_int16(duckdb_result *result, idx_t col, idx_t row);

int32_t duckdb_value_int32(duckdb_result *result, idx_t col, idx_t row);

int64_t duckdb_value_int64(duckdb_result *result, idx_t col, idx_t row);

duckdb_hugeint duckdb_value_hugeint(duckdb_result *result, idx_t col, idx_t row);

duckdb_uhugeint duckdb_value_uhugeint(duckdb_result *result, idx_t col, idx_t row);

duckdb_decimal duckdb_value_decimal(duckdb_result *result, idx_t col, idx_t row);

uint8_t duckdb_value_uint8(duckdb_result *result, idx_t col, idx_t row);

uint16_t duckdb_value_uint16(duckdb_result *result, idx_t col, idx_t row);

uint32_t duckdb_value_uint32(duckdb_result *result, idx_t col, idx_t row);

uint64_t duckdb_value_uint64(duckdb_result *result, idx_t col, idx_t row);

float duckdb_value_float(duckdb_result *result, idx_t col, idx_t row);

double duckdb_value_double(duckdb_result *result, idx_t col, idx_t row);

duckdb_date duckdb_value_date(duckdb_result *result, idx_t col, idx_t row);

duckdb_time duckdb_value_time(duckdb_result *result, idx_t col, idx_t row);

duckdb_timestamp duckdb_value_timestamp(duckdb_result *result, idx_t col, idx_t row);

duckdb_interval duckdb_value_interval(duckdb_result *result, idx_t col, idx_t row);

char *duckdb_value_varchar(duckdb_result *result, idx_t col, idx_t row);

duckdb_string duckdb_value_string(duckdb_result *result, idx_t col, idx_t row);

char *duckdb_value_varchar_internal(duckdb_result *result, idx_t col, idx_t row);

duckdb_string duckdb_value_string_internal(duckdb_result *result, idx_t col, idx_t row);

duckdb_blob duckdb_value_blob(duckdb_result *result, idx_t col, idx_t row);

bool duckdb_value_is_null(duckdb_result *result, idx_t col, idx_t row);

### Helpers

void *duckdb_malloc(size_t size);

void duckdb_free(void *ptr);

idx_t duckdb_vector_size();

bool duckdb_string_is_inlined(duckdb_string_t string);

uint32_t duckdb_string_t_length(duckdb_string_t string);

const char *duckdb_string_t_data(duckdb_string_t *string);

### Date Time Timestamp Helpers

duckdb_date_struct duckdb_from_date(duckdb_date date);

duckdb_date duckdb_to_date(duckdb_date_struct date);

bool duckdb_is_finite_date(duckdb_date date);

duckdb_time_struct duckdb_from_time(duckdb_time time);

duckdb_time_tz duckdb_create_time_tz(int64_t micros, int32_t offset);

duckdb_time_tz_struct duckdb_from_time_tz(duckdb_time_tz micros);

duckdb_time duckdb_to_time(duckdb_time_struct time);

duckdb_timestamp_struct duckdb_from_timestamp(duckdb_timestamp ts);

duckdb_timestamp duckdb_to_timestamp(duckdb_timestamp_struct ts);

bool duckdb_is_finite_timestamp(duckdb_timestamp ts);

bool duckdb_is_finite_timestamp_s(duckdb_timestamp_s ts);

bool duckdb_is_finite_timestamp_ms(duckdb_timestamp_ms ts);

bool duckdb_is_finite_timestamp_ns(duckdb_timestamp_ns ts);

### Hugeint Helpers

double duckdb_hugeint_to_double(duckdb_hugeint val);

duckdb_hugeint duckdb_double_to_hugeint(double val);

### Unsigned Hugeint Helpers

double duckdb_uhugeint_to_double(duckdb_uhugeint val);

duckdb_uhugeint duckdb_double_to_uhugeint(double val);

### Decimal Helpers

duckdb_decimal duckdb_double_to_decimal(double val, uint8_t width, uint8_t scale);

double duckdb_decimal_to_double(duckdb_decimal val);

### Prepared Statements

duckdb_state duckdb_prepare(duckdb_connection connection, const char *query, duckdb_prepared_statement *out_prepared_statement);

void duckdb_destroy_prepare(duckdb_prepared_statement *prepared_statement);

const char *duckdb_prepare_error(duckdb_prepared_statement prepared_statement);

idx_t duckdb_nparams(duckdb_prepared_statement prepared_statement);

const char *duckdb_parameter_name(duckdb_prepared_statement prepared_statement, idx_t index);

duckdb_type duckdb_param_type(duckdb_prepared_statement prepared_statement, idx_t param_idx);

duckdb_logical_type duckdb_param_logical_type(duckdb_prepared_statement prepared_statement, idx_t param_idx);

duckdb_state duckdb_clear_bindings(duckdb_prepared_statement prepared_statement);

duckdb_statement_type duckdb_prepared_statement_type(duckdb_prepared_statement statement);

### Bind Values To Prepared Statements

duckdb_state duckdb_bind_value(duckdb_prepared_statement prepared_statement, idx_t param_idx, duckdb_value val);

duckdb_state duckdb_bind_parameter_index(duckdb_prepared_statement prepared_statement, idx_t *param_idx_out, const char *name);

duckdb_state duckdb_bind_boolean(duckdb_prepared_statement prepared_statement, idx_t param_idx, bool val);

duckdb_state duckdb_bind_int8(duckdb_prepared_statement prepared_statement, idx_t param_idx, int8_t val);

duckdb_state duckdb_bind_int16(duckdb_prepared_statement prepared_statement, idx_t param_idx, int16_t val);

duckdb_state duckdb_bind_int32(duckdb_prepared_statement prepared_statement, idx_t param_idx, int32_t val);

duckdb_state duckdb_bind_int64(duckdb_prepared_statement prepared_statement, idx_t param_idx, int64_t val);

duckdb_state duckdb_bind_hugeint(duckdb_prepared_statement prepared_statement, idx_t param_idx, duckdb_hugeint val);

duckdb_state duckdb_bind_uhugeint(duckdb_prepared_statement prepared_statement, idx_t param_idx, duckdb_uhugeint val);

duckdb_state duckdb_bind_decimal(duckdb_prepared_statement prepared_statement, idx_t param_idx, duckdb_decimal val);

duckdb_state duckdb_bind_uint8(duckdb_prepared_statement prepared_statement, idx_t param_idx, uint8_t val);

duckdb_state duckdb_bind_uint16(duckdb_prepared_statement prepared_statement, idx_t param_idx, uint16_t val);

duckdb_state duckdb_bind_uint32(duckdb_prepared_statement prepared_statement, idx_t param_idx, uint32_t val);

duckdb_state duckdb_bind_uint64(duckdb_prepared_statement prepared_statement, idx_t param_idx, uint64_t val);

duckdb_state duckdb_bind_float(duckdb_prepared_statement prepared_statement, idx_t param_idx, float val);

duckdb_state duckdb_bind_double(duckdb_prepared_statement prepared_statement, idx_t param_idx, double val);

duckdb_state duckdb_bind_date(duckdb_prepared_statement prepared_statement, idx_t param_idx, duckdb_date val);

duckdb_state duckdb_bind_time(duckdb_prepared_statement prepared_statement, idx_t param_idx, duckdb_time val);

duckdb_state duckdb_bind_timestamp(duckdb_prepared_statement prepared_statement, idx_t param_idx, duckdb_timestamp val);

duckdb_state duckdb_bind_timestamp_tz(duckdb_prepared_statement prepared_statement, idx_t param_idx, duckdb_timestamp val);

duckdb_state duckdb_bind_interval(duckdb_prepared_statement prepared_statement, idx_t param_idx, duckdb_interval val);

duckdb_state duckdb_bind_varchar(duckdb_prepared_statement prepared_statement, idx_t param_idx, const char *val);

duckdb_state duckdb_bind_varchar_length(duckdb_prepared_statement prepared_statement, idx_t param_idx, const char *val, idx_t length);

duckdb_state duckdb_bind_blob(duckdb_prepared_statement prepared_statement, idx_t param_idx, const void *data, idx_t length);

duckdb_state duckdb_bind_null(duckdb_prepared_statement prepared_statement, idx_t param_idx);

### Execute Prepared Statements

duckdb_state duckdb_execute_prepared(duckdb_prepared_statement prepared_statement, duckdb_result *out_result);

duckdb_state duckdb_execute_prepared_streaming(duckdb_prepared_statement prepared_statement, duckdb_result *out_result);

### Extract Statements

idx_t duckdb_extract_statements(duckdb_connection connection, const char *query, duckdb_extracted_statements *out_extracted_statements);

duckdb_state duckdb_prepare_extracted_statement(duckdb_connection connection, duckdb_extracted_statements extracted_statements, idx_t index, duckdb_prepared_statement *out_prepared_statement);

const char *duckdb_extract_statements_error(duckdb_extracted_statements extracted_statements);

void duckdb_destroy_extracted(duckdb_extracted_statements *extracted_statements);

### Pending Result Interface

duckdb_state duckdb_pending_prepared(duckdb_prepared_statement prepared_statement, duckdb_pending_result *out_result);

duckdb_state duckdb_pending_prepared_streaming(duckdb_prepared_statement prepared_statement, duckdb_pending_result *out_result);

void duckdb_destroy_pending(duckdb_pending_result *pending_result);

const char *duckdb_pending_error(duckdb_pending_result pending_result);

duckdb_pending_state duckdb_pending_execute_task(duckdb_pending_result pending_result);

duckdb_pending_state duckdb_pending_execute_check_state(duckdb_pending_result pending_result);

duckdb_state duckdb_execute_pending(duckdb_pending_result pending_result, duckdb_result *out_result);

bool duckdb_pending_execution_is_finished(duckdb_pending_state pending_state);

### Value Interface

void duckdb_destroy_value(duckdb_value *value);

duckdb_value duckdb_create_varchar(const char *text);

duckdb_value duckdb_create_varchar_length(const char *text, idx_t length);

duckdb_value duckdb_create_bool(bool input);

duckdb_value duckdb_create_int8(int8_t input);

duckdb_value duckdb_create_uint8(uint8_t input);

duckdb_value duckdb_create_int16(int16_t input);

duckdb_value duckdb_create_uint16(uint16_t input);

duckdb_value duckdb_create_int32(int32_t input);

duckdb_value duckdb_create_uint32(uint32_t input);

duckdb_value duckdb_create_uint64(uint64_t input);

duckdb_value duckdb_create_int64(int64_t val);

duckdb_value duckdb_create_hugeint(duckdb_hugeint input);

duckdb_value duckdb_create_uhugeint(duckdb_uhugeint input);

duckdb_value duckdb_create_varint(duckdb_varint input);

duckdb_value duckdb_create_decimal(duckdb_decimal input);

duckdb_value duckdb_create_float(float input);

duckdb_value duckdb_create_double(double input);

duckdb_value duckdb_create_date(duckdb_date input);

duckdb_value duckdb_create_time(duckdb_time input);

duckdb_value duckdb_create_time_tz_value(duckdb_time_tz value);

duckdb_value duckdb_create_timestamp(duckdb_timestamp input);

duckdb_value duckdb_create_timestamp_tz(duckdb_timestamp input);

duckdb_value duckdb_create_timestamp_s(duckdb_timestamp_s input);

duckdb_value duckdb_create_timestamp_ms(duckdb_timestamp_ms input);

duckdb_value duckdb_create_timestamp_ns(duckdb_timestamp_ns input);

duckdb_value duckdb_create_interval(duckdb_interval input);

duckdb_value duckdb_create_blob(const uint8_t *data, idx_t length);

duckdb_value duckdb_create_bit(duckdb_bit input);

duckdb_value duckdb_create_uuid(duckdb_uhugeint input);

bool duckdb_get_bool(duckdb_value val);

int8_t duckdb_get_int8(duckdb_value val);

uint8_t duckdb_get_uint8(duckdb_value val);

int16_t duckdb_get_int16(duckdb_value val);

uint16_t duckdb_get_uint16(duckdb_value val);

int32_t duckdb_get_int32(duckdb_value val);

uint32_t duckdb_get_uint32(duckdb_value val);

int64_t duckdb_get_int64(duckdb_value val);

uint64_t duckdb_get_uint64(duckdb_value val);

duckdb_hugeint duckdb_get_hugeint(duckdb_value val);

duckdb_uhugeint duckdb_get_uhugeint(duckdb_value val);

duckdb_varint duckdb_get_varint(duckdb_value val);

duckdb_decimal duckdb_get_decimal(duckdb_value val);

float duckdb_get_float(duckdb_value val);

double duckdb_get_double(duckdb_value val);

duckdb_date duckdb_get_date(duckdb_value val);

duckdb_time duckdb_get_time(duckdb_value val);

duckdb_time_tz duckdb_get_time_tz(duckdb_value val);

duckdb_timestamp duckdb_get_timestamp(duckdb_value val);

duckdb_timestamp duckdb_get_timestamp_tz(duckdb_value val);

duckdb_timestamp_s duckdb_get_timestamp_s(duckdb_value val);

duckdb_timestamp_ms duckdb_get_timestamp_ms(duckdb_value val);

duckdb_timestamp_ns duckdb_get_timestamp_ns(duckdb_value val);

duckdb_interval duckdb_get_interval(duckdb_value val);

duckdb_logical_type duckdb_get_value_type(duckdb_value val);

duckdb_blob duckdb_get_blob(duckdb_value val);

duckdb_bit duckdb_get_bit(duckdb_value val);

duckdb_uhugeint duckdb_get_uuid(duckdb_value val);

char *duckdb_get_varchar(duckdb_value value);

duckdb_value duckdb_create_struct_value(duckdb_logical_type type, duckdb_value *values);

duckdb_value duckdb_create_list_value(duckdb_logical_type type, duckdb_value *values, idx_t value_count);

duckdb_value duckdb_create_array_value(duckdb_logical_type type, duckdb_value *values, idx_t value_count);

idx_t duckdb_get_map_size(duckdb_value value);

duckdb_value duckdb_get_map_key(duckdb_value value, idx_t index);

duckdb_value duckdb_get_map_value(duckdb_value value, idx_t index);

bool duckdb_is_null_value(duckdb_value value);

duckdb_value duckdb_create_null_value();

idx_t duckdb_get_list_size(duckdb_value value);

duckdb_value duckdb_get_list_child(duckdb_value value, idx_t index);

duckdb_value duckdb_create_enum_value(duckdb_logical_type type, uint64_t value);

uint64_t duckdb_get_enum_value(duckdb_value value);

duckdb_value duckdb_get_struct_child(duckdb_value value, idx_t index);

### Logical Type Interface

duckdb_logical_type duckdb_create_logical_type(duckdb_type type);

char *duckdb_logical_type_get_alias(duckdb_logical_type type);

void duckdb_logical_type_set_alias(duckdb_logical_type type, const char *alias);

duckdb_logical_type duckdb_create_list_type(duckdb_logical_type type);

duckdb_logical_type duckdb_create_array_type(duckdb_logical_type type, idx_t array_size);

duckdb_logical_type duckdb_create_map_type(duckdb_logical_type key_type, duckdb_logical_type value_type);

duckdb_logical_type duckdb_create_union_type(duckdb_logical_type *member_types, const char **member_names, idx_t member_count);

duckdb_logical_type duckdb_create_struct_type(duckdb_logical_type *member_types, const char **member_names, idx_t member_count);

duckdb_logical_type duckdb_create_enum_type(const char **member_names, idx_t member_count);

duckdb_logical_type duckdb_create_decimal_type(uint8_t width, uint8_t scale);

duckdb_type duckdb_get_type_id(duckdb_logical_type type);

uint8_t duckdb_decimal_width(duckdb_logical_type type);

uint8_t duckdb_decimal_scale(duckdb_logical_type type);

duckdb_type duckdb_decimal_internal_type(duckdb_logical_type type);

duckdb_type duckdb_enum_internal_type(duckdb_logical_type type);

uint32_t duckdb_enum_dictionary_size(duckdb_logical_type type);

char *duckdb_enum_dictionary_value(duckdb_logical_type type, idx_t index);

duckdb_logical_type duckdb_list_type_child_type(duckdb_logical_type type);

duckdb_logical_type duckdb_array_type_child_type(duckdb_logical_type type);

idx_t duckdb_array_type_array_size(duckdb_logical_type type);

duckdb_logical_type duckdb_map_type_key_type(duckdb_logical_type type);

duckdb_logical_type duckdb_map_type_value_type(duckdb_logical_type type);

idx_t duckdb_struct_type_child_count(duckdb_logical_type type);

char *duckdb_struct_type_child_name(duckdb_logical_type type, idx_t index);

duckdb_logical_type duckdb_struct_type_child_type(duckdb_logical_type type, idx_t index);

idx_t duckdb_union_type_member_count(duckdb_logical_type type);

char *duckdb_union_type_member_name(duckdb_logical_type type, idx_t index);

duckdb_logical_type duckdb_union_type_member_type(duckdb_logical_type type, idx_t index);

void duckdb_destroy_logical_type(duckdb_logical_type *type);

duckdb_state duckdb_register_logical_type(duckdb_connection con, duckdb_logical_type type, duckdb_create_type_info info);

### Data Chunk Interface

duckdb_data_chunk duckdb_create_data_chunk(duckdb_logical_type *types, idx_t column_count);

void duckdb_destroy_data_chunk(duckdb_data_chunk *chunk);

void duckdb_data_chunk_reset(duckdb_data_chunk chunk);

idx_t duckdb_data_chunk_get_column_count(duckdb_data_chunk chunk);

duckdb_vector duckdb_data_chunk_get_vector(duckdb_data_chunk chunk, idx_t col_idx);

idx_t duckdb_data_chunk_get_size(duckdb_data_chunk chunk);

void duckdb_data_chunk_set_size(duckdb_data_chunk chunk, idx_t size);

### Vector Interface

duckdb_logical_type duckdb_vector_get_column_type(duckdb_vector vector);

void *duckdb_vector_get_data(duckdb_vector vector);

uint64_t *duckdb_vector_get_validity(duckdb_vector vector);

void duckdb_vector_ensure_validity_writable(duckdb_vector vector);

void duckdb_vector_assign_string_element(duckdb_vector vector, idx_t index, const char *str);

void duckdb_vector_assign_string_element_len(duckdb_vector vector, idx_t index, const char *str, idx_t str_len);

duckdb_vector duckdb_list_vector_get_child(duckdb_vector vector);

idx_t duckdb_list_vector_get_size(duckdb_vector vector);

duckdb_state duckdb_list_vector_set_size(duckdb_vector vector, idx_t size);

duckdb_state duckdb_list_vector_reserve(duckdb_vector vector, idx_t required_capacity);

duckdb_vector duckdb_struct_vector_get_child(duckdb_vector vector, idx_t index);

duckdb_vector duckdb_array_vector_get_child(duckdb_vector vector);

### Validity Mask Functions

bool duckdb_validity_row_is_valid(uint64_t *validity, idx_t row);

void duckdb_validity_set_row_validity(uint64_t *validity, idx_t row, bool valid);

void duckdb_validity_set_row_invalid(uint64_t *validity, idx_t row);

void duckdb_validity_set_row_valid(uint64_t *validity, idx_t row);

### Scalar Functions

duckdb_scalar_function duckdb_create_scalar_function();

void duckdb_destroy_scalar_function(duckdb_scalar_function *scalar_function);

void duckdb_scalar_function_set_name(duckdb_scalar_function scalar_function, const char *name);

void duckdb_scalar_function_set_varargs(duckdb_scalar_function scalar_function, duckdb_logical_type type);

void duckdb_scalar_function_set_special_handling(duckdb_scalar_function scalar_function);

void duckdb_scalar_function_set_volatile(duckdb_scalar_function scalar_function);

void duckdb_scalar_function_add_parameter(duckdb_scalar_function scalar_function, duckdb_logical_type type);

void duckdb_scalar_function_set_return_type(duckdb_scalar_function scalar_function, duckdb_logical_type type);

void duckdb_scalar_function_set_extra_info(duckdb_scalar_function scalar_function, void *extra_info, duckdb_delete_callback_t destroy);

void duckdb_scalar_function_set_function(duckdb_scalar_function scalar_function, duckdb_scalar_function_t function);

duckdb_state duckdb_register_scalar_function(duckdb_connection con, duckdb_scalar_function scalar_function);

void *duckdb_scalar_function_get_extra_info(duckdb_function_info info);

void duckdb_scalar_function_set_error(duckdb_function_info info, const char *error);

duckdb_scalar_function_set duckdb_create_scalar_function_set(const char *name);

void duckdb_destroy_scalar_function_set(duckdb_scalar_function_set *scalar_function_set);

duckdb_state duckdb_add_scalar_function_to_set(duckdb_scalar_function_set set, duckdb_scalar_function function);

duckdb_state duckdb_register_scalar_function_set(duckdb_connection con, duckdb_scalar_function_set set);

### Aggregate Functions

duckdb_aggregate_function duckdb_create_aggregate_function();

void duckdb_destroy_aggregate_function(duckdb_aggregate_function *aggregate_function);

void duckdb_aggregate_function_set_name(duckdb_aggregate_function aggregate_function, const char *name);

void duckdb_aggregate_function_add_parameter(duckdb_aggregate_function aggregate_function, duckdb_logical_type type);

void duckdb_aggregate_function_set_return_type(duckdb_aggregate_function aggregate_function, duckdb_logical_type type);

void duckdb_aggregate_function_set_functions(duckdb_aggregate_function aggregate_function, duckdb_aggregate_state_size state_size, duckdb_aggregate_init_t state_init, duckdb_aggregate_update_t update, duckdb_aggregate_combine_t combine, duckdb_aggregate_finalize_t finalize);

void duckdb_aggregate_function_set_destructor(duckdb_aggregate_function aggregate_function, duckdb_aggregate_destroy_t destroy);

duckdb_state duckdb_register_aggregate_function(duckdb_connection con, duckdb_aggregate_function aggregate_function);

void duckdb_aggregate_function_set_special_handling(duckdb_aggregate_function aggregate_function);

void duckdb_aggregate_function_set_extra_info(duckdb_aggregate_function aggregate_function, void *extra_info, duckdb_delete_callback_t destroy);

void *duckdb_aggregate_function_get_extra_info(duckdb_function_info info);

void duckdb_aggregate_function_set_error(duckdb_function_info info, const char *error);

duckdb_aggregate_function_set duckdb_create_aggregate_function_set(const char *name);

void duckdb_destroy_aggregate_function_set(duckdb_aggregate_function_set *aggregate_function_set);

duckdb_state duckdb_add_aggregate_function_to_set(duckdb_aggregate_function_set set, duckdb_aggregate_function function);

duckdb_state duckdb_register_aggregate_function_set(duckdb_connection con, duckdb_aggregate_function_set set);

### Table Functions

duckdb_table_function duckdb_create_table_function();

void duckdb_destroy_table_function(duckdb_table_function *table_function);

void duckdb_table_function_set_name(duckdb_table_function table_function, const char *name);

void duckdb_table_function_add_parameter(duckdb_table_function table_function, duckdb_logical_type type);

void duckdb_table_function_add_named_parameter(duckdb_table_function table_function, const char *name, duckdb_logical_type type);

void duckdb_table_function_set_extra_info(duckdb_table_function table_function, void *extra_info, duckdb_delete_callback_t destroy);

void duckdb_table_function_set_bind(duckdb_table_function table_function, duckdb_table_function_bind_t bind);

void duckdb_table_function_set_init(duckdb_table_function table_function, duckdb_table_function_init_t init);

void duckdb_table_function_set_local_init(duckdb_table_function table_function, duckdb_table_function_init_t init);

void duckdb_table_function_set_function(duckdb_table_function table_function, duckdb_table_function_t function);

void duckdb_table_function_supports_projection_pushdown(duckdb_table_function table_function, bool pushdown);

duckdb_state duckdb_register_table_function(duckdb_connection con, duckdb_table_function function);

### Table Function Bind

void *duckdb_bind_get_extra_info(duckdb_bind_info info);

void duckdb_bind_add_result_column(duckdb_bind_info info, const char *name, duckdb_logical_type type);

idx_t duckdb_bind_get_parameter_count(duckdb_bind_info info);

duckdb_value duckdb_bind_get_parameter(duckdb_bind_info info, idx_t index);

duckdb_value duckdb_bind_get_named_parameter(duckdb_bind_info info, const char *name);

void duckdb_bind_set_bind_data(duckdb_bind_info info, void *bind_data, duckdb_delete_callback_t destroy);

void duckdb_bind_set_cardinality(duckdb_bind_info info, idx_t cardinality, bool is_exact);

void duckdb_bind_set_error(duckdb_bind_info info, const char *error);

### Table Function Init

void *duckdb_init_get_extra_info(duckdb_init_info info);

void *duckdb_init_get_bind_data(duckdb_init_info info);

void duckdb_init_set_init_data(duckdb_init_info info, void *init_data, duckdb_delete_callback_t destroy);

idx_t duckdb_init_get_column_count(duckdb_init_info info);

idx_t duckdb_init_get_column_index(duckdb_init_info info, idx_t column_index);

void duckdb_init_set_max_threads(duckdb_init_info info, idx_t max_threads);

void duckdb_init_set_error(duckdb_init_info info, const char *error);

### Table Function

void *duckdb_function_get_extra_info(duckdb_function_info info);

void *duckdb_function_get_bind_data(duckdb_function_info info);

void *duckdb_function_get_init_data(duckdb_function_info info);

void *duckdb_function_get_local_init_data(duckdb_function_info info);

void duckdb_function_set_error(duckdb_function_info info, const char *error);

### Replacement Scans

void duckdb_add_replacement_scan(duckdb_database db, duckdb_replacement_callback_t replacement, void *extra_data, duckdb_delete_callback_t delete_callback);

void duckdb_replacement_scan_set_function_name(duckdb_replacement_scan_info info, const char *function_name);

void duckdb_replacement_scan_add_parameter(duckdb_replacement_scan_info info, duckdb_value parameter);

void duckdb_replacement_scan_set_error(duckdb_replacement_scan_info info, const char *error);

### Profiling Info

duckdb_profiling_info duckdb_get_profiling_info(duckdb_connection connection);

duckdb_value duckdb_profiling_info_get_value(duckdb_profiling_info info, const char *key);

duckdb_value duckdb_profiling_info_get_metrics(duckdb_profiling_info info);

idx_t duckdb_profiling_info_get_child_count(duckdb_profiling_info info);

duckdb_profiling_info duckdb_profiling_info_get_child(duckdb_profiling_info info, idx_t index);

### Appender

duckdb_state duckdb_appender_create(duckdb_connection connection, const char *schema, const char *table, duckdb_appender *out_appender);

duckdb_state duckdb_appender_create_ext(duckdb_connection connection, const char *catalog, const char *schema, const char *table, duckdb_appender *out_appender);

idx_t duckdb_appender_column_count(duckdb_appender appender);

duckdb_logical_type duckdb_appender_column_type(duckdb_appender appender, idx_t col_idx);

const char *duckdb_appender_error(duckdb_appender appender);

duckdb_state duckdb_appender_flush(duckdb_appender appender);

duckdb_state duckdb_appender_close(duckdb_appender appender);

duckdb_state duckdb_appender_destroy(duckdb_appender *appender);

duckdb_state duckdb_appender_add_column(duckdb_appender appender, const char *name);

duckdb_state duckdb_appender_clear_columns(duckdb_appender appender);

duckdb_state duckdb_appender_begin_row(duckdb_appender appender);

duckdb_state duckdb_appender_end_row(duckdb_appender appender);

duckdb_state duckdb_append_default(duckdb_appender appender);

duckdb_state duckdb_append_default_to_chunk(duckdb_appender appender, duckdb_data_chunk chunk, idx_t col, idx_t row);

duckdb_state duckdb_append_bool(duckdb_appender appender, bool value);

duckdb_state duckdb_append_int8(duckdb_appender appender, int8_t value);

duckdb_state duckdb_append_int16(duckdb_appender appender, int16_t value);

duckdb_state duckdb_append_int32(duckdb_appender appender, int32_t value);

duckdb_state duckdb_append_int64(duckdb_appender appender, int64_t value);

duckdb_state duckdb_append_hugeint(duckdb_appender appender, duckdb_hugeint value);

duckdb_state duckdb_append_uint8(duckdb_appender appender, uint8_t value);

duckdb_state duckdb_append_uint16(duckdb_appender appender, uint16_t value);

duckdb_state duckdb_append_uint32(duckdb_appender appender, uint32_t value);

duckdb_state duckdb_append_uint64(duckdb_appender appender, uint64_t value);

duckdb_state duckdb_append_uhugeint(duckdb_appender appender, duckdb_uhugeint value);

duckdb_state duckdb_append_float(duckdb_appender appender, float value);

duckdb_state duckdb_append_double(duckdb_appender appender, double value);

duckdb_state duckdb_append_date(duckdb_appender appender, duckdb_date value);

duckdb_state duckdb_append_time(duckdb_appender appender, duckdb_time value);

duckdb_state duckdb_append_timestamp(duckdb_appender appender, duckdb_timestamp value);

duckdb_state duckdb_append_interval(duckdb_appender appender, duckdb_interval value);

duckdb_state duckdb_append_varchar(duckdb_appender appender, const char *val);

duckdb_state duckdb_append_varchar_length(duckdb_appender appender, const char *val, idx_t length);

duckdb_state duckdb_append_blob(duckdb_appender appender, const void *data, idx_t length);

duckdb_state duckdb_append_null(duckdb_appender appender);

duckdb_state duckdb_append_value(duckdb_appender appender, duckdb_value value);

duckdb_state duckdb_append_data_chunk(duckdb_appender appender, duckdb_data_chunk chunk);

### Table Description

duckdb_state duckdb_table_description_create(duckdb_connection connection, const char *schema, const char *table, duckdb_table_description *out);

duckdb_state duckdb_table_description_create_ext(duckdb_connection connection, const char *catalog, const char *schema, const char *table, duckdb_table_description *out);

void duckdb_table_description_destroy(duckdb_table_description *table_description);

const char *duckdb_table_description_error(duckdb_table_description table_description);

duckdb_state duckdb_column_has_default(duckdb_table_description table_description, idx_t index, bool *out);

char *duckdb_table_description_get_column_name(duckdb_table_description table_description, idx_t index);

### Arrow Interface

duckdb_state duckdb_query_arrow(duckdb_connection connection, const char *query, duckdb_arrow *out_result);

duckdb_state duckdb_query_arrow_schema(duckdb_arrow result, duckdb_arrow_schema *out_schema);

duckdb_state duckdb_prepared_arrow_schema(duckdb_prepared_statement prepared, duckdb_arrow_schema *out_schema);

void duckdb_result_arrow_array(duckdb_result result, duckdb_data_chunk chunk, duckdb_arrow_array *out_array);

duckdb_state duckdb_query_arrow_array(duckdb_arrow result, duckdb_arrow_array *out_array);

idx_t duckdb_arrow_column_count(duckdb_arrow result);

idx_t duckdb_arrow_row_count(duckdb_arrow result);

idx_t duckdb_arrow_rows_changed(duckdb_arrow result);

const char *duckdb_query_arrow_error(duckdb_arrow result);

void duckdb_destroy_arrow(duckdb_arrow *result);

void duckdb_destroy_arrow_stream(duckdb_arrow_stream *stream_p);

duckdb_state duckdb_execute_prepared_arrow(duckdb_prepared_statement prepared_statement, duckdb_arrow *out_result);

duckdb_state duckdb_arrow_scan(duckdb_connection connection, const char *table_name, duckdb_arrow_stream arrow);

duckdb_state duckdb_arrow_array_scan(duckdb_connection connection, const char *table_name, duckdb_arrow_schema arrow_schema, duckdb_arrow_array arrow_array, duckdb_arrow_stream *out_stream);

### Threading Information

void duckdb_execute_tasks(duckdb_database database, idx_t max_tasks);

duckdb_task_state duckdb_create_task_state(duckdb_database database);

void duckdb_execute_tasks_state(duckdb_task_state state);

idx_t duckdb_execute_n_tasks_state(duckdb_task_state state, idx_t max_tasks);

void duckdb_finish_execution(duckdb_task_state state);

bool duckdb_task_state_is_finished(duckdb_task_state state);

void duckdb_destroy_task_state(duckdb_task_state state);

bool duckdb_execution_is_finished(duckdb_connection con);

### Streaming Result Interface

duckdb_data_chunk duckdb_stream_fetch_chunk(duckdb_result result);

duckdb_data_chunk duckdb_fetch_chunk(duckdb_result result);

### Cast Functions

duckdb_cast_function duckdb_create_cast_function();

void duckdb_cast_function_set_source_type(duckdb_cast_function cast_function, duckdb_logical_type source_type);

void duckdb_cast_function_set_target_type(duckdb_cast_function cast_function, duckdb_logical_type target_type);

void duckdb_cast_function_set_implicit_cast_cost(duckdb_cast_function cast_function, int64_t cost);

void duckdb_cast_function_set_function(duckdb_cast_function cast_function, duckdb_cast_function_t function);

void duckdb_cast_function_set_extra_info(duckdb_cast_function cast_function, void *extra_info, duckdb_delete_callback_t destroy);

void *duckdb_cast_function_get_extra_info(duckdb_function_info info);

duckdb_cast_mode duckdb_cast_function_get_cast_mode(duckdb_function_info info);

void duckdb_cast_function_set_error(duckdb_function_info info, const char *error);

void duckdb_cast_function_set_row_error(duckdb_function_info info, const char *error, idx_t row, duckdb_vector output);

duckdb_state duckdb_register_cast_function(duckdb_connection con, duckdb_cast_function cast_function);

void duckdb_destroy_cast_function(duckdb_cast_function *cast_function);

#### `duckdb_create_instance_cache`

Creates a new database instance cache.

The instance cache is necessary if a client/program (re)opens multiple databases to the same file within the same

process. Must be destroyed with 'duckdb_destroy_instance_cache'.

##### Return Value

The database instance cache.

##### Syntax

duckdb_instance_cache duckdb_create_instance_cache(

  

);

#### `duckdb_get_or_create_from_cache`

Creates a new database instance in the instance cache, or retrieves an existing database instance.

Must be closed with 'duckdb_close'.

##### Syntax

duckdb_state duckdb_get_or_create_from_cache(

  duckdb_instance_cache instance_cache,

  const char *path,

  duckdb_database *out_database,

  duckdb_config config,

  char **out_error

);

##### Parameters

* `instance_cache`: The instance cache in which to create the database, or from which to take the database.

* `path`: Path to the database file on disk. Both `nullptr` and `:memory:` open or retrieve an in-memory database.

* `out_database`: The resulting cached database.

* `config`: (Optional) configuration used to create the database.

* `out_error`: If set and the function returns `DuckDBError`, this contains the error message.

Note that the error message must be freed using `duckdb_free`.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_destroy_instance_cache`

Destroys an existing database instance cache and de-allocates its memory.

##### Syntax

void duckdb_destroy_instance_cache(

  duckdb_instance_cache *instance_cache

);

##### Parameters

* `instance_cache`: The instance cache to destroy.

#### `duckdb_open`

Creates a new database or opens an existing database file stored at the given path.

If no path is given a new in-memory database is created instead.

The database must be closed with 'duckdb_close'.

##### Syntax

duckdb_state duckdb_open(

  const char *path,

  duckdb_database *out_database

);

##### Parameters

* `path`: Path to the database file on disk. Both `nullptr` and `:memory:` open an in-memory database.

* `out_database`: The result database object.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_open_ext`

Extended version of duckdb_open. Creates a new database or opens an existing database file stored at the given path.

The database must be closed with 'duckdb_close'.

##### Syntax

duckdb_state duckdb_open_ext(

  const char *path,

  duckdb_database *out_database,

  duckdb_config config,

  char **out_error

);

##### Parameters

* `path`: Path to the database file on disk. Both `nullptr` and `:memory:` open an in-memory database.

* `out_database`: The result database object.

* `config`: (Optional) configuration used to start up the database.

* `out_error`: If set and the function returns `DuckDBError`, this contains the error message.

Note that the error message must be freed using `duckdb_free`.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_close`

Closes the specified database and de-allocates all memory allocated for that database.

This should be called after you are done with any database allocated through `duckdb_open` or `duckdb_open_ext`.

Note that failing to call `duckdb_close` (in case of e.g., a program crash) will not cause data corruption.

Still, it is recommended to always correctly close a database object after you are done with it.

##### Syntax

void duckdb_close(

  duckdb_database *database

);

##### Parameters

* `database`: The database object to shut down.

#### `duckdb_connect`

Opens a connection to a database. Connections are required to query the database, and store transactional state

associated with the connection.

The instantiated connection should be closed using 'duckdb_disconnect'.

##### Syntax

duckdb_state duckdb_connect(

  duckdb_database database,

  duckdb_connection *out_connection

);

##### Parameters

* `database`: The database file to connect to.

* `out_connection`: The result connection object.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_interrupt`

Interrupt running query

##### Syntax

void duckdb_interrupt(

  duckdb_connection connection

);

##### Parameters

* `connection`: The connection to interrupt

#### `duckdb_query_progress`

Get progress of the running query

##### Syntax

duckdb_query_progress_type duckdb_query_progress(

  duckdb_connection connection

);

##### Parameters

* `connection`: The working connection

##### Return Value

-1 if no progress or a percentage of the progress

#### `duckdb_disconnect`

Closes the specified connection and de-allocates all memory allocated for that connection.

##### Syntax

void duckdb_disconnect(

  duckdb_connection *connection

);

##### Parameters

* `connection`: The connection to close.

#### `duckdb_library_version`

Returns the version of the linked DuckDB, with a version postfix for dev versions

Usually used for developing C extensions that must return this for a compatibility check.

##### Syntax

const char *duckdb_library_version(

  

);

#### `duckdb_create_config`

Initializes an empty configuration object that can be used to provide start-up options for the DuckDB instance

through `duckdb_open_ext`.

The duckdb_config must be destroyed using 'duckdb_destroy_config'

This will always succeed unless there is a malloc failure.

Note that `duckdb_destroy_config` should always be called on the resulting config, even if the function returns

`DuckDBError`.

##### Syntax

duckdb_state duckdb_create_config(

  duckdb_config *out_config

);

##### Parameters

* `out_config`: The result configuration object.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_config_count`

This returns the total amount of configuration options available for usage with `duckdb_get_config_flag`.

This should not be called in a loop as it internally loops over all the options.

##### Return Value

The amount of config options available.

##### Syntax

size_t duckdb_config_count(

  

);

#### `duckdb_get_config_flag`

Obtains a human-readable name and description of a specific configuration option. This can be used to e.g.

display configuration options. This will succeed unless `index` is out of range (i.e., `>= duckdb_config_count`).

The result name or description MUST NOT be freed.

##### Syntax

duckdb_state duckdb_get_config_flag(

  size_t index,

  const char **out_name,

  const char **out_description

);

##### Parameters

* `index`: The index of the configuration option (between 0 and `duckdb_config_count`)

* `out_name`: A name of the configuration flag.

* `out_description`: A description of the configuration flag.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_set_config`

Sets the specified option for the specified configuration. The configuration option is indicated by name.

To obtain a list of config options, see `duckdb_get_config_flag`.

In the source code, configuration options are defined in `config.cpp`.

This can fail if either the name is invalid, or if the value provided for the option is invalid.

##### Syntax

duckdb_state duckdb_set_config(

  duckdb_config config,

  const char *name,

  const char *option

);

##### Parameters

* `config`: The configuration object to set the option on.

* `name`: The name of the configuration flag to set.

* `option`: The value to set the configuration flag to.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_destroy_config`

Destroys the specified configuration object and de-allocates all memory allocated for the object.

##### Syntax

void duckdb_destroy_config(

  duckdb_config *config

);

##### Parameters

* `config`: The configuration object to destroy.

#### `duckdb_query`

Executes a SQL query within a connection and stores the full (materialized) result in the out_result pointer.

If the query fails to execute, DuckDBError is returned and the error message can be retrieved by calling

`duckdb_result_error`.

Note that after running `duckdb_query`, `duckdb_destroy_result` must be called on the result object even if the

query fails, otherwise the error stored within the result will not be freed correctly.

##### Syntax

duckdb_state duckdb_query(

  duckdb_connection connection,

  const char *query,

  duckdb_result *out_result

);

##### Parameters

* `connection`: The connection to perform the query in.

* `query`: The SQL query to run.

* `out_result`: The query result.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_destroy_result`

Closes the result and de-allocates all memory allocated for that connection.

##### Syntax

void duckdb_destroy_result(

  duckdb_result *result

);

##### Parameters

* `result`: The result to destroy.

#### `duckdb_column_name`

Returns the column name of the specified column. The result should not need to be freed; the column names will

automatically be destroyed when the result is destroyed.

Returns `NULL` if the column is out of range.

##### Syntax

const char *duckdb_column_name(

  duckdb_result *result,

  idx_t col

);

##### Parameters

* `result`: The result object to fetch the column name from.

* `col`: The column index.

##### Return Value

The column name of the specified column.

#### `duckdb_column_type`

Returns the column type of the specified column.

Returns `DUCKDB_TYPE_INVALID` if the column is out of range.

##### Syntax

duckdb_type duckdb_column_type(

  duckdb_result *result,

  idx_t col

);

##### Parameters

* `result`: The result object to fetch the column type from.

* `col`: The column index.

##### Return Value

The column type of the specified column.

#### `duckdb_result_statement_type`

Returns the statement type of the statement that was executed

##### Syntax

duckdb_statement_type duckdb_result_statement_type(

  duckdb_result result

);

##### Parameters

* `result`: The result object to fetch the statement type from.

##### Return Value

duckdb_statement_type value or DUCKDB_STATEMENT_TYPE_INVALID

#### `duckdb_column_logical_type`

Returns the logical column type of the specified column.

The return type of this call should be destroyed with `duckdb_destroy_logical_type`.

Returns `NULL` if the column is out of range.

##### Syntax

duckdb_logical_type duckdb_column_logical_type(

  duckdb_result *result,

  idx_t col

);

##### Parameters

* `result`: The result object to fetch the column type from.

* `col`: The column index.

##### Return Value

The logical column type of the specified column.

#### `duckdb_column_count`

Returns the number of columns present in a the result object.

##### Syntax

idx_t duckdb_column_count(

  duckdb_result *result

);

##### Parameters

* `result`: The result object.

##### Return Value

The number of columns present in the result object.

#### `duckdb_row_count`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Returns the number of rows present in the result object.

##### Syntax

idx_t duckdb_row_count(

  duckdb_result *result

);

##### Parameters

* `result`: The result object.

##### Return Value

The number of rows present in the result object.

#### `duckdb_rows_changed`

Returns the number of rows changed by the query stored in the result. This is relevant only for INSERT/UPDATE/DELETE

queries. For other queries the rows_changed will be 0.

##### Syntax

idx_t duckdb_rows_changed(

  duckdb_result *result

);

##### Parameters

* `result`: The result object.

##### Return Value

The number of rows changed.

#### `duckdb_column_data`

> Deprecated This method has been deprecated. Prefer using `duckdb_result_get_chunk` instead.

Returns the data of a specific column of a result in columnar format.

The function returns a dense array which contains the result data. The exact type stored in the array depends on the

corresponding duckdb_type (as provided by `duckdb_column_type`). For the exact type by which the data should be

accessed, see the comments in [the types section](types) or the `DUCKDB_TYPE` enum.

For example, for a column of type `DUCKDB_TYPE_INTEGER`, rows can be accessed in the following manner:

```c

int32_t *data = (int32_t *) duckdb_column_data(&result, 0);

printf("Data for row %d: %d\n", row, data[row]);

```

##### Syntax

void *duckdb_column_data(

  duckdb_result *result,

  idx_t col

);

##### Parameters

* `result`: The result object to fetch the column data from.

* `col`: The column index.

##### Return Value

The column data of the specified column.

#### `duckdb_nullmask_data`

> Deprecated This method has been deprecated. Prefer using `duckdb_result_get_chunk` instead.

Returns the nullmask of a specific column of a result in columnar format. The nullmask indicates for every row

whether or not the corresponding row is `NULL`. If a row is `NULL`, the values present in the array provided

by `duckdb_column_data` are undefined.

```c

int32_t *data = (int32_t *) duckdb_column_data(&result, 0);

bool *nullmask = duckdb_nullmask_data(&result, 0);

if (nullmask[row]) {

printf("Data for row %d: NULL\n", row);

} else {

printf("Data for row %d: %d\n", row, data[row]);

}

```

##### Syntax

bool *duckdb_nullmask_data(

  duckdb_result *result,

  idx_t col

);

##### Parameters

* `result`: The result object to fetch the nullmask from.

* `col`: The column index.

##### Return Value

The nullmask of the specified column.

#### `duckdb_result_error`

Returns the error message contained within the result. The error is only set if `duckdb_query` returns `DuckDBError`.

The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_result` is called.

##### Syntax

const char *duckdb_result_error(

  duckdb_result *result

);

##### Parameters

* `result`: The result object to fetch the error from.

##### Return Value

The error of the result.

#### `duckdb_result_error_type`

Returns the result error type contained within the result. The error is only set if `duckdb_query` returns

`DuckDBError`.

##### Syntax

duckdb_error_type duckdb_result_error_type(

  duckdb_result *result

);

##### Parameters

* `result`: The result object to fetch the error from.

##### Return Value

The error type of the result.

#### `duckdb_result_get_chunk`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Fetches a data chunk from the duckdb_result. This function should be called repeatedly until the result is exhausted.

The result must be destroyed with `duckdb_destroy_data_chunk`.

This function supersedes all `duckdb_value` functions, as well as the `duckdb_column_data` and `duckdb_nullmask_data`

functions. It results in significantly better performance, and should be preferred in newer code-bases.

If this function is used, none of the other result functions can be used and vice versa (i.e., this function cannot be

mixed with the legacy result functions).

Use `duckdb_result_chunk_count` to figure out how many chunks there are in the result.

##### Syntax

duckdb_data_chunk duckdb_result_get_chunk(

  duckdb_result result,

  idx_t chunk_index

);

##### Parameters

* `result`: The result object to fetch the data chunk from.

* `chunk_index`: The chunk index to fetch from.

##### Return Value

The resulting data chunk. Returns `NULL` if the chunk index is out of bounds.

#### `duckdb_result_is_streaming`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Checks if the type of the internal result is StreamQueryResult.

##### Syntax

bool duckdb_result_is_streaming(

  duckdb_result result

);

##### Parameters

* `result`: The result object to check.

##### Return Value

Whether or not the result object is of the type StreamQueryResult

#### `duckdb_result_chunk_count`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Returns the number of data chunks present in the result.

##### Syntax

idx_t duckdb_result_chunk_count(

  duckdb_result result

);

##### Parameters

* `result`: The result object

##### Return Value

Number of data chunks present in the result.

#### `duckdb_result_return_type`

Returns the return_type of the given result, or DUCKDB_RETURN_TYPE_INVALID on error

##### Syntax

duckdb_result_type duckdb_result_return_type(

  duckdb_result result

);

##### Parameters

* `result`: The result object

##### Return Value

The return_type

#### `duckdb_value_boolean`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The boolean value at the specified location, or false if the value cannot be converted.

##### Syntax

bool duckdb_value_boolean(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_int8`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The int8_t value at the specified location, or 0 if the value cannot be converted.

##### Syntax

int8_t duckdb_value_int8(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_int16`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The int16_t value at the specified location, or 0 if the value cannot be converted.

##### Syntax

int16_t duckdb_value_int16(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_int32`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The int32_t value at the specified location, or 0 if the value cannot be converted.

##### Syntax

int32_t duckdb_value_int32(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_int64`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The int64_t value at the specified location, or 0 if the value cannot be converted.

##### Syntax

int64_t duckdb_value_int64(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_hugeint`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The duckdb_hugeint value at the specified location, or 0 if the value cannot be converted.

##### Syntax

duckdb_hugeint duckdb_value_hugeint(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_uhugeint`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The duckdb_uhugeint value at the specified location, or 0 if the value cannot be converted.

##### Syntax

duckdb_uhugeint duckdb_value_uhugeint(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_decimal`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The duckdb_decimal value at the specified location, or 0 if the value cannot be converted.

##### Syntax

duckdb_decimal duckdb_value_decimal(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_uint8`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The uint8_t value at the specified location, or 0 if the value cannot be converted.

##### Syntax

uint8_t duckdb_value_uint8(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_uint16`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The uint16_t value at the specified location, or 0 if the value cannot be converted.

##### Syntax

uint16_t duckdb_value_uint16(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_uint32`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The uint32_t value at the specified location, or 0 if the value cannot be converted.

##### Syntax

uint32_t duckdb_value_uint32(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_uint64`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The uint64_t value at the specified location, or 0 if the value cannot be converted.

##### Syntax

uint64_t duckdb_value_uint64(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_float`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The float value at the specified location, or 0 if the value cannot be converted.

##### Syntax

float duckdb_value_float(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_double`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The double value at the specified location, or 0 if the value cannot be converted.

##### Syntax

double duckdb_value_double(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_date`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The duckdb_date value at the specified location, or 0 if the value cannot be converted.

##### Syntax

duckdb_date duckdb_value_date(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_time`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The duckdb_time value at the specified location, or 0 if the value cannot be converted.

##### Syntax

duckdb_time duckdb_value_time(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_timestamp`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The duckdb_timestamp value at the specified location, or 0 if the value cannot be converted.

##### Syntax

duckdb_timestamp duckdb_value_timestamp(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_interval`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The duckdb_interval value at the specified location, or 0 if the value cannot be converted.

##### Syntax

duckdb_interval duckdb_value_interval(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_varchar`

> Deprecated This method has been deprecated. Use duckdb_value_string instead. This function does not work correctly if the string contains null

bytes.

##### Return Value

The text value at the specified location as a null-terminated string, or nullptr if the value cannot be

converted. The result must be freed with `duckdb_free`.

##### Syntax

char *duckdb_value_varchar(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_string`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

No support for nested types, and for other complex types.

The resulting field "string.data" must be freed with `duckdb_free.`

##### Return Value

The string value at the specified location. Attempts to cast the result value to string.

##### Syntax

duckdb_string duckdb_value_string(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_varchar_internal`

> Deprecated This method has been deprecated. Use duckdb_value_string_internal instead. This function does not work correctly if the string contains

null bytes.

##### Return Value

The char* value at the specified location. ONLY works on VARCHAR columns and does not auto-cast.

If the column is NOT a VARCHAR column this function will return NULL.

The result must NOT be freed.

##### Syntax

char *duckdb_value_varchar_internal(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_string_internal`

> Deprecated This method has been deprecated. Use duckdb_value_string_internal instead. This function does not work correctly if the string contains

null bytes.

##### Return Value

The char* value at the specified location. ONLY works on VARCHAR columns and does not auto-cast.

If the column is NOT a VARCHAR column this function will return NULL.

The result must NOT be freed.

##### Syntax

duckdb_string duckdb_value_string_internal(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_blob`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

The duckdb_blob value at the specified location. Returns a blob with blob.data set to nullptr if the

value cannot be converted. The resulting field "blob.data" must be freed with `duckdb_free.`

##### Syntax

duckdb_blob duckdb_value_blob(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_value_is_null`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

##### Return Value

Returns true if the value at the specified index is NULL, and false otherwise.

##### Syntax

bool duckdb_value_is_null(

  duckdb_result *result,

  idx_t col,

  idx_t row

);

#### `duckdb_malloc`

Allocate `size` bytes of memory using the duckdb internal malloc function. Any memory allocated in this manner

should be freed using `duckdb_free`.

##### Syntax

void *duckdb_malloc(

  size_t size

);

##### Parameters

* `size`: The number of bytes to allocate.

##### Return Value

A pointer to the allocated memory region.

#### `duckdb_free`

Free a value returned from `duckdb_malloc`, `duckdb_value_varchar`, `duckdb_value_blob`, or

`duckdb_value_string`.

##### Syntax

void duckdb_free(

  void *ptr

);

##### Parameters

* `ptr`: The memory region to de-allocate.

#### `duckdb_vector_size`

The internal vector size used by DuckDB.

This is the amount of tuples that will fit into a data chunk created by `duckdb_create_data_chunk`.

##### Return Value

The vector size.

##### Syntax

idx_t duckdb_vector_size(

  

);

#### `duckdb_string_is_inlined`

Whether or not the duckdb_string_t value is inlined.

This means that the data of the string does not have a separate allocation.

##### Syntax

bool duckdb_string_is_inlined(

  duckdb_string_t string

);

#### `duckdb_string_t_length`

Get the string length of a string_t

##### Syntax

uint32_t duckdb_string_t_length(

  duckdb_string_t string

);

##### Parameters

* `string`: The string to get the length of.

##### Return Value

The length.

#### `duckdb_string_t_data`

Get a pointer to the string data of a string_t

##### Syntax

const char *duckdb_string_t_data(

  duckdb_string_t *string

);

##### Parameters

* `string`: The string to get the pointer to.

##### Return Value

The pointer.

#### `duckdb_from_date`

Decompose a `duckdb_date` object into year, month and date (stored as `duckdb_date_struct`).

##### Syntax

duckdb_date_struct duckdb_from_date(

  duckdb_date date

);

##### Parameters

* `date`: The date object, as obtained from a `DUCKDB_TYPE_DATE` column.

##### Return Value

The `duckdb_date_struct` with the decomposed elements.

#### `duckdb_to_date`

Re-compose a `duckdb_date` from year, month and date (`duckdb_date_struct`).

##### Syntax

duckdb_date duckdb_to_date(

  duckdb_date_struct date

);

##### Parameters

* `date`: The year, month and date stored in a `duckdb_date_struct`.

##### Return Value

The `duckdb_date` element.

#### `duckdb_is_finite_date`

Test a `duckdb_date` to see if it is a finite value.

##### Syntax

bool duckdb_is_finite_date(

  duckdb_date date

);

##### Parameters

* `date`: The date object, as obtained from a `DUCKDB_TYPE_DATE` column.

##### Return Value

True if the date is finite, false if it is ±infinity.

#### `duckdb_from_time`

Decompose a `duckdb_time` object into hour, minute, second and microsecond (stored as `duckdb_time_struct`).

##### Syntax

duckdb_time_struct duckdb_from_time(

  duckdb_time time

);

##### Parameters

* `time`: The time object, as obtained from a `DUCKDB_TYPE_TIME` column.

##### Return Value

The `duckdb_time_struct` with the decomposed elements.

#### `duckdb_create_time_tz`

Create a `duckdb_time_tz` object from micros and a timezone offset.

##### Syntax

duckdb_time_tz duckdb_create_time_tz(

  int64_t micros,

  int32_t offset

);

##### Parameters

* `micros`: The microsecond component of the time.

* `offset`: The timezone offset component of the time.

##### Return Value

The `duckdb_time_tz` element.

#### `duckdb_from_time_tz`

Decompose a TIME_TZ objects into micros and a timezone offset.

Use `duckdb_from_time` to further decompose the micros into hour, minute, second and microsecond.

##### Syntax

duckdb_time_tz_struct duckdb_from_time_tz(

  duckdb_time_tz micros

);

##### Parameters

* `micros`: The time object, as obtained from a `DUCKDB_TYPE_TIME_TZ` column.

#### `duckdb_to_time`

Re-compose a `duckdb_time` from hour, minute, second and microsecond (`duckdb_time_struct`).

##### Syntax

duckdb_time duckdb_to_time(

  duckdb_time_struct time

);

##### Parameters

* `time`: The hour, minute, second and microsecond in a `duckdb_time_struct`.

##### Return Value

The `duckdb_time` element.

#### `duckdb_from_timestamp`

Decompose a `duckdb_timestamp` object into a `duckdb_timestamp_struct`.

##### Syntax

duckdb_timestamp_struct duckdb_from_timestamp(

  duckdb_timestamp ts

);

##### Parameters

* `ts`: The ts object, as obtained from a `DUCKDB_TYPE_TIMESTAMP` column.

##### Return Value

The `duckdb_timestamp_struct` with the decomposed elements.

#### `duckdb_to_timestamp`

Re-compose a `duckdb_timestamp` from a duckdb_timestamp_struct.

##### Syntax

duckdb_timestamp duckdb_to_timestamp(

  duckdb_timestamp_struct ts

);

##### Parameters

* `ts`: The de-composed elements in a `duckdb_timestamp_struct`.

##### Return Value

The `duckdb_timestamp` element.

#### `duckdb_is_finite_timestamp`

Test a `duckdb_timestamp` to see if it is a finite value.

##### Syntax

bool duckdb_is_finite_timestamp(

  duckdb_timestamp ts

);

##### Parameters

* `ts`: The duckdb_timestamp object, as obtained from a `DUCKDB_TYPE_TIMESTAMP` column.

##### Return Value

True if the timestamp is finite, false if it is ±infinity.

#### `duckdb_is_finite_timestamp_s`

Test a `duckdb_timestamp_s` to see if it is a finite value.

##### Syntax

bool duckdb_is_finite_timestamp_s(

  duckdb_timestamp_s ts

);

##### Parameters

* `ts`: The duckdb_timestamp_s object, as obtained from a `DUCKDB_TYPE_TIMESTAMP_S` column.

##### Return Value

True if the timestamp is finite, false if it is ±infinity.

#### `duckdb_is_finite_timestamp_ms`

Test a `duckdb_timestamp_ms` to see if it is a finite value.

##### Syntax

bool duckdb_is_finite_timestamp_ms(

  duckdb_timestamp_ms ts

);

##### Parameters

* `ts`: The duckdb_timestamp_ms object, as obtained from a `DUCKDB_TYPE_TIMESTAMP_MS` column.

##### Return Value

True if the timestamp is finite, false if it is ±infinity.

#### `duckdb_is_finite_timestamp_ns`

Test a `duckdb_timestamp_ns` to see if it is a finite value.

##### Syntax

bool duckdb_is_finite_timestamp_ns(

  duckdb_timestamp_ns ts

);

##### Parameters

* `ts`: The duckdb_timestamp_ns object, as obtained from a `DUCKDB_TYPE_TIMESTAMP_NS` column.

##### Return Value

True if the timestamp is finite, false if it is ±infinity.

#### `duckdb_hugeint_to_double`

Converts a duckdb_hugeint object (as obtained from a `DUCKDB_TYPE_HUGEINT` column) into a double.

##### Syntax

double duckdb_hugeint_to_double(

  duckdb_hugeint val

);

##### Parameters

* `val`: The hugeint value.

##### Return Value

The converted `double` element.

#### `duckdb_double_to_hugeint`

Converts a double value to a duckdb_hugeint object.

If the conversion fails because the double value is too big the result will be 0.

##### Syntax

duckdb_hugeint duckdb_double_to_hugeint(

  double val

);

##### Parameters

* `val`: The double value.

##### Return Value

The converted `duckdb_hugeint` element.

#### `duckdb_uhugeint_to_double`

Converts a duckdb_uhugeint object (as obtained from a `DUCKDB_TYPE_UHUGEINT` column) into a double.

##### Syntax

double duckdb_uhugeint_to_double(

  duckdb_uhugeint val

);

##### Parameters

* `val`: The uhugeint value.

##### Return Value

The converted `double` element.

#### `duckdb_double_to_uhugeint`

Converts a double value to a duckdb_uhugeint object.

If the conversion fails because the double value is too big the result will be 0.

##### Syntax

duckdb_uhugeint duckdb_double_to_uhugeint(

  double val

);

##### Parameters

* `val`: The double value.

##### Return Value

The converted `duckdb_uhugeint` element.

#### `duckdb_double_to_decimal`

Converts a double value to a duckdb_decimal object.

If the conversion fails because the double value is too big, or the width/scale are invalid the result will be 0.

##### Syntax

duckdb_decimal duckdb_double_to_decimal(

  double val,

  uint8_t width,

  uint8_t scale

);

##### Parameters

* `val`: The double value.

##### Return Value

The converted `duckdb_decimal` element.

#### `duckdb_decimal_to_double`

Converts a duckdb_decimal object (as obtained from a `DUCKDB_TYPE_DECIMAL` column) into a double.

##### Syntax

double duckdb_decimal_to_double(

  duckdb_decimal val

);

##### Parameters

* `val`: The decimal value.

##### Return Value

The converted `double` element.

#### `duckdb_prepare`

Create a prepared statement object from a query.

Note that after calling `duckdb_prepare`, the prepared statement should always be destroyed using

`duckdb_destroy_prepare`, even if the prepare fails.

If the prepare fails, `duckdb_prepare_error` can be called to obtain the reason why the prepare failed.

##### Syntax

duckdb_state duckdb_prepare(

  duckdb_connection connection,

  const char *query,

  duckdb_prepared_statement *out_prepared_statement

);

##### Parameters

* `connection`: The connection object

* `query`: The SQL query to prepare

* `out_prepared_statement`: The resulting prepared statement object

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_destroy_prepare`

Closes the prepared statement and de-allocates all memory allocated for the statement.

##### Syntax

void duckdb_destroy_prepare(

  duckdb_prepared_statement *prepared_statement

);

##### Parameters

* `prepared_statement`: The prepared statement to destroy.

#### `duckdb_prepare_error`

Returns the error message associated with the given prepared statement.

If the prepared statement has no error message, this returns `nullptr` instead.

The error message should not be freed. It will be de-allocated when `duckdb_destroy_prepare` is called.

##### Syntax

const char *duckdb_prepare_error(

  duckdb_prepared_statement prepared_statement

);

##### Parameters

* `prepared_statement`: The prepared statement to obtain the error from.

##### Return Value

The error message, or `nullptr` if there is none.

#### `duckdb_nparams`

Returns the number of parameters that can be provided to the given prepared statement.

Returns 0 if the query was not successfully prepared.

##### Syntax

idx_t duckdb_nparams(

  duckdb_prepared_statement prepared_statement

);

##### Parameters

* `prepared_statement`: The prepared statement to obtain the number of parameters for.

#### `duckdb_parameter_name`

Returns the name used to identify the parameter

The returned string should be freed using `duckdb_free`.

Returns NULL if the index is out of range for the provided prepared statement.

##### Syntax

const char *duckdb_parameter_name(

  duckdb_prepared_statement prepared_statement,

  idx_t index

);

##### Parameters

* `prepared_statement`: The prepared statement for which to get the parameter name from.

#### `duckdb_param_type`

Returns the parameter type for the parameter at the given index.

Returns `DUCKDB_TYPE_INVALID` if the parameter index is out of range or the statement was not successfully prepared.

##### Syntax

duckdb_type duckdb_param_type(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx

);

##### Parameters

* `prepared_statement`: The prepared statement.

* `param_idx`: The parameter index.

##### Return Value

The parameter type

#### `duckdb_param_logical_type`

Returns the logical type for the parameter at the given index.

Returns `nullptr` if the parameter index is out of range or the statement was not successfully prepared.

The return type of this call should be destroyed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_param_logical_type(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx

);

##### Parameters

* `prepared_statement`: The prepared statement.

* `param_idx`: The parameter index.

##### Return Value

The logical type of the parameter

#### `duckdb_clear_bindings`

Clear the params bind to the prepared statement.

##### Syntax

duckdb_state duckdb_clear_bindings(

  duckdb_prepared_statement prepared_statement

);

#### `duckdb_prepared_statement_type`

Returns the statement type of the statement to be executed

##### Syntax

duckdb_statement_type duckdb_prepared_statement_type(

  duckdb_prepared_statement statement

);

##### Parameters

* `statement`: The prepared statement.

##### Return Value

duckdb_statement_type value or DUCKDB_STATEMENT_TYPE_INVALID

#### `duckdb_bind_value`

Binds a value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_value(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  duckdb_value val

);

#### `duckdb_bind_parameter_index`

Retrieve the index of the parameter for the prepared statement, identified by name

##### Syntax

duckdb_state duckdb_bind_parameter_index(

  duckdb_prepared_statement prepared_statement,

  idx_t *param_idx_out,

  const char *name

);

#### `duckdb_bind_boolean`

Binds a bool value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_boolean(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  bool val

);

#### `duckdb_bind_int8`

Binds an int8_t value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_int8(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  int8_t val

);

#### `duckdb_bind_int16`

Binds an int16_t value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_int16(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  int16_t val

);

#### `duckdb_bind_int32`

Binds an int32_t value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_int32(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  int32_t val

);

#### `duckdb_bind_int64`

Binds an int64_t value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_int64(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  int64_t val

);

#### `duckdb_bind_hugeint`

Binds a duckdb_hugeint value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_hugeint(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  duckdb_hugeint val

);

#### `duckdb_bind_uhugeint`

Binds an duckdb_uhugeint value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_uhugeint(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  duckdb_uhugeint val

);

#### `duckdb_bind_decimal`

Binds a duckdb_decimal value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_decimal(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  duckdb_decimal val

);

#### `duckdb_bind_uint8`

Binds an uint8_t value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_uint8(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  uint8_t val

);

#### `duckdb_bind_uint16`

Binds an uint16_t value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_uint16(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  uint16_t val

);

#### `duckdb_bind_uint32`

Binds an uint32_t value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_uint32(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  uint32_t val

);

#### `duckdb_bind_uint64`

Binds an uint64_t value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_uint64(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  uint64_t val

);

#### `duckdb_bind_float`

Binds a float value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_float(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  float val

);

#### `duckdb_bind_double`

Binds a double value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_double(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  double val

);

#### `duckdb_bind_date`

Binds a duckdb_date value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_date(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  duckdb_date val

);

#### `duckdb_bind_time`

Binds a duckdb_time value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_time(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  duckdb_time val

);

#### `duckdb_bind_timestamp`

Binds a duckdb_timestamp value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_timestamp(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  duckdb_timestamp val

);

#### `duckdb_bind_timestamp_tz`

Binds a duckdb_timestamp value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_timestamp_tz(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  duckdb_timestamp val

);

#### `duckdb_bind_interval`

Binds a duckdb_interval value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_interval(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  duckdb_interval val

);

#### `duckdb_bind_varchar`

Binds a null-terminated varchar value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_varchar(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  const char *val

);

#### `duckdb_bind_varchar_length`

Binds a varchar value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_varchar_length(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  const char *val,

  idx_t length

);

#### `duckdb_bind_blob`

Binds a blob value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_blob(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx,

  const void *data,

  idx_t length

);

#### `duckdb_bind_null`

Binds a NULL value to the prepared statement at the specified index.

##### Syntax

duckdb_state duckdb_bind_null(

  duckdb_prepared_statement prepared_statement,

  idx_t param_idx

);

#### `duckdb_execute_prepared`

Executes the prepared statement with the given bound parameters, and returns a materialized query result.

This method can be called multiple times for each prepared statement, and the parameters can be modified

between calls to this function.

Note that the result must be freed with `duckdb_destroy_result`.

##### Syntax

duckdb_state duckdb_execute_prepared(

  duckdb_prepared_statement prepared_statement,

  duckdb_result *out_result

);

##### Parameters

* `prepared_statement`: The prepared statement to execute.

* `out_result`: The query result.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_execute_prepared_streaming`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Executes the prepared statement with the given bound parameters, and returns an optionally-streaming query result.

To determine if the resulting query was in fact streamed, use `duckdb_result_is_streaming`

This method can be called multiple times for each prepared statement, and the parameters can be modified

between calls to this function.

Note that the result must be freed with `duckdb_destroy_result`.

##### Syntax

duckdb_state duckdb_execute_prepared_streaming(

  duckdb_prepared_statement prepared_statement,

  duckdb_result *out_result

);

##### Parameters

* `prepared_statement`: The prepared statement to execute.

* `out_result`: The query result.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_extract_statements`

Extract all statements from a query.

Note that after calling `duckdb_extract_statements`, the extracted statements should always be destroyed using

`duckdb_destroy_extracted`, even if no statements were extracted.

If the extract fails, `duckdb_extract_statements_error` can be called to obtain the reason why the extract failed.

##### Syntax

idx_t duckdb_extract_statements(

  duckdb_connection connection,

  const char *query,

  duckdb_extracted_statements *out_extracted_statements

);

##### Parameters

* `connection`: The connection object

* `query`: The SQL query to extract

* `out_extracted_statements`: The resulting extracted statements object

##### Return Value

The number of extracted statements or 0 on failure.

#### `duckdb_prepare_extracted_statement`

Prepare an extracted statement.

Note that after calling `duckdb_prepare_extracted_statement`, the prepared statement should always be destroyed using

`duckdb_destroy_prepare`, even if the prepare fails.

If the prepare fails, `duckdb_prepare_error` can be called to obtain the reason why the prepare failed.

##### Syntax

duckdb_state duckdb_prepare_extracted_statement(

  duckdb_connection connection,

  duckdb_extracted_statements extracted_statements,

  idx_t index,

  duckdb_prepared_statement *out_prepared_statement

);

##### Parameters

* `connection`: The connection object

* `extracted_statements`: The extracted statements object

* `index`: The index of the extracted statement to prepare

* `out_prepared_statement`: The resulting prepared statement object

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_extract_statements_error`

Returns the error message contained within the extracted statements.

The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_extracted` is called.

##### Syntax

const char *duckdb_extract_statements_error(

  duckdb_extracted_statements extracted_statements

);

##### Parameters

* `extracted_statements`: The extracted statements to fetch the error from.

##### Return Value

The error of the extracted statements.

#### `duckdb_destroy_extracted`

De-allocates all memory allocated for the extracted statements.

##### Syntax

void duckdb_destroy_extracted(

  duckdb_extracted_statements *extracted_statements

);

##### Parameters

* `extracted_statements`: The extracted statements to destroy.

#### `duckdb_pending_prepared`

Executes the prepared statement with the given bound parameters, and returns a pending result.

The pending result represents an intermediate structure for a query that is not yet fully executed.

The pending result can be used to incrementally execute a query, returning control to the client between tasks.

Note that after calling `duckdb_pending_prepared`, the pending result should always be destroyed using

`duckdb_destroy_pending`, even if this function returns DuckDBError.

##### Syntax

duckdb_state duckdb_pending_prepared(

  duckdb_prepared_statement prepared_statement,

  duckdb_pending_result *out_result

);

##### Parameters

* `prepared_statement`: The prepared statement to execute.

* `out_result`: The pending query result.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_pending_prepared_streaming`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Executes the prepared statement with the given bound parameters, and returns a pending result.

This pending result will create a streaming duckdb_result when executed.

The pending result represents an intermediate structure for a query that is not yet fully executed.

Note that after calling `duckdb_pending_prepared_streaming`, the pending result should always be destroyed using

`duckdb_destroy_pending`, even if this function returns DuckDBError.

##### Syntax

duckdb_state duckdb_pending_prepared_streaming(

  duckdb_prepared_statement prepared_statement,

  duckdb_pending_result *out_result

);

##### Parameters

* `prepared_statement`: The prepared statement to execute.

* `out_result`: The pending query result.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_destroy_pending`

Closes the pending result and de-allocates all memory allocated for the result.

##### Syntax

void duckdb_destroy_pending(

  duckdb_pending_result *pending_result

);

##### Parameters

* `pending_result`: The pending result to destroy.

#### `duckdb_pending_error`

Returns the error message contained within the pending result.

The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_pending` is called.

##### Syntax

const char *duckdb_pending_error(

  duckdb_pending_result pending_result

);

##### Parameters

* `pending_result`: The pending result to fetch the error from.

##### Return Value

The error of the pending result.

#### `duckdb_pending_execute_task`

Executes a single task within the query, returning whether or not the query is ready.

If this returns DUCKDB_PENDING_RESULT_READY, the duckdb_execute_pending function can be called to obtain the result.

If this returns DUCKDB_PENDING_RESULT_NOT_READY, the duckdb_pending_execute_task function should be called again.

If this returns DUCKDB_PENDING_ERROR, an error occurred during execution.

The error message can be obtained by calling duckdb_pending_error on the pending_result.

##### Syntax

duckdb_pending_state duckdb_pending_execute_task(

  duckdb_pending_result pending_result

);

##### Parameters

* `pending_result`: The pending result to execute a task within.

##### Return Value

The state of the pending result after the execution.

#### `duckdb_pending_execute_check_state`

If this returns DUCKDB_PENDING_RESULT_READY, the duckdb_execute_pending function can be called to obtain the result.

If this returns DUCKDB_PENDING_RESULT_NOT_READY, the duckdb_pending_execute_check_state function should be called again.

If this returns DUCKDB_PENDING_ERROR, an error occurred during execution.

The error message can be obtained by calling duckdb_pending_error on the pending_result.

##### Syntax

duckdb_pending_state duckdb_pending_execute_check_state(

  duckdb_pending_result pending_result

);

##### Parameters

* `pending_result`: The pending result.

##### Return Value

The state of the pending result.

#### `duckdb_execute_pending`

Fully execute a pending query result, returning the final query result.

If duckdb_pending_execute_task has been called until DUCKDB_PENDING_RESULT_READY was returned, this will return fast.

Otherwise, all remaining tasks must be executed first.

Note that the result must be freed with `duckdb_destroy_result`.

##### Syntax

duckdb_state duckdb_execute_pending(

  duckdb_pending_result pending_result,

  duckdb_result *out_result

);

##### Parameters

* `pending_result`: The pending result to execute.

* `out_result`: The result object.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_pending_execution_is_finished`

Returns whether a duckdb_pending_state is finished executing. For example if `pending_state` is

DUCKDB_PENDING_RESULT_READY, this function will return true.

##### Syntax

bool duckdb_pending_execution_is_finished(

  duckdb_pending_state pending_state

);

##### Parameters

* `pending_state`: The pending state on which to decide whether to finish execution.

##### Return Value

Boolean indicating pending execution should be considered finished.

#### `duckdb_destroy_value`

Destroys the value and de-allocates all memory allocated for that type.

##### Syntax

void duckdb_destroy_value(

  duckdb_value *value

);

##### Parameters

* `value`: The value to destroy.

#### `duckdb_create_varchar`

Creates a value from a null-terminated string

##### Syntax

duckdb_value duckdb_create_varchar(

  const char *text

);

##### Parameters

* `text`: The null-terminated string

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_varchar_length`

Creates a value from a string

##### Syntax

duckdb_value duckdb_create_varchar_length(

  const char *text,

  idx_t length

);

##### Parameters

* `text`: The text

* `length`: The length of the text

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_bool`

Creates a value from a boolean

##### Syntax

duckdb_value duckdb_create_bool(

  bool input

);

##### Parameters

* `input`: The boolean value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_int8`

Creates a value from a int8_t (a tinyint)

##### Syntax

duckdb_value duckdb_create_int8(

  int8_t input

);

##### Parameters

* `input`: The tinyint value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_uint8`

Creates a value from a uint8_t (a utinyint)

##### Syntax

duckdb_value duckdb_create_uint8(

  uint8_t input

);

##### Parameters

* `input`: The utinyint value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_int16`

Creates a value from a int16_t (a smallint)

##### Syntax

duckdb_value duckdb_create_int16(

  int16_t input

);

##### Parameters

* `input`: The smallint value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_uint16`

Creates a value from a uint16_t (a usmallint)

##### Syntax

duckdb_value duckdb_create_uint16(

  uint16_t input

);

##### Parameters

* `input`: The usmallint value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_int32`

Creates a value from a int32_t (an integer)

##### Syntax

duckdb_value duckdb_create_int32(

  int32_t input

);

##### Parameters

* `input`: The integer value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_uint32`

Creates a value from a uint32_t (a uinteger)

##### Syntax

duckdb_value duckdb_create_uint32(

  uint32_t input

);

##### Parameters

* `input`: The uinteger value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_uint64`

Creates a value from a uint64_t (a ubigint)

##### Syntax

duckdb_value duckdb_create_uint64(

  uint64_t input

);

##### Parameters

* `input`: The ubigint value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_int64`

Creates a value from an int64

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

##### Syntax

duckdb_value duckdb_create_int64(

  int64_t val

);

#### `duckdb_create_hugeint`

Creates a value from a hugeint

##### Syntax

duckdb_value duckdb_create_hugeint(

  duckdb_hugeint input

);

##### Parameters

* `input`: The hugeint value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_uhugeint`

Creates a value from a uhugeint

##### Syntax

duckdb_value duckdb_create_uhugeint(

  duckdb_uhugeint input

);

##### Parameters

* `input`: The uhugeint value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_varint`

Creates a VARINT value from a duckdb_varint

##### Syntax

duckdb_value duckdb_create_varint(

  duckdb_varint input

);

##### Parameters

* `input`: The duckdb_varint value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_decimal`

Creates a DECIMAL value from a duckdb_decimal

##### Syntax

duckdb_value duckdb_create_decimal(

  duckdb_decimal input

);

##### Parameters

* `input`: The duckdb_decimal value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_float`

Creates a value from a float

##### Syntax

duckdb_value duckdb_create_float(

  float input

);

##### Parameters

* `input`: The float value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_double`

Creates a value from a double

##### Syntax

duckdb_value duckdb_create_double(

  double input

);

##### Parameters

* `input`: The double value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_date`

Creates a value from a date

##### Syntax

duckdb_value duckdb_create_date(

  duckdb_date input

);

##### Parameters

* `input`: The date value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_time`

Creates a value from a time

##### Syntax

duckdb_value duckdb_create_time(

  duckdb_time input

);

##### Parameters

* `input`: The time value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_time_tz_value`

Creates a value from a time_tz.

Not to be confused with `duckdb_create_time_tz`, which creates a duckdb_time_tz_t.

##### Syntax

duckdb_value duckdb_create_time_tz_value(

  duckdb_time_tz value

);

##### Parameters

* `value`: The time_tz value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_timestamp`

Creates a TIMESTAMP value from a duckdb_timestamp

##### Syntax

duckdb_value duckdb_create_timestamp(

  duckdb_timestamp input

);

##### Parameters

* `input`: The duckdb_timestamp value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_timestamp_tz`

Creates a TIMESTAMP_TZ value from a duckdb_timestamp

##### Syntax

duckdb_value duckdb_create_timestamp_tz(

  duckdb_timestamp input

);

##### Parameters

* `input`: The duckdb_timestamp value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_timestamp_s`

Creates a TIMESTAMP_S value from a duckdb_timestamp_s

##### Syntax

duckdb_value duckdb_create_timestamp_s(

  duckdb_timestamp_s input

);

##### Parameters

* `input`: The duckdb_timestamp_s value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_timestamp_ms`

Creates a TIMESTAMP_MS value from a duckdb_timestamp_ms

##### Syntax

duckdb_value duckdb_create_timestamp_ms(

  duckdb_timestamp_ms input

);

##### Parameters

* `input`: The duckdb_timestamp_ms value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_timestamp_ns`

Creates a TIMESTAMP_NS value from a duckdb_timestamp_ns

##### Syntax

duckdb_value duckdb_create_timestamp_ns(

  duckdb_timestamp_ns input

);

##### Parameters

* `input`: The duckdb_timestamp_ns value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_interval`

Creates a value from an interval

##### Syntax

duckdb_value duckdb_create_interval(

  duckdb_interval input

);

##### Parameters

* `input`: The interval value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_blob`

Creates a value from a blob

##### Syntax

duckdb_value duckdb_create_blob(

  const uint8_t *data,

  idx_t length

);

##### Parameters

* `data`: The blob data

* `length`: The length of the blob data

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_bit`

Creates a BIT value from a duckdb_bit

##### Syntax

duckdb_value duckdb_create_bit(

  duckdb_bit input

);

##### Parameters

* `input`: The duckdb_bit value

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_create_uuid`

Creates a UUID value from a uhugeint

##### Syntax

duckdb_value duckdb_create_uuid(

  duckdb_uhugeint input

);

##### Parameters

* `input`: The duckdb_uhugeint containing the UUID

##### Return Value

The value. This must be destroyed with `duckdb_destroy_value`.

#### `duckdb_get_bool`

Returns the boolean value of the given value.

##### Syntax

bool duckdb_get_bool(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a boolean

##### Return Value

A boolean, or false if the value cannot be converted

#### `duckdb_get_int8`

Returns the int8_t value of the given value.

##### Syntax

int8_t duckdb_get_int8(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a tinyint

##### Return Value

A int8_t, or MinValue if the value cannot be converted

#### `duckdb_get_uint8`

Returns the uint8_t value of the given value.

##### Syntax

uint8_t duckdb_get_uint8(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a utinyint

##### Return Value

A uint8_t, or MinValue if the value cannot be converted

#### `duckdb_get_int16`

Returns the int16_t value of the given value.

##### Syntax

int16_t duckdb_get_int16(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a smallint

##### Return Value

A int16_t, or MinValue if the value cannot be converted

#### `duckdb_get_uint16`

Returns the uint16_t value of the given value.

##### Syntax

uint16_t duckdb_get_uint16(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a usmallint

##### Return Value

A uint16_t, or MinValue if the value cannot be converted

#### `duckdb_get_int32`

Returns the int32_t value of the given value.

##### Syntax

int32_t duckdb_get_int32(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a integer

##### Return Value

A int32_t, or MinValue if the value cannot be converted

#### `duckdb_get_uint32`

Returns the uint32_t value of the given value.

##### Syntax

uint32_t duckdb_get_uint32(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a uinteger

##### Return Value

A uint32_t, or MinValue if the value cannot be converted

#### `duckdb_get_int64`

Returns the int64_t value of the given value.

##### Syntax

int64_t duckdb_get_int64(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a bigint

##### Return Value

A int64_t, or MinValue if the value cannot be converted

#### `duckdb_get_uint64`

Returns the uint64_t value of the given value.

##### Syntax

uint64_t duckdb_get_uint64(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a ubigint

##### Return Value

A uint64_t, or MinValue if the value cannot be converted

#### `duckdb_get_hugeint`

Returns the hugeint value of the given value.

##### Syntax

duckdb_hugeint duckdb_get_hugeint(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a hugeint

##### Return Value

A duckdb_hugeint, or MinValue if the value cannot be converted

#### `duckdb_get_uhugeint`

Returns the uhugeint value of the given value.

##### Syntax

duckdb_uhugeint duckdb_get_uhugeint(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a uhugeint

##### Return Value

A duckdb_uhugeint, or MinValue if the value cannot be converted

#### `duckdb_get_varint`

Returns the duckdb_varint value of the given value.

The `data` field must be destroyed with `duckdb_free`.

##### Syntax

duckdb_varint duckdb_get_varint(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a VARINT

##### Return Value

A duckdb_varint. The `data` field must be destroyed with `duckdb_free`.

#### `duckdb_get_decimal`

Returns the duckdb_decimal value of the given value.

##### Syntax

duckdb_decimal duckdb_get_decimal(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a DECIMAL

##### Return Value

A duckdb_decimal, or MinValue if the value cannot be converted

#### `duckdb_get_float`

Returns the float value of the given value.

##### Syntax

float duckdb_get_float(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a float

##### Return Value

A float, or NAN if the value cannot be converted

#### `duckdb_get_double`

Returns the double value of the given value.

##### Syntax

double duckdb_get_double(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a double

##### Return Value

A double, or NAN if the value cannot be converted

#### `duckdb_get_date`

Returns the date value of the given value.

##### Syntax

duckdb_date duckdb_get_date(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a date

##### Return Value

A duckdb_date, or MinValue if the value cannot be converted

#### `duckdb_get_time`

Returns the time value of the given value.

##### Syntax

duckdb_time duckdb_get_time(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a time

##### Return Value

A duckdb_time, or MinValue if the value cannot be converted

#### `duckdb_get_time_tz`

Returns the time_tz value of the given value.

##### Syntax

duckdb_time_tz duckdb_get_time_tz(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a time_tz

##### Return Value

A duckdb_time_tz, or MinValue if the value cannot be converted

#### `duckdb_get_timestamp`

Returns the TIMESTAMP value of the given value.

##### Syntax

duckdb_timestamp duckdb_get_timestamp(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a TIMESTAMP

##### Return Value

A duckdb_timestamp, or MinValue if the value cannot be converted

#### `duckdb_get_timestamp_tz`

Returns the TIMESTAMP_TZ value of the given value.

##### Syntax

duckdb_timestamp duckdb_get_timestamp_tz(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a TIMESTAMP_TZ

##### Return Value

A duckdb_timestamp, or MinValue if the value cannot be converted

#### `duckdb_get_timestamp_s`

Returns the duckdb_timestamp_s value of the given value.

##### Syntax

duckdb_timestamp_s duckdb_get_timestamp_s(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a TIMESTAMP_S

##### Return Value

A duckdb_timestamp_s, or MinValue if the value cannot be converted

#### `duckdb_get_timestamp_ms`

Returns the duckdb_timestamp_ms value of the given value.

##### Syntax

duckdb_timestamp_ms duckdb_get_timestamp_ms(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a TIMESTAMP_MS

##### Return Value

A duckdb_timestamp_ms, or MinValue if the value cannot be converted

#### `duckdb_get_timestamp_ns`

Returns the duckdb_timestamp_ns value of the given value.

##### Syntax

duckdb_timestamp_ns duckdb_get_timestamp_ns(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a TIMESTAMP_NS

##### Return Value

A duckdb_timestamp_ns, or MinValue if the value cannot be converted

#### `duckdb_get_interval`

Returns the interval value of the given value.

##### Syntax

duckdb_interval duckdb_get_interval(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a interval

##### Return Value

A duckdb_interval, or MinValue if the value cannot be converted

#### `duckdb_get_value_type`

Returns the type of the given value. The type is valid as long as the value is not destroyed.

The type itself must not be destroyed.

##### Syntax

duckdb_logical_type duckdb_get_value_type(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value

##### Return Value

A duckdb_logical_type.

#### `duckdb_get_blob`

Returns the blob value of the given value.

##### Syntax

duckdb_blob duckdb_get_blob(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a blob

##### Return Value

A duckdb_blob

#### `duckdb_get_bit`

Returns the duckdb_bit value of the given value.

The `data` field must be destroyed with `duckdb_free`.

##### Syntax

duckdb_bit duckdb_get_bit(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a BIT

##### Return Value

A duckdb_bit

#### `duckdb_get_uuid`

Returns a duckdb_uhugeint representing the UUID value of the given value.

##### Syntax

duckdb_uhugeint duckdb_get_uuid(

  duckdb_value val

);

##### Parameters

* `val`: A duckdb_value containing a UUID

##### Return Value

A duckdb_uhugeint representing the UUID value

#### `duckdb_get_varchar`

Obtains a string representation of the given value.

The result must be destroyed with `duckdb_free`.

##### Syntax

char *duckdb_get_varchar(

  duckdb_value value

);

##### Parameters

* `value`: The value

##### Return Value

The string value. This must be destroyed with `duckdb_free`.

#### `duckdb_create_struct_value`

Creates a struct value from a type and an array of values. Must be destroyed with `duckdb_destroy_value`.

##### Syntax

duckdb_value duckdb_create_struct_value(

  duckdb_logical_type type,

  duckdb_value *values

);

##### Parameters

* `type`: The type of the struct

* `values`: The values for the struct fields

##### Return Value

The struct value, or nullptr, if any child type is `DUCKDB_TYPE_ANY` or `DUCKDB_TYPE_INVALID`.

#### `duckdb_create_list_value`

Creates a list value from a child (element) type and an array of values of length `value_count`.

Must be destroyed with `duckdb_destroy_value`.

##### Syntax

duckdb_value duckdb_create_list_value(

  duckdb_logical_type type,

  duckdb_value *values,

  idx_t value_count

);

##### Parameters

* `type`: The type of the list

* `values`: The values for the list

* `value_count`: The number of values in the list

##### Return Value

The list value, or nullptr, if the child type is `DUCKDB_TYPE_ANY` or `DUCKDB_TYPE_INVALID`.

#### `duckdb_create_array_value`

Creates an array value from a child (element) type and an array of values of length `value_count`.

Must be destroyed with `duckdb_destroy_value`.

##### Syntax

duckdb_value duckdb_create_array_value(

  duckdb_logical_type type,

  duckdb_value *values,

  idx_t value_count

);

##### Parameters

* `type`: The type of the array

* `values`: The values for the array

* `value_count`: The number of values in the array

##### Return Value

The array value, or nullptr, if the child type is `DUCKDB_TYPE_ANY` or `DUCKDB_TYPE_INVALID`.

#### `duckdb_get_map_size`

Returns the number of elements in a MAP value.

##### Syntax

idx_t duckdb_get_map_size(

  duckdb_value value

);

##### Parameters

* `value`: The MAP value.

##### Return Value

The number of elements in the map.

#### `duckdb_get_map_key`

Returns the MAP key at index as a duckdb_value.

##### Syntax

duckdb_value duckdb_get_map_key(

  duckdb_value value,

  idx_t index

);

##### Parameters

* `value`: The MAP value.

* `index`: The index of the key.

##### Return Value

The key as a duckdb_value.

#### `duckdb_get_map_value`

Returns the MAP value at index as a duckdb_value.

##### Syntax

duckdb_value duckdb_get_map_value(

  duckdb_value value,

  idx_t index

);

##### Parameters

* `value`: The MAP value.

* `index`: The index of the value.

##### Return Value

The value as a duckdb_value.

#### `duckdb_is_null_value`

Returns whether the value's type is SQLNULL or not.

##### Syntax

bool duckdb_is_null_value(

  duckdb_value value

);

##### Parameters

* `value`: The value to check.

##### Return Value

True, if the value's type is SQLNULL, otherwise false.

#### `duckdb_create_null_value`

Creates a value of type SQLNULL.

##### Return Value

The duckdb_value representing SQLNULL. This must be destroyed with `duckdb_destroy_value`.

##### Syntax

duckdb_value duckdb_create_null_value(

  

);

#### `duckdb_get_list_size`

Returns the number of elements in a LIST value.

##### Syntax

idx_t duckdb_get_list_size(

  duckdb_value value

);

##### Parameters

* `value`: The LIST value.

##### Return Value

The number of elements in the list.

#### `duckdb_get_list_child`

Returns the LIST child at index as a duckdb_value.

##### Syntax

duckdb_value duckdb_get_list_child(

  duckdb_value value,

  idx_t index

);

##### Parameters

* `value`: The LIST value.

* `index`: The index of the child.

##### Return Value

The child as a duckdb_value.

#### `duckdb_create_enum_value`

Creates an enum value from a type and a value. Must be destroyed with `duckdb_destroy_value`.

##### Syntax

duckdb_value duckdb_create_enum_value(

  duckdb_logical_type type,

  uint64_t value

);

##### Parameters

* `type`: The type of the enum

* `value`: The value for the enum

##### Return Value

The enum value, or nullptr.

#### `duckdb_get_enum_value`

Returns the enum value of the given value.

##### Syntax

uint64_t duckdb_get_enum_value(

  duckdb_value value

);

##### Parameters

* `value`: A duckdb_value containing an enum

##### Return Value

A uint64_t, or MinValue if the value cannot be converted

#### `duckdb_get_struct_child`

Returns the STRUCT child at index as a duckdb_value.

##### Syntax

duckdb_value duckdb_get_struct_child(

  duckdb_value value,

  idx_t index

);

##### Parameters

* `value`: The STRUCT value.

* `index`: The index of the child.

##### Return Value

The child as a duckdb_value.

#### `duckdb_create_logical_type`

Creates a `duckdb_logical_type` from a primitive type.

The resulting logical type must be destroyed with `duckdb_destroy_logical_type`.

Returns an invalid logical type, if type is: `DUCKDB_TYPE_INVALID`, `DUCKDB_TYPE_DECIMAL`, `DUCKDB_TYPE_ENUM`,

`DUCKDB_TYPE_LIST`, `DUCKDB_TYPE_STRUCT`, `DUCKDB_TYPE_MAP`, `DUCKDB_TYPE_ARRAY`, or `DUCKDB_TYPE_UNION`.

##### Syntax

duckdb_logical_type duckdb_create_logical_type(

  duckdb_type type

);

##### Parameters

* `type`: The primitive type to create.

##### Return Value

The logical type.

#### `duckdb_logical_type_get_alias`

Returns the alias of a duckdb_logical_type, if set, else `nullptr`.

The result must be destroyed with `duckdb_free`.

##### Syntax

char *duckdb_logical_type_get_alias(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type

##### Return Value

The alias or `nullptr`

#### `duckdb_logical_type_set_alias`

Sets the alias of a duckdb_logical_type.

##### Syntax

void duckdb_logical_type_set_alias(

  duckdb_logical_type type,

  const char *alias

);

##### Parameters

* `type`: The logical type

* `alias`: The alias to set

#### `duckdb_create_list_type`

Creates a LIST type from its child type.

The return type must be destroyed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_create_list_type(

  duckdb_logical_type type

);

##### Parameters

* `type`: The child type of the list

##### Return Value

The logical type.

#### `duckdb_create_array_type`

Creates an ARRAY type from its child type.

The return type must be destroyed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_create_array_type(

  duckdb_logical_type type,

  idx_t array_size

);

##### Parameters

* `type`: The child type of the array.

* `array_size`: The number of elements in the array.

##### Return Value

The logical type.

#### `duckdb_create_map_type`

Creates a MAP type from its key type and value type.

The return type must be destroyed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_create_map_type(

  duckdb_logical_type key_type,

  duckdb_logical_type value_type

);

##### Parameters

* `key_type`: The map's key type.

* `value_type`: The map's value type.

##### Return Value

The logical type.

#### `duckdb_create_union_type`

Creates a UNION type from the passed arrays.

The return type must be destroyed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_create_union_type(

  duckdb_logical_type *member_types,

  const char **member_names,

  idx_t member_count

);

##### Parameters

* `member_types`: The array of union member types.

* `member_names`: The union member names.

* `member_count`: The number of union members.

##### Return Value

The logical type.

#### `duckdb_create_struct_type`

Creates a STRUCT type based on the member types and names.

The resulting type must be destroyed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_create_struct_type(

  duckdb_logical_type *member_types,

  const char **member_names,

  idx_t member_count

);

##### Parameters

* `member_types`: The array of types of the struct members.

* `member_names`: The array of names of the struct members.

* `member_count`: The number of members of the struct.

##### Return Value

The logical type.

#### `duckdb_create_enum_type`

Creates an ENUM type from the passed member name array.

The resulting type should be destroyed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_create_enum_type(

  const char **member_names,

  idx_t member_count

);

##### Parameters

* `member_names`: The array of names that the enum should consist of.

* `member_count`: The number of elements that were specified in the array.

##### Return Value

The logical type.

#### `duckdb_create_decimal_type`

Creates a DECIMAL type with the specified width and scale.

The resulting type should be destroyed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_create_decimal_type(

  uint8_t width,

  uint8_t scale

);

##### Parameters

* `width`: The width of the decimal type

* `scale`: The scale of the decimal type

##### Return Value

The logical type.

#### `duckdb_get_type_id`

Retrieves the enum `duckdb_type` of a `duckdb_logical_type`.

##### Syntax

duckdb_type duckdb_get_type_id(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type.

##### Return Value

The `duckdb_type` id.

#### `duckdb_decimal_width`

Retrieves the width of a decimal type.

##### Syntax

uint8_t duckdb_decimal_width(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type object

##### Return Value

The width of the decimal type

#### `duckdb_decimal_scale`

Retrieves the scale of a decimal type.

##### Syntax

uint8_t duckdb_decimal_scale(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type object

##### Return Value

The scale of the decimal type

#### `duckdb_decimal_internal_type`

Retrieves the internal storage type of a decimal type.

##### Syntax

duckdb_type duckdb_decimal_internal_type(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type object

##### Return Value

The internal type of the decimal type

#### `duckdb_enum_internal_type`

Retrieves the internal storage type of an enum type.

##### Syntax

duckdb_type duckdb_enum_internal_type(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type object

##### Return Value

The internal type of the enum type

#### `duckdb_enum_dictionary_size`

Retrieves the dictionary size of the enum type.

##### Syntax

uint32_t duckdb_enum_dictionary_size(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type object

##### Return Value

The dictionary size of the enum type

#### `duckdb_enum_dictionary_value`

Retrieves the dictionary value at the specified position from the enum.

The result must be freed with `duckdb_free`.

##### Syntax

char *duckdb_enum_dictionary_value(

  duckdb_logical_type type,

  idx_t index

);

##### Parameters

* `type`: The logical type object

* `index`: The index in the dictionary

##### Return Value

The string value of the enum type. Must be freed with `duckdb_free`.

#### `duckdb_list_type_child_type`

Retrieves the child type of the given LIST type. Also accepts MAP types.

The result must be freed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_list_type_child_type(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type, either LIST or MAP.

##### Return Value

The child type of the LIST or MAP type.

#### `duckdb_array_type_child_type`

Retrieves the child type of the given ARRAY type.

The result must be freed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_array_type_child_type(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type. Must be ARRAY.

##### Return Value

The child type of the ARRAY type.

#### `duckdb_array_type_array_size`

Retrieves the array size of the given array type.

##### Syntax

idx_t duckdb_array_type_array_size(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type object

##### Return Value

The fixed number of elements the values of this array type can store.

#### `duckdb_map_type_key_type`

Retrieves the key type of the given map type.

The result must be freed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_map_type_key_type(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type object

##### Return Value

The key type of the map type. Must be destroyed with `duckdb_destroy_logical_type`.

#### `duckdb_map_type_value_type`

Retrieves the value type of the given map type.

The result must be freed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_map_type_value_type(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type object

##### Return Value

The value type of the map type. Must be destroyed with `duckdb_destroy_logical_type`.

#### `duckdb_struct_type_child_count`

Returns the number of children of a struct type.

##### Syntax

idx_t duckdb_struct_type_child_count(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type object

##### Return Value

The number of children of a struct type.

#### `duckdb_struct_type_child_name`

Retrieves the name of the struct child.

The result must be freed with `duckdb_free`.

##### Syntax

char *duckdb_struct_type_child_name(

  duckdb_logical_type type,

  idx_t index

);

##### Parameters

* `type`: The logical type object

* `index`: The child index

##### Return Value

The name of the struct type. Must be freed with `duckdb_free`.

#### `duckdb_struct_type_child_type`

Retrieves the child type of the given struct type at the specified index.

The result must be freed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_struct_type_child_type(

  duckdb_logical_type type,

  idx_t index

);

##### Parameters

* `type`: The logical type object

* `index`: The child index

##### Return Value

The child type of the struct type. Must be destroyed with `duckdb_destroy_logical_type`.

#### `duckdb_union_type_member_count`

Returns the number of members that the union type has.

##### Syntax

idx_t duckdb_union_type_member_count(

  duckdb_logical_type type

);

##### Parameters

* `type`: The logical type (union) object

##### Return Value

The number of members of a union type.

#### `duckdb_union_type_member_name`

Retrieves the name of the union member.

The result must be freed with `duckdb_free`.

##### Syntax

char *duckdb_union_type_member_name(

  duckdb_logical_type type,

  idx_t index

);

##### Parameters

* `type`: The logical type object

* `index`: The child index

##### Return Value

The name of the union member. Must be freed with `duckdb_free`.

#### `duckdb_union_type_member_type`

Retrieves the child type of the given union member at the specified index.

The result must be freed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_union_type_member_type(

  duckdb_logical_type type,

  idx_t index

);

##### Parameters

* `type`: The logical type object

* `index`: The child index

##### Return Value

The child type of the union member. Must be destroyed with `duckdb_destroy_logical_type`.

#### `duckdb_destroy_logical_type`

Destroys the logical type and de-allocates all memory allocated for that type.

##### Syntax

void duckdb_destroy_logical_type(

  duckdb_logical_type *type

);

##### Parameters

* `type`: The logical type to destroy.

#### `duckdb_register_logical_type`

Registers a custom type within the given connection.

The type must have an alias

##### Syntax

duckdb_state duckdb_register_logical_type(

  duckdb_connection con,

  duckdb_logical_type type,

  duckdb_create_type_info info

);

##### Parameters

* `con`: The connection to use

* `type`: The custom type to register

##### Return Value

Whether or not the registration was successful.

#### `duckdb_create_data_chunk`

Creates an empty data chunk with the specified column types.

The result must be destroyed with `duckdb_destroy_data_chunk`.

##### Syntax

duckdb_data_chunk duckdb_create_data_chunk(

  duckdb_logical_type *types,

  idx_t column_count

);

##### Parameters

* `types`: An array of column types. Column types can not contain ANY and INVALID types.

* `column_count`: The number of columns.

##### Return Value

The data chunk.

#### `duckdb_destroy_data_chunk`

Destroys the data chunk and de-allocates all memory allocated for that chunk.

##### Syntax

void duckdb_destroy_data_chunk(

  duckdb_data_chunk *chunk

);

##### Parameters

* `chunk`: The data chunk to destroy.

#### `duckdb_data_chunk_reset`

Resets a data chunk, clearing the validity masks and setting the cardinality of the data chunk to 0.

After calling this method, you must call `duckdb_vector_get_validity` and `duckdb_vector_get_data` to obtain current

data and validity pointers

##### Syntax

void duckdb_data_chunk_reset(

  duckdb_data_chunk chunk

);

##### Parameters

* `chunk`: The data chunk to reset.

#### `duckdb_data_chunk_get_column_count`

Retrieves the number of columns in a data chunk.

##### Syntax

idx_t duckdb_data_chunk_get_column_count(

  duckdb_data_chunk chunk

);

##### Parameters

* `chunk`: The data chunk to get the data from

##### Return Value

The number of columns in the data chunk

#### `duckdb_data_chunk_get_vector`

Retrieves the vector at the specified column index in the data chunk.

The pointer to the vector is valid for as long as the chunk is alive.

It does NOT need to be destroyed.

##### Syntax

duckdb_vector duckdb_data_chunk_get_vector(

  duckdb_data_chunk chunk,

  idx_t col_idx

);

##### Parameters

* `chunk`: The data chunk to get the data from

##### Return Value

The vector

#### `duckdb_data_chunk_get_size`

Retrieves the current number of tuples in a data chunk.

##### Syntax

idx_t duckdb_data_chunk_get_size(

  duckdb_data_chunk chunk

);

##### Parameters

* `chunk`: The data chunk to get the data from

##### Return Value

The number of tuples in the data chunk

#### `duckdb_data_chunk_set_size`

Sets the current number of tuples in a data chunk.

##### Syntax

void duckdb_data_chunk_set_size(

  duckdb_data_chunk chunk,

  idx_t size

);

##### Parameters

* `chunk`: The data chunk to set the size in

* `size`: The number of tuples in the data chunk

#### `duckdb_vector_get_column_type`

Retrieves the column type of the specified vector.

The result must be destroyed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_vector_get_column_type(

  duckdb_vector vector

);

##### Parameters

* `vector`: The vector get the data from

##### Return Value

The type of the vector

#### `duckdb_vector_get_data`

Retrieves the data pointer of the vector.

The data pointer can be used to read or write values from the vector.

How to read or write values depends on the type of the vector.

##### Syntax

void *duckdb_vector_get_data(

  duckdb_vector vector

);

##### Parameters

* `vector`: The vector to get the data from

##### Return Value

The data pointer

#### `duckdb_vector_get_validity`

Retrieves the validity mask pointer of the specified vector.

If all values are valid, this function MIGHT return NULL!

The validity mask is a bitset that signifies null-ness within the data chunk.

It is a series of uint64_t values, where each uint64_t value contains validity for 64 tuples.

The bit is set to 1 if the value is valid (i.e., not NULL) or 0 if the value is invalid (i.e., NULL).

Validity of a specific value can be obtained like this:

idx_t entry_idx = row_idx / 64;

idx_t idx_in_entry = row_idx % 64;

bool is_valid = validity_mask[entry_idx] & (1 << idx_in_entry);

Alternatively, the (slower) duckdb_validity_row_is_valid function can be used.

##### Syntax

uint64_t *duckdb_vector_get_validity(

  duckdb_vector vector

);

##### Parameters

* `vector`: The vector to get the data from

##### Return Value

The pointer to the validity mask, or NULL if no validity mask is present

#### `duckdb_vector_ensure_validity_writable`

Ensures the validity mask is writable by allocating it.

After this function is called, `duckdb_vector_get_validity` will ALWAYS return non-NULL.

This allows NULL values to be written to the vector, regardless of whether a validity mask was present before.

##### Syntax

void duckdb_vector_ensure_validity_writable(

  duckdb_vector vector

);

##### Parameters

* `vector`: The vector to alter

#### `duckdb_vector_assign_string_element`

Assigns a string element in the vector at the specified location.

##### Syntax

void duckdb_vector_assign_string_element(

  duckdb_vector vector,

  idx_t index,

  const char *str

);

##### Parameters

* `vector`: The vector to alter

* `index`: The row position in the vector to assign the string to

* `str`: The null-terminated string

#### `duckdb_vector_assign_string_element_len`

Assigns a string element in the vector at the specified location. You may also use this function to assign BLOBs.

##### Syntax

void duckdb_vector_assign_string_element_len(

  duckdb_vector vector,

  idx_t index,

  const char *str,

  idx_t str_len

);

##### Parameters

* `vector`: The vector to alter

* `index`: The row position in the vector to assign the string to

* `str`: The string

* `str_len`: The length of the string (in bytes)

#### `duckdb_list_vector_get_child`

Retrieves the child vector of a list vector.

The resulting vector is valid as long as the parent vector is valid.

##### Syntax

duckdb_vector duckdb_list_vector_get_child(

  duckdb_vector vector

);

##### Parameters

* `vector`: The vector

##### Return Value

The child vector

#### `duckdb_list_vector_get_size`

Returns the size of the child vector of the list.

##### Syntax

idx_t duckdb_list_vector_get_size(

  duckdb_vector vector

);

##### Parameters

* `vector`: The vector

##### Return Value

The size of the child list

#### `duckdb_list_vector_set_size`

Sets the total size of the underlying child-vector of a list vector.

##### Syntax

duckdb_state duckdb_list_vector_set_size(

  duckdb_vector vector,

  idx_t size

);

##### Parameters

* `vector`: The list vector.

* `size`: The size of the child list.

##### Return Value

The duckdb state. Returns DuckDBError if the vector is nullptr.

#### `duckdb_list_vector_reserve`

Sets the total capacity of the underlying child-vector of a list.

After calling this method, you must call `duckdb_vector_get_validity` and `duckdb_vector_get_data` to obtain current

data and validity pointers

##### Syntax

duckdb_state duckdb_list_vector_reserve(

  duckdb_vector vector,

  idx_t required_capacity

);

##### Parameters

* `vector`: The list vector.

* `required_capacity`: the total capacity to reserve.

##### Return Value

The duckdb state. Returns DuckDBError if the vector is nullptr.

#### `duckdb_struct_vector_get_child`

Retrieves the child vector of a struct vector.

The resulting vector is valid as long as the parent vector is valid.

##### Syntax

duckdb_vector duckdb_struct_vector_get_child(

  duckdb_vector vector,

  idx_t index

);

##### Parameters

* `vector`: The vector

* `index`: The child index

##### Return Value

The child vector

#### `duckdb_array_vector_get_child`

Retrieves the child vector of a array vector.

The resulting vector is valid as long as the parent vector is valid.

The resulting vector has the size of the parent vector multiplied by the array size.

##### Syntax

duckdb_vector duckdb_array_vector_get_child(

  duckdb_vector vector

);

##### Parameters

* `vector`: The vector

##### Return Value

The child vector

#### `duckdb_validity_row_is_valid`

Returns whether or not a row is valid (i.e., not NULL) in the given validity mask.

##### Syntax

bool duckdb_validity_row_is_valid(

  uint64_t *validity,

  idx_t row

);

##### Parameters

* `validity`: The validity mask, as obtained through `duckdb_vector_get_validity`

* `row`: The row index

##### Return Value

true if the row is valid, false otherwise

#### `duckdb_validity_set_row_validity`

In a validity mask, sets a specific row to either valid or invalid.

Note that `duckdb_vector_ensure_validity_writable` should be called before calling `duckdb_vector_get_validity`,

to ensure that there is a validity mask to write to.

##### Syntax

void duckdb_validity_set_row_validity(

  uint64_t *validity,

  idx_t row,

  bool valid

);

##### Parameters

* `validity`: The validity mask, as obtained through `duckdb_vector_get_validity`.

* `row`: The row index

* `valid`: Whether or not to set the row to valid, or invalid

#### `duckdb_validity_set_row_invalid`

In a validity mask, sets a specific row to invalid.

Equivalent to `duckdb_validity_set_row_validity` with valid set to false.

##### Syntax

void duckdb_validity_set_row_invalid(

  uint64_t *validity,

  idx_t row

);

##### Parameters

* `validity`: The validity mask

* `row`: The row index

#### `duckdb_validity_set_row_valid`

In a validity mask, sets a specific row to valid.

Equivalent to `duckdb_validity_set_row_validity` with valid set to true.

##### Syntax

void duckdb_validity_set_row_valid(

  uint64_t *validity,

  idx_t row

);

##### Parameters

* `validity`: The validity mask

* `row`: The row index

#### `duckdb_create_scalar_function`

Creates a new empty scalar function.

The return value should be destroyed with `duckdb_destroy_scalar_function`.

##### Return Value

The scalar function object.

##### Syntax

duckdb_scalar_function duckdb_create_scalar_function(

  

);

#### `duckdb_destroy_scalar_function`

Destroys the given scalar function object.

##### Syntax

void duckdb_destroy_scalar_function(

  duckdb_scalar_function *scalar_function

);

##### Parameters

* `scalar_function`: The scalar function to destroy

#### `duckdb_scalar_function_set_name`

Sets the name of the given scalar function.

##### Syntax

void duckdb_scalar_function_set_name(

  duckdb_scalar_function scalar_function,

  const char *name

);

##### Parameters

* `scalar_function`: The scalar function

* `name`: The name of the scalar function

#### `duckdb_scalar_function_set_varargs`

Sets the parameters of the given scalar function to varargs. Does not require adding parameters with

duckdb_scalar_function_add_parameter.

##### Syntax

void duckdb_scalar_function_set_varargs(

  duckdb_scalar_function scalar_function,

  duckdb_logical_type type

);

##### Parameters

* `scalar_function`: The scalar function.

* `type`: The type of the arguments.

##### Return Value

The parameter type. Cannot contain INVALID.

#### `duckdb_scalar_function_set_special_handling`

Sets the parameters of the given scalar function to varargs. Does not require adding parameters with

duckdb_scalar_function_add_parameter.

##### Syntax

void duckdb_scalar_function_set_special_handling(

  duckdb_scalar_function scalar_function

);

##### Parameters

* `scalar_function`: The scalar function.

#### `duckdb_scalar_function_set_volatile`

Sets the Function Stability of the scalar function to VOLATILE, indicating the function should be re-run for every row.

This limits optimization that can be performed for the function.

##### Syntax

void duckdb_scalar_function_set_volatile(

  duckdb_scalar_function scalar_function

);

##### Parameters

* `scalar_function`: The scalar function.

#### `duckdb_scalar_function_add_parameter`

Adds a parameter to the scalar function.

##### Syntax

void duckdb_scalar_function_add_parameter(

  duckdb_scalar_function scalar_function,

  duckdb_logical_type type

);

##### Parameters

* `scalar_function`: The scalar function.

* `type`: The parameter type. Cannot contain INVALID.

#### `duckdb_scalar_function_set_return_type`

Sets the return type of the scalar function.

##### Syntax

void duckdb_scalar_function_set_return_type(

  duckdb_scalar_function scalar_function,

  duckdb_logical_type type

);

##### Parameters

* `scalar_function`: The scalar function

* `type`: Cannot contain INVALID or ANY.

#### `duckdb_scalar_function_set_extra_info`

Assigns extra information to the scalar function that can be fetched during binding, etc.

##### Syntax

void duckdb_scalar_function_set_extra_info(

  duckdb_scalar_function scalar_function,

  void *extra_info,

  duckdb_delete_callback_t destroy

);

##### Parameters

* `scalar_function`: The scalar function

* `extra_info`: The extra information

* `destroy`: The callback that will be called to destroy the bind data (if any)

#### `duckdb_scalar_function_set_function`

Sets the main function of the scalar function.

##### Syntax

void duckdb_scalar_function_set_function(

  duckdb_scalar_function scalar_function,

  duckdb_scalar_function_t function

);

##### Parameters

* `scalar_function`: The scalar function

* `function`: The function

#### `duckdb_register_scalar_function`

Register the scalar function object within the given connection.

The function requires at least a name, a function and a return type.

If the function is incomplete or a function with this name already exists DuckDBError is returned.

##### Syntax

duckdb_state duckdb_register_scalar_function(

  duckdb_connection con,

  duckdb_scalar_function scalar_function

);

##### Parameters

* `con`: The connection to register it in.

* `scalar_function`: The function pointer

##### Return Value

Whether or not the registration was successful.

#### `duckdb_scalar_function_get_extra_info`

Retrieves the extra info of the function as set in `duckdb_scalar_function_set_extra_info`.

##### Syntax

void *duckdb_scalar_function_get_extra_info(

  duckdb_function_info info

);

##### Parameters

* `info`: The info object.

##### Return Value

The extra info.

#### `duckdb_scalar_function_set_error`

Report that an error has occurred while executing the scalar function.

##### Syntax

void duckdb_scalar_function_set_error(

  duckdb_function_info info,

  const char *error

);

##### Parameters

* `info`: The info object.

* `error`: The error message

#### `duckdb_create_scalar_function_set`

Creates a new empty scalar function set.

The return value should be destroyed with `duckdb_destroy_scalar_function_set`.

##### Return Value

The scalar function set object.

##### Syntax

duckdb_scalar_function_set duckdb_create_scalar_function_set(

  const char *name

);

#### `duckdb_destroy_scalar_function_set`

Destroys the given scalar function set object.

##### Syntax

void duckdb_destroy_scalar_function_set(

  duckdb_scalar_function_set *scalar_function_set

);

#### `duckdb_add_scalar_function_to_set`

Adds the scalar function as a new overload to the scalar function set.

Returns DuckDBError if the function could not be added, for example if the overload already exists.

##### Syntax

duckdb_state duckdb_add_scalar_function_to_set(

  duckdb_scalar_function_set set,

  duckdb_scalar_function function

);

##### Parameters

* `set`: The scalar function set

* `function`: The function to add

#### `duckdb_register_scalar_function_set`

Register the scalar function set within the given connection.

The set requires at least a single valid overload.

If the set is incomplete or a function with this name already exists DuckDBError is returned.

##### Syntax

duckdb_state duckdb_register_scalar_function_set(

  duckdb_connection con,

  duckdb_scalar_function_set set

);

##### Parameters

* `con`: The connection to register it in.

* `set`: The function set to register

##### Return Value

Whether or not the registration was successful.

#### `duckdb_create_aggregate_function`

Creates a new empty aggregate function.

The return value should be destroyed with `duckdb_destroy_aggregate_function`.

##### Return Value

The aggregate function object.

##### Syntax

duckdb_aggregate_function duckdb_create_aggregate_function(

  

);

#### `duckdb_destroy_aggregate_function`

Destroys the given aggregate function object.

##### Syntax

void duckdb_destroy_aggregate_function(

  duckdb_aggregate_function *aggregate_function

);

#### `duckdb_aggregate_function_set_name`

Sets the name of the given aggregate function.

##### Syntax

void duckdb_aggregate_function_set_name(

  duckdb_aggregate_function aggregate_function,

  const char *name

);

##### Parameters

* `aggregate_function`: The aggregate function

* `name`: The name of the aggregate function

#### `duckdb_aggregate_function_add_parameter`

Adds a parameter to the aggregate function.

##### Syntax

void duckdb_aggregate_function_add_parameter(

  duckdb_aggregate_function aggregate_function,

  duckdb_logical_type type

);

##### Parameters

* `aggregate_function`: The aggregate function.

* `type`: The parameter type. Cannot contain INVALID.

#### `duckdb_aggregate_function_set_return_type`

Sets the return type of the aggregate function.

##### Syntax

void duckdb_aggregate_function_set_return_type(

  duckdb_aggregate_function aggregate_function,

  duckdb_logical_type type

);

##### Parameters

* `aggregate_function`: The aggregate function.

* `type`: The return type. Cannot contain INVALID or ANY.

#### `duckdb_aggregate_function_set_functions`

Sets the main functions of the aggregate function.

##### Syntax

void duckdb_aggregate_function_set_functions(

  duckdb_aggregate_function aggregate_function,

  duckdb_aggregate_state_size state_size,

  duckdb_aggregate_init_t state_init,

  duckdb_aggregate_update_t update,

  duckdb_aggregate_combine_t combine,

  duckdb_aggregate_finalize_t finalize

);

##### Parameters

* `aggregate_function`: The aggregate function

* `state_size`: state size

* `state_init`: state init function

* `update`: update states

* `combine`: combine states

* `finalize`: finalize states

#### `duckdb_aggregate_function_set_destructor`

Sets the state destructor callback of the aggregate function (optional)

##### Syntax

void duckdb_aggregate_function_set_destructor(

  duckdb_aggregate_function aggregate_function,

  duckdb_aggregate_destroy_t destroy

);

##### Parameters

* `aggregate_function`: The aggregate function

* `destroy`: state destroy callback

#### `duckdb_register_aggregate_function`

Register the aggregate function object within the given connection.

The function requires at least a name, functions and a return type.

If the function is incomplete or a function with this name already exists DuckDBError is returned.

##### Syntax

duckdb_state duckdb_register_aggregate_function(

  duckdb_connection con,

  duckdb_aggregate_function aggregate_function

);

##### Parameters

* `con`: The connection to register it in.

##### Return Value

Whether or not the registration was successful.

#### `duckdb_aggregate_function_set_special_handling`

Sets the NULL handling of the aggregate function to SPECIAL_HANDLING.

##### Syntax

void duckdb_aggregate_function_set_special_handling(

  duckdb_aggregate_function aggregate_function

);

##### Parameters

* `aggregate_function`: The aggregate function

#### `duckdb_aggregate_function_set_extra_info`

Assigns extra information to the scalar function that can be fetched during binding, etc.

##### Syntax

void duckdb_aggregate_function_set_extra_info(

  duckdb_aggregate_function aggregate_function,

  void *extra_info,

  duckdb_delete_callback_t destroy

);

##### Parameters

* `aggregate_function`: The aggregate function

* `extra_info`: The extra information

* `destroy`: The callback that will be called to destroy the bind data (if any)

#### `duckdb_aggregate_function_get_extra_info`

Retrieves the extra info of the function as set in `duckdb_aggregate_function_set_extra_info`.

##### Syntax

void *duckdb_aggregate_function_get_extra_info(

  duckdb_function_info info

);

##### Parameters

* `info`: The info object

##### Return Value

The extra info

#### `duckdb_aggregate_function_set_error`

Report that an error has occurred while executing the aggregate function.

##### Syntax

void duckdb_aggregate_function_set_error(

  duckdb_function_info info,

  const char *error

);

##### Parameters

* `info`: The info object

* `error`: The error message

#### `duckdb_create_aggregate_function_set`

Creates a new empty aggregate function set.

The return value should be destroyed with `duckdb_destroy_aggregate_function_set`.

##### Return Value

The aggregate function set object.

##### Syntax

duckdb_aggregate_function_set duckdb_create_aggregate_function_set(

  const char *name

);

#### `duckdb_destroy_aggregate_function_set`

Destroys the given aggregate function set object.

##### Syntax

void duckdb_destroy_aggregate_function_set(

  duckdb_aggregate_function_set *aggregate_function_set

);

#### `duckdb_add_aggregate_function_to_set`

Adds the aggregate function as a new overload to the aggregate function set.

Returns DuckDBError if the function could not be added, for example if the overload already exists.

##### Syntax

duckdb_state duckdb_add_aggregate_function_to_set(

  duckdb_aggregate_function_set set,

  duckdb_aggregate_function function

);

##### Parameters

* `set`: The aggregate function set

* `function`: The function to add

#### `duckdb_register_aggregate_function_set`

Register the aggregate function set within the given connection.

The set requires at least a single valid overload.

If the set is incomplete or a function with this name already exists DuckDBError is returned.

##### Syntax

duckdb_state duckdb_register_aggregate_function_set(

  duckdb_connection con,

  duckdb_aggregate_function_set set

);

##### Parameters

* `con`: The connection to register it in.

* `set`: The function set to register

##### Return Value

Whether or not the registration was successful.

#### `duckdb_create_table_function`

Creates a new empty table function.

The return value should be destroyed with `duckdb_destroy_table_function`.

##### Return Value

The table function object.

##### Syntax

duckdb_table_function duckdb_create_table_function(

  

);

#### `duckdb_destroy_table_function`

Destroys the given table function object.

##### Syntax

void duckdb_destroy_table_function(

  duckdb_table_function *table_function

);

##### Parameters

* `table_function`: The table function to destroy

#### `duckdb_table_function_set_name`

Sets the name of the given table function.

##### Syntax

void duckdb_table_function_set_name(

  duckdb_table_function table_function,

  const char *name

);

##### Parameters

* `table_function`: The table function

* `name`: The name of the table function

#### `duckdb_table_function_add_parameter`

Adds a parameter to the table function.

##### Syntax

void duckdb_table_function_add_parameter(

  duckdb_table_function table_function,

  duckdb_logical_type type

);

##### Parameters

* `table_function`: The table function.

* `type`: The parameter type. Cannot contain INVALID.

#### `duckdb_table_function_add_named_parameter`

Adds a named parameter to the table function.

##### Syntax

void duckdb_table_function_add_named_parameter(

  duckdb_table_function table_function,

  const char *name,

  duckdb_logical_type type

);

##### Parameters

* `table_function`: The table function.

* `name`: The parameter name.

* `type`: The parameter type. Cannot contain INVALID.

#### `duckdb_table_function_set_extra_info`

Assigns extra information to the table function that can be fetched during binding, etc.

##### Syntax

void duckdb_table_function_set_extra_info(

  duckdb_table_function table_function,

  void *extra_info,

  duckdb_delete_callback_t destroy

);

##### Parameters

* `table_function`: The table function

* `extra_info`: The extra information

* `destroy`: The callback that will be called to destroy the bind data (if any)

#### `duckdb_table_function_set_bind`

Sets the bind function of the table function.

##### Syntax

void duckdb_table_function_set_bind(

  duckdb_table_function table_function,

  duckdb_table_function_bind_t bind

);

##### Parameters

* `table_function`: The table function

* `bind`: The bind function

#### `duckdb_table_function_set_init`

Sets the init function of the table function.

##### Syntax

void duckdb_table_function_set_init(

  duckdb_table_function table_function,

  duckdb_table_function_init_t init

);

##### Parameters

* `table_function`: The table function

* `init`: The init function

#### `duckdb_table_function_set_local_init`

Sets the thread-local init function of the table function.

##### Syntax

void duckdb_table_function_set_local_init(

  duckdb_table_function table_function,

  duckdb_table_function_init_t init

);

##### Parameters

* `table_function`: The table function

* `init`: The init function

#### `duckdb_table_function_set_function`

Sets the main function of the table function.

##### Syntax

void duckdb_table_function_set_function(

  duckdb_table_function table_function,

  duckdb_table_function_t function

);

##### Parameters

* `table_function`: The table function

* `function`: The function

#### `duckdb_table_function_supports_projection_pushdown`

Sets whether or not the given table function supports projection pushdown.

If this is set to true, the system will provide a list of all required columns in the `init` stage through

the `duckdb_init_get_column_count` and `duckdb_init_get_column_index` functions.

If this is set to false (the default), the system will expect all columns to be projected.

##### Syntax

void duckdb_table_function_supports_projection_pushdown(

  duckdb_table_function table_function,

  bool pushdown

);

##### Parameters

* `table_function`: The table function

* `pushdown`: True if the table function supports projection pushdown, false otherwise.

#### `duckdb_register_table_function`

Register the table function object within the given connection.

The function requires at least a name, a bind function, an init function and a main function.

If the function is incomplete or a function with this name already exists DuckDBError is returned.

##### Syntax

duckdb_state duckdb_register_table_function(

  duckdb_connection con,

  duckdb_table_function function

);

##### Parameters

* `con`: The connection to register it in.

* `function`: The function pointer

##### Return Value

Whether or not the registration was successful.

#### `duckdb_bind_get_extra_info`

Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`.

##### Syntax

void *duckdb_bind_get_extra_info(

  duckdb_bind_info info

);

##### Parameters

* `info`: The info object

##### Return Value

The extra info

#### `duckdb_bind_add_result_column`

Adds a result column to the output of the table function.

##### Syntax

void duckdb_bind_add_result_column(

  duckdb_bind_info info,

  const char *name,

  duckdb_logical_type type

);

##### Parameters

* `info`: The table function's bind info.

* `name`: The column name.

* `type`: The logical column type.

#### `duckdb_bind_get_parameter_count`

Retrieves the number of regular (non-named) parameters to the function.

##### Syntax

idx_t duckdb_bind_get_parameter_count(

  duckdb_bind_info info

);

##### Parameters

* `info`: The info object

##### Return Value

The number of parameters

#### `duckdb_bind_get_parameter`

Retrieves the parameter at the given index.

The result must be destroyed with `duckdb_destroy_value`.

##### Syntax

duckdb_value duckdb_bind_get_parameter(

  duckdb_bind_info info,

  idx_t index

);

##### Parameters

* `info`: The info object

* `index`: The index of the parameter to get

##### Return Value

The value of the parameter. Must be destroyed with `duckdb_destroy_value`.

#### `duckdb_bind_get_named_parameter`

Retrieves a named parameter with the given name.

The result must be destroyed with `duckdb_destroy_value`.

##### Syntax

duckdb_value duckdb_bind_get_named_parameter(

  duckdb_bind_info info,

  const char *name

);

##### Parameters

* `info`: The info object

* `name`: The name of the parameter

##### Return Value

The value of the parameter. Must be destroyed with `duckdb_destroy_value`.

#### `duckdb_bind_set_bind_data`

Sets the user-provided bind data in the bind object. This object can be retrieved again during execution.

##### Syntax

void duckdb_bind_set_bind_data(

  duckdb_bind_info info,

  void *bind_data,

  duckdb_delete_callback_t destroy

);

##### Parameters

* `info`: The info object

* `bind_data`: The bind data object.

* `destroy`: The callback that will be called to destroy the bind data (if any)

#### `duckdb_bind_set_cardinality`

Sets the cardinality estimate for the table function, used for optimization.

##### Syntax

void duckdb_bind_set_cardinality(

  duckdb_bind_info info,

  idx_t cardinality,

  bool is_exact

);

##### Parameters

* `info`: The bind data object.

* `is_exact`: Whether or not the cardinality estimate is exact, or an approximation

#### `duckdb_bind_set_error`

Report that an error has occurred while calling bind.

##### Syntax

void duckdb_bind_set_error(

  duckdb_bind_info info,

  const char *error

);

##### Parameters

* `info`: The info object

* `error`: The error message

#### `duckdb_init_get_extra_info`

Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`.

##### Syntax

void *duckdb_init_get_extra_info(

  duckdb_init_info info

);

##### Parameters

* `info`: The info object

##### Return Value

The extra info

#### `duckdb_init_get_bind_data`

Gets the bind data set by `duckdb_bind_set_bind_data` during the bind.

Note that the bind data should be considered as read-only.

For tracking state, use the init data instead.

##### Syntax

void *duckdb_init_get_bind_data(

  duckdb_init_info info

);

##### Parameters

* `info`: The info object

##### Return Value

The bind data object

#### `duckdb_init_set_init_data`

Sets the user-provided init data in the init object. This object can be retrieved again during execution.

##### Syntax

void duckdb_init_set_init_data(

  duckdb_init_info info,

  void *init_data,

  duckdb_delete_callback_t destroy

);

##### Parameters

* `info`: The info object

* `init_data`: The init data object.

* `destroy`: The callback that will be called to destroy the init data (if any)

#### `duckdb_init_get_column_count`

Returns the number of projected columns.

This function must be used if projection pushdown is enabled to figure out which columns to emit.

##### Syntax

idx_t duckdb_init_get_column_count(

  duckdb_init_info info

);

##### Parameters

* `info`: The info object

##### Return Value

The number of projected columns.

#### `duckdb_init_get_column_index`

Returns the column index of the projected column at the specified position.

This function must be used if projection pushdown is enabled to figure out which columns to emit.

##### Syntax

idx_t duckdb_init_get_column_index(

  duckdb_init_info info,

  idx_t column_index

);

##### Parameters

* `info`: The info object

* `column_index`: The index at which to get the projected column index, from 0..duckdb_init_get_column_count(info)

##### Return Value

The column index of the projected column.

#### `duckdb_init_set_max_threads`

Sets how many threads can process this table function in parallel (default: 1)

##### Syntax

void duckdb_init_set_max_threads(

  duckdb_init_info info,

  idx_t max_threads

);

##### Parameters

* `info`: The info object

* `max_threads`: The maximum amount of threads that can process this table function

#### `duckdb_init_set_error`

Report that an error has occurred while calling init.

##### Syntax

void duckdb_init_set_error(

  duckdb_init_info info,

  const char *error

);

##### Parameters

* `info`: The info object

* `error`: The error message

#### `duckdb_function_get_extra_info`

Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`.

##### Syntax

void *duckdb_function_get_extra_info(

  duckdb_function_info info

);

##### Parameters

* `info`: The info object

##### Return Value

The extra info

#### `duckdb_function_get_bind_data`

Gets the bind data set by `duckdb_bind_set_bind_data` during the bind.

Note that the bind data should be considered as read-only.

For tracking state, use the init data instead.

##### Syntax

void *duckdb_function_get_bind_data(

  duckdb_function_info info

);

##### Parameters

* `info`: The info object

##### Return Value

The bind data object

#### `duckdb_function_get_init_data`

Gets the init data set by `duckdb_init_set_init_data` during the init.

##### Syntax

void *duckdb_function_get_init_data(

  duckdb_function_info info

);

##### Parameters

* `info`: The info object

##### Return Value

The init data object

#### `duckdb_function_get_local_init_data`

Gets the thread-local init data set by `duckdb_init_set_init_data` during the local_init.

##### Syntax

void *duckdb_function_get_local_init_data(

  duckdb_function_info info

);

##### Parameters

* `info`: The info object

##### Return Value

The init data object

#### `duckdb_function_set_error`

Report that an error has occurred while executing the function.

##### Syntax

void duckdb_function_set_error(

  duckdb_function_info info,

  const char *error

);

##### Parameters

* `info`: The info object

* `error`: The error message

#### `duckdb_add_replacement_scan`

Add a replacement scan definition to the specified database.

##### Syntax

void duckdb_add_replacement_scan(

  duckdb_database db,

  duckdb_replacement_callback_t replacement,

  void *extra_data,

  duckdb_delete_callback_t delete_callback

);

##### Parameters

* `db`: The database object to add the replacement scan to

* `replacement`: The replacement scan callback

* `extra_data`: Extra data that is passed back into the specified callback

* `delete_callback`: The delete callback to call on the extra data, if any

#### `duckdb_replacement_scan_set_function_name`

Sets the replacement function name. If this function is called in the replacement callback,

the replacement scan is performed. If it is not called, the replacement callback is not performed.

##### Syntax

void duckdb_replacement_scan_set_function_name(

  duckdb_replacement_scan_info info,

  const char *function_name

);

##### Parameters

* `info`: The info object

* `function_name`: The function name to substitute.

#### `duckdb_replacement_scan_add_parameter`

Adds a parameter to the replacement scan function.

##### Syntax

void duckdb_replacement_scan_add_parameter(

  duckdb_replacement_scan_info info,

  duckdb_value parameter

);

##### Parameters

* `info`: The info object

* `parameter`: The parameter to add.

#### `duckdb_replacement_scan_set_error`

Report that an error has occurred while executing the replacement scan.

##### Syntax

void duckdb_replacement_scan_set_error(

  duckdb_replacement_scan_info info,

  const char *error

);

##### Parameters

* `info`: The info object

* `error`: The error message

#### `duckdb_get_profiling_info`

Returns the root node of the profiling information. Returns nullptr, if profiling is not enabled.

##### Syntax

duckdb_profiling_info duckdb_get_profiling_info(

  duckdb_connection connection

);

##### Parameters

* `connection`: A connection object.

##### Return Value

A profiling information object.

#### `duckdb_profiling_info_get_value`

Returns the value of the metric of the current profiling info node. Returns nullptr, if the metric does

not exist or is not enabled. Currently, the value holds a string, and you can retrieve the string

by calling the corresponding function: char *duckdb_get_varchar(duckdb_value value).

##### Syntax

duckdb_value duckdb_profiling_info_get_value(

  duckdb_profiling_info info,

  const char *key

);

##### Parameters

* `info`: A profiling information object.

* `key`: The name of the requested metric.

##### Return Value

The value of the metric. Must be freed with `duckdb_destroy_value`

#### `duckdb_profiling_info_get_metrics`

Returns the key-value metric map of this profiling node as a MAP duckdb_value.

The individual elements are accessible via the duckdb_value MAP functions.

##### Syntax

duckdb_value duckdb_profiling_info_get_metrics(

  duckdb_profiling_info info

);

##### Parameters

* `info`: A profiling information object.

##### Return Value

The key-value metric map as a MAP duckdb_value.

#### `duckdb_profiling_info_get_child_count`

Returns the number of children in the current profiling info node.

##### Syntax

idx_t duckdb_profiling_info_get_child_count(

  duckdb_profiling_info info

);

##### Parameters

* `info`: A profiling information object.

##### Return Value

The number of children in the current node.

#### `duckdb_profiling_info_get_child`

Returns the child node at the specified index.

##### Syntax

duckdb_profiling_info duckdb_profiling_info_get_child(

  duckdb_profiling_info info,

  idx_t index

);

##### Parameters

* `info`: A profiling information object.

* `index`: The index of the child node.

##### Return Value

The child node at the specified index.

#### `duckdb_appender_create`

Creates an appender object.

Note that the object must be destroyed with `duckdb_appender_destroy`.

##### Syntax

duckdb_state duckdb_appender_create(

  duckdb_connection connection,

  const char *schema,

  const char *table,

  duckdb_appender *out_appender

);

##### Parameters

* `connection`: The connection context to create the appender in.

* `schema`: The schema of the table to append to, or `nullptr` for the default schema.

* `table`: The table name to append to.

* `out_appender`: The resulting appender object.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_appender_create_ext`

Creates an appender object.

Note that the object must be destroyed with `duckdb_appender_destroy`.

##### Syntax

duckdb_state duckdb_appender_create_ext(

  duckdb_connection connection,

  const char *catalog,

  const char *schema,

  const char *table,

  duckdb_appender *out_appender

);

##### Parameters

* `connection`: The connection context to create the appender in.

* `catalog`: The catalog of the table to append to, or `nullptr` for the default catalog.

* `schema`: The schema of the table to append to, or `nullptr` for the default schema.

* `table`: The table name to append to.

* `out_appender`: The resulting appender object.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_appender_column_count`

Returns the number of columns that belong to the appender.

If there is no active column list, then this equals the table's physical columns.

##### Syntax

idx_t duckdb_appender_column_count(

  duckdb_appender appender

);

##### Parameters

* `appender`: The appender to get the column count from.

##### Return Value

The number of columns in the data chunks.

#### `duckdb_appender_column_type`

Returns the type of the column at the specified index. This is either a type in the active column list, or the same type

as a column in the receiving table.

Note: The resulting type must be destroyed with `duckdb_destroy_logical_type`.

##### Syntax

duckdb_logical_type duckdb_appender_column_type(

  duckdb_appender appender,

  idx_t col_idx

);

##### Parameters

* `appender`: The appender to get the column type from.

* `col_idx`: The index of the column to get the type of.

##### Return Value

The `duckdb_logical_type` of the column.

#### `duckdb_appender_error`

Returns the error message associated with the given appender.

If the appender has no error message, this returns `nullptr` instead.

The error message should not be freed. It will be de-allocated when `duckdb_appender_destroy` is called.

##### Syntax

const char *duckdb_appender_error(

  duckdb_appender appender

);

##### Parameters

* `appender`: The appender to get the error from.

##### Return Value

The error message, or `nullptr` if there is none.

#### `duckdb_appender_flush`

Flush the appender to the table, forcing the cache of the appender to be cleared. If flushing the data triggers a

constraint violation or any other error, then all data is invalidated, and this function returns DuckDBError.

It is not possible to append more values. Call duckdb_appender_error to obtain the error message followed by

duckdb_appender_destroy to destroy the invalidated appender.

##### Syntax

duckdb_state duckdb_appender_flush(

  duckdb_appender appender

);

##### Parameters

* `appender`: The appender to flush.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_appender_close`

Closes the appender by flushing all intermediate states and closing it for further appends. If flushing the data

triggers a constraint violation or any other error, then all data is invalidated, and this function returns DuckDBError.

Call duckdb_appender_error to obtain the error message followed by duckdb_appender_destroy to destroy the invalidated

appender.

##### Syntax

duckdb_state duckdb_appender_close(

  duckdb_appender appender

);

##### Parameters

* `appender`: The appender to flush and close.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_appender_destroy`

Closes the appender by flushing all intermediate states to the table and destroying it. By destroying it, this function

de-allocates all memory associated with the appender. If flushing the data triggers a constraint violation,

then all data is invalidated, and this function returns DuckDBError. Due to the destruction of the appender, it is no

longer possible to obtain the specific error message with duckdb_appender_error. Therefore, call duckdb_appender_close

before destroying the appender, if you need insights into the specific error.

##### Syntax

duckdb_state duckdb_appender_destroy(

  duckdb_appender *appender

);

##### Parameters

* `appender`: The appender to flush, close and destroy.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_appender_add_column`

Appends a column to the active column list of the appender. Immediately flushes all previous data.

The active column list specifies all columns that are expected when flushing the data. Any non-active columns are filled

with their default values, or NULL.

##### Syntax

duckdb_state duckdb_appender_add_column(

  duckdb_appender appender,

  const char *name

);

##### Parameters

* `appender`: The appender to add the column to.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_appender_clear_columns`

Removes all columns from the active column list of the appender, resetting the appender to treat all columns as active.

Immediately flushes all previous data.

##### Syntax

duckdb_state duckdb_appender_clear_columns(

  duckdb_appender appender

);

##### Parameters

* `appender`: The appender to clear the columns from.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_appender_begin_row`

A nop function, provided for backwards compatibility reasons. Does nothing. Only `duckdb_appender_end_row` is required.

##### Syntax

duckdb_state duckdb_appender_begin_row(

  duckdb_appender appender

);

#### `duckdb_appender_end_row`

Finish the current row of appends. After end_row is called, the next row can be appended.

##### Syntax

duckdb_state duckdb_appender_end_row(

  duckdb_appender appender

);

##### Parameters

* `appender`: The appender.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_append_default`

Append a DEFAULT value (NULL if DEFAULT not available for column) to the appender.

##### Syntax

duckdb_state duckdb_append_default(

  duckdb_appender appender

);

#### `duckdb_append_default_to_chunk`

Append a DEFAULT value, at the specified row and column, (NULL if DEFAULT not available for column) to the chunk created

from the specified appender. The default value of the column must be a constant value. Non-deterministic expressions

like nextval('seq') or random() are not supported.

##### Syntax

duckdb_state duckdb_append_default_to_chunk(

  duckdb_appender appender,

  duckdb_data_chunk chunk,

  idx_t col,

  idx_t row

);

##### Parameters

* `appender`: The appender to get the default value from.

* `chunk`: The data chunk to append the default value to.

* `col`: The chunk column index to append the default value to.

* `row`: The chunk row index to append the default value to.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_append_bool`

Append a bool value to the appender.

##### Syntax

duckdb_state duckdb_append_bool(

  duckdb_appender appender,

  bool value

);

#### `duckdb_append_int8`

Append an int8_t value to the appender.

##### Syntax

duckdb_state duckdb_append_int8(

  duckdb_appender appender,

  int8_t value

);

#### `duckdb_append_int16`

Append an int16_t value to the appender.

##### Syntax

duckdb_state duckdb_append_int16(

  duckdb_appender appender,

  int16_t value

);

#### `duckdb_append_int32`

Append an int32_t value to the appender.

##### Syntax

duckdb_state duckdb_append_int32(

  duckdb_appender appender,

  int32_t value

);

#### `duckdb_append_int64`

Append an int64_t value to the appender.

##### Syntax

duckdb_state duckdb_append_int64(

  duckdb_appender appender,

  int64_t value

);

#### `duckdb_append_hugeint`

Append a duckdb_hugeint value to the appender.

##### Syntax

duckdb_state duckdb_append_hugeint(

  duckdb_appender appender,

  duckdb_hugeint value

);

#### `duckdb_append_uint8`

Append a uint8_t value to the appender.

##### Syntax

duckdb_state duckdb_append_uint8(

  duckdb_appender appender,

  uint8_t value

);

#### `duckdb_append_uint16`

Append a uint16_t value to the appender.

##### Syntax

duckdb_state duckdb_append_uint16(

  duckdb_appender appender,

  uint16_t value

);

#### `duckdb_append_uint32`

Append a uint32_t value to the appender.

##### Syntax

duckdb_state duckdb_append_uint32(

  duckdb_appender appender,

  uint32_t value

);

#### `duckdb_append_uint64`

Append a uint64_t value to the appender.

##### Syntax

duckdb_state duckdb_append_uint64(

  duckdb_appender appender,

  uint64_t value

);

#### `duckdb_append_uhugeint`

Append a duckdb_uhugeint value to the appender.

##### Syntax

duckdb_state duckdb_append_uhugeint(

  duckdb_appender appender,

  duckdb_uhugeint value

);

#### `duckdb_append_float`

Append a float value to the appender.

##### Syntax

duckdb_state duckdb_append_float(

  duckdb_appender appender,

  float value

);

#### `duckdb_append_double`

Append a double value to the appender.

##### Syntax

duckdb_state duckdb_append_double(

  duckdb_appender appender,

  double value

);

#### `duckdb_append_date`

Append a duckdb_date value to the appender.

##### Syntax

duckdb_state duckdb_append_date(

  duckdb_appender appender,

  duckdb_date value

);

#### `duckdb_append_time`

Append a duckdb_time value to the appender.

##### Syntax

duckdb_state duckdb_append_time(

  duckdb_appender appender,

  duckdb_time value

);

#### `duckdb_append_timestamp`

Append a duckdb_timestamp value to the appender.

##### Syntax

duckdb_state duckdb_append_timestamp(

  duckdb_appender appender,

  duckdb_timestamp value

);

#### `duckdb_append_interval`

Append a duckdb_interval value to the appender.

##### Syntax

duckdb_state duckdb_append_interval(

  duckdb_appender appender,

  duckdb_interval value

);

#### `duckdb_append_varchar`

Append a varchar value to the appender.

##### Syntax

duckdb_state duckdb_append_varchar(

  duckdb_appender appender,

  const char *val

);

#### `duckdb_append_varchar_length`

Append a varchar value to the appender.

##### Syntax

duckdb_state duckdb_append_varchar_length(

  duckdb_appender appender,

  const char *val,

  idx_t length

);

#### `duckdb_append_blob`

Append a blob value to the appender.

##### Syntax

duckdb_state duckdb_append_blob(

  duckdb_appender appender,

  const void *data,

  idx_t length

);

#### `duckdb_append_null`

Append a NULL value to the appender (of any type).

##### Syntax

duckdb_state duckdb_append_null(

  duckdb_appender appender

);

#### `duckdb_append_value`

Append a duckdb_value to the appender.

##### Syntax

duckdb_state duckdb_append_value(

  duckdb_appender appender,

  duckdb_value value

);

#### `duckdb_append_data_chunk`

Appends a pre-filled data chunk to the specified appender.

Attempts casting, if the data chunk types do not match the active appender types.

##### Syntax

duckdb_state duckdb_append_data_chunk(

  duckdb_appender appender,

  duckdb_data_chunk chunk

);

##### Parameters

* `appender`: The appender to append to.

* `chunk`: The data chunk to append.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_table_description_create`

Creates a table description object. Note that `duckdb_table_description_destroy` should always be called on the

resulting table_description, even if the function returns `DuckDBError`.

##### Syntax

duckdb_state duckdb_table_description_create(

  duckdb_connection connection,

  const char *schema,

  const char *table,

  duckdb_table_description *out

);

##### Parameters

* `connection`: The connection context.

* `schema`: The schema of the table, or `nullptr` for the default schema.

* `table`: The table name.

* `out`: The resulting table description object.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_table_description_create_ext`

Creates a table description object. Note that `duckdb_table_description_destroy` must be called on the resulting

table_description, even if the function returns `DuckDBError`.

##### Syntax

duckdb_state duckdb_table_description_create_ext(

  duckdb_connection connection,

  const char *catalog,

  const char *schema,

  const char *table,

  duckdb_table_description *out

);

##### Parameters

* `connection`: The connection context.

* `catalog`: The catalog (database) name of the table, or `nullptr` for the default catalog.

* `schema`: The schema of the table, or `nullptr` for the default schema.

* `table`: The table name.

* `out`: The resulting table description object.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_table_description_destroy`

Destroy the TableDescription object.

##### Syntax

void duckdb_table_description_destroy(

  duckdb_table_description *table_description

);

##### Parameters

* `table_description`: The table_description to destroy.

#### `duckdb_table_description_error`

Returns the error message associated with the given table_description.

If the table_description has no error message, this returns `nullptr` instead.

The error message should not be freed. It will be de-allocated when `duckdb_table_description_destroy` is called.

##### Syntax

const char *duckdb_table_description_error(

  duckdb_table_description table_description

);

##### Parameters

* `table_description`: The table_description to get the error from.

##### Return Value

The error message, or `nullptr` if there is none.

#### `duckdb_column_has_default`

Check if the column at 'index' index of the table has a DEFAULT expression.

##### Syntax

duckdb_state duckdb_column_has_default(

  duckdb_table_description table_description,

  idx_t index,

  bool *out

);

##### Parameters

* `table_description`: The table_description to query.

* `index`: The index of the column to query.

* `out`: The out-parameter used to store the result.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_table_description_get_column_name`

Obtain the column name at 'index'.

The out result must be destroyed with `duckdb_free`.

##### Syntax

char *duckdb_table_description_get_column_name(

  duckdb_table_description table_description,

  idx_t index

);

##### Parameters

* `table_description`: The table_description to query.

* `index`: The index of the column to query.

##### Return Value

The column name.

#### `duckdb_query_arrow`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Executes a SQL query within a connection and stores the full (materialized) result in an arrow structure.

If the query fails to execute, DuckDBError is returned and the error message can be retrieved by calling

`duckdb_query_arrow_error`.

Note that after running `duckdb_query_arrow`, `duckdb_destroy_arrow` must be called on the result object even if the

query fails, otherwise the error stored within the result will not be freed correctly.

##### Syntax

duckdb_state duckdb_query_arrow(

  duckdb_connection connection,

  const char *query,

  duckdb_arrow *out_result

);

##### Parameters

* `connection`: The connection to perform the query in.

* `query`: The SQL query to run.

* `out_result`: The query result.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_query_arrow_schema`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Fetch the internal arrow schema from the arrow result. Remember to call release on the respective

ArrowSchema object.

##### Syntax

duckdb_state duckdb_query_arrow_schema(

  duckdb_arrow result,

  duckdb_arrow_schema *out_schema

);

##### Parameters

* `result`: The result to fetch the schema from.

* `out_schema`: The output schema.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_prepared_arrow_schema`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Fetch the internal arrow schema from the prepared statement. Remember to call release on the respective

ArrowSchema object.

##### Syntax

duckdb_state duckdb_prepared_arrow_schema(

  duckdb_prepared_statement prepared,

  duckdb_arrow_schema *out_schema

);

##### Parameters

* `prepared`: The prepared statement to fetch the schema from.

* `out_schema`: The output schema.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_result_arrow_array`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Convert a data chunk into an arrow struct array. Remember to call release on the respective

ArrowArray object.

##### Syntax

void duckdb_result_arrow_array(

  duckdb_result result,

  duckdb_data_chunk chunk,

  duckdb_arrow_array *out_array

);

##### Parameters

* `result`: The result object the data chunk have been fetched from.

* `chunk`: The data chunk to convert.

* `out_array`: The output array.

#### `duckdb_query_arrow_array`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Fetch an internal arrow struct array from the arrow result. Remember to call release on the respective

ArrowArray object.

This function can be called multiple time to get next chunks, which will free the previous out_array.

So consume the out_array before calling this function again.

##### Syntax

duckdb_state duckdb_query_arrow_array(

  duckdb_arrow result,

  duckdb_arrow_array *out_array

);

##### Parameters

* `result`: The result to fetch the array from.

* `out_array`: The output array.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_arrow_column_count`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Returns the number of columns present in the arrow result object.

##### Syntax

idx_t duckdb_arrow_column_count(

  duckdb_arrow result

);

##### Parameters

* `result`: The result object.

##### Return Value

The number of columns present in the result object.

#### `duckdb_arrow_row_count`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Returns the number of rows present in the arrow result object.

##### Syntax

idx_t duckdb_arrow_row_count(

  duckdb_arrow result

);

##### Parameters

* `result`: The result object.

##### Return Value

The number of rows present in the result object.

#### `duckdb_arrow_rows_changed`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Returns the number of rows changed by the query stored in the arrow result. This is relevant only for

INSERT/UPDATE/DELETE queries. For other queries the rows_changed will be 0.

##### Syntax

idx_t duckdb_arrow_rows_changed(

  duckdb_arrow result

);

##### Parameters

* `result`: The result object.

##### Return Value

The number of rows changed.

#### `duckdb_query_arrow_error`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Returns the error message contained within the result. The error is only set if `duckdb_query_arrow` returns

`DuckDBError`.

The error message should not be freed. It will be de-allocated when `duckdb_destroy_arrow` is called.

##### Syntax

const char *duckdb_query_arrow_error(

  duckdb_arrow result

);

##### Parameters

* `result`: The result object to fetch the error from.

##### Return Value

The error of the result.

#### `duckdb_destroy_arrow`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Closes the result and de-allocates all memory allocated for the arrow result.

##### Syntax

void duckdb_destroy_arrow(

  duckdb_arrow *result

);

##### Parameters

* `result`: The result to destroy.

#### `duckdb_destroy_arrow_stream`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Releases the arrow array stream and de-allocates its memory.

##### Syntax

void duckdb_destroy_arrow_stream(

  duckdb_arrow_stream *stream_p

);

##### Parameters

* `stream_p`: The arrow array stream to destroy.

#### `duckdb_execute_prepared_arrow`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Executes the prepared statement with the given bound parameters, and returns an arrow query result.

Note that after running `duckdb_execute_prepared_arrow`, `duckdb_destroy_arrow` must be called on the result object.

##### Syntax

duckdb_state duckdb_execute_prepared_arrow(

  duckdb_prepared_statement prepared_statement,

  duckdb_arrow *out_result

);

##### Parameters

* `prepared_statement`: The prepared statement to execute.

* `out_result`: The query result.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_arrow_scan`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Scans the Arrow stream and creates a view with the given name.

##### Syntax

duckdb_state duckdb_arrow_scan(

  duckdb_connection connection,

  const char *table_name,

  duckdb_arrow_stream arrow

);

##### Parameters

* `connection`: The connection on which to execute the scan.

* `table_name`: Name of the temporary view to create.

* `arrow`: Arrow stream wrapper.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_arrow_array_scan`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Scans the Arrow array and creates a view with the given name.

Note that after running `duckdb_arrow_array_scan`, `duckdb_destroy_arrow_stream` must be called on the out stream.

##### Syntax

duckdb_state duckdb_arrow_array_scan(

  duckdb_connection connection,

  const char *table_name,

  duckdb_arrow_schema arrow_schema,

  duckdb_arrow_array arrow_array,

  duckdb_arrow_stream *out_stream

);

##### Parameters

* `connection`: The connection on which to execute the scan.

* `table_name`: Name of the temporary view to create.

* `arrow_schema`: Arrow schema wrapper.

* `arrow_array`: Arrow array wrapper.

* `out_stream`: Output array stream that wraps around the passed schema, for releasing/deleting once done.

##### Return Value

`DuckDBSuccess` on success or `DuckDBError` on failure.

#### `duckdb_execute_tasks`

Execute DuckDB tasks on this thread.

Will return after `max_tasks` have been executed, or if there are no more tasks present.

##### Syntax

void duckdb_execute_tasks(

  duckdb_database database,

  idx_t max_tasks

);

##### Parameters

* `database`: The database object to execute tasks for

* `max_tasks`: The maximum amount of tasks to execute

#### `duckdb_create_task_state`

Creates a task state that can be used with duckdb_execute_tasks_state to execute tasks until

`duckdb_finish_execution` is called on the state.

`duckdb_destroy_state` must be called on the result.

##### Syntax

duckdb_task_state duckdb_create_task_state(

  duckdb_database database

);

##### Parameters

* `database`: The database object to create the task state for

##### Return Value

The task state that can be used with duckdb_execute_tasks_state.

#### `duckdb_execute_tasks_state`

Execute DuckDB tasks on this thread.

The thread will keep on executing tasks forever, until duckdb_finish_execution is called on the state.

Multiple threads can share the same duckdb_task_state.

##### Syntax

void duckdb_execute_tasks_state(

  duckdb_task_state state

);

##### Parameters

* `state`: The task state of the executor

#### `duckdb_execute_n_tasks_state`

Execute DuckDB tasks on this thread.

The thread will keep on executing tasks until either duckdb_finish_execution is called on the state,

max_tasks tasks have been executed or there are no more tasks to be executed.

Multiple threads can share the same duckdb_task_state.

##### Syntax

idx_t duckdb_execute_n_tasks_state(

  duckdb_task_state state,

  idx_t max_tasks

);

##### Parameters

* `state`: The task state of the executor

* `max_tasks`: The maximum amount of tasks to execute

##### Return Value

The amount of tasks that have actually been executed

#### `duckdb_finish_execution`

Finish execution on a specific task.

##### Syntax

void duckdb_finish_execution(

  duckdb_task_state state

);

##### Parameters

* `state`: The task state to finish execution

#### `duckdb_task_state_is_finished`

Check if the provided duckdb_task_state has finished execution

##### Syntax

bool duckdb_task_state_is_finished(

  duckdb_task_state state

);

##### Parameters

* `state`: The task state to inspect

##### Return Value

Whether or not duckdb_finish_execution has been called on the task state

#### `duckdb_destroy_task_state`

Destroys the task state returned from duckdb_create_task_state.

Note that this should not be called while there is an active duckdb_execute_tasks_state running

on the task state.

##### Syntax

void duckdb_destroy_task_state(

  duckdb_task_state state

);

##### Parameters

* `state`: The task state to clean up

#### `duckdb_execution_is_finished`

Returns true if the execution of the current query is finished.

##### Syntax

bool duckdb_execution_is_finished(

  duckdb_connection con

);

##### Parameters

* `con`: The connection on which to check

#### `duckdb_stream_fetch_chunk`

> Warning Deprecation notice. This method is scheduled for removal in a future release.

Fetches a data chunk from the (streaming) duckdb_result. This function should be called repeatedly until the result is

exhausted.

The result must be destroyed with `duckdb_destroy_data_chunk`.

This function can only be used on duckdb_results created with 'duckdb_pending_prepared_streaming'

If this function is used, none of the other result functions can be used and vice versa (i.e., this function cannot be

mixed with the legacy result functions or the materialized result functions).

It is not known beforehand how many chunks will be returned by this result.

##### Syntax

duckdb_data_chunk duckdb_stream_fetch_chunk(

  duckdb_result result

);

##### Parameters

* `result`: The result object to fetch the data chunk from.

##### Return Value

The resulting data chunk. Returns `NULL` if the result has an error.

#### `duckdb_fetch_chunk`

Fetches a data chunk from a duckdb_result. This function should be called repeatedly until the result is exhausted.

The result must be destroyed with `duckdb_destroy_data_chunk`.

It is not known beforehand how many chunks will be returned by this result.

##### Syntax

duckdb_data_chunk duckdb_fetch_chunk(

  duckdb_result result

);

##### Parameters

* `result`: The result object to fetch the data chunk from.

##### Return Value

The resulting data chunk. Returns `NULL` if the result has an error.

#### `duckdb_create_cast_function`

Creates a new cast function object.

##### Return Value

The cast function object.

##### Syntax

duckdb_cast_function duckdb_create_cast_function(

  

);

#### `duckdb_cast_function_set_source_type`

Sets the source type of the cast function.

##### Syntax

void duckdb_cast_function_set_source_type(

  duckdb_cast_function cast_function,

  duckdb_logical_type source_type

);

##### Parameters

* `cast_function`: The cast function object.

* `source_type`: The source type to set.

#### `duckdb_cast_function_set_target_type`

Sets the target type of the cast function.

##### Syntax

void duckdb_cast_function_set_target_type(

  duckdb_cast_function cast_function,

  duckdb_logical_type target_type

);

##### Parameters

* `cast_function`: The cast function object.

* `target_type`: The target type to set.

#### `duckdb_cast_function_set_implicit_cast_cost`

Sets the "cost" of implicitly casting the source type to the target type using this function.

##### Syntax

void duckdb_cast_function_set_implicit_cast_cost(

  duckdb_cast_function cast_function,

  int64_t cost

);

##### Parameters

* `cast_function`: The cast function object.

* `cost`: The cost to set.

#### `duckdb_cast_function_set_function`

Sets the actual cast function to use.

##### Syntax

void duckdb_cast_function_set_function(

  duckdb_cast_function cast_function,

  duckdb_cast_function_t function

);

##### Parameters

* `cast_function`: The cast function object.

* `function`: The function to set.

#### `duckdb_cast_function_set_extra_info`

Assigns extra information to the cast function that can be fetched during execution, etc.

##### Syntax

void duckdb_cast_function_set_extra_info(

  duckdb_cast_function cast_function,

  void *extra_info,

  duckdb_delete_callback_t destroy

);

##### Parameters

* `extra_info`: The extra information

* `destroy`: The callback that will be called to destroy the extra information (if any)

#### `duckdb_cast_function_get_extra_info`

Retrieves the extra info of the function as set in `duckdb_cast_function_set_extra_info`.

##### Syntax

void *duckdb_cast_function_get_extra_info(

  duckdb_function_info info

);

##### Parameters

* `info`: The info object.

##### Return Value

The extra info.

#### `duckdb_cast_function_get_cast_mode`

Get the cast execution mode from the given function info.

##### Syntax

duckdb_cast_mode duckdb_cast_function_get_cast_mode(

  duckdb_function_info info

);

##### Parameters

* `info`: The info object.

##### Return Value

The cast mode.

#### `duckdb_cast_function_set_error`

Report that an error has occurred while executing the cast function.

##### Syntax

void duckdb_cast_function_set_error(

  duckdb_function_info info,

  const char *error

);

##### Parameters

* `info`: The info object.

* `error`: The error message.

#### `duckdb_cast_function_set_row_error`

Report that an error has occurred while executing the cast function, setting the corresponding output row to NULL.

##### Syntax

void duckdb_cast_function_set_row_error(

  duckdb_function_info info,

  const char *error,

  idx_t row,

  duckdb_vector output

);

##### Parameters

* `info`: The info object.

* `error`: The error message.

* `row`: The index of the row within the output vector to set to NULL.

* `output`: The output vector.

#### `duckdb_register_cast_function`

Registers a cast function within the given connection.

##### Syntax

duckdb_state duckdb_register_cast_function(

  duckdb_connection con,

  duckdb_cast_function cast_function

);

##### Parameters

* `con`: The connection to use.

* `cast_function`: The cast function to register.

##### Return Value

Whether or not the registration was successful.

#### `duckdb_destroy_cast_function`

Destroys the cast function object.

##### Syntax

void duckdb_destroy_cast_function(

  duckdb_cast_function *cast_function

);

##### Parameters

* `cast_function`: The cast function object.

