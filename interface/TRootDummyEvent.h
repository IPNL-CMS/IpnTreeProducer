#include "TObject.h"
#include "TList.h"

class dummyparticle : public TObject
{
   public :
      dummyparticle():value(0){}
      dummyparticle(int val):value(val){}
      int value;
      ClassDef(dummyparticle,1);
};

class dummyevent : public TObject
{
   public :
      dummyevent(){list=new TList();}
      ~dummyevent()
      {
         list->Delete();
         delete list;
      }
      void add_value(int val) {list -> AddLast(new dummyparticle(val));}

      TList* list;

      ClassDef(dummyevent,1);
};
