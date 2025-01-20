#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA 100

typedef struct {
    float co2;
    float so2;
    float no2;
    float pm25;
    float temperature;
    float wind_speed;
    float humidity;
} AirData;

void linear_regression(const float x[], const float y[], int n, float *m, float *b) {
    float sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0;
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }
    float denominator = (n * sum_x2 - sum_x * sum_x);
    if (denominator == 0) {
        *m = 0;
        *b = 0;
    } else {
        *m = (n * sum_xy - sum_x * sum_y) / denominator;
        *b = (sum_y - (*m) * sum_x) / n;
    }
}

void calculate_regression_prediction(const AirData history[], int size) {
    float co2_levels[MAX_DATA], temp_levels[MAX_DATA];
    for (int i = 0; i < size; i++) {
        co2_levels[i] = history[i].co2;
        temp_levels[i] = history[i].temperature;
    }
    float m, b;
    linear_regression(temp_levels, co2_levels, size, &m, &b);
    printf("Prediccion por regresion lineal (CO2 vs Temp): y = %.2fx + %.2f\n", m, b);
}

int main() {
    AirData history[] = {
        {400, 50, 30, 20, 25.0, 10.0, 60.0},
        {420, 55, 35, 22, 26.0, 12.0, 65.0},
        {430, 60, 40, 23, 27.0, 14.0, 70.0}
    };
    int size = sizeof(history) / sizeof(history[0]);

    calculate_regression_prediction(history, size);
    return 0;
}
