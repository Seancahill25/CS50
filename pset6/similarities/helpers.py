from nltk.tokenize import sent_tokenize
def lines(a, b):
    linesA = set(a.split("\n"))
    linesB = set(b.split("\n"))

    return linesA & linesB

def sentences(a, b):
    sentencesA = set(sent_tokenize(a))
    sentencesB = set(sent_tokenize(b))

    return sentencesA & sentencesB

def substringLength(str, n):
    substrings = []

    for i in range(len(str) - n + 1):
        substrings.append(str[i:i + n])

    return substrings

def substrings(a, b, n):
    substringsA = set(substringLength(a, n))
    substringsB = set(substringLength(b, n))

    return substringsA & substringsB