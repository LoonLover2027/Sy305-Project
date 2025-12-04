#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

void catchkill(int sig, siginfo_t *info, void *uc)
{
	int childio = getpid();
	printf("child_io = %d\n", childio);
}
int main(void)
{
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = catchkill;
	sigaction(SIGUSR1, &sa, NULL);
	while(1)
	{
		sleep(1);
	}
	
	return 0;
}
	
