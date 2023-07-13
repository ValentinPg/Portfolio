# https://www.hackerrank.com/challenges/one-month-preparation-kit-sparse-arrays/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one


def matchingStrings(strings, queries):
    cont = 0
    q = []
    for query in queries:
        cont = 0
        for string in strings:
            if (query == string):
                cont+=1
        q.append(cont)
    return q