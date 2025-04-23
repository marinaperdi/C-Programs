// Marina Perdiguero, 1705467, 11/17/2024. HW7, exercise 1: This program manages and processes order records by inputting data, printing records, and generating reports on order and product subtotals.

#include <stdio.h>
#define MAX 100  // maximum number of records in orders data file

/* inputs at most "limit" records of order records 
*/
int input_orders(int order_arr[], int product_arr[], int quantity_arr[], float price_arr[], int limit);


/* Prints "size" records of order id, product id, ordered quantity, and price.
   Prints an error msg and aborts printing if "size" <= 0
*/
void print_orders(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size);


/* Prints subtotals per order (quantity * price accumulated for the same order). 
   Returns 1 if successful, 0 otherwise.
*/
int print_order_report(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size);

int print_product_report(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size);

//----------------------------

int main(void) {
  int orders[MAX];     // store order ids
  int products[MAX];   // store product ids
  int quantities[MAX]; // store ordered quantities
  float prices[MAX];   // store product prices
  int size = 0;

  size = input_orders(orders, products, quantities, prices, MAX);
  print_orders(orders, products, quantities, prices, size);

  print_order_report(orders, products, quantities, prices, size);
  print_product_report(orders, products, quantities, prices, size);

}

//----------------------------

/* inputs at most "limit" records of order records:
   - each record includes an order id, product id, ordered quantity and product id. 
   - The records will be stored in four parallel arrays order_arr, product_arr, quantity_arr, and price_arr. 
   - order id, product id, ordered quantity, and price from the same order will be saved in the same spot in each of those four arrays starting from index 0.
 
   The function returns the number of records successfully input. 
*/
int input_orders(int order_arr[], int product_arr[], int quantity_arr[], float price_arr[], int limit) {
  
  FILE *file = fopen("orders.txt", "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file 'orders.txt'.\n");
        return 0;
    }
  int size = 0;
  printf("Input your orders (at most %d records of <orderid>, <productid>, <quantity>, <price>).", limit);
  printf("Press CTRL+z on Windows and CTRL+d on Mac/UNIX to end your input.\n");
  printf("Enter: ");
  while (size < limit && fscanf(file, "%d,%d,%d,%f", &order_arr[size], &product_arr[size], &quantity_arr[size], &price_arr[size]) == 4) {
    size++;
  }
  fclose(file);
  return size;
}

//----------------------------

/* Prints "size" records of order id, product id, ordered quantity, and price.
   Prints an error msg and aborts printing if "size" <= 0
*/
void print_orders(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size) {
  if (size < 0) {
    fprintf(stderr, "\nError: invalid size %d. Abort print.\n", size);
    return;
  }

  if (size == 0) {
    fprintf(stderr, "\nWarning: empty array (size is 0). Abort print.\n");
    return;
  }

  // now size > 0
  printf("\nOrderID | ProductID | Quantity | Price\n"); // header
  printf("----------------------------------------\n");
  int i;
  for (i=0; i<size; i++) {
    printf("%d | %d | %d | $%.2f\n", order_arr[i], product_arr[i], quantity_arr[i], price_arr[i]);
  }
  printf("----------------------------------------\n");
}

//----------------------------

/* Prints subtotals per order (quantity * price accumulated for the same order). 
   Returns 1 if successful, 0 otherwise.
*/

int print_order_report(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size) {
  
  /* == algorithm ==
  check and handle size<=0

  // Now at least one record
  process [0] and print test record // first order id
  loop to process [1] ~ [size-1]
    if orderid [i] == order id[i-1] // same order id, accumulate
      calculate and accumulate
    else // a new order id
      print the subtotal result of last order id // the last orderid has ended
      restart calculation for this new order id
    end if 
    test print for this record
  end loop
  print the subtotal result of the last order id // didn't get to print in the loop
  */

    // Check for invalid size
	if (size <= 0) {
        fprintf(stderr, "Error: Invalid size %d. No records to process.\n", size);
        return 0;
    }

    float subtotal = 0.0;  // Initialize subtotal for each order
    int current_order_id = order_arr[0];  // Start with the first order ID
    
    // Print header for the report
    printf("Report - subtotals per order\n");
    printf("--------------------\n");
    printf("OrderID | Subtotal\n");

	// Loop through each order
	int i;
    for (i = 0; i < size; i++) {
        if (order_arr[i] == current_order_id) {
        	float item_total = quantity_arr[i] * price_arr[i];
            printf("test - %d | %d | $%.2f * %d = $%.2f\n", order_arr[i], product_arr[i], price_arr[i], quantity_arr[i], item_total);
            subtotal += item_total;
        } else {
            printf("%d | $%.2f\n", current_order_id, subtotal); // Print previous order subtotal
            current_order_id = order_arr[i];
            subtotal = quantity_arr[i] * price_arr[i]; // Reset subtotal for new order
        	
			float item_total = subtotal;
            printf("test - %d | %d | $%.2f * %d = $%.2f\n", order_arr[i], product_arr[i], price_arr[i], quantity_arr[i], item_total);
        
		}
    }

    // Print the subtotal for the last order
    printf("%d | $%.2f\n", current_order_id, subtotal);
    printf("------------------\n");

    return 1; // Successful
}

//----------------------------


int print_product_report(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size) {
/* == algorithm ==  
Check and return 0 on invalid size parameter.

// [need a loop]
First, scan product_arr to generate a list of unique product ids.
  // may store them in a new array, static or dynamic

// [need a nested loop]
// Now use this list of unique product ids to scan the arrays
Loop through the list of unique product ids // outer loop
  // one product id from the unique list
  subtotal <- 0
  Loop through the param arrays // inner loop
    sum up quantity * price of one record [for this product id]
    test print
  End inner loop
  Print subtotal result for this product id
End outer loop

return 1 for success 
*/

    // Check for invalid size
    if (size <= 0) {
        fprintf(stderr, "Error: Invalid size %d. No records to process.\n", size);
        return 0;
    }

    // Identify unique product IDs
    int unique_products[MAX];
    int unique_count = 0;

    // Scan for unique product IDs
    int i;
    for (i = 0; i < size; i++) {
        int is_unique = 1;
        int j;
        for (j = 0; j < unique_count; j++) {
            if (product_arr[i] == unique_products[j]) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            unique_products[unique_count++] = product_arr[i];
        }
    }

    // Print header for the report
    printf("Report - subtotals per product\n");
    printf("--------------------\n");
    printf("ProductID | Subtotal\n");

    // Loop through the unique product IDs
    int k;
    for (k = 0; k < unique_count; k++) {
        int product_id = unique_products[k];
        float subtotal = 0.0;

        // Loop through all records for the current product
        int q;
        for (q = 0; q < size; q++) {
            if (product_arr[q] == product_id) {
                // Calculate and accumulate the subtotal for this product
                float item_total = quantity_arr[q] * price_arr[q];

                // Test print for each item processed (product, quantity, price, calculation)
                printf("test - %d | %d | $%.2f * %d = $%.2f\n", order_arr[q], product_id, price_arr[q], quantity_arr[q], item_total);

                // Accumulate the subtotal
                subtotal += item_total;
            }
        }

        // Print the subtotal for this product
        printf("%d | $%.2f\n", product_id, subtotal);
    }

    printf("--------------------\n");

    return 1; // Success
}

