#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void uart_write(char c);
EXTERNC int uart_writechar(char c);

#undef EXTERNC
// ...