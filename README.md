# API
`int stack_init(Stack* stack, size_t size)`
- Returns **zero** if **no error**. Returns **non-zero** if **error**.
- If `size` is `0`, size is set to `1`.

<br>
<br>

`void stack_free(Stack* stack)`

<br>
<br>

`int stack_push(Stack* stack, void* data, size_t data_size)`
- Returns **zero** if **no error**. Returns **non-zero** if **error**.

<br>
<br>

`void* stack_pop(Stack* stack, size_t* data_size)`
- `data_size` output is optional; Can be set to `NULL` if not needed.

<br>
<br>

`void* stack_concat(Stack* stack, size_t* out_size)`
- Returns `(char*)-1` if **error**.

# Example
```
#include <stdio.h>

#include "stack.h"



int main() {

	Stack s;
	if (stack_init(&s, 2) != 0) { puts("ERROR: stack_init() failed"); return -1; }

	char foo[] = "Hello";
	char bar[] = "World!";



	// Example 1 - Pushing & popping

	if (stack_push(&s, bar, sizeof(bar)) != 0) { puts("ERROR: stack_push() failed"); return -1; }
	if (stack_push(&s, foo, sizeof(foo)) != 0) { puts("ERROR: stack_push() failed"); return -1; }

	size_t pop1_size;
	char* pop1 = stack_pop(&s, &pop1_size);

	char* pop2 = stack_pop(&s, NULL);

	printf("pop1: %s (size: %d)\npop2: %s\n", pop1, pop1_size, pop2);



	// Example 2 - Auto-resizing

	printf("\nStack size: %d\nNumber of items in stack: %d\n\n", s.size, s.top_offset);

	printf("Pushing \"%s\"\n", bar);
	if (stack_push(&s, bar, sizeof(bar)) != 0) { puts("ERROR: stack_push() failed"); return -1; }
	printf("Pushing \"%s\"\n", foo);
	if (stack_push(&s, foo, sizeof(foo)) != 0) { puts("ERROR: stack_push() failed"); return -1; }
	printf("Pushing \"%s\"\n", bar);
	if (stack_push(&s, bar, sizeof(bar)) != 0) { puts("ERROR: stack_push() failed"); return -1; }
	printf("Pushing \"%s\"\n", foo);
	if (stack_push(&s, foo, sizeof(foo)) != 0) { puts("ERROR: stack_push() failed"); return -1; }

	printf("\nStack size: %d\nNumber of items in stack: %d\n\n", s.size, s.top_offset);	



	// Example 3 - Concatenation

	size_t combined_size;
	char* combined = (char*) stack_concat(&s, &combined_size);
	if (combined == (char*)-1) { puts("ERROR: stack_concat() failed"); return -1; }

	puts("Combined:");
	for (int i = 0; i < combined_size; i++) { putchar(combined[i]); }
	putchar('\n');



	stack_free(&s);

	return 0;

}

```
