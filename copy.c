#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if(argc < 3)
	{
		printf("Usage : %s <src file> <dst file>\n", argv[0]);
		return -1;
	}

	int rf, wf;
	char* buf;
	int cnt;

	if((rf = open(argv[1], O_RDONLY)) == -1) {
		printf("Error Src file open %s\n", argv[1]);
		return -1;
	}

	else {

		if(access(argv[2], F_OK) == -1)	{
			if((wf = open(argv[2], O_WRONLY| O_CREAT| O_TRUNC, 0664)) == -1) {
				printf("Error Dst file open %s\n", argv[2]);
				close(rf);
				return -1;
			}
		}
		else {
			wf = open(argv[2], O_WRONLY);
		}
		buf = malloc(4096);

		while((cnt = read(rf, buf, 4096))) {
			printf("Writing...\n");
			if(write(wf, buf, cnt)) continue;
			else {
				printf("Wirte Error %s\n", argv[2]);
				close(wf);
				close(rf);
				free(buf);
				return -1;
			}
		}
		free(buf);
	}
	printf("Copy is done.\n");
	close(wf);
	close(rf);
	return 0;
}