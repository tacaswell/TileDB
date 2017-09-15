/**
 * @file query_type.h
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2017 TileDB, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * This defines the TileDB QueryType enum that maps to tiledb_query_type_t C-API
 * enum.
 */

#ifndef TILEDB_QUERY_TYPE_H
#define TILEDB_QUERY_TYPE_H

namespace tiledb {

/** Defines the query type. */
enum class QueryType : char {
#define TILEDB_QUERY_TYPE_ENUM(id) id
#include "tiledb_enum.inc"
#undef TILEDB_QUERY_TYPE_ENUM
};

/** Checks if the query type is "read". */
inline bool is_read_type(const QueryType query_type) {
  return query_type == QueryType::READ ||
         query_type == QueryType::READ_SORTED_COL ||
         query_type == QueryType::READ_SORTED_ROW;
}

/** Checks if the query type is "write". */
inline bool is_write_type(const QueryType query_type) {
  return query_type == QueryType::WRITE ||
         query_type == QueryType::WRITE_SORTED_COL ||
         query_type == QueryType::WRITE_SORTED_ROW ||
         query_type == QueryType::WRITE_UNSORTED;
}

}  // namespace tiledb

#endif  // TILEDB_QUERY_TYPE_H
