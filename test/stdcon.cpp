#include <vector_arg.hpp>
#include <list_arg.hpp>

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

BOOST_PYTHON_MODULE(stdcon) {
  py::def("sum", &sum);
  py::def("sum_rvalue", &sum_rvalue);
  py::def("sum_list", &sum_list);
  py::def("sum_list_rvalue", &sum_list_rvalue);
}
