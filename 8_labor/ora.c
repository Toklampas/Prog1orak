typedef struct clock {
    unsigned hour;
    unsigned minute;
    unsigned second;
} clock;

clock make_clock(unsigned int hour, unsigned int min, unsigned int sec)
{
    clock c;
    c.hour = hour;
    c.minute = min;
    c.second = sec;
    return c;
}

void step_clock(clock *c)
{
    if ((*c).second++ >= 59)
    {
        (*c).second = 0;
        if ((*c).minute++ >= 59)
        {
            (*c).minute = 0;
            if ((*c).hour++ >= 23)
            {
                (*c).hour = 0;
                (*c).minute = 0;
                (*c).second = 0;
            }
        }
    }
    return;
}

int main()
{
    clock c;
    c.hour = 23; c.minute=59; c.second=58;
    step_clock(&c);
    return 0;
}