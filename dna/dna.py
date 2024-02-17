import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: dna database.csv sequence.txt")
    # TODO: Read database file into a variable
    database_file = open(sys.argv[1], "r")
    # TODO: Read DNA sequence file into a variable
    sequence_file = open(sys.argv[2], "r")
    sequence = sequence_file.read()
    # TODO: Find longest match of each STR in DNA sequence
    database_read = csv.reader(database_file)
    database = []
    for row in database_read:
        database.append(row)


    # TODO: Check database for matching profiles
    longest_match_list = []
    for i in range(1, len(database[0])):
        longest_match_list.append(longest_match(sequence, database[0][i]))

    checker = False
    for i in range(1, len(database)):
        for j in range(len(longest_match_list)):
            if int(database[i][j + 1]) == int(longest_match_list[j]):
                checker = True
            else:
                checker = False
                break
        if checker == True:
            print(database[i][0])
            return
    print("No match")
    return


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
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
