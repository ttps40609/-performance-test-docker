#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define msleep(x) usleep(x*1000)//函式庫只有usleep而沒有msleep，所以用此種方法取代
pthread_mutex_t exec_mutex;//mutex變數，因為要讓兩個thread使用，所以要設為全域

void *thread_for() { 
int i=0;
while(1)
{ 
pthread_mutex_lock(&exec_mutex);
i++;
pthread_mutex_unlock(&exec_mutex);
// printf("thread_function is running. i= %d\n",i);
}
pthread_exit("Thank you for the CPU time");
}

 

int main(int argc ,char *argv[]) {
//printf("argv is %s\n",argv[1]);

float load = atoi(argv[1])*0.01;//要的負載
int res;
int load_sample_time=atoi(argv[2]);//CPU負載取樣時間
int busy_time;
int rest_time; 
if(load<=0.5) //不知道為何算起來會有誤差，因此用這種方法將誤差取消
{
busy_time=load_sample_time*load;
rest_time=load_sample_time-busy_time;
}
else
{
rest_time=load_sample_time*(1-load);
busy_time=load_sample_time-rest_time;//(load)*load_sample_time;
}
pthread_mutex_init(&exec_mutex,NULL);//初始化mutex

printf("load=%f,busy_time=%d,rest_time=%d\n",load,busy_time,rest_time);
pthread_mutex_lock(&exec_mutex);//取得mutex
pthread_t for_thread;//thread變數

res = pthread_create(&for_thread, NULL, thread_for, NULL);//產生另一個thread
if (res != 0) {
perror("Thread creation failed");
exit(EXIT_FAILURE);
}

while(1)
{//w
pthread_mutex_unlock(&exec_mutex);
msleep(busy_time); 
pthread_mutex_lock(&exec_mutex);
msleep(rest_time);
}//w

exit(EXIT_SUCCESS);
}
