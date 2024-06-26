#include <stdio.h>
#include <unistd.h>

extern "C" int make_syscall(int arg1, int arg2, int syscall_number);

enum my_syscalls {
    SET_TRACES = 700,
    CUSTOM_SYSCALL1 = 701,
    CUSTOM_SYSCALL2 = 702,
};

int main(){
    //make a syscall
    int res = make_syscall(5, 3, CUSTOM_SYSCALL1);
    printf("syscall result: %d\n", res);
    return 0;
}
