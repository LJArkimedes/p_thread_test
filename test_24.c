#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

//线程标识符
static pthread_t G_test_f;
static pthread_t G_test_s;
static pthread_t G_test_t;

void *t_thread_f(void *args)
{
    while (1)
    {
        printf("thread_f is working now \n");
        sleep(1);
    }
}
void *t_thread_s(void *args)
{
    while (1)
    {
        printf("thread_s is working now \n");
        sleep(1);
    }
}
void *t_thread_t(void *args)
{
    while (1)
    {
        // printf("thread_t is working now \n");
        // sleep(10);
        for (int i = 0; i < 10; i++)
        {
            printf("thread_t_%d is working now\n", i);
            sleep(1);
        }
    }
}

int main()
{
    int res;

    pthread_attr_t thread_attr; // 设置线程属性
    struct sched_param thread_param_f;
    struct sched_param thread_param_t;
    struct sched_param thread_param_s;

    pthread_attr_init(&thread_attr);
    thread_param_f.sched_priority = 1;
    thread_param_s.sched_priority = 1;
    thread_param_t.sched_priority = 99;
    
    pthread_setschedparam(G_test_t, SCHED_FIFO, &thread_param_t);
    pthread_setschedparam(G_test_s, SCHED_OTHER, &thread_param_s);
    pthread_setschedparam(G_test_f, SCHED_OTHER, &thread_param_f);


    //设置线程
    res = pthread_create(&G_test_f, NULL, t_thread_f, NULL);
    if (res < 0)
    {
        printf("create thread_f failed \n");
    }

    res = pthread_create(&G_test_s, NULL, t_thread_s, NULL);
    if (res < 0)
    {
        printf("create thread_s failed \n");
    }

    res = pthread_create(&G_test_t, NULL, t_thread_t, NULL);
    if (res < 0)
    {
        printf("create thread_t failed \n");
    }

    
    //空主线程
    while (1)
    {
    }

    pthread_join(G_test_f, NULL); //会阻塞在这个函数里面直到对应线程完成
    pthread_join(G_test_s, NULL);
    pthread_join(G_test_t, NULL);

    // pthread_exit(0)://正常结束使用
}
