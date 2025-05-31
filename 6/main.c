#include "log_system.h"
#include <unistd.h>

int main() 
{
    // 初始化日志系统
    log_init("app.log");
    set_log_level(LOG_LEVEL_DEBUG);
    
    // 测试普通日志
    log_print(LOG_LEVEL_INFO, "Application started");
    
    // 测试过滤日志
    for (int i = 0; i < 100; i++) {
        log_print_filtered(LOG_LEVEL_WARNING, "This is a test message %d", i);
        if (i % 10 == 0) {
            log_print_filtered(LOG_LEVEL_ERROR, "This is another message");
        }
        usleep(10000); // 10ms
    }
    
    // 测试海量日志屏蔽
    for (int i = 0; i < 200; i++) {
        log_print_filtered(LOG_LEVEL_ERROR, "Flood message test %d", i);
        usleep(1000); // 1ms
    }
    
    // 关闭日志系统
    log_close();
    return 0;
}
