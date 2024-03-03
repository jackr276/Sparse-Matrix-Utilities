# Converting a Sparse Matrix into Compressed Sparse Row(CSR) Format
Author: [Jack Robbins](https://www.github.com/jackr276)
 
This project provides 3 C programs that are designed to generate, print and convert binary files containing sequences of unsigned integers. The binary files are treated as sparse matrices, that is, matrices who contain at least 50% zeroes, making them truly sparse. 


## What is a Sparse Matrix?
A sparse matrix is a matrix whose contents are at least 50% 0's. Here is a small 5 X 5 example:
  |0 | 1 | 0 | 0 | 0 |
  |-----|-----|-----|-----|------|
  |**0**|**0**|**2**|**0**|**1**|
  |**0**|**4**|**0**|**0**|**0**|
  |**12**|**0**|**0**|**0**|**0**|
  |**3**|**0**|**0**|**0**|**0**|

Notice how we only have 6 nonzero values(1, 2, 3, 4 and 12) out of 25 total values, making this matrix truly sparse.

Unlike this small 5 X 5 example, these matrices are often quite large, and therefore storing them efficiently in memory provides an interesting challenge to solve. Consider a sparse matrix of unsigned integers that is 1000 rows by 1000 columns. If we know that this matrix is sparse, we know that out of the $1,000 * 1,000 = 1,000,000$ elements in the matrix, at least 50% of them, $500,000$, will be 0's. If we were to store all of these 0's in memory, we are guaranteed, in our example, to be storing at least $500,000 * 4$ Bytes/Unisgned Integer = $2,000,000$ Bytes = $2$ MegaBytes(MB) of 0's in memory, or in a file somewhere, a gross waste of resources. Remember, this is the **best case** scenario, as we guarantee that the matrix is **at least** 50% 0's, so in all likelihood we will be wasting more than $2$ MB's of memory.
