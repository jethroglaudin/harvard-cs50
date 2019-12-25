from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    # TODO
    # Take in string inputs a,b
    # Split each string into lines
    # Comput a list of all lines that appear in both a and b
    # Finally return that list

    a_lines = set(a.splitlines())
    b_lines = set(b.splitlines())
    # print(a_lines)

    return list(a_lines.intersection(b_lines))


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO
    # split each string into sentences
    # calculate the list of sentenes appearing in both a & b

    sentences_a = set(sent_tokenize(a, language="english"))
    sentences_b = set(sent_tokenize(b, language="english"))
    # print()
    # print()
    # print(sentences_b)

    return list(sentences_a.intersection(sentences_b))


def make_sub(str, n):
    substring_list = []
    str = str.replace("\n", "")
    # initializer
    x = 0
    # we want to keep spitting out each substring for the entire file

    for x in range(len(str) - n + 1):
        substring_list.append(str[x:x+n])
    return substring_list


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # TODO
    # take in string inputs a , b and lenght n
    # split eawch string into all substrings by length n

    # print(make_sub(a, n))
    # print(make_sub(b, n))

    sub_a = set(make_sub(a, n))
    sub_b = set(make_sub(b, n))

    # result = set()
    # result = sub_a.intersection(sub_b)

    print("print", list(sub_a.intersection(sub_b)))
    return list(sub_a.intersection(sub_b))