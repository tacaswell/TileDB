/**
 * @file   tiledb_write_sparse_2.cc
 *
 * @section LICENSE
 *
 * The MIT License
 * 
 * @copyright Copyright (c) 2016 MIT and Intel Corporation
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
 * It shows how to write to a sparse array with two sorted batch writes.
 */

#include "tiledb.h"

int main() {
  // Initialize context with the default configuration parameters
  tiledb_ctx_t* ctx;
  tiledb_ctx_create(&ctx);

  // Prepare cell buffers - #1
  int buffer_a1[] = { 0, 1, 2 };
  uint64_t buffer_a2[] = { 0, 1, 3, 6, 10, 11, 13, 16 };
  char buffer_var_a2[] = "abbcccddddeffggghhhh";
  float buffer_a3[] = 
  {
      0.1,  0.2,  1.1,  1.2,  2.1,  2.2,  3.1,  3.2,
      4.1,  4.2,  5.1,  5.2,  6.1,  6.2,  7.1,  7.2 
  };
  int64_t buffer_coords[] = { 1, 1, 1, 2 };
  void* buffers[] =
      { buffer_a1, buffer_a2, buffer_var_a2, buffer_a3, buffer_coords };
  uint64_t buffer_sizes[] =
  { 
      sizeof(buffer_a1),  
      sizeof(buffer_a2),
      sizeof(buffer_var_a2)-1,  // No need to store the last '\0' character
      sizeof(buffer_a3),
      sizeof(buffer_coords)
  };

  // Create query
  tiledb_query_t* query;
  tiledb_query_create(
    ctx,
    &query,
    "my_group/sparse_arrays/my_array_B",
    TILEDB_WRITE,
    TILEDB_GLOBAL_ORDER,
    nullptr,
    nullptr,
    0,
    buffers,
    buffer_sizes);

  // Submit query - #1
  tiledb_query_submit(ctx, query);

  // Prepare cell buffers - #2
  int buffer_a1_2[] = { 3, 4, 5, 6, 7 };
  uint64_t* buffer_a2_2 = nullptr;
  char* buffer_var_a2_2 = nullptr;
  float* buffer_a3_2 = nullptr; 
  int64_t buffer_coords_2[] = { 1, 4, 2, 3, 3, 1, 4, 2, 3, 3, 3, 4 };
  void* buffers_2[] =
  { 
       buffer_a1_2, 
       buffer_a2_2, 
       buffer_var_a2_2, 
       buffer_a3_2, 
       buffer_coords_2 };
  uint64_t buffer_sizes_2[] =
  { 
      sizeof(buffer_a1_2),  
      0,
      0,
      0,
      sizeof(buffer_coords_2)
  };

  // Submit query - #2
  tiledb_query_reset_buffers(ctx, query, buffers_2, buffer_sizes_2);
  tiledb_query_submit(ctx, query);

  // Clean up
  tiledb_query_free(ctx, query);
  tiledb_ctx_free(ctx);

  // Finalize context
  tiledb_ctx_free(ctx);

  return 0;
}