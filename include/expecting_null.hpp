#ifndef __BOOST_PYTHON_STDCON_EXPECTING_NULL_INCLUDED__
#define __BOOST_PYTHON_STDCON_EXPECTING_NULL_INCLUDED__
namespace boost::python::converter {
  struct expecting_null
  {
    static PyTypeObject const *get_pytype() {return nullptr;}
  };
}
#endif
