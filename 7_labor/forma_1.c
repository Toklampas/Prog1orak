typedef struct {
    int pole_position;
    double best_lap;
} qr;

typedef struct {
    int racing_number;
    char name[4];
    qr qualifying_results[3];
} pilot;

pilot t[2] = {
        {1, "MSC", {{1, 67.423},{3, 46.735},{1, 70.264}}},
        {2, "MAS", {{2, 67.433},{5, 46.855},{3, 70.317}}}
    };