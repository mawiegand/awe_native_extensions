%module battle

%include std_string.i
%include std_vector.i
%include std_map.i

%exceptionclass DataException;

 %{
 /* Includes the header in the wrapper code */
 #include "../src/battle/DataException.h"
 #include "../src/battle/DamageLog.h"
 #include "../src/battle/TestResult.h"
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
 #include "../src/battle/util/MemoryManagement.h"
 #include "../src/battle/util/ErrorHandling.h"
 %}
 
 %trackobjects;
 
 %markfunc Battle "mark_Battle";
 %markfunc Faction "mark_Faction";
 %markfunc Army "mark_Army";
 %markfunc UnitCategory "mark_UnitCategory";
 %markfunc Unit "mark_Unit";
 
 /* Parse the header file to generate wrappers */
 %include "../src/battle/DataException.h"
 %include "../src/battle/DamageLog.h"
 %include "../src/battle/TestResult.h"
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
 #include <iostream>
 
//#include "../src/battle/util/MemoryManagement.h"
namespace awe {
	void MemoryManagement::registerNewObject(DamageLog* obj) {
		SWIG_Ruby_NewPointerObj((void*)obj, SWIGTYPE_p_DamageLog, SWIG_POINTER_OWN);
	}
	void MemoryManagement::registerNewObject(TestResult* obj) {
		SWIG_Ruby_NewPointerObj((void*)obj, SWIGTYPE_p_TestResult, SWIG_POINTER_OWN);
	}
}
 
static void mark_Battle(void* ptr) {
 //std::cout<<"GCLOG Battle MARK"<<std::endl;
 Battle* battle = (Battle*) ptr;
 //std::cout<<"GCLOG Battle MARK 1"<<std::endl;
 /* Loop over each object and tell the garbage collector
 that we are holding a reference to them. */
 {
   std::vector<UnitCategory*>::iterator it;
   //std::cout<<"GCLOG Battle MARK 2"<<std::endl;
   //it = battle->categories.begin();
   //std::cout<<"GCLOG Battle MARK 3"<<std::endl;
   for(it = battle->categories.begin(); it != battle->categories.end(); it++) {
     //std::cout<<"GCLOG Battle MARK 3.1 --> category "<<std::endl;
     UnitCategory* category = (*it);
     VALUE object = SWIG_RubyInstanceFor(category);
	 //std::cout<<"GCLOG Battle MARK --> category "<<category<<std::endl;
     if (object != Qnil) {
       rb_gc_mark(object);
     }
   }
 }
 {
   //std::cout<<"GCLOG Battle MARK 3"<<std::endl;
   std::vector<Faction*>::iterator it;
   for(it = battle->factions.begin(); it != battle->factions.end(); it++) {
     Faction* faction = (*it);
     VALUE object = SWIG_RubyInstanceFor(faction);
     //std::cout<<"GCLOG Battle MARK --> faction "<<faction<<std::endl;
     if (object != Qnil) {
       rb_gc_mark(object);
     }
   }
 }
 //std::cout<<"GCLOG Battle MARK DONE"<<std::endl;
}

static void mark_Faction(void* ptr) {
 //std::cout<<"GCLOG Faction MARK"<<std::endl;
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
 //Test Results
  {
   std::map<int, TestResult*>::iterator it;
   for(it = faction->testResults.begin(); it != faction->testResults.end(); it++) {
     TestResult* result = it->second;
     VALUE object = SWIG_RubyInstanceFor(result);

     if (object != Qnil) {
       rb_gc_mark(object);
     }
   }
 }
}

static void mark_Army(void* ptr) {
 //std::cout<<"GCLOG Army MARK "<<ptr<<std::endl;
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
 //std::cout<<"GCLOG UnitCategory MARK"<<std::endl;
 UnitCategory* category = (UnitCategory*) ptr;

 /* Loop over each object and tell the garbage collector
 that we are holding a reference to them. */
 
 PriorityTest* test = category->test;
 VALUE object = SWIG_RubyInstanceFor(test);

 if (object != Qnil) {
   rb_gc_mark(object);
 }
}

static void mark_Unit(void* ptr) {
  //std::cout<<"GCLOG Unit MARK"<<std::endl;
 Unit* unit = (Unit*) ptr;

 /* Loop over each object and tell the garbage collector
 that we are holding a reference to them. */
 
 std::vector<std::vector<DamageLog*> >::iterator it0;
 for (it0 = unit->damageLogs.begin(); it0 != unit->damageLogs.end(); it0++) {
  std::vector<DamageLog*>::iterator it1;
  for (it1 = it0->begin(); it1 != it0->end(); it1++) {
	DamageLog* logentry = (*it1);
	VALUE object = SWIG_RubyInstanceFor(logentry);
	
    if (object != Qnil) {
     rb_gc_mark(object);
    }
  }
 }
}
%}


