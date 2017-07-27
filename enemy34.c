/*enemy2.c*/
#include<enemy34.h>
#include<movingobject.h>
#include<object.h>

static object* obj34[3];

static void onestep34(movingobject* mobj){
  if(((mobj ->cnt)/6)%4){
    mobj ->pos.y = mobj->pos.y +mobj ->vel.y;
  }else{
    mobj ->pos.y = mobj->pos.y - mobj->vel.y;
  }
  mobj ->cnt = (mobj ->cnt +1)%48;
}

static void disp34(movingobject* mobj){
  int l = (mobj ->cnt/12)%3;
  mobj ->currentobj = (mobj ->obj)[l];
  putobject(mobj ->currentobj,mobj->id,mobj->pos.x,mobj->pos.y);
}

static int bomba(movingobject* mobj){
  return 1;
}

movingobject* newenemy34(void){
  obj34[0] = newobject(3,1,"^_-");
  obj34[1] = newobject(3,1,"^_^");
  obj34[2] = newobject(3,1,"^o^");
  return newmovingobject(&obj34[0], onestep34, disp34, bomba,"enemy34");
}
