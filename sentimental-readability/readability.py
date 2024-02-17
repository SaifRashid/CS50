from cs50 import get_string

text = get_string("Text: ")

letters = 0
words = 0
sentences = 0

for i in range((len(text))):
    if text[i].isalpha():
        letters += 1
    if text[i] == " ":
        words += 1
    if text[i] == "." or text[i] == "?" or text[i] == "!":
        sentences += 1
if letters > 0:
    words += 1

grade_level = 0.0588 * (letters/words*100) - 0.296 * (sentences/words*100) - 15.8
grade_level = int(grade_level + .5)
if grade_level < 1:
    print("Before Grade 1")
elif grade_level > 16:
    print("Grade 16+")
else:
    print("Grade", grade_level)