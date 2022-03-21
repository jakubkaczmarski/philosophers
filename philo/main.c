#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
void *myturn(void *arg)
{
    int i = 0;
    int *iptr = (int*)arg;
    while(i < 5)
    {
        i++;
        sleep(1);
        printf("My turn\n");
        (*iptr)++;
    }
}
void yourturn()
{ 
    int i = 0;
    while(i < 2)
    {
        i++;
        sleep(2);
        printf("Your turn\n");
    }
}
int main(void)
{
    int v = 0;
    pthread_t newthread;

    pthread_create(&newthread, NULL, myturn, &v);
    pthread_join(newthread, NULL);
    printf("%d",v);
    // myturn();
    yourturn();
}