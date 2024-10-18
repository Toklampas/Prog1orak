enum colour{WHITE, RED, YELLOW, LIME, CYAN, BLUE, MAGENTA, BLACK};

struct rgb
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct rgb make_rgb(enum colour c)
{
    struct rgb out;    
    switch (c) {
        case WHITE:
            out.r = 255;
            out.g = 255;
            out.b = 255;
            break;
        case RED:
            out.r = 255;
            out.g = 0;
            out.b = 0;
            break;
        case YELLOW:
            out.r = 255;
            out.g = 255;
            out.b = 0;
            break;
        case LIME:
            out.r = 0;
            out.g = 255;
            out.b = 0;
            break;
        case CYAN:
            out.r = 0;
            out.g = 255;
            out.b = 255;
            break;
        case BLUE:
            out.r = 0;
            out.g = 0;
            out.b = 255;
            break;
        case MAGENTA:
            out.r = 255;
            out.g = 0;
            out.b = 255;
            break;
        case BLACK:
            out.r = 0;
            out.g = 0;
            out.b = 0;
            break;
    }
    return out;
}