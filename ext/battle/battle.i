%module battle

%include std_string.i
%include std_vector.i
%include std_map.i

%exceptionclass DataException;

 %{
 /* Includes the header in the wrapper code */
 #include "../src/battle/DataException.h"
 #include "../src/battle/PriorityTest.h"
 #include "../src/battle/NoTest.h"
 #include "../src/battle/LineSizeTest.h"
 #include "../src/battle/UnitCategory.h"
 #include "../src/battle/Unit.h"
 #include "../src/battle/Army.h"
 #include "../src/battle/Faction.h"
 #include "../src/battle/Battle.h"
 #include "../src/battle/BattleCalculator.h"
 #include "../src/battle/util/Random.h"
 %}
 
 %trackobjects;
 
 %markfunc Battle "mark_Battle";
 %markfunc Faction "mark_Faction";
 %markfunc Army "mark_Army";
 %markfunc UnitCategory "mark_UnitCategory";
 
 /* Parse the header file to generate wrappers */
 %include "../src/battle/DataException.h"
 %include "../src/battle/PriorityTest.h"
 %include "../src/battle/NoTest.h"
 %include "../src/battle/LineSizeTest.h"
 %include "../src/battle/UnitCategory.h"
 %include "../src/battle/Unit.h"
 %include "../src/battle/Army.h"
 %include "../src/battle/Faction.h"
 %include "../src/battle/Battle.h"
 %include "../src/battle/BattleCalculator.h"
 %include "../src/battle/util/Random.h"
 
 %header %{

static void mark_Battle(void* ptr) {
 Battle* battle = (Battle*) ptr;

 /* Loop over each object and tell the garbage collector
 that we are holding a reference to them. */
 {
   std::vector<UnitCategory*>::iterator it;
   for(it = battle->categories.begin(); it != battle->categories.end(); it++) {
     UnitCategory* category = (*it);
     VALUE object = SWIG_RubyInstanceFor(category);

     if (object != Qnil) {
       rb_gc_mark(object);
     }
   }
 }
 {
   std::vector<Faction*>::iterator it;
   for(it = battle->factions.begin(); it != battle->factions.end(); it++) {
     Faction* faction = (*it);
     VALUE object = SWIG_RubyInstanceFor(faction);

     if (object != Qnil) {
       rb_gc_mark(object);
     }
   }
 }
}

static void mark_Faction(void* ptr) {
 Faction* faction = (Faction*) ptr;

 /* Loop over each object and tell the garbage collector
 that we are holding a reference to them. */
 {
   std::vector<Army*>::iterator it;
   for(it = faction->armies.begin(); it != faction->armies.end(); it++) {
     Army* army = (*it);
     VALUE object = SWIG_RubyInstanceFor(army);

     if (object != Qnil) {
       rb_gc_mark(object);
     }
   }
 }
}

static void mark_Army(void* ptr) {
 Army* army = (Army*) ptr;

 /* Loop over each object and tell the garbage collector
 that we are holding a reference to them. */
 {
   std::vector<Unit*>::iterator it;
   for(it = army->units.begin(); it != army->units.end(); it++) {
     Unit* unit = (*it);
     VALUE object = SWIG_RubyInstanceFor(unit);

     if (object != Qnil) {
       rb_gc_mark(object);
     }
   }
 }
}

static void mark_UnitCategory(void* ptr) {
 UnitCategory* category = (UnitCategory*) ptr;

 /* Loop over each object and tell the garbage collector
 that we are holding a reference to them. */
 
 PriorityTest* test = category->test;
 VALUE object = SWIG_RubyInstanceFor(test);

 if (object != Qnil) {
   rb_gc_mark(object);
 }
}
%}


