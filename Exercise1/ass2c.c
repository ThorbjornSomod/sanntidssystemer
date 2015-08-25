#include <stdio.h>
#include <stdlib.h>

void allocate(int value){
	int *ptr = NULL;
	ptr = malloc(1000000000000000 * sizeof(int));

	if(ptr == NULL || ptr < 0){
		perror("Error, invalid ptr");
		exit(0);
	}	

	*ptr = value;
	printf("test of allocated memory: %i\n", value);
}

int main(){
	while(1){
		allocate(1);
	}

	return 0;
}
