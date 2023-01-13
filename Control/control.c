#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#define STR_SIZE 256

volatile sig_atomic_t sigint_flag = 0;

void signal_handler(int, siginfo_t*, void*);
void show_time(void);

int main(void) {
	struct sigaction sa_signal;
	
	memset(&sa_signal, 0, sizeof(sa_signal));
	sa_signal.sa_sigaction = signal_handler;
	sa_signal.sa_flags = SA_SIGINFO;
	
	if ( sigaction(SIGINT, &sa_signal, NULL) < 0 ) {
		exit(1);
	}
	if ( sigaction(SIGTERM, &sa_signal, NULL) < 0 ) {
		exit(1);
	}
	
	while ( !sigint_flag ) {
		show_time();
		usleep(100);
	}
	printf("\n");
	printf("\x1b[31m");
	printf("\x1b[1m");
	if (sigint_flag == SIGINT) {
		printf("SIGINT");
	} else if (sigint_flag == SIGTERM) {
		printf("SIGTERM");
	} else {
		printf("SIGNAL");
	}
	printf("\x1b[39m");
	printf("\x1b[0m");
	printf("\n");
	
	printf("Exit\n");
	
	return 0;
}

void show_time(void) {
	char date[STR_SIZE];
	time_t t;
	time(&t);
	strftime(date, sizeof(date), "%Y/%m/%d %a %H:%M:%S", localtime(&t));
	printf("\r%s", date);
	fflush(stdout);
} 

void signal_handler(int sig, siginfo_t *info, void *ctx) {
	sigint_flag = sig;
}