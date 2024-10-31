typedef struct {
    double x;
    double y;
} point;

typedef struct{
    int hour;
    int minute;
    int second;
} time;

typedef struct{
    point position;
    time interval;
} record;

int in_seconds(time t)
{
    return t.second+t.minute*60+t.hour*60*60;    
}

#include <math.h>

double distance(point a, point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double average_speed(record records[], int n)
{
    double sum_dist = 0, sum_time = 0;
    for(int i = 0; i < n-1; i++)
    {    
        sum_dist += distance(records[i].position, records[i+1].position);
        sum_time += in_seconds(records[i+1].interval);
    }
    return sum_dist/sum_time;
}

int main()
{
    point p1 = {-2.8, 3.14};
    point p2 = {5.2, 0.14};
    time t1 = {0, 2, 0};
    time t2 = {0, 5, 0};
    record records[2] = {{p1, t1},{p2, t2}};
    int seconds = in_seconds(t1);
    printf("t1 másodpercekben: %d\n", seconds);
    double dist = distance(p1, p2);
    printf("p1 és p2 közötti távolság: %.2f\n", dist);
    double avg_speed = average_speed(records, 2);
    printf("Átlagos sebesség: %.2f egység/másodperc\n", avg_speed);
    return 0;
}