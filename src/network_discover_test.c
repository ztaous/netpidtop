#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_number(const char *str)
{
	while (*str) {
		if (*str < '0' || *str > '9')
			return 0;
		str++;
	}
	return 1;
}

int count_process_sockets(int pid)
{
	char fd_path[256];
	snprintf(fd_path, sizeof(fd_path), "/proc/%d/fd", pid);

	DIR *fd_dir = opendir(fd_path);
	if (!fd_dir)
		return -1;

	int socket_count = 0;
	struct dirent *fd_entry;

	while ((fd_entry = readdir(fd_dir)) != NULL) {

		if (is_number(fd_entry->d_name)) {
			printf("%s\n", fd_entry->d_name);
		}
	}
}

int main()
{
	printf("=== Test ===\n\n");

	DIR *proc = opendir("/proc");
	if (!proc) {
		printf("Cannot open /proc");
		return 1;
	}
	printf("opened /proc\n");

	// firefox pid = 4108 (testing)
	count_process_sockets(4108);

	closedir(proc);
	return 0;
}
