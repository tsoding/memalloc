# Artifacts of those Memory Management Tsoding Sessions

## Quick Start

```console
$ make
$ ./heap
```

## Limitations

- The pointers to the heap can only be located in the heap and the stack.
- No packed structs. All of the pointers should be aligned.
- No tricks that obscure the pointers (like XOR Linked Lists).
- Probably works only on x86_64
- Probably works only when compiled with GCC
