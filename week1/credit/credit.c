#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number, orginalnumber;
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
    int x, y, total, check, fnum, snum;
    int counter = 0;

    // Promting user
    number = get_long("Number: ");
    orginalnumber = number;

    // checking if number is negative
    if (number > 0)
    {

        // checking number of digits
        do
        {
            counter++;
            number /= 10;
        }
        while (number != 0);

        // if 16 digits
        if (counter == 16)
        {
            // Check first number
            fnum = (orginalnumber / 1000000000000000) % 10;

            // Check second number
            snum = (orginalnumber / 100000000000000) % 10;

            // Isolating The single Digits
            a = orginalnumber % 10;
            b = orginalnumber % 100 / 10;
            c = orginalnumber % 1000 / 100;
            d = orginalnumber % 10000 / 1000;
            e = orginalnumber % 100000 / 10000;
            f = orginalnumber % 1000000 / 100000;
            g = orginalnumber % 10000000 / 1000000;
            h = orginalnumber % 100000000 / 10000000;
            i = orginalnumber % 1000000000 / 100000000;
            j = orginalnumber % 10000000000 / 1000000000;
            k = orginalnumber % 100000000000 / 10000000000;
            l = orginalnumber % 1000000000000 / 100000000000;
            m = orginalnumber % 10000000000000 / 1000000000000;
            n = orginalnumber % 100000000000000 / 10000000000000;
            o = orginalnumber % 1000000000000000 / 100000000000000;
            p = orginalnumber % 10000000000000000 / 1000000000000000;

            // Checksum

            // multiply ever other number by 2 and add them
            b *= 2;
            d *= 2;
            f *= 2;
            h *= 2;
            j *= 2;
            l *= 2;
            n *= 2;
            p *= 2;

            // add indivigual digits of the product together

            b = b % 10 + b / 10;
            d = d % 10 + d / 10;
            f = f % 10 + f / 10;
            h = h % 10 + h / 10;
            j = j % 10 + j / 10;
            l = l % 10 + l / 10;
            n = n % 10 + n / 10;
            p = p % 10 + p / 10;

            x = b + d + f + h + j + l + n + p;

            // Sum of other digits
            y = a + c + e + g + i + k + m + o;

            // Checking if Totals last digit is 0

            total = x + y;
            check = total % 10;

            // Print card Type
            if (check == 0 && fnum == 4)
            {
                printf("VISA\n");
            }
            else if (check == 0 && fnum == 5 && (snum >= 1 && snum <= 5))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }

            // If 15 digits
        }
        else if (counter == 15)
        {
            // Check first number
            fnum = (orginalnumber / 100000000000000) % 10;

            // Check second number
            snum = (orginalnumber / 10000000000000) % 10;

            // Isolating The single Digits
            a = orginalnumber % 10;
            b = orginalnumber % 100 / 10;
            c = orginalnumber % 1000 / 100;
            d = orginalnumber % 10000 / 1000;
            e = orginalnumber % 100000 / 10000;
            f = orginalnumber % 1000000 / 100000;
            g = orginalnumber % 10000000 / 1000000;
            h = orginalnumber % 100000000 / 10000000;
            i = orginalnumber % 1000000000 / 100000000;
            j = orginalnumber % 10000000000 / 1000000000;
            k = orginalnumber % 100000000000 / 10000000000;
            l = orginalnumber % 1000000000000 / 100000000000;
            m = orginalnumber % 10000000000000 / 1000000000000;
            n = orginalnumber % 100000000000000 / 10000000000000;
            o = orginalnumber % 1000000000000000 / 100000000000000;

            // Checksum

            // multiply ever other number by 2 and add them
            b *= 2;
            d *= 2;
            f *= 2;
            h *= 2;
            j *= 2;
            l *= 2;
            n *= 2;

            // add indivigual digits of the product together

            b = b % 10 + b / 10;
            d = d % 10 + d / 10;
            f = f % 10 + f / 10;
            h = h % 10 + h / 10;
            j = j % 10 + j / 10;
            l = l % 10 + l / 10;
            n = n % 10 + n / 10;

            x = b + d + f + h + j + l + n;

            // Sum of other digits
            y = a + c + e + g + i + k + m + o;

            // Checking if Totals last digit is 0

            total = x + y;
            check = total % 10;

            // Print card Type
            if (check == 0 && fnum == 3 && (snum == 4 || snum == 7))
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }

            // If 13 digits
        }
        else if (counter == 13)
        {
            // Check first number
            fnum = (orginalnumber / 1000000000000) % 10;

            // Check second number
            snum = (orginalnumber / 100000000000) % 10;

            // Isolating The single Digits
            a = orginalnumber % 10;
            b = orginalnumber % 100 / 10;
            c = orginalnumber % 1000 / 100;
            d = orginalnumber % 10000 / 1000;
            e = orginalnumber % 100000 / 10000;
            f = orginalnumber % 1000000 / 100000;
            g = orginalnumber % 10000000 / 1000000;
            h = orginalnumber % 100000000 / 10000000;
            i = orginalnumber % 1000000000 / 100000000;
            j = orginalnumber % 10000000000 / 1000000000;
            k = orginalnumber % 100000000000 / 10000000000;
            l = orginalnumber % 1000000000000 / 100000000000;
            m = orginalnumber % 10000000000000 / 1000000000000;

            // Checksum

            // multiply ever other number by 2 and add them
            b *= 2;
            d *= 2;
            f *= 2;
            h *= 2;
            j *= 2;
            l *= 2;

            // add indivigual digits of the product together

            b = b % 10 + b / 10;
            d = d % 10 + d / 10;
            f = f % 10 + f / 10;
            h = h % 10 + h / 10;
            j = j % 10 + j / 10;
            l = l % 10 + l / 10;

            x = b + d + f + h + j + l;

            // Sum of other digits
            y = a + c + e + g + i + k + m;

            // Checking if Totals last digit is 0

            total = x + y;
            check = total % 10;

            // Print card Type
            if (check == 0 && fnum == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
