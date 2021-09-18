#include <vector_arg.hpp>
#include <pair_arg.hpp>

using namespace std;
namespace py = boost::python;

int first_at(vector<pair<int, float>> const &v, size_t idx)
{
  return v[idx].first;
}

int size_of_first(pair<vector<int>, float> const &v)
{
  return v.first.size();
}

void def_combined()
{
  py::def("first_at", &first_at);
  py::def("size_of_first", &size_of_first);
}

