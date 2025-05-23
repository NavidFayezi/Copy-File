#include<stdio.h>

// Declare environ. The C run-time startup code defines this variable and 
// assignes the address of the location of environment list to it.
extern char **environ;

int main(){
	char ** env_var;

	// The following block prints one variable per line.
	for( env_var = environ; *env_var != NULL; env_var ++){
		printf("%s\n", *env_var);
	}

	return 0;
}

