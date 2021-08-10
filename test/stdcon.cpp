#include <vector_arg.hpp>
#include <list_arg.hpp>
#include <map_arg.hpp>

using namespace std;
namespace py = boost::python;
int sum(vector<int> const &vec)
{
  int i = 0;
  for (int v : vec) i += v;
  return i;
}

int sum_rvalue(vector<int> &&vec)
{
  return sum(vec);
}

int sum_list(list<int> const &l)
{
  int i = 0;
  for (int v : l) i += v;
  return i;
}

int sum_list_rvalue(list<int> &&l)
{
  return sum_list(l);
}

float map_ref(map<int, float> const &m, int k, float v)
{
  auto it = m.find(k);
  if (it != m.end())
    return it->second;
  else
    return v;
}

float map_ref_rvalue(map<int, float> &&m, int k, float v)
{
  return map_ref(m, k, v);
}

BOOST_PYTHON_MODULE(stdcon) {
  py::def("sum", &sum);
  py::def("sum_rvalue", &sum_rvalue);
  py::def("sum_list", &sum_list);
  py::def("sum_list_rvalue", &sum_list_rvalue);
  py::def("map_ref", &map_ref);
  py::def("map_ref_rvalue", &map_ref_rvalue);
}
