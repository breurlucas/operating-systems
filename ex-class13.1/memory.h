char memory[50*1024*1024]; // The memory representation as an array

// Struct which defines an allocated/free memory section. Its has a 'size_t' in bytes,
typedef struct section {
  int isFree; // Bool for checking if the section is free
  size_t size; // Section size in bytes
  struct section *next; // Pointer to the next section of memory in the linked list
} _section;

void *allocate(size_t nbytes); 
void liberate(void *p); 
void startupMemory();
