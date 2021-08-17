import stdcon as c

l = [1, 2, 3]
assert c.vsum([]) == 0
assert c.vsum(l) == 6
assert c.vsum_rvalue(l) == 6
assert c.vsum_cref(l) == 6
assert c.lsum(l) == 6
assert c.lsum_rvalue(l) == 6
assert c.lsum_cref(l) == 6

d = {0: 0.5, 1: 1.5}
assert c.map_find(d, 0, 0) == 0.5
assert c.map_find_cref(d, 3, 2) == 2
assert c.map_find_rvalue(d, 1, 0) == 1.5

assert c.hashmap_find(d, 0, 0) == 0.5
assert c.hashmap_find_cref(d, 3, 2) == 2
assert c.hashmap_find_rvalue(d, 1, 0) == 1.5

s = {0, 1, 2}
fs = frozenset(s)
assert c.set_element_of(s, 0) == True
assert c.set_cref_element_of(fs, 4) == False
assert c.set_rvalue_element_of(fs, 1) == True

print("Passed")
