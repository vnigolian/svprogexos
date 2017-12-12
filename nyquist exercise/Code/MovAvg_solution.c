#include <stdio.h>
#include <stdlib.h>

#define N 10

void movAvg(float *in, float *out, int m) {
    int i, j;
    
    for (i = 0; i < N - m + 1; i++) {
        *(out + i) = 0;
        for (j = 0; j < m; j++) {
            *(out + i) += *(in + i + j);
        }
        *(out + i) /= m;
        printf("%.1f ", *(out + i));
    }    
}

void movAvgFull(float *in, float *out, int m) {
    int i, j;
        
    for (i = 0; i < N; i++) {
        *(out + i) = 0;
        for (j = 0; j < m; j++) {
            if ((i + j) >= N) *(out + i) += *(in + N - 1);
            else *(out + i) += *(in + i + j);
        }
        *(out + i) /= m;
        printf("%.1f ", *(out + i));
    }
}

int main(int argc, char* argv[]) {
    
    float samples[N] = {1,2,3,4,5,5,4,3,2,1};
    
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return 0;
    }
    
    int m = atoi(argv[1]);
    
    if ((m < 1) || (m > N)) {
        printf("Invalid argument value.\n");
        return 0;
    }
       
    printf("\n\n");

    printf("Moving average for m = %d...\n", m);
    float MovAvgOut[N - m + 1];
    movAvg(samples, MovAvgOut, m); 
    
    printf("\n\n");
    
    printf("Full moving average for m = %d...\n", m);
    float MovAvgFullOut[N];
    movAvgFull(samples, MovAvgFullOut, m); 
    
    printf("\n\n");
        
    return 0;
}