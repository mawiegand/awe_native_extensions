#ifndef awe_native_extensions_MemoryManagement_h
#define awe_native_extensions_MemoryManagement_h

#ifndef SWIG
	#define AWE_registerNewObject(ptr, type) 
#else
	#define AWE_registerNewObject(ptr, type) SWIG_NewPointerObj(ptr, SWIGTYPE_p_ ## type, SWIG_POINTER_OWN)
#endif

#endif
