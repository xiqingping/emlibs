#ifndef __SHELL_PRIVATE_H__
#define __SHELL_PRIVATE_H__

#include "shell.h"

/// shell��Ӧ��ִ�к���.
typedef void(*shell_handler)(int argc, char **argv);

/// һ��shell����������Ϣ.
typedef struct {
    const char *cmd; ///< shell����.
    const char *summary; ///< ��Ҫ����.
    const char *help; ///< ��ϸ����
    shell_handler handler; ///< ��Ӧִ�еĺ���.
} shell_command_t;

/// ��������һ��shell����.
#define SHELL_PROTYPE(cmd)  \
    extern void shell_func_##cmd(int argc, char **argv); \
    extern const char shell_help_##cmd[]; \
    extern const char shell_summary_##cmd[]

/// ���ڳ�ʼ��һ��shell����Ľṹ��.
#define SHELL_COMMAND(cmd, shell) \
    {cmd, shell_summary_##shell, shell_help_##shell, shell_func_##shell }



#include "shell_config.h"

#endif

