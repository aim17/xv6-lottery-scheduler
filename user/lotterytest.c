#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"


void spin() {
    unsigned x = 0;
    unsigned y = 0;
    int pid = getpid();

    while (x < 100000) {
        y = 0;
        while (y < (10000)) {
            y++;
        }
        x++;
    }
}

void printpinfo(int pid)
{
	struct pstat pi = {0};
	getpinfo(&pi);
	int i;
    for (i = 0; i < NPROC; i++) {
        if(pi.pid[i] == pid) {
		    printf(0, "Number of tickets that PID %d has: %d\n", pid, pi.tickets[i]);
	        printf(0, "Number of ticks that PID %d has: %d\n", pid, pi.ticks[i]);
	        printf(0, "Is the process with PID %d in use? (0 or 1): %d\n", pid, pi.inuse[i]);
        }
    }
}

int
main(int argc, char *argv[])
{
    int pid1, pid2, pid3;
      
    if ((pid1 = fork()) == 0) {
        int pp1 = getpid();
	printf(0, "Process started with PID %d\n\n", pp1);
        settickets(10);
        spin();
	printpinfo(pp1);
        printf(0, "Process with PID %d finished!\n\n", pp1);
        exit(); 
    }
    else if ((pid2 = fork()) == 0) {
        int pp2 = getpid();
	printf(0, "Process started with PID %d\n\n", pp2);
        settickets(20);
        spin();
	printpinfo(pp2);
        printf(0, "Process with PID %d finished!\n\n", pp2);
        exit();
    }
    else if ((pid3 = fork()) == 0) {
        int pp3 = getpid();
	printf(0, "Process started with PID %d\n\n", pp3);
        settickets(30);
        spin();
	printpinfo(pp3);
        printf(0, "Process with PID %d finished!\n\n", pp3);
        exit();
    }
    wait();
    wait();
    wait();
    exit();
}
