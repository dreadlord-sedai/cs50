
#include <cs50.h>
#include <stdio.h>


int main (void)
{
    string name = get_string("What's your name ? ");
    string age = get_string("What's your age ? ");
    string number = get_string("Whats your number ? ");

    printf("Age is %s\n. Name is %s.\n Phone is : %s.\n",age ,name ,number);


}

