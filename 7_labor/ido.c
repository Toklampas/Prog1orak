struct time
{
    int hour; int min; int sec;
};

typedef struct time time;

int time2sec(time t)
{
    int sum=0;
    sum += t.hour*60*60;
    sum += t.min*60;
    sum += t.sec;
    return sum;
}

time sec2time(int s)
{
    time t;
    s = s%86400;
    if (s < 0)
        s += 86400;
    t.hour = s/3600;
    s %= 3600;
    t.min = s/60;
    s %= 60;
    t.sec = s;
    return t;
}

time timeplus(time a, time b)
{
    int sum = time2sec(a)+time2sec(b);
    return sec2time(sum);
}

int timecmp(time a, time b)
{
    if (time2sec(a) < time2sec(b))
        return -1;
    else if (time2sec(a) > time2sec(b))
        return 1;
    else
        return 0;
}

void timereset(time *p)
{
    (*p).hour = 0;
    (*p).min = 0;
    (*p).sec = 0; 
}

int main(void)
{
    time workout_begins = {23, 15, 0};
    timereset(&workout_begins);
    return 0;
}

/*
#include <stdio.h>
int main()
{
    time workout_begins = {10, 15, 0};
    time workout_duration = {1, 40, 0};
    time workout_ends = timeplus(workout_begins, workout_duration);
    if (timecmp(workout_ends, workout_begins) < 0)
        printf("Hamarabb van vege, mint mikor kezdodik\n");
    return 0;
}
*/

/*
int main(void)
{
    time t1 = {2, 5, 0};
    int d = time2sec(t1);       // 7500
    time t2 = sec2time(6002);   // 1:40:02
    time t3 = sec2time(-600);   // 23:50:00
    return 0;
}
*/
