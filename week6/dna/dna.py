import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # Read database file into a variable
    db_rows = []
    with open(sys.argv[1]) as database:
        db = csv.DictReader(database)
        for row in db:
            db_rows.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequence_file:
        sequence = sequence_file.read().strip()

    # Get list of STRs (keys in the database except for 'name')
    str_names = db.fieldnames[1:]

    # Find longest match of each STR in DNA sequence
    longest_str_matches = {}
    for str_name in str_names:
        longest_str_matches[str_name] = longest_match(sequence, str_name)

    # Check database for matching profiles
    match = check_database_for_match(db_rows, longest_str_matches, str_names)

    if match:
        print(match)
    else:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    return longest_run


def check_database_for_match(db_rows, longest_str_matches, str_names):
    """Compares the longest STR matches with each profile in the database."""

    for person in db_rows:
        match = True
        for str_name in str_names:
            if int(person[str_name]) != longest_str_matches[str_name]:
                match = False
                break
        if match:
            return person['name']

    return None


main()
