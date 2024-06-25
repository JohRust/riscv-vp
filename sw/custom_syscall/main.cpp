#include <stdio.h>
#include <unistd.h>

extern "C" int make_syscall(int arg1, int arg2, int syscall_number);

int main(){
    //make syscall
    int res = make_syscall(5, 3, 701);
    printf("syscall result: %d\n", res);
    return 0;
}
