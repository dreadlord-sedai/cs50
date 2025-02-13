#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int validate_key(string argv[]);
string encipher(string argv[], string plaintext);

int main(int argc, string argv[])
{

    // Check number of cmd line arguments
    if (argc == 2)
    {
        // Validate key
        if (validate_key(argv) == 0)
        {
            // Ask for Plaintext if key is valid
            string plaintext = get_string("Plaintext: ");

            // Encipher
            string ciphertext = encipher(argv, plaintext);

            // Print cypher text
            printf("ciphertext: %s\n", ciphertext);

            return 0;
        }
    }
    else
    {
        // Print instructions
        printf("Usage: ./substitution key\n");
        return 1;
    }
    return 1;
}

int validate_key(string argv[])
{
    // Array to keep track of encountered characters
    char encountered[26] = {0};

    // Check if there are only 26 characters in the key
    if (strlen(argv[1]) == 26)
    {
        // Check if character is alphabetical
        for (int i = 0; i < 26; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Key Must Contain 26 Alphabatical characters.\n");
                return 1;
            }

            // Convert character to upper
            char c = toupper(argv[1][i]);

            // Check if character is repeated (Case-sensitive)
            if (encountered[c - 'A'])
            {
                printf("Key Must Contain 26 Non-Repeating characters.\n");
                return 1;
            }

            // Mark the character as encountered
            encountered[c - 'A'] = 1;
        }
        // Key is Valid
        return 0;
    }
    else
    {
        printf("Key Must Contain 26 characters.\n");
        return 1;
    }
}

string encipher(string argv[], string plaintext)
{
    // Initialize ciphertext variable with same size of plaintext
    string ciphertext = plaintext;

    // iterate over ever character in plaintext
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Is alphabetic ?
        if (isalpha(plaintext[i]))
        {

            // Is Upper or lower
            if (isupper(plaintext[i]))
            {
                // Map the letter using the key (UPPER)
                int index = plaintext[i] - 'A';
                ciphertext[i] = toupper(argv[1][index]);
            }
            else if (islower(plaintext[i]))
            {
                // Map the letter using the key (LOWER)
                int index = plaintext[i] - 'a';
                ciphertext[i] = tolower(argv[1][index]);
            }
        }
        // Is non-alphabatic
        else
        {
            // Leave as it is
            ciphertext[i] = plaintext[i];
        }
    }

    // Properly terminate the string
    ciphertext[strlen(plaintext)] = '\0';

    return ciphertext;
}
