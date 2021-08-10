import stdcon as c

l = [1, 2, 3]
assert c.sum([]) == 0
assert c.sum(l) == 6
assert c.sum_rvalue(l) == 6
assert c.sum_list(l) == 6
assert c.sum_list_rvalue(l) == 6
d = {0: 0.5, 1: 1.5}
assert c.map_ref(d, 0, 0) == 0.5
assert c.map_ref(d, 3, 2) == 2
assert c.map_ref_rvalue(d, 1, 0) == 1.5

print("Passed")
