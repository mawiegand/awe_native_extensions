#ifndef awe_native_extensions_ErrorHandling_h
#define awe_native_extensions_ErrorHandling_h

#include <DataException.h>

#ifndef SWIG
# define awePtrCheck(ptr) if((ptr) == 0)throw new DataException(__FILE__, __LINE__, __FUNCTION__ ,"null pointer");
#else
# define awePtrCheck(ptr) if((ptr) == 0)SWIG_exception(SWIG_NullReferenceError, "null pointer");
#endif

#ifndef SWIG
# define aweError(err) throw new DataException(__FILE__, __LINE__, __FUNCTION__ ,err);
#else
# define aweError(err) SWIG_exception(SWIG_RuntimeError, err);
#endif

#endif
