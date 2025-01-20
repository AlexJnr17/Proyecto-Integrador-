#include <stdio.h>

#define ROWS 2 
#define COLS 7 

double weighted_average(double values[], double weights[], int size) {
    double total_weight = 0;
    double weighted_sum = 0;
    for (int i = 0; i < size; i++) {
        total_weight += weights[i];
        weighted_sum += values[i] * weights[i];
    }
    return total_weight != 0 ? weighted_sum / total_weight : 0;
}

void calculate_weighted_prediction(double history[ROWS][COLS], int rows, int cols, double predictions[]) {
    for (int i = 0; i < rows; i++) {
        double weights[COLS];
        for (int j = 0; j < cols; j++) {
            weights[j] = j + 1; 
        }
        predictions[i] = weighted_average(history[i], weights, cols);
    }
}

int main() {
    double history[ROWS][COLS] = {
        {400, 50, 30, 20, 25.0, 10.0, 60.0}, 
        {380, 45, 28, 18, 24.0, 12.0, 55.0}  
    };
    double predictions[ROWS]; 

    calculate_weighted_prediction(history, ROWS, COLS, predictions);

    for (int i = 0; i < ROWS; i++) {
        printf("Prediccion para el conjunto %d: %.2f\n", i + 1, predictions[i]);
    }

    return 0;
}
