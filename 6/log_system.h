#ifndef LOG_SYSTEM_H
#define LOG_SYSTEM_H

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// 日志级别定义
typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_CRITICAL
} LogLevel;

// 日志系统初始化
void log_init(const char* filename);

// 日志系统关闭
void log_close();

// 普通日志打印
void log_print(LogLevel level, const char* format, ...);

// 过滤日志打印(1小时内相同日志只打印前2条)
void log_print_filtered(LogLevel level, const char* format, ...);

// 设置日志级别
void set_log_level(LogLevel level);

#endif
