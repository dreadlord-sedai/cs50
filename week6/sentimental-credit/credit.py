import cs50
import re
import sys

# Prompt and check card number


def ask_number():
    number = cs50.get_string("Number: ")

    # Check if the input matches the required digit length
    if re.fullmatch(r"\d{13,16}", number):
        return number
    else:
        return "INVALID\n"

# Calculate the checksum using the Luhn algorithm


def checksum(number):
    total_sum = 0
    position = 0

    # Process digits from right to left
    for digit in reversed(number):
        n = int(digit)

        # If position is odd (0-based indexing)
        if position % 2 == 1:
            n *= 2

            # Add the digits of the product together
            total_sum += n // 10 + n % 10
        else:
            total_sum += n

        position += 1

    # Return True if checksum is valid (last digit is 0)
    return total_sum % 10 == 0

# Determine the card type based on the number


def card_type(number):
    length = len(number)
    first_digit = int(number[0])
    second_digit = int(number[1]) if length > 1 else 0

    # Check card type based on length and first digits
    if (length == 13 or length == 16) and first_digit == 4:
        return "VISA\n"
    elif length == 16 and first_digit == 5 and 1 <= second_digit <= 5:
        return "MASTERCARD\n"
    elif length == 15 and first_digit == 3 and (second_digit == 4 or second_digit == 7):
        return "AMEX\n"
    else:
        return "INVALID\n"


def main():
    # Get the card number from the user
    number = ask_number()

    # Check if the input was invalid and exit
    if number == "INVALID\n":
        sys.exit(number)

    # Validate the card number using Luhn's algorithm
    if checksum(number):
        # Identify and print the card type
        print(card_type(number), end='')  # Using end='' to avoid double newline
    else:
        print("INVALID\n", end='')  # Ensure consistent formatting


if __name__ == "__main__":
    main()
