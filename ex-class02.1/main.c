/* 

uname - print system information
uname --all (print all information)
sys_uname struct old_utsname__user*name 

*/

/*

Source: https://man7.org/linux/man-pages/man2/syscalls.2.html

System calls are generaly not invoked directly, but rather via wrapper functions in glibc.
Often but now always, the name of the wrapper function is the same as the name of the system
call that it invokes. For example, glibc contains a function chdir() which invokes the underlying
"chdir" system call 

*/

#include <sys/utsname.h>
#include <stdio.h>

void main() {

    // int uname(struct utsname *buf);

    struct utsname dt;

    uname(&dt);

    printf("%s\n %s\n %s\n %s\n %s\n", dt.sysname, dt.nodename, dt.release, dt.version, dt.machine);
}

