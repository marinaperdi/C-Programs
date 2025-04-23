// Marina Perdiguero, 1705467, 9/30/2024. HW4, exercise 1: calculate the mean and standard deviation of a list of numbers

#include <stdio.h>
#include <math.h> // for sqrt()

// Calculate and return the mean of a list of numbers. 
double get_mean(const double list[], int size);

//Calculate and return the population standard deviation of a list of numbers.   
double get_sdev(const double list[], int size);

// Print a list of numbers. 
void print_arr(const double list[], int size);


int main(void) {
  double numbers[] = {43, 74, 35, 82, 71, 67, 53, 32, 91, 43};
  int size = sizeof(numbers) / sizeof(numbers[0]);  // actual number of values

  printf("arr is: ");
  print_arr(numbers, size);
  printf("\n");

  // Call get_mean and get_sdev, then print the results
  double mean = get_mean(numbers, size);
  double sdev = get_sdev(numbers, size);

  printf("  mean: %.6f\n", mean);
  printf("  standard deviation: %.6f\n", sdev);

}



// Function to calculate and return the mean
double get_mean(const double list[], int size) {
    double sum = 0.0;
    int i;
    for (i = 0; i < size; i++) {
        sum += list[i];
    }
    return sum / size;
}

// Function to calculate and return the population standard deviation
double get_sdev(const double list[], int size) {
    double mean = get_mean(list, size);
    double sum_deviation = 0.0;
    int i;
    for (i = 0; i < size; i++) {
        sum_deviation += pow(list[i] - mean, 2);
    }
    return sqrt(sum_deviation / size);  // Population standard deviation formula
}

// Print a list of numbers. 
void print_arr(const double list[], int size) {
  printf("[");
  if (size <= 0) {  // optional
    printf("] (size %d)", size);
    return;  // end here
  }
  
  // now at least one element
  printf("%f", list[0]);
  int i;
  for (i = 1; i < size; i++) {
    printf(", %f", list[i]);
  }
  printf("]");
}
