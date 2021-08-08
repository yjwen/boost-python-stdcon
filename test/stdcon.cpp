#include <vector_arg.hpp>

using namespace std;
namespace py = boost::python;
int sum(vector<int> const &vec)
{
  int i = 0;
  for (int v : vec) i += v;
  return i;
}

int sumrvalue(vector<int> &&vec)
{
  return sum(vec);
}

BOOST_PYTHON_MODULE(stdcon) {
  py::def("sum", &sum);
  py::def("sumrvalue", &sumrvalue);
}
