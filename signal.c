#if 0
// alarm
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int sig)
{
    sig = sig;
    alarm_fired = 1;
}

int main()
{
    pid_t pid;
    printf("alarm application starting\n");
    pid = fork();
    switch (pid) {
        case -1:
            perror("fork failed\n");
            break;
        case 0:
            sleep(2);
            printf("child pid is %d, parent pid is %d\n", getpid(), getppid());
            sleep(2);
            kill(getppid(), SIGALRM);
            exit(0);
        }
    printf("waiting for alarm to go off\n");
    (void)signal(SIGALRM, ding);

    pause();
    if (alarm_fired) {
        printf("Ding!\n");
    }

    printf("Done\n");
    exit(0);
}
#endif

#if 1
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void ouch(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
}

int main()
{
    struct sigaction act;
    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, 0);

    while (1) {
        printf("Hello World!\n");
        sleep(1);
    }

    return 0;
}
#endif
