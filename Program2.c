// Marina Perdiguero, 1705467, 11/10/2024. HW6, exercise 2: write a program for managing contacts. 

#include <stdio.h>  // printf, scanf
#include <stdlib.h> // malloc, realloc, free, exit, NULL
#include <string.h> // strlen, strcpy

/* display menu on screen */
void display_menu(void);

/* Prints size number of strings, one per line. */
void print_contacts(char *strlist[], int size);

/* Add one more contact to the contact list */
char **add_contact(char **strlist, int *psize);

/* free up space allocated to dynamic string array strlist */
void free_str_arr(char *strlist[], int size);

// declaration of search_str()
/* search for name in strlist (contains "size" strings). Case-sensitive search.
 * Return 1 if found, otherwise, return 0 */
int search_str(char **strlist, int size, const char *name);

//--------------------------

int main(void) {
  char **contacts = NULL; // store a list of contacts (just names at this point)
  int size = 0;           // track the number of contacts in the list

  int choice = -1;
  do {
    display_menu();

    char **result = NULL; // store the returned result of add_contact()
    scanf("%d", &choice);
    switch (choice) {
    case 0:
      puts("End the system. Bye!");
      break;
    case 1:
      result = add_contact(contacts, &size);
      if (result == NULL) {
        free_str_arr(contacts, size); // free up heap space
        exit(1);
      } else {
        contacts = result;
      }
      break;
    case 2:
      print_contacts(contacts, size);
      break;
    default:
      puts("Invalid choice. Try again.");
    }
  } while (choice != 0);

  free_str_arr(contacts, size); // free up heap space
} // end main()

//--------------------------

/* display menu on screen */
void display_menu(void) {
  char *menu_strs[] = {"\n=========================\n",
                       "Contact Management System\n",
                       "\n",
                       "1. Add a new contact\n",
                       "2. Display contacts\n",
                       "3. Search for a contact\n",
                       "4. Delete a contact\n",
                       "0. Exit\n",
                       "Enter your choice (0~4): "};

  int length =
      sizeof(menu_strs) / sizeof(char *); // number of strings in menu_strs
  int i;
  for (i = 0; i < length; i++) {
    printf("%s", menu_strs[i]);
  }
}

//--------------------------

// Add one more contact to the contact list
char **add_contact(char **strlist, int *psize) {
  // strlist is a string array
  // strlist[i] is a string, 0<= i < *psize

  // Input a new contact.
  char name[100];
  printf("Enter one contact (LastName, FirstName): ");
  while (getchar() != '\n'); // consume '\n' at the end of line
  

  if (1 != scanf("%[^\n]s", name)) {
    printf("Error: contact input failed.\n");
    return NULL; // failed to input a name string
  }

  // call search_str() to check if the name is already in the
  // list. if yes, directly return strlist

  // check for duplicates and don't add
	if (search_str(strlist, *psize, name)) {
    printf("Error: Contact already exists.\n");
    return strlist; // do not add duplicate
  }


  // Resize the dynamic string array to add one more spot.

  declare a local var "count" of int, set it to be 1 more than the value pointed
  by psize

  declare a local var "new_strlist" of char** type and set it to NULL. (Later it
  will point to a reallocated string array)

  call realloc() on "strlist" to reallocate a new char** of size count *
  sizeof(char*), assign the returned value to your local char** var
  "new_strlist".

  check the return value of realloc() to see if it is NULL. if so, print an
  error message and return NULL.*/
  
  int count = *psize + 1;
  char **new_strlist = realloc(strlist, count * sizeof(char *));
  if (new_strlist == NULL) {
    printf("Error: Memory allocation failed.\n");
    return NULL;
  }
  strlist=new_strlist;

  // allocate space for the new contact
  /*declare a local var of char* to point to a newly allocated dynamic char array
  that's long enough to hold the string in local var "name"

  check the return value of malloc() to see if it is NULL. if so, print an error
  message and return NULL.*/
  
  new_strlist[*psize] = malloc(strlen(name) + 1);
  if (new_strlist[*psize] == NULL) {
    printf("Error: Memory allocation for contact name failed.\n");
    return NULL;
  }

  // add the new contact
  strcpy(new_strlist[*psize], name);
  (*psize)++; // Increase the size of the contact list

  printf("%s has been added.\n", name);
  
  // Return the newly allocated array on success
  return new_strlist;
}

//--------------------------

/* Prints size number of strings, one per line. */
void print_contacts(char *strlist[], int size) {
  printf("You have %d contacts: [\n", size);
  int i;
  for (i = 0; i < size; i++) {
    printf("%s\n", strlist[i]);
  }
  printf("]\n");
}

//--------------------------

/* free up space allocated to dynamic string array strlist */
void free_str_arr(char *strlist[], int size) {
  // Loop through each spot in strlist
  int i;
  for (i = 0; i < size; i++) {
    free(strlist[i]); // Free each string in the array
    strlist[i] = NULL; // Set each element to NULL
  }

  // Deallocate strlist itself
  free(strlist);
  strlist = NULL; // Set the main array pointer to NULL
}

//--------------------------

// definition of search_str()
/* search for name in strlist (contains "size" strings). 
   Case-sensitive search i.e. "Steve, Tom" is different from "Steve, tom".
 * Return 1 if found, otherwise, return 0 */

/* Algorithm for the function:

loop through each string in strlist
  if "name" matches the string at [i] // use strcmp() from <string.h>
    return 1 // found
  end if
end loop

// if we get here, we didn't find "name" in strlist
return 0 

*/

int search_str(char **strlist, int size, const char *name) {
	int i;
  for (i = 0; i < size; i++) {
    if (strcmp(strlist[i], name) == 0) {
      return 1; // Found the contact
    }
  }
  return 0; // Not found
}
