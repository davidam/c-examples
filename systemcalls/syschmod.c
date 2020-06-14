#include <unistd.h>
#include <linux/syscall.h>
#include <errno.h>

int rc;

rc = syscall(SYS_chmod, "lala", 0444);

if (rc == -1)
   fprintf(stderr, "chmod failed, errno = %d\n", errno);

