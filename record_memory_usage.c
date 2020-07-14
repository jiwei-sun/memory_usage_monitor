//#include <sys/types.h>
//#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int record_memory_usage(unsigned int pid,
		        unsigned long sample_interval, unsigned long count)
{
	char *buf = NULL;
	char *tmp_buf = NULL;
	char *token = NULL;
	char file_name[64] = {0};
	int proc_fd, log_fd;
	unsigned long time_stamp = time(NULL);
	unsigned long len = 0;

	buf = malloc(1024 * sizeof(char));
	if (!buf) {
		printf("error malloc\n");
		return -1;
	}

	log_fd = open("./status.log", O_WRONLY | O_CREAT | O_TRUNC, 00666);
	if (log_fd == -1) {
		printf("error open\n");
		return -1;
	}

	sprintf(file_name, "/proc/%d/comm", pid);
	proc_fd = open(file_name, O_RDONLY);
	if (proc_fd == -1) {
		printf("error open\n");
		return -1;
	}
	len = read(proc_fd, buf, 1024);
	if (len == -1) {
		printf("error read\n");
		return -1;
	}
	write(log_fd, buf, strlen(buf));
	close(proc_fd);

	sprintf(buf, "Sample Begin time stamp:%ld\n", time_stamp);
	write(log_fd, buf, strlen(buf));
	sprintf(buf, "Sample interval time:%ld Sec\n", sample_interval);
	write(log_fd, buf, strlen(buf));

	sprintf(file_name, "/proc/%d/status", pid);

	while (count--) {
		proc_fd = open(file_name, O_RDONLY);
		if (proc_fd == -1) {
			printf("error open\n");
			return -1;
		}
		memset(buf, 0x0, 1024);

		len = read(proc_fd, buf, 1024);
		if (len == -1) {
			printf("error read\n");
			return -1;
		}

		token = strtok(buf, "\n");
		while (token) {
			tmp_buf = strstr(token, "Vm");
			if (tmp_buf) {
				write(log_fd, tmp_buf, strlen(tmp_buf));
				write(log_fd, "\n", 1);
			}
			token = strtok(NULL, "\n");
		}
		sleep(sample_interval);
		close(proc_fd);
	}

	free(buf);
	close(log_fd);

	return 0;
}
