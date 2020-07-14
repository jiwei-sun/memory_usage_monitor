#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern int record_memory_usage(unsigned int pid,
		unsigned long sample_interval, unsigned long count);
void usage(char* name)
{
	printf("%s\n", name);
	printf("    -h,    help\n");
	printf("    -p,    pid\n");
	printf("    -c,    count\n");
	printf("    -i,    interval time\n");

	exit(0);
}

const char* my_opt = "hp:i:c:";

int main(int argc, char *argv[])
{
	int c;
	unsigned int pid = 0;
	unsigned long sample_interval = 60;
	unsigned long count = -1;

	while (1) {
		c = getopt(argc, argv, my_opt);
		if (c < 0)
			break;

		switch(c) {
			case 'p':
				pid = atol(optarg);
				break;
			case 'i':
				sample_interval = atol(optarg);
				break;
			case 'c':
				count = atol(optarg);
				break;
			default:
				usage(argv[0]);
				break;
		}
	}
	if (optind == 1)
		usage(argv[0]);

	record_memory_usage(pid, sample_interval, count);

	return 0;
}
