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

time sec2time(int sec_since_midnight)
{
    int hour=0, min=0, sec=0;
    time t;
    sec = sec_since_midnight;
    if (sec_since_midnight > 0)
    {
        while (sec >= 60)
        {
            min++;
            sec -= 60;
        }
        while (min >=60)
        {
            hour++;
            min -= 60;
        }
    }
    else if (sec_since_midnight < 0)
    {
        hour = 23; min = 59; sec = 59;
        while (sec_since_midnight >= -60)
        {
            min--;
            sec -= 60;
        }
        while (min > 0)
        {
            hour--;
            min -= 60;
        }
    }
    
    t.hour = hour;
    t.min = min;
    t.sec = sec;
    return t;
}

int main(void)
{
    time t1 = {2, 5, 0};
    int d = time2sec(t1);       // 7500
    time t2 = sec2time(6002);   // 1:40:02
    time t3 = sec2time(-600);   // 23:50:00
    return 0;
}
