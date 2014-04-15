/*
 * SYSCALL_DEFINE3(open, const char __user *, filename, int, flags, int, mode)
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "sanitise.h"
#include "shm.h"
#include "utils.h"
#include "compat.h"

static const unsigned long o_flags[] = {
	O_EXCL, O_NOCTTY, O_TRUNC, O_APPEND,
	O_NONBLOCK, O_SYNC, O_ASYNC, O_DIRECTORY,
	O_NOFOLLOW, O_CLOEXEC, O_DIRECT, O_NOATIME,
	O_PATH, O_DSYNC, O_LARGEFILE, O_TMPFILE,
};

static unsigned long get_o_flags(void)
{
	unsigned long mask = 0;
	unsigned long bits;
	unsigned int i, num;

	num = ARRAY_SIZE(o_flags);

	bits = rand() % (num + 1);      /* num of bits to OR */

	for (i = 0; i < bits; i++)
		mask |= o_flags[rand() % num];

	return mask;
}

static void sanitise_open(int childno)
{
	unsigned long flags;

	flags = get_o_flags();

	shm->syscall[childno].a2 |= flags;
}

struct syscallentry syscall_open = {
	.name = "open",
	.num_args = 3,
	.arg1name = "filename",
	.arg1type = ARG_PATHNAME,
	.arg2name = "flags",
	.arg2type = ARG_OP,
	.arg2list = {
		.num = 4,
		.values = { O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, },
	},
	.arg3name = "mode",
	.arg3type = ARG_MODE_T,
	.sanitise = sanitise_open,
};

static void sanitise_openat(int childno)
{
	unsigned long flags;

	flags = get_o_flags();

	shm->syscall[childno].a3 |= flags;
}

/*
 * SYSCALL_DEFINE4(openat, int, dfd, const char __user *, filename, int, flags, int, mode)
 */
struct syscallentry syscall_openat = {
	.name = "openat",
	.num_args = 4,
	.arg1name = "dfd",
	.arg1type = ARG_FD,
	.arg2name = "filename",
	.arg2type = ARG_PATHNAME,
	.arg3name = "flags",
	.arg3type = ARG_OP,
	.arg3list = {
		.num = 4,
		.values = { O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, },
	},
	.arg4name = "mode",
	.arg4type = ARG_MODE_T,
	.flags = NEED_ALARM,
	.sanitise = sanitise_openat,
};
