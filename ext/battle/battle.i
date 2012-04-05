%module battle

%include std_string.i
%include std_vector.i
%include std_map.i

 %{
 /* Includes the header in the wrapper code */
 #include "../src/battle/UnitClass.h"
 #include "../src/battle/UnitType.h"
 #include "../src/battle/Army.h"
 #include "../src/battle/Force.h"
 #include "../src/battle/Fight.h"
 #include "../src/battle/BattleCalculator.h"
 #include "../src/battle/util/Random.h"
 %}
 
 /* Parse the header file to generate wrappers */
 %include "../src/battle/UnitClass.h"
 %include "../src/battle/UnitType.h"
 %include "../src/battle/Army.h"
 %include "../src/battle/Force.h"
 %include "../src/battle/Fight.h"
 %include "../src/battle/BattleCalculator.h"
 %include "../src/battle/util/Random.h"