import stdcon as c

l123 = [1, 2, 3]
assert c.sum([]) == 0
assert c.sum([1, 2, 3]) == 6
assert c.sumrvalue([1, 2, 3]) == 6
print("Passed")
