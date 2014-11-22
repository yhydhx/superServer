#include <unistd.h>
#include <sys/types.h>

uid_t uid,euid;
gid_t gid,egid;

uid = getuid();
euid = geteuid();
gid = getgid();
egid = getegid();
