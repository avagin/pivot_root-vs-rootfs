#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mount.h>

int main(int argc, char **argv)
{
	int fd;

	fd = open("/proc/self/ns/mnt", O_RDONLY);
	if (fd < 0)
		return 1;
	umount2("/", MNT_DETACH);
	if (setns(fd, CLONE_NEWNS))
		return 1;

	if (argc > 1)
		execv(argv[1], &argv[1]);
	else
		execl("/bin/sh", "/bin/sh", "-i", NULL);
	return 1;
}
