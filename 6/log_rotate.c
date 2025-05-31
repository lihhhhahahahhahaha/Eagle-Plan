#include "log_system.h"
#include <unistd.h>
#include <libgen.h>
#include <dirent.h>

#define MAX_LOG_FILES 10
#define MAX_LOG_SIZE (10 * 1024 * 1024) // 10MB

void rotate_logs(const char *filename)
{
    struct stat st;
    if (stat(filename, &st) == 0) {
        // 检查文件大小
        if (st.st_size >= MAX_LOG_SIZE) {
            char old_path[256];
            char new_path[256];
            
            // 找到最高编号的日志文件
            int max_num = 0;
            DIR* dir = opendir(".");
            if (dir != NULL) {
                struct dirent* entry;
                while ((entry = readdir(dir)) != NULL) {
                    if (strncmp(entry->d_name, basename(filename), strlen(basename(filename))) == 0) {
                        char* dot = strrchr(entry->d_name, '.');
                        if (dot != NULL && strcmp(dot, ".log") == 0) {
                            char* num_str = dot - 1;
                            if (num_str >= entry->d_name && *num_str >= '0' && *num_str <= '9') {
                                int num = atoi(num_str);
                                if (num > max_num) max_num = num;
                            }
                        }
                    }
                }
                closedir(dir);
            }
            
            // 如果达到最大文件数，删除最旧的
            if (max_num >= MAX_LOG_FILES) {
                snprintf(old_path, sizeof(old_path), "%s.%d.log", filename, 1);
                remove(old_path);
                
                // 重命名其他文件
                for (int i = 2; i <= max_num; i++) {
                    snprintf(old_path, sizeof(old_path), "%s.%d.log", filename, i);
                    snprintf(new_path, sizeof(new_path), "%s.%d.log", filename, i-1);
                    rename(old_path, new_path);
                }
                max_num--;
            }
            
            // 重命名当前日志文件
            snprintf(new_path, sizeof(new_path), "%s.%d.log", filename, max_num + 1);
            rename(filename, new_path);
        }
    }
}
