#include<stdio.h> #including important libraries
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include <pthread.h>
int x=0;
void capture() #to capture the colliding node via timestamp
{
exit(0);
}
int get() #to get the colliding node
{
return x;
}
void put() #counter for increasing the channel no.
{
x++;
}
void node(char *p) #node creation
{
int name;
int seq1,seq2,i=0;
long t;
struct timeval tv; #timestamp setting
struct timezone tz; #system time note
name=atoi(p); #for printing of variable time
while(1) #infinite while loop
{
seq1=get(); #sequence initiation
seq2=get(); #sequence initiation
if(seq1==seq2) #check for same timestamp
{
put();
seq1=get(); #compare timestamp
gettimeofday(&tv,&tz);
printf("station %d transmitting frame %d at %ld \n",name,++i,tv,tz); #print stations
usleep(10); #sleep time
seq2=get(); #compare timestamp
if(seq1!=seq2) #if not equal timestamp
{
printf("station %d collision occurred %d \n",name,i--); #print information
usleep(100); #sleep time
}
else
{
printf("station %d transmission of frame %d success \n",name,i); #print stations
}
}
usleep(200000); #system sleep
}
}
main()
{
pthread_t t1,t2,t3;
signal(SIGINT,capture);
pthread_create(&t1,0,(void *)node,"1"); #thread creation 1
pthread_create(&t2,0,(void *)node,"2"); #thread creation 2
pthread_create(&t3,0,(void *)node,"3"); #thread creation 3
while(1);
}