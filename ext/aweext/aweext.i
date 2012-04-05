%module aweext

%include std_string.i
%include std_vector.i
%include std_map.i

 %{
 /* Includes the header in the wrapper code */
 #include "../src/battle/BlaBla.h"
 %}
 
 /* Parse the header file to generate wrappers */
 %include "../src/battle/BlaBla.h"
