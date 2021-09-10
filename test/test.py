import stdcon as c

l = [1, 2, 3]
assert c.vpack([]) == 0
assert c.vpack(l) == 123
assert c.vpack_rvalue(l) == 123
assert c.vpack_cref(l) == 123
assert c.lpack(l) == 123
assert c.lpack_rvalue(l) == 123
assert c.lpack_cref(l) == 123
assert c.flpack(l) == 123
assert c.flpack_rvalue(l) == 123
assert c.flpack_cref(l) == 123

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

assert c.hashset_element_of(s, 0) == True
assert c.hashset_cref_element_of(fs, 4) == False
assert c.hashset_rvalue_element_of(fs, 1) == True

assert c.icpair_equal0((1, 'c'), (1, 'c')) == True
assert c.icpair_equal1((1, 'c'), (2, 'b')) == False

assert c.tuple1_get0((1,)) == 1
assert c.tuple2_get1((1, 'c')) == 'c'
assert c.tuple3_get2((1, 'c', 'foo')) == 'foo'
print("Passed")
