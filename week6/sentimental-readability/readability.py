import cs50

# Promt input
text = cs50.get_string("Text: ")


def count_letters(text):
    count = 0
    for char in text:
        if char.isalpha():
            count += 1
    return count


def count_words(text):
    return len(text.split())


def count_sentences(text):
    count = 0
    for char in text:
        if char in {'.', '!', '?'}:
            count += 1
    return count


# Calculate Grade
def grade(text):
    # count number of letters, words and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Compute Coleman-Liau index
    L = (letters / words) * 100
    s = (sentences / words) * 100
    index = 0.0588 * L - 0.296 * s - 15.8

    # Round index into nearest whole number
    X = round(index)

    # Print Grade
    if X in range(1, 17):
        print(f"Grade {X}")
    elif index < 1:
        print("Before Grade 1")
    else:
        print("Grade 16+")


# Print Grade
grade(text)
