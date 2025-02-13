#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Promt user for some text

    string text = get_string("Text: ");

    // Count number of letters, words and sentences

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute Coleman-Liau index
    float L = ((float) letters / (float) words) * 100;
    float S = ((float) sentences / (float) words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Round index to nearest whole number
    int rounded_grade = round(index);

    // Print Grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (rounded_grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", rounded_grade);
    }
}

int count_letters(string text)
{
    // Return number of letters

    int count = 0;

    // Loop and iterate over every character in the array

    for (int i = 0; text[i] != '\0'; i++)
    {
        // Check if character is alphabetic
        if (isalpha(text[i]) && text[i] != ' ')
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    // Return Number of words

    int count = 0;

    // Loop and iterate over every character in the array

    for (int i = 0; text[i] != '\0'; i++)
    {
        // Check if character is blank(space)
        if (isblank(text[i]))
        {
            count++;
        }
    }
    // no.of Words == no.of blanks +1
    return count + 1;
}

int count_sentences(string text)
{
    // Return the number of sentences in text

    int count = 0;

    // Loop and iterate over every character in the array

    for (int i = 0; text[i] != '\0'; i++)
    {
        // Check if character is ./!/?
        if ((text[i]) == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
