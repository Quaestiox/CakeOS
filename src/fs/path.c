#include "path.h"
#include "error.h"
#include "string.h"
#include "config.h"
#include "kheap.h"
#include "memory.h"

static bool valid_format(const char* filename){
	int len = strnlen(filename, MAX_PATH);
	
	return (len >= 3 && isdigit(filename[0]) && memcmp((void*)&filename[1],":/",2) == 0);
}


static int get_drive_id(const char** path){
	if(!valid_format(*path)){
		return -ERR_PATH;
	}

	int drive_id = tonumericdigit(*path[0]);

	*path += 3;
	return drive_id;
}


static struct path* path_create_root(int drive_id){
	struct path* new_path = kzalloc(sizeof(struct path));
	new_path->drive_id = drive_id;
	new_path->body = 0;
	return new_path;
}

static const char* get_path_part(const char** path){
	char* result_path_part = kzalloc(MAX_PATH);
	int i = 0;
	while(**path != '/' && **path != 0x00){
		result_path_part[i] = **path;
		*path += 1;
		i++;
	}

	if(**path == '/'){
		*path += 1;
	}

	if(i == 0){
		kfree(result_path_part);
		result_path_part = 0;
	}

	return result_path_part;
}

struct path_part* parse_path_part(struct path_part* prev_part,const char** path){
	const char* path_part_str = get_path_part(path);
	if(!path_part_str){
		return 0;
	}

	struct path_part* part = kzalloc(sizeof(struct path_part));
	part->part = path_part_str;
	part->next = 0x00;

	if(prev_part){
		prev_part->next = part;
	}

	return part;
}

struct path* path_parser(const char* path, const char* current_directory_path){
	const char* tmp_path = path;
	struct path* path_root = 0;

	if(strlen(path) > MAX_PATH){
		goto out;
	}

	int drive_id = get_drive_id(&tmp_path);
	if(drive_id < 0){
		goto out;
	}

	path_root = path_create_root(drive_id);

	if(!path_root){
		goto out;
	}

	struct path_part* first_part = parse_path_part(NULL,&tmp_path);
	if(!first_part){
		goto out;
	}

	path_root->body = first_part;
	struct path_part* part = parse_path_part(first_part,&tmp_path);
	while(part){
		part = parse_path_part(part,&tmp_path);
	}

out:
	return path_root;	
}


void path_free(struct path* path_root){
	struct path_part* part = path_root->body;
	while(part){
		struct path_part* next_part = part->next;
		kfree((void*)part->part);
		kfree(part);
		part = next_part;
	}

	kfree(path_root);
}
