/* enemy363.c */
#include<enemy363.h>
#include<movingobject.h>
#include<object.h>

static object* objp363[2];

static void onesteppm363(movingobject* mobj){
  if(((mobj->cnt)/6)%4){
    mobj->pos.y = mobj->pos.y +mobj->vel.y;
  }else{
    mobj->pos.y = mobj->pos.y -mobj->vel.y;
  }
  mobj->cnt = (mobj->cnt +1)%48;
  mobj->currentobj = (mobj->obj)[(mobj->cnt/12)%2];
}

static void dispa363(movingobject* mobj){
  putobject(mobj->currentobj, mobj->id, mobj->pos.x, mobj->pos.y);
}

static int bomba363(movingobject* mobj){
  return 1;
}

movingobject* newenemy363(void){
  objp363[0] = newobject(4,4," :: :**::::: :: ");
  objp363[1] = newobject(3,3," : :*: : ");
  return newmovingobject(&objp363[0], onesteppm363, dispa363, bomba363, "enemy363");
}
