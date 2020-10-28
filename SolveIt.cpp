#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double eps = 0.00000001;

double equation(vector <int> nums, double x){
    double aux1 = nums[0] * exp((-1)*x);
    double aux2 = nums[1] * sin(x) + nums[2] * cos(x) + nums[3] * tan(x);
    double aux3 = nums[4] * pow(x, 2);
    return aux1 + aux2 + aux3 + nums[5];
}

double bisection(vector <int> nums, double low, double high){
    while (high - low > eps) {
        double center = (low + high) / 2;
        if (equation(nums, low) * equation(nums, center) <= 0){
            high = center;
        } else {
            low = center;
        }
    }
    return (low + high)/2;
}

int main() {
    int aux;

    while (scanf("%d", &aux) != EOF ) {
        vector <int> nums;
        nums.push_back(aux);
        for (int i = 0; i < 5; i++){
            scanf("%d", &aux);
            nums.push_back(aux);
        }

        if (equation(nums, 0) * equation(nums, 1) > 0) printf("No solution\n");
        else {
            double solution = bisection(nums, 0, 1);
            printf("%.4f\n", solution);
        }
    }

    return 0;
}