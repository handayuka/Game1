/* enemy36.c */
#include<enemy36.h>
#include<movingobject.h>
#include<object.h>

static object* objp36[2];

static void onesteppm36(movingobject* mobj){
  if(((mobj->cnt)/6)%4){
    mobj->pos.y = mobj->pos.y +mobj->vel.y;
  }else{
    mobj->pos.y = mobj->pos.y -mobj->vel.y;
  }
  mobj->cnt = (mobj->cnt +1)%48;
  
}

static void dispa36(movingobject* mobj){
  int l =(mobj ->cnt/12)%3;
  mobj ->currentobj = (mobj ->obj)[l]; 
 putobject(mobj->currentobj, mobj->id, mobj->pos.x, mobj->pos.y);
}

static int bomba36(movingobject* mobj){
  return 1;
}

movingobject* newenemy36(void){
  objp36[0] = newobject(4,4," :: :::: :: ");
  objp36[1] = newobject(3,3," : :*: : ");
  return newmovingobject(&objp36[0], onesteppm36, dispa36, bomba36, "enemy");
}
