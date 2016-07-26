#include "string_stack.h"

// resets the object to it's original state
void StrStack::clear(){

	for (uint8_t i = 0; i < stackDepth; i++)
		free(*(buffer--));

  	// set buffer to it's original size
	stackHead = buffer = (char**) realloc(buffer, 256);

	stackDepth = 0;

}

// doubles the size of the buffer
void StrStack::grow(){

  	// don't copy the contents of an empty buffer
	if (stackDepth == 0)
		buffer = (char**) realloc(buffer, (1 << ++sizeFactor) * 256);

	else {

	  	// make a new buffer twice as big as the old one
		char** buffer2 = (char**) malloc((1 << ++sizeFactor) * 256);

	  	// copy all the strings into their new locations
	  	for (uint8_t i = 0; i < stackDepth; i++)
			*(buffer2 + i) = *(buffer + i);

		// delete the old buffer
	  	free(buffer);

	  	// replace buffer with buffer2
	  	stackHead = buffer = buffer2;

	}

}


// pushes a line to the top of the stack
void StrStack::push(const char* str){
	*buffer = (char*) malloc(strlen(str) + 1);

	// write the string to the buffer
	strcpy(*buffer, str);

	// go to next empty space
	buffer++;

  	stackDepth++;
}



// deletes the string at the top of the stack.
void StrStack::pop(){
	if (stackDepth != 0) {
		// deallocate the line
		// & continue to point to the top
		free(*(--buffer));

		// decrease stack depth
		stackDepth--;

	}
}