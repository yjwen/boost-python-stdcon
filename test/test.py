import stdcon as c

l123 = [1, 2, 3]
assert c.sum([]) == 0
assert c.sum([1, 2, 3]) == 6
assert c.sum_rvalue([1, 2, 3]) == 6
assert c.sum_list([4, 5, 6]) == 15
assert c.sum_list_rvalue([4, 5, 6]) == 15

print("Passed")
