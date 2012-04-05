require 'mkmf'

#copy the source files into this folder
FileUtils.cp(Dir['../src/**/*.cpp'], '.')

#execute swig to generate the wrapper classes
%x[swig -ruby -c++ aweext.i]

LIBDIR      = Config::CONFIG['libdir']
INCLUDEDIR  = Config::CONFIG['includedir']
 
HEADER_DIRS = [
  "../src",

  # First search /opt/local for macports
  '/opt/local/include',
 
  # Then search /usr/local for people that installed from source
  '/usr/local/include',
 
  # Check the ruby install locations
  INCLUDEDIR,
 
  # Finally fall back to /usr
  '/usr/include',
]
 
LIB_DIRS = [
  # First search /opt/local for macports
  '/opt/local/lib',
 
  # Then search /usr/local for people that installed from source
  '/usr/local/lib',
 
  # Check the ruby install locations
  LIBDIR,
 
  # Finally fall back to /usr
  '/usr/lib',
]
 
dir_config('stree', HEADER_DIRS, LIB_DIRS)

create_makefile('awe_native_extensions/aweext')