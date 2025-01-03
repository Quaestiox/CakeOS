#ifndef PATH_H
#define PATH_H

#include "type.h"

struct path{
	int drive_id;
	struct path_part* body;
};

struct path_part{
	const char* part;
	struct path_part* next;
};

struct path* path_parser(const char* path, const char* current_directory_path);
void path_free(struct path* root);

#endif 

