/* gamemain2.c */
#include<scenario.h>
#include<screen.h>
#include<gameio.h>
#include<walls.h>
#include<stdio.h>
#include<enemy.h>
#include<enemy36.h>
#include<enemy363.h>
#include<enemy34.h>/*林　美香子　1520534*/
#include<movingobjectmanager.h>
#ifdef DEBUG
#include<log.h>
#endif

#define OBJNUM 2
#define MOBJNUM 8
#define EVNUM 12

object* objp[OBJNUM];
movingobject* mobjp[MOBJNUM];
event* ev[EVNUM];
vector2 mypos;
int isfire;
int score;
int life;

void onestepb(movingobject* mobj){
  vec2add(&(mobj->pos), &(mobj->vel));
}

void dispb(movingobject* mobj){
  putobject(*(mobj->obj), mobj->id, mobj->pos.x, mobj->pos.y);
}

void dispm(movingobject* mobj){
  putobject(*(mobj->obj), 0, mobj->pos.x, mobj->pos.y);
}

int bomba(movingobject* mobj){
  return 1;
}

void initobjects(void){
  objp[0] = newobject(1,1,"x");
  objp[1] = newobject(3,2," ^ =x=");
}

void initmovingobjects(void){
  mobjp[0] = newenemy();
  mobjp[1] = newmovingobject(&objp[0], onestepb, dispb, bomba, "bullet");
  mobjp[2] = newmovingobject(&objp[1], NULL, dispm, bomba, "me");
  mobjp[3] = newenemy36();
  mobjp[4] = newenemy363();
  mobjp[5] = newenemy34();
}

void setevents(void){
  int i;
  ev[0] = newevent(3, makevector2(30,2),makevector2(0,0.1), mobjp[0],"plus0");
  ev[1] = newevent(15, makevector2(10,2),makevector2(0,0.1), mobjp[0],"plus1");
  ev[2] = newevent(20, makevector2(20,5),makevector2(0,0.1), mobjp[0],"plus2");
  ev[3] = newevent(25, makevector2(10,2),makevector2(0,0.1), mobjp[0],"plus3");
  ev[4] = newevent(25, makevector2(25,3),makevector2(0,0.3), mobjp[0],"plus4");
  ev[5] = newevent(40, makevector2(15,8),makevector2(0,0.3), mobjp[4],"plus6");
  ev[6] = newevent(60, makevector2(2,10),makevector2(0,0.3), mobjp[5],"plus7");
  ev[7] = newevent(65, makevector2(18,5),makevector2(0,0.3), mobjp[5],"plus7");
  ev[8] = newevent(70, makevector2(5,5),makevector2(0,0.3), mobjp[5],"plus7");
  ev[9] = newevent(60, makevector2(30,30),makevector2(0,0.3), mobjp[5],"plus7");
  ev[12] = newevent(1000000, 
		    makevector2(30,1),makevector2(0,1), mobjp[0],"dummy");
 

  for(i=0;i<EVNUM;i++){
    addevent(ev[i]);
  }
  resetmark();
}

void init(void){
  initscreen();
  initwalls();
  initmom();
  initobjects();
  initmovingobjects();
  initscenario();
  setevents();
}


void getstate(vector2* ret, int* isfire){
  static vector2 pos = {SCREENWIDTH/2-1, SCREENHEIGHT-3}; 
  *isfire = 0;
  int in = gameioread();
  switch(in){
  case 'j':
  case 'J':
    pos.x++;
    break;
  case 'f':
  case 'F':
    pos.x--;
    break;
  case 'y':
  case 'Y':
    pos.y--;
    break;
  case 'b':
  case 'B':
    pos.y++;
    break;
  case ' ':
    *isfire = 1;
  } 
  *ret = pos;
}

void show(void){
  int x,y;
  for(y=0;y<SCREENHEIGHT;y++){
    for(x=0;x<SCREENWIDTH;x++){
      gameioput(x,y,dispbuffer[SCREENWIDTH*y+x]);
    }
  }
  gameiorefresh();
}

void gameloop(void){
  int speedlevel = 8; 
  int time=0;
  vector2 tmpv;
  event* e = getnextevent();
  while(1){
    gameiousleep(30000);
    if(time%speedlevel == 0){
      scrollwall();
      while(e!= NULL && e->time*speedlevel < time){
        addmo(e->mobj, e->pos, e->vel);
        e = getnextevent();
      }
      score++;
    }
    getstate(&mypos, &isfire);
    gameioput(SCREENWIDTH+3,1,'0'+(int)mypos.x/10);
    gameioput(SCREENWIDTH+4,1,'0'+(int)mypos.x%10);
    gameioput(SCREENWIDTH+6,1,'0'+(int)mypos.y/10);
    gameioput(SCREENWIDTH+7,1,'0'+(int)mypos.y%10);

    gameioput(SCREENWIDTH+3,3,'S');
    gameioput(SCREENWIDTH+4,3,'c');
    gameioput(SCREENWIDTH+5,3,'o');
    gameioput(SCREENWIDTH+6,3,'r');
    gameioput(SCREENWIDTH+7,3,'e');
    gameioput(SCREENWIDTH+8,3,' ');
    gameioput(SCREENWIDTH+9,3,':');
    gameioput(SCREENWIDTH+10,3,' ');
    gameioput(SCREENWIDTH+11,3,'0'+score/1000);
    gameioput(SCREENWIDTH+12,3,'0'+(score/100)%10);
    gameioput(SCREENWIDTH+13,3,'0'+(score%100)/10);
    gameioput(SCREENWIDTH+14,3,'0'+score%10);


    gameioput(SCREENWIDTH+3,5,'L');
    gameioput(SCREENWIDTH+4,5,'i');
    gameioput(SCREENWIDTH+5,5,'f');
    gameioput(SCREENWIDTH+6,5,'e');
    gameioput(SCREENWIDTH+7,5,' ');
    gameioput(SCREENWIDTH+8,5,':');
    gameioput(SCREENWIDTH+9,5,' ');
    gameioput(SCREENWIDTH+10,5,'0'+(life/8)%10);


    putwalls(SCREENHEIGHT);
    putmo();
    onestepmo();
    if(checkcollision(mypos, objp[1])!=NONOBJ){
      life--;
      if(life==0){
	break;
}   
 }
    if(isfire){
      tmpv = mypos;
      tmpv.x +=1;
      tmpv.y -=2;
      addmo(mobjp[1], tmpv, makevector2(0,-1));
    }
    mobjp[2]->pos = mypos;
    dispm(mobjp[2]);
    show();
    time++;
  }
}

int main(void){
  gameioinit();
  gameioclear();
  init();
  
  score=0;
  life=40;
  gameloop();

  gameiopost();
  printf(" * * * G A M E  O V E R * * * ");
  printf("score %d\n",score);
  
  return 0;
}
