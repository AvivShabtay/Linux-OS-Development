# Shared-memory
* Using Linux OS syscall to create multi-processing application.
* Each child-process aimed to do different work:
  * Check the rows
  * Check the coloums
  * Check the inside-matrix.
* All child-process using shared memory, which is done by mmap syscall.
* Multi-processing is done by fork syscall.
* Have fun!
