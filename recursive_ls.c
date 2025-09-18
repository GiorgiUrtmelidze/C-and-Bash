#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

#define PATH_LENGTH 256

void print_tabs(int n) {
    for(int i = 0; i < n; i++) {
        printf("\t");
    }
}

// Depth variable determines how deep is
// current directory from starting directory
// and prints such quantity of tabs

void ls(char *curr_dir, int depth) {
	DIR *directory;
	struct dirent *entry;

	directory = opendir(curr_dir);

	if (directory == NULL) {
		return;
	}

	while ((entry = readdir(directory)) != NULL) {
		if (entry->d_name[0] == '.') continue;

		print_tabs(depth);
		printf("%s\n", entry->d_name);

		// If it is a directory then create new path
		// do the same logic
		// then free up path(new_dir) variable
		if (entry->d_type == DT_DIR) {
			char* new_dir = (char *)malloc(strlen(curr_dir) + strlen(entry->d_name) + 2);

    		strcpy(new_dir, curr_dir);
			strcat(new_dir, "/");
    		strcat(new_dir, entry->d_name);

			ls(new_dir, depth + 1);

			free(new_dir);
		}
	}

	closedir(directory);
}

int main() {
	char cwd[PATH_LENGTH];

	// Get current directory path...
	getcwd(cwd, sizeof(cwd));

	ls(cwd, 0);
}
