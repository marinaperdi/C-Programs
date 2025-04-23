// Marina Perdiguero, 1705467, 9/30/2024. HW4, exercise 2: revised program from exercise 1 to allow inputting multiple numbers from keyboard until EOF

#include <stdio.h>
#include <math.h> // for sqrt()

#define MAX 20 // Define the maximum capacity for the array

// Function to input at most "limit" # of numbers from keyboard. 
// Return the actual number of items received
int input(double list[], int limit);

// Calculate and return the mean of a list of numbers. 
double get_mean(const double list[], int size);

//Calculate and return the population standard deviation of a list of numbers.   
double get_sdev(const double list[], int size);

// Print a list of numbers. 
void print_arr(const double list[], int size);


int main(void) {
  double numbers[MAX];
  int size = 0; // actual number of values
  
  printf("Input a list of numbers (at most %d items). Press CTRL+z on Windows and CTRL+d on MAC/Unix to end your input.\nEnter: ", MAX);
  size = input(numbers, MAX); // call input() to get numbers
  printf("\nReceived %d numbers.\n", size);

  printf("arr is: ");
  print_arr(numbers, size);
  printf("\n");

  // Call get_mean and get_sdev, then print the results
  if (size>0) {
  	double mean = get_mean(numbers, size);
	double sdev = get_sdev(numbers, size);
	
	printf("  mean: %.6f\n", mean);
  	printf("  standard deviation: %.6f\n", sdev);
  } else {
  	printf("No numbers entered.\n");
  }
}


// Function to input at most "limit" # of numbers from keyboard. 
// Return the actual number of items received
int input(double list[], int limit) {
    int count = 0;
    while (count < limit) {
        if (scanf("%lf", &list[count]) != 1) {
            break; // Stop input on EOF or invalid input
        }
        count++;
    }
    return count;
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
