#ifndef awe_native_extensions_MemoryManagement_h
#define awe_native_extensions_MemoryManagement_h

#include <DamageLog.h>
#include <TestResult.h>

class DamageLog;
class TestResult;

namespace awe {

	class MemoryManagement {
		public:
			static void registerNewObject(DamageLog* obj);
			static void registerNewObject(TestResult* obj);
	};
#ifndef SWIG
	//#define aweRegisterNewObject(ptr, type)
	inline void MemoryManagement::registerNewObject(DamageLog* obj) {}
	inline void MemoryManagement::registerNewObject(TestResult* obj) {}
#else
	//struct swig_type_info;
	//VALUE SWIG_Ruby_NewPointerObj(void *ptr, swig_type_info *type, int flags);
	//#define aweRegisterNewObject(ptr, type) SWIG_Ruby_NewPointerObj((void*)ptr, SWIGTYPE_p_ ## type, SWIG_POINTER_OWN)
	//#define aweblabla(str) std::cout<<str<<std::endl;
#endif

};

#endif
