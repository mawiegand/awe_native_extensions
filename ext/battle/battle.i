%module battle

%include std_string.i
%include std_vector.i
%include std_map.i

 %{
 /* Includes the header in the wrapper code */
 #include "../src/battle/PriorityTest.h"
 #include "../src/battle/AlwaysSameTest.h"
 #include "../src/battle/CavalryTest.h"
 #include "../src/battle/UnitCategory.h"
 #include "../src/battle/Units.h"
 #include "../src/battle/Army.h"
 #include "../src/battle/Faction.h"
 #include "../src/battle/Battle.h"
 #include "../src/battle/BattleCalculator.h"
 #include "../src/battle/util/Random.h"
 %}
 
 /* Parse the header file to generate wrappers */
 %include "../src/battle/PriorityTest.h"
 %include "../src/battle/AlwaysSameTest.h"
 %include "../src/battle/CavalryTest.h"
 %include "../src/battle/UnitCategory.h"
 %include "../src/battle/Units.h"
 %include "../src/battle/Army.h"
 %include "../src/battle/Faction.h"
 %include "../src/battle/Battle.h"
 %include "../src/battle/BattleCalculator.h"
 %include "../src/battle/util/Random.h"

