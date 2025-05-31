#include "log_system.h"
#include <stdlib.h>
#include <stdarg.h>
#include <sys/stat.h>

#define MAX_LOG_ENTRIES 1000
#define FLOOD_THRESHOLD 60    // 1分钟内60条相同日志视为海量
#define FLOOD_INTERVAL 3600   // 海量日志屏蔽时间(1小时)

typedef struct {
    char message[256];
    time_t first_seen;
    time_t last_seen;
    int count;
    bool is_flooding;
    time_t flood_start;
} LogEntry;

static FILE *log_file = NULL;
static LogLevel current_level = LOG_LEVEL_INFO;
static LogEntry log_entries[MAX_LOG_ENTRIES];
static int entry_count = 0;

void log_init(const char *filename) 
{
    if (log_file != NULL) {
        fclose(log_file);
    }
    
    log_file = fopen(filename, "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }
    
    // 设置文件权限为644
    chmod(filename, 0644);
    
    // 初始化日志条目
    memset(log_entries, 0, sizeof(log_entries));
    entry_count = 0;
}

void log_close()
{
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}

static const char *level_to_string(LogLevel level)
{
    switch (level) {
        case LOG_LEVEL_DEBUG:    return "DEBUG";
        case LOG_LEVEL_INFO:     return "INFO";
        case LOG_LEVEL_WARNING:  return "WARNING";
        case LOG_LEVEL_ERROR:    return "ERROR";
        case LOG_LEVEL_CRITICAL: return "CRITICAL";
        default:                 return "UNKNOWN";
    }
}

static void write_log(LogLevel level, const char *message)
{
    if (log_file == NULL || level < current_level) {
        return;
    }
    
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    
    fprintf(log_file, "[%s] %s: %s\n", timestamp, level_to_string(level), message);
    fflush(log_file);
}

static bool should_filter_message(const char *message, bool *is_flooding) {
    time_t now = time(NULL);
    *is_flooding = false;
    
    // 查找现有条目
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(log_entries[i].message, message) == 0) {
            // 检查是否是海量日志
            if (log_entries[i].is_flooding) {
                if (now - log_entries[i].flood_start < FLOOD_INTERVAL) {
                    // 仍在屏蔽期内
                    *is_flooding = true;
                    return true;
                } else {
                    // 屏蔽期结束，重置状态
                    log_entries[i].is_flooding = false;
                    log_entries[i].count = 0;
                }
            }
            
            // 检查是否达到海量阈值
            if (!log_entries[i].is_flooding && 
                now - log_entries[i].first_seen <= 60 && 
                log_entries[i].count >= FLOOD_THRESHOLD) {
                log_entries[i].is_flooding = true;
                log_entries[i].flood_start = now;
                *is_flooding = true;
                return true;
            }
            
            // 检查1小时内相同日志是否超过2条
            if (now - log_entries[i].first_seen <= 3600 && log_entries[i].count >= 2) {
                log_entries[i].count++;
                log_entries[i].last_seen = now;
                return true;
            }
            
            // 更新条目
            log_entries[i].count++;
            log_entries[i].last_seen = now;
            return false;
        }
    }
    
    // 添加新条目
    if (entry_count < MAX_LOG_ENTRIES) {
        strncpy(log_entries[entry_count].message, message, sizeof(log_entries[entry_count].message) - 1);
        log_entries[entry_count].first_seen = now;
        log_entries[entry_count].last_seen = now;
        log_entries[entry_count].count = 1;
        log_entries[entry_count].is_flooding = false;
        entry_count++;
    }
    
    return false;
}

void log_print(LogLevel level, const char* format)
{
    va_list args;
    char message[256];
    
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    write_log(level, message);
}

void log_print_filtered(LogLevel level, const char* format)
{
    va_list args;
    char message[256];
    bool is_flooding;
    
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    if (should_filter_message(message, &is_flooding)) {
        if (is_flooding) {
            static time_t last_flood_log = 0;
            time_t now = time(NULL);
            if (now - last_flood_log >= 3600) {
                char flood_msg[300];
                snprintf(flood_msg, sizeof(flood_msg), 
                        "[FLOOD CONTROL] Suppressed similar messages for 1 hour: %s", message);
                write_log(level, flood_msg);
                last_flood_log = now;
            }
        }
        return;
    }
    
    write_log(level, message);
}

void set_log_level(LogLevel level)
{
    current_level = level;
}
