#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define IMG_NAME "user_img.img"
#define MAX_FILES 1024

typedef unsigned int u32;

// 文件信息结构体
typedef struct {
    char filename[64];  // 文件名
    u32 size;           // 文件大小
    u32 offset;         // 在 .img 文件中的偏移量
} FileInfo;

FileInfo files[MAX_FILES]; // 存储文件信息
int file_count = 0; // 文件数量

// 统计目录下的文件数量并收集文件信息
void scan_directory(const char *dirpath) {
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("无法打开目录");
        exit(1);
    }

    struct dirent *entry;
    struct stat st;
    char filepath[256];

    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_REG) { // 只处理普通文件
            snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, entry->d_name);
            if (stat(filepath, &st) == 0 && file_count < MAX_FILES) {
                strncpy(files[file_count].filename, entry->d_name, 64);
                files[file_count].size = st.st_size;
                file_count++;
            }
        }
    }

    closedir(dir);
}

// 写入 .img 文件
void write_to_img(const char *dirpath) {
    FILE *img = fopen(IMG_NAME, "wb");
    if (!img) {
        perror("无法创建 .img 文件");
        exit(1);
    }

    // 1. 先写入 4 字节的文件数量
    fwrite(&file_count, sizeof(u32), 1, img);

    // 计算并写入文件信息结构体
    u32 current_offset = 4 + file_count * sizeof(FileInfo); // 数据区的起始偏移
    for (int i = 0; i < file_count; i++) {
        files[i].offset = current_offset;
        fwrite(&files[i], sizeof(FileInfo), 1, img);
        current_offset += files[i].size;
    }

    // 逐个写入文件数据
    char buffer[1024];
    size_t bytes;
    for (int i = 0; i < file_count; i++) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, files[i].filename);
        FILE *fp = fopen(filepath, "rb");
        if (!fp) {
            perror("无法打开文件");
            continue;
        }

        while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
            fwrite(buffer, 1, bytes, img);
        }
        fclose(fp);
    }

    fclose(img);
    printf("打包完成! %d 个文件写入 %s\n", file_count, IMG_NAME);
}

int main() {
    const char *source_dir = "./programs";
    scan_directory(source_dir); // 统计文件
    write_to_img(source_dir);   // 写入 .img
    return 0;
}

