#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {

	size_t size;

	void** data;
	size_t* data_size;

	size_t top_offset;

} Stack;



int stack_init(Stack* stack, size_t size) {

	if (size == 0) { size = 1; }

	stack->size = size;

	stack->data = malloc(size);
	if (stack->data == NULL) { puts("ERROR: Failed to malloc for Stack->data in stack_init()"); return -1; }

	stack->data_size = (size_t*) malloc(sizeof(size_t) * size);
	if (stack->data_size == NULL) { puts("ERROR: Failed to malloc for Stack->data_size in stack_init()"); return -2; }

	stack->top_offset = 0;

	return 0;

}



void stack_free(Stack* stack) {

	free(stack->data);

	free(stack->data_size);

}



int stack_push(Stack* stack, void* data, size_t data_size) {

	if (stack->top_offset == stack->size - 1) {

		size_t new_size = (stack->size << 1);
		if (new_size == 0) { puts("ERROR: Ran out of addressable memory? stack_push() stack resize"); return -1; } // This error will most likely never happen

		stack->data = realloc(stack->data, new_size);
		if (stack->data == NULL) { puts("ERROR: Failed to realloc Stack->data"); return -2; }

		stack->data_size = (size_t*) realloc(stack->data_size, sizeof(size_t) * new_size);
		if (stack->data_size == NULL) { puts("ERROR: Failed to realloc Stack->data_size"); return -3; }

		stack->size = new_size;

	}



	stack->data[stack->top_offset] = data;

	stack->data_size[stack->top_offset] = data_size;

	stack->top_offset++;



	return 0;

}



void* stack_pop(Stack* stack, size_t* data_size) {

	stack->top_offset--;

	if (data_size != NULL) { *data_size = stack->data_size[stack->top_offset]; }

	void* out = stack->data[stack->top_offset];

	return out;

}



void* stack_concat(Stack* stack, size_t* out_size) {

	size_t data_size_sum = 0;
	for (int i = 0; i < stack->top_offset; i++) {

		data_size_sum += stack->data_size[i];

	}

	void* out = malloc(data_size_sum);
	if (out == NULL) { puts("ERROR: malloc() failed in concat_stack()"); return (char*)-1; }

	void* out_end = out;

	for (int i = 0; i < stack->top_offset; i++) {

		memcpy(out_end, stack->data[i], stack->data_size[i]);

		out_end += stack->data_size[i];

	}

	*out_size = out_end - out;

	return out;

}

