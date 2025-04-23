// Marina Perdiguero, 1705467, 10/20/2024. HW5, exercise 1: A program that encrypts and decrypts text using Caesar Cipher by shifting letters with a given key.

#include <stdio.h>
#include <string.h> // strlen()

/* Encrypt the first "length" characters of plaintext using Caesar Cipher encryption with the specified "key" value. 
   - Modify the plaintext parameter. 
   - Only apply the encryption on letters. 
   - Preserve the case of letters (uppercase to uppercase, and lowercase to lowercase).
   - Assume length <= the number of characters in plaintext
*/
void caesar_encrypt(char plaintext[], int length, int key);




/* Decrypt the first "length" characters of ciphertext that have been encrypted using Caesar encryption with the specified "key" value. 
   - Modify the ciphertext parameter. 
   - Only letters have been encrypted. 
   - Preserve the case of letters (uppercase to uppercase, and lowercase to lowercase).
   - Assume length <= the number of characters in ciphertext
*/
void caesar_decrypt(char ciphertext[], int length, int key);



/********************************/

int main(void) {
  int key = 10;
  char text[] = "No problem";
  
  caesar_encrypt(text, strlen(text), key);
  printf("After encryption: %s\n", text); // should be: Xy zbylvow.

  // call caesar_decrypt() to decrypt var "text" and print out the result.
  caesar_decrypt(text, strlen(text), key);
  printf("After decryption: %s\n", text); // should be: No problem.


}

/********************************/

// function definition of caesar_encrypt()
// Encrypt the first "length" characters of plaintext using Caesar Cipher encryption
void caesar_encrypt(char plaintext[], int length, int key) {
	int i;
    for (i = 0; i < length; i++) {
        char ch = plaintext[i];

        // Encrypt only letters
        if (ch >= 'A' && ch <= 'Z') {
            // Uppercase letter encryption
            plaintext[i] = ((ch - 'A' + key) % 26) + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            // Lowercase letter encryption
            plaintext[i] = ((ch - 'a' + key) % 26) + 'a';
        }
    }
}

// function definition of caesar_decrypt()
// Decrypt the first "length" characters of ciphertext using Caesar Cipher decryption
void caesar_decrypt(char ciphertext[], int length, int key) {
	int i;
    for (i = 0; i < length; i++) {
        char ch = ciphertext[i];

        // Decrypt only letters
        if (ch >= 'A' && ch <= 'Z') {
            // Uppercase letter decryption
            ciphertext[i] = ((ch - 'A' - key + 26) % 26) + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            // Lowercase letter decryption
            ciphertext[i] = ((ch - 'a' - key + 26) % 26) + 'a';
        }
    }
}



