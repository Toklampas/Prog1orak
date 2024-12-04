#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int hour;
    int minute;
} time;

typedef struct {
    int id;
    time time;
    int jelleg;
} train;

train *read (char *fajlnev, int *size)
{
    int n;
    FILE *file = fopen(fajlnev, "r");
    if (file == NULL) return NULL;
    fscanf(file, "%d", &n);
    train *trains = (train*)malloc(n * sizeof(train));
    for (int i = 0; i<n; i++)
    {
        fscanf(file, "%d %d:%d %d", &trains[i].id, &trains[i].time.hour, &trains[i].time.minute, &trains[i].jelleg);
    }
    fclose(file);
    *size = n;
    return trains;
}

int compare(const void *a, const void *b)
{
    train *trainA = (train *)a;
    train *trainB = (train *)b;
    if (trainA->id != trainB->id)
        return trainA->id - trainB->id;
    if (trainA->time.hour != trainB->time.hour)
        return trainA->time.hour - trainB->time.hour;
    return trainA->time.minute - trainB->time.minute;
}

int nterminal(train *trains, int n)
{
    qsort(trains, n, sizeof(train), compare);
    int count = 0;
    for (int i = 0; i < n;)
    {
        int j = i + 1;
        while (j < n && trains[j].id == trains[i].id)
        {
            trains[i].jelleg = trains[j].jelleg;
            j++;
        }
        if (trains[i].jelleg == 0)
            count++;
        i = j;
    }
    return count;
}

