#include <signal.h>
#include <stdio.h>
//sigint = ^C, sigquit = ^\,
void got_the_blody_signal(int n)
{
signal(SIGQUIT, got_the_blody_signal);
printf(" gotcha!! your (%d) signal is useless \n", n);
signal(SIGINT, got_the_blody_signal);
printf(" gotcha!! your access (%d) signal is useless \n", n);
}

int main()
{
signal(SIGQUIT, got_the_blody_signal);
signal(SIGINT, got_the_blody_signal);
printf(" kill me now !! \n");
for(;;);
}