/*****************************************************************************
 *                        EMPIRE OF THE PEASANTS                             *
 *                            version 02.03                                  *
 *                                                                           *
 * Worldgroup 3.2 Conversion                         - R. Hadsall 6/24/2012  * 
 * v2.03 - fix elwepusr.dat structure pack size      - R. Hadsall 5/13/2021  *
 * v2.03 - Major BBS 10 conversion                   - R. Hadsall 5/02/2023  *
 *                                                                           *
 * Copyright (C) 2007-2024 Rick Hadsall.  All Rights Reserved.               *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as published  *
 * by the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.     *
 *                                                                           *
 * Additional Terms for Contributors:                                        *
 * 1. By contributing to this project, you agree to assign all right, title, *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies.                              *
 * 2. You grant Rick Hadsall and Elwynor Technologies a non-exclusive,       *
 *    royalty-free, worldwide license to use, reproduce, prepare derivative  *
 *    works of, publicly display, publicly perform, sublicense, and          *
 *    distribute your contributions                                          *
 * 3. You represent that you have the legal right to make your contributions *
 *    and that the contributions do not infringe any third-party rights.     *
 * 4. Rick Hadsall and Elwynor Technologies are not obligated to incorporate *
 *    any contributions into the project.                                    *
 * 5. This project is licensed under the AGPL v3, and any derivative works   *
 *    must also be licensed under the AGPL v3.                               *
 * 6. If you create an entirely new project (a fork) based on this work, it  *
 *    must also be licensed under the AGPL v3, you assign all right, title,  *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies, and you must include these   *
 *    additional terms in your project's LICENSE file(s).                    *
 *                                                                           *
 * By contributing to this project, you agree to these terms.                *
 *                                                                           *
 *****************************************************************************/

#include "gcomm.h"
#include "majorbbs.h"
#include "elwep.h"

#define VERSION "2.03"

/* module function declarations */
void EXPORT init__elwep(VOID);
GBOOL empin(VOID);
GBOOL empon(VOID);
VOID empnws(VOID);
VOID emphang(VOID);
VOID clsemp(VOID);

/* module definition */
INT empstt;
struct module elwep={     /* module interface block               */
     "",                      /*    name used to refer to this module */
     empon,                   /*    user logon supplemental routine   */
     empin,                   /*    input routine if selected         */
     empnws,                  /*    status-input routine if selected  */
     NULL,                    /*    "injoth" routine for this module  */
     NULL,                    /*    user logoff supplemental routine  */
     emphang,                 /*    hangup (lost carrier) routine     */
     NULL,                    /*    midnight cleanup routine          */
     NULL,                    /*    delete-account routine            */
     clsemp                   /*    finish-up (sys shutdown) routine  */
};

/* structure definitions */ 
struct emptype {          /* definition of emptype for elwepusr.dat */
   CHAR  userid[UIDSIZ];  /* username                               */ // 000-029
   CHAR  lastd[DATSIZ];   /* last date MMDDYYYY                     */ // 030-038
   CHAR  spare;                                                        // 039
   ULONG land;            /* land                                   */ // 040-043
   ULONG money;           /* money                                  */ // 044-047
   ULONG grain;           /* grain                                  */ // 048-051
   ULONG last;            /* last                                   */ // 052-055
   ULONG soldiers;        /* soldiers                               */ // 056-059
   ULONG nobles;          /* nobles                                 */ // 060-063
   ULONG line;            /* line                                   */ // 064-067
   ULONG play;            /* play                                   */ // 068-071
   ULONG serfs;           /* serfs                                  */ // 072-075
   ULONG table;           /* table                                  */ // 076-079
   ULONG markets;         /* markets                                */ // 080-083
   ULONG mills;           /* mills                                  */ // 084-087
   ULONG foundries;       /* foundries                              */ // 088-091
   ULONG shipyards; //56  /* shipyards                              */ // 092-095
   SHORT taxrate;         /* tax rate                               */ // 099-097
   SHORT lastt;           /* last                                   */ // 098-099
   SHORT palace;          /* palace                                 */ // 100-101
   SHORT count;           /* count                                  */ // 102-103
   SHORT wins;            /* wins                                   */ // 104-105
   SHORT valid;           /* valid                                  */ // 106-107
   SHORT spies;           /* spies                                  */ // 108-109
   SHORT phase; //16      /* phase                                  */ // 110-111
}; //size 112

static
struct enews {            /* definition of enews for elwepnws.dat   */
   CHAR datestamp[10];    /* datestamp                              */ // 000-009
   CHAR info[80];         /* news information                       */ // 010-089
} news,newstmp; // size: 90

static
struct einout {           /* definition of einout for elweppm.dat   */
   CHAR userid[UIDSIZ];   /* user                                   */ // 000-029
   CHAR inmsg[74];        /* inbound message                        */ // 030-103
   CHAR outmsg[74];       /* outbound message                       */ // 104-177
} emppub,emptmp; // size: 178

static
struct act {              /* definition of act for elweppa.dat      */
   CHAR word[10];         /* word                                   */ // 000-009
   CHAR owner[UIDSIZ];    /* owner userid                           */ // 010-039
   CHAR orig[74];         /* original                               */ // 040-113
   CHAR all[74];          /* all                                    */ // 114-187
} pubact,pubtmp; // size: 188

static
struct courdata {         /* courier data for elwepcou.dat          */
   CHAR cto[UIDSIZ];      /* user to                                */ // 000-029
   CHAR cfrom[UIDSIZ];    /* user from                              */ // 030-059
   CHAR cmessage[76];     /* message                                */ // 060-135
} ccdata,cctmp; // size: 136

struct temp {
   CHAR attid[UIDSIZ]; // was 10
   CHAR moduserid[30];
   CHAR attlist[88];
   ULONG x1;
   ULONG x2;
   ULONG x3;
   ULONG x4;
   ULONG x5;
   LONG tmp;
   SHORT buynum;
   SHORT pagepause;
   SHORT free;
   SHORT nofight;
   SHORT tempsub;
   SHORT empcount;
   SHORT sendmode;
   SHORT sendusrnum;
};

struct emptype *emptype,spare;
struct emptype *empother;

struct temp *temp;

struct pchar {
   CHAR *charname;        /* character name                         */
   CHAR *chartype;        /* type of character                      */
                          /*     0=barmaid
                                 1=wench
                                 2=barman
                                 3=pirate
                          */
   SHORT  descript;  /* msg file associated with character  */
   SHORT  sex;       /* characters sex 0=female 1=male      */
};

struct pchar pubchar[]={
   /* character   character   description
      name        type        file name      sex      */
   {"Susie",    "Barmaid",  DESC01,        0},
   {"Jane",     "Wench",    DESC02,        0},
   {"Bill",     "Barman",   DESC03,        1},
   {"Jack",     "Pirate",   DESC04,        1}
};

/* variables arrays and defines */

#define MAXCHARS 4

CHAR items[][10]={       /* items available */
   "Soldiers",
   "Markets",
   "Mills",
   "Foundries",
   "Shipyards",
   "Palaces",
   "Nobles",
   "Spies"
};

CHAR class[][8]={       /* class ranking for users */
   "Peasant",
   "Master",
   "Duke",
   "Lord",
   "King",
   "Emperor"
};

struct hlp {
   CHAR *hlpcmd;
   SHORT hlpname;
};

struct hlp emphelp[]={
   {"general",   HLP01},
   {"ranks"  ,   HLP02},
   {"strategy",  HLP03},
   {"REMOVED",   HLP04},
   {"news",      HLP05},
   {"taxes",     HLP06},
   {"others",    HLP07},
   {"pub",       HLP08},
   {"exiting",   HLP09},
   {"battle",    HLP10},
   {"purchases", HLP11},
   {"growth",    HLP12},
   {"protection",HLP13},
   {"turns",     HLP14},
   {"palace",    HLP15}
};

static
HMCVFILE empmb;

static
DFAFILE *empfile,*newsfile,*pubfile,*wordfile,*courfile;

CHAR *gamop1,*gamop2,*gamop3;

SHORT nlvemp,taxemk,palemk,couemk,turemk,turliv;
SHORT maremk,milemk,fouemk,shiemk,seremk,nobemk,solemk,graemk,monemk,lanemk;
SHORT acttog,tlktog,atttog,enttog,exitog,rnktog,wsptog,chatog,pubtog,
valtog,acctog,tratog,msgtog,empwin;

LONG price1,price2,price3,price4,price5,price6,price7,price8;

#define RTIME 180

/* function declarations */
VOID barmaid(VOID);
VOID empnws(VOID);
SHORT rou1(VOID);
VOID rou2(VOID);
VOID rou3(SHORT unum);
VOID rou4(VOID);
VOID rou5(VOID);
VOID rou6(VOID);
VOID rou7(VOID);
VOID rou8(VOID);
VOID rou9(VOID);
VOID rou10(VOID);
SHORT rou11(VOID);
SHORT rou12(VOID);
SHORT rou13(VOID);
SHORT rou14(VOID);
VOID rou15(VOID);
VOID rou16(VOID);
VOID rou17(VOID);
VOID rou18(VOID);
VOID rou19(VOID);
SHORT rou20(VOID);
VOID rou21(VOID);
VOID emp_look(VOID);
SHORT check_act(VOID);
VOID rou22(VOID);
VOID rou23(VOID);
VOID rou24(VOID);
VOID rou25(VOID);
VOID rou26(VOID);
VOID rou27(VOID);
VOID rou28(VOID);
VOID rou29(VOID);
SHORT rou33(VOID);
SHORT rou34(VOID);
SHORT rou35(VOID);
SHORT rou36(VOID);
VOID rou45(VOID);
VOID rou46(VOID);
VOID shownws(VOID);
VOID showact(VOID);
VOID notify(CHAR* text);
VOID notcour(CHAR* coto, CHAR* cofrom, CHAR* comes);
SHORT cnv(CHAR* uid);
VOID empexit(VOID);
VOID others(VOID);
VOID distat(struct emptype* ptr);
SHORT check(VOID);
SHORT empcyc(VOID);
VOID upother(VOID);
SHORT delemp(CHAR* uid);
VOID died(VOID);
VOID viewnews(VOID);
VOID acts(VOID);
VOID usrapp(CHAR* app, CHAR* uid);
VOID pubout(VOID);
VOID puball(VOID);
VOID pubcur(VOID);
VOID whoin(VOID);
VOID cnvmod(CHAR* uid);
SHORT calc(SHORT lnum);
VOID calgrain(VOID);
VOID chkcap(VOID);
ULONG rndemp(ULONG num);
SHORT rndint(SHORT num);
SHORT chkpower(VOID);
VOID chkx(VOID);
VOID emprompt(VOID);
VOID changemp(VOID);
SHORT emplogon(VOID);
VOID emp_prfmsg(SHORT msgn);
DOUBLE elw__rnd(SHORT rn);
DOUBLE elw_rnd(VOID);
ULONG elw_rand(ULONG low, ULONG high);
ULONG elw_random(ULONG high);


/**************************************************************************/
/*                    sets up system files and storage                    */
/**************************************************************************/

VOID EXPORT init__elwep() {

   stzcpy(elwep.descrp,gmdnam("ELWEP.MDF"),MNMSIZ);
   empstt=register_module(&elwep);

   empmb = opnmsg("elwep.mcv");
   nlvemp=ynopt(NLVEMP);
   empwin= (SHORT)numopt(EMPWIN,1,32000);
   turemk= (SHORT)numopt(TUREMK,1,32000);
   turliv= (SHORT)numopt(TURLIV,1,32000);
   taxemk= (SHORT)numopt(TAXEMK,1,50);
   palemk= (SHORT)numopt(PALEMK,1,10);
   couemk= (SHORT)numopt(COUEMK,1,10);
   maremk= (SHORT)numopt(MAREMK,0,32000);
   milemk= (SHORT)numopt(MILEMK,0,32000);
   fouemk= (SHORT)numopt(FOUEMK,0,32000);
   shiemk= (SHORT)numopt(SHIEMK,0,32000);
   seremk= (SHORT)numopt(SEREMK,1000,10000);
   nobemk= (SHORT)numopt(NOBEMK,0,32000);
   solemk= (SHORT)numopt(SOLEMK,0,32000);
   graemk= (SHORT)numopt(GRAEMK,5000,32000);
   monemk= (SHORT)numopt(MONEMK,0,32000);
   lanemk= (SHORT)numopt(LANEMK,1000,32000);
   acttog=ynopt(ACTTOG);
   tlktog=ynopt(TLKTOG);
   atttog=ynopt(ATTTOG);
   enttog=ynopt(ENTTOG);
   exitog=ynopt(EXITOG);
   rnktog=ynopt(RNKTOG);
   wsptog=ynopt(WSPTOG);
   chatog=ynopt(CHATOG);
   pubtog=ynopt(PUBTOG);
   valtog=ynopt(VALTOG);
   acctog=ynopt(ACCTOG);
   tratog=ynopt(TRATOG);
   msgtog=ynopt(MSGTOG);
   price1=lngopt(PRICE1,0,2000000);
   price2=lngopt(PRICE2,0,2000000);
   price3=lngopt(PRICE3,0,2000000);
   price4=lngopt(PRICE4,0,2000000);
   price5=lngopt(PRICE5,0,2000000);
   price6=lngopt(PRICE6,0,2000000);
   price7=lngopt(PRICE7,0,2000000);
   price8=lngopt(PRICE8,0,2000000);
   gamop1=stgopt(GAMOP1);
   gamop2=stgopt(GAMOP2);
   gamop3=stgopt(GAMOP3);

   emptype=(struct emptype *)alcmem(nterms*sizeof(struct emptype));
   setmem(emptype,nterms*sizeof(struct emptype),0);
   empother=(struct emptype *)alcmem(nterms*sizeof(struct emptype));
   setmem(empother,nterms*sizeof(struct emptype),0);
   temp=(struct temp *)alcmem(nterms*sizeof(struct temp));
   setmem(temp,nterms*sizeof(struct temp),0);
   newsfile=dfaOpen("elwepnws.dat",sizeof(struct enews),NULL);
   dfaSetBlk(newsfile);
   empfile=dfaOpen("elwepusr.dat",sizeof(struct emptype),NULL);
   dfaSetBlk(empfile);
   pubfile=dfaOpen("elweppm.dat",sizeof(struct einout),NULL);
   dfaSetBlk(pubfile);
   wordfile=dfaOpen("elweppa.dat",sizeof(struct act),NULL);
   dfaSetBlk(wordfile);
   courfile=dfaOpen("elwepcou.dat",sizeof(struct courdata),NULL);
   dfaSetBlk(courfile);
   rtkick(RTIME,barmaid);

   shocst(spr("ELW Empire of the Peasants v%s", VERSION), "Copyright (c) 2024 Elwynor Technologies - www.elwynor.com");
}

/**************************************************************************/
/*                   routine for handling carrier loss                    */
/**************************************************************************/

VOID
emphang()
   {
   setmbk(empmb);
   btumil(usrnum,DFTIMX);
   if (usrptr->substt==21) {
      prfmsg(HUNGUP,class[calc((SHORT)usrnum)],emptype[usrnum].userid);
      pubout();
      }

   if (usrptr->state==empstt) {
      dfaSetBlk(empfile);
      if (dfaAcqEQ(&spare,usaptr->userid,0)) {
         dfaUpdate(&emptype[usrnum]);
         }
      }
   }

/**************************************************************************/
/*                       routine run at logon                             */
/**************************************************************************/

GBOOL
empon()
   {
   setmbk(empmb);
   setmem(temp[usrnum].attlist,88,0);

   dfaSetBlk(empfile);
   if (!(dfaAcqEQ(&spare,usaptr->userid,0))) {
      prfmsg(NEWEMP,usaptr->userid);
      return(0);
   }
   dfaSetBlk(courfile);
   if (dfaAcqEQ(&ccdata,usaptr->userid,0)) {
      emp_prfmsg(CMSGWAIT);
      }
   return(0);
   }

/**************************************************************************/
/*                   closes off all btrieve and msg files                 */
/**************************************************************************/
VOID
barmaid(VOID)
   {

   switch(rndint(11)) {
   case 1:
      emp_prfmsg(LOSTBAR);
      break;

   case 2:
      emp_prfmsg(BAR01);
      break;

   case 3:
      emp_prfmsg(BAR02);
      break;

   case 4:
      emp_prfmsg(BAR03);
      break;

   case 5:
      emp_prfmsg(BAR04);
      break;

   case 6:
      emp_prfmsg(BAR05);
      break;

   case 7:
      emp_prfmsg(BAR06);
      break;

   case 8:
      emp_prfmsg(BAR07);
      break;

   case 9:
      emp_prfmsg(BAR08);
      break;

   case 10:
      emp_prfmsg(BAR09);
      break;

   case 11:
      emp_prfmsg(BAR10);
      break;
      }

   puball();
   rtkick(RTIME,barmaid);
   }

VOID
clsemp()
   {
   clsmsg(empmb);
   dfaClose(empfile);
   dfaClose(newsfile);
   dfaClose(pubfile);
   dfaClose(wordfile);
   dfaClose(courfile);
   }

/**************************************************************************/
/*                   cycle routine for displaying news                    */
/**************************************************************************/

VOID
empnws(VOID)
   {

   setmbk(empmb);
   if (temp[usrnum].pagepause+1>22) {
      btupmt(usrnum,':');
      prf("\r(C)ontinue (N)onstop (Q)uit");
      outprf(usrnum);
      temp[usrnum].pagepause=0;
      usrptr->substt=29;
      return;
      }

   if (usrptr->substt==16 && status==CYCLE) {
      dfaSetBlk(newsfile);
      shownws();
      return;
      }

   else if (usrptr->substt==28 && status==CYCLE) {
      dfaSetBlk(wordfile);
      showact();
      return;
      }
   dfsthn();
   }

/**************************************************************************/
/*                 routine called when entering module                    */
/**************************************************************************/

GBOOL
empin()
   {
   SHORT num;

   usrptr->flags|=X2MAIN; /* send user back to main menu after sysop chat */

   setmbk(empmb);
   dfaSetBlk(empfile);

   temp[usrnum].tempsub=(SHORT)usrptr->substt;
   chkcap();

   if (sameas(margv[0],"help")) {
      if (margc>1) {
         for (num=0;num<15;num++) {
            if (sameto(margv[1],emphelp[num].hlpcmd)) {
               emp_prfmsg(emphelp[num].hlpname);
               emprompt();
               return(1);
               }
            }
         }
      emp_prfmsg(EMPHELP);
      emprompt();
      return(1);
      }


   if (chkpower()) {
      if (sameas(margv[0],"val") && margc > 1) {
         if (onsys(margv[1])) {
            if (usroff(othusn)->state==empstt) {
               return(1);
               }
            }

         cnvmod(margv[1]);
         dfaSetBlk(empfile);
         if (dfaAcqEQ(&spare,temp[usrnum].moduserid,0)) {
            spare.valid=1;
            dfaUpdate(&spare);
            prfmsg(UPDD,temp[usrnum].moduserid);
            emprompt();
            return(1);
            }
         }

      else if (sameas(margv[0],"grant")) {
         if (onsys(margv[1])) {
            if (usroff(othusn)->state==empstt) {
               emp_prfmsg(OKRESET);
               emprompt();
               emptype[othusn].play=0;
               }
            }
         return(1);
         }

      else if (sameas(margv[0],"overlook")) {
         if (onsys(margv[1])) {
            if (usroff(othusn)->state==empstt) {
               distat(&emptype[othusn]);
               emprompt();
               }
            }
         return(1);
         }

      else if (sameas(margv[0],"behead")) {
         cnvmod(margv[1]);
         if (delemp(temp[usrnum].moduserid)==1 &&
             !sameas(margv[1],emptype[usrnum].userid)) {
            prfmsg(BEHEADED,temp[usrnum].moduserid);
            puball();
            }
         emprompt();
         return(1);
         }
      }

   if (usrptr->state==empstt && usrptr->substt != 3 &&
       usrptr->substt != 13  && usrptr->substt != 5 &&
       usrptr->substt != 15  && !(usrptr->substt>18 && usrptr->substt<31) &&
       usrptr->substt !=16   && !(usrptr->substt>32 && usrptr->substt<37) &&
       usrptr->substt != 45  && usrptr->substt != 46) {

      if (sameas(margv[0],"y") || sameas(margv[0],"status") ||
          sameas(margv[0],"stat")) {
          distat(&emptype[usrnum]);
          emprompt();
          return(1);
         }

      else if (sameas(margv[0],"x") || sameas(margv[0],"exit")) {
         empexit();
         return(0);
         }
      }

   switch (usrptr->substt) {
   case 0:
      if (emplogon()==0) return(0);
      break;
   case 1:
      if (rou1()==0) return(0);
      break;
   case 2:
      rou2();
      break;
   case 3:
      rou3((SHORT)usrnum);
      break;
   case 4:
      rou4();
      break;
   case 5:
      rou5();
      break;
   case 6:
      rou6();
      break;
   case 7:
      rou7();
      break;
   case 8:
      rou8();
      break;
   case 9:
      rou9();
      break;
   case 10:
      rou10();
      break;
   case 11:
      if (rou11()==0) return(0);
      break;
   case 12:
      rou12();
      break;
   case 13:
      if (rou13()==0) return(0);
      break;
   case 14:
      if (rou14()==0) return(0);
      break;
   case 15:
      rou15();
      break;
   case 16:
      rou16();
      break;
   case 17:
      rou17();
      break;
   case 18:
      rou18();
      break;
   case 19:
      rou19();
      break;
   case 20:
      if (rou20()==0) return(0);
      break;
   case 21:
      rou21();
      break;
   case 22:
      rou22();
      break;
   case 23:
      rou23();
      break;
   case 24:
      rou24();
      break;
   case 25:
      rou25();
      break;
   case 26:
      rou26();
      break;
   case 27:
      rou27();
      break;
   case 28:
      rou28();
      break;
   case 29:
      rou29();
      break;
   case 33:
      rou33();
      break;
   case 34:
      rou34();
      break;
   case 35:
      rou35();
      break;
   case 36:
      rou36();
      break;
   case 45:
      rou45();
      break;
   case 46:
      rou46();
      }
   outprf(usrnum);
   prf("");
   return(1);
   }

/**************************************************************************/
/*                   main menu for empire (selections)                    */
/**************************************************************************/

SHORT rou1(VOID)
{
   SHORT i;
   CHAR e1[14],e2[14];

   setmbk(empmb);
   if (sameas(margv[0],"q")) {
      empexit();
      return(0);
      }

   else if (sameas(margv[0],"o")) {
      others();
      emp_prfmsg(ENTER);
      usrptr->substt=4;
      return(1);
      }

   else if (sameas(margv[0],"c")) {
      if (usaptr->creds < 1 && nlvemp==0) {
         emp_prfmsg(REJECT);
         emp_prfmsg(MAINSHT);
         return(1);
         }

      if (calc((SHORT)usrnum)==5) {
         emptype[usrnum].phase++;
         if (emptype[usrnum].phase==10) {
            prfmsg(VICTORY,usaptr->userid);
            dfaSetBlk(empfile);
            if (dfaAcqEQ(&spare,usaptr->userid,0)) {
               dfaDelete();
            }
            usrapp("*** COMPLETED EMPIRE! Surely a true emperor! ***"," ");
            addcrd(usaptr->userid,spr("%d",empwin),1);
            return(1);
         }

         prfmsg(NEWPH,usaptr->userid,emptype[usrnum].phase);
         usrapp("*** Has completed a phase! Ultimate rule isn't far away! ***"," ");
         changemp();
         dfaSetBlk(empfile);
         if (dfaAcqEQ(&spare,emptype[usrnum].userid,0)) {
            dfaUpdate(&emptype[usrnum]);
            }
         }

      /* RH: Question; if he's expecting money to be able to be negative, why did he define them as unsigned longs? */
      if ( (emptype[usrnum].land < 500) || (emptype[usrnum].serfs < 1000) || (emptype[usrnum].money <= 0) ) { /* RH: Changed money < 0 to <= 6/22/2012 */
         emp_prfmsg(DEAD);
         died();
         usrapp("was caught neglecting the empire and was beheaded"," ");
         btupmt(usrnum,0);
         return(0);
      }

      strcpy(e1,nctime(now()));
      strcpy(e2,nctime(emptype[usrnum].lastt));

      for (i=2;i < 8;i++) {
         e1[i]='\0';
         e2[i]='\0';
         }

      if (!sameas(e1,e2)) {
         emptype[usrnum].play=0;
         emptype[usrnum].lastt=now();
         dfaSetBlk(empfile);
         if (dfaAcqEQ(&spare,emptype[usrnum].userid,0)) {
            dfaUpdate(&emptype[usrnum]);
            }
         }

      if ((emptype[usrnum].play+(ULONG)1>(USHORT)turemk && usaptr->creds < 1) ||
         (emptype[usrnum].play+1>(USHORT)turliv && usaptr->creds > 0)) {
         prfmsg(OUTTURN,(usaptr->creds < 1 ? turemk : turliv));
         emp_prfmsg(MAINSHT);
         usrptr->substt=1;
         return(1);
      }

      emptype[usrnum].count++;
      emptype[usrnum].play++;
      emptype[usrnum].last=emptype[usrnum].count;
      emptype[usrnum].last*=376;
      emptype[usrnum].last+=8523;
      emptype[usrnum].last+=(ULONG)emptype[usrnum].land/8;
      emptype[usrnum].last-=(ULONG)emptype[usrnum].taxrate*2/2;
      emptype[usrnum].grain+=(ULONG)emptype[usrnum].last;

      prfmsg(CONT,spr("%ld",emptype[usrnum].last));
      usrptr->substt=5;
      return(1);
      }

   else if (sameas(margv[0],"t")) {
      prfmsg(TAXPMPT,emptype[usrnum].taxrate);
      usrptr->substt=19;
      return(1);
      }

   else if (sameas(margv[0],"n")) {
      btupmt(usrnum,0);
      viewnews();
      return(1);
      }

   else if (sameas(margv[0],"m")) {
      if (usaptr->creds < 1 && msgtog==0) {
         emp_prfmsg(CANTMSG);
         emp_prfmsg(MAINSHT);
         usrptr->substt=1;
         return(1);
         }
      dfaSetBlk(courfile);
      if (dfaAcqEQ(&ccdata,usaptr->userid,0)) {
         emp_prfmsg(COURWAIT);
         }
      emp_prfmsg(MSGMENU);
      usrptr->substt=33;
      return(1);
      }

   else if (sameas(margv[0],"p")) {
      if (usaptr->creds < 1 && pubtog==0) {
         emp_prfmsg(NOPUB);
         emp_prfmsg(MAINSHT);
         usrptr->substt=1;
         return(1);
         }

      else if (usaptr->creds <1 && chatog==0) {
         emptype[usrnum].table=1;
         }

      else if (usaptr->creds > 1 || (usaptr->creds <1 && enttog==1)) {
         dfaSetBlk(pubfile);
         if (dfaAcqEQ(&emppub,emptype[usrnum].userid,0) &&
             !sameas(emppub.inmsg,"none")) {
            prfmsg(ENTMSG,emppub.inmsg);
            pubout();
            emp_prfmsg(PUBENT);
            whoin();
            usrptr->substt=21;
            return(1);
            }
         }

      prfmsg(ENTERED,class[calc((SHORT)usrnum)],emptype[usrnum].userid);
      pubout();
      emp_prfmsg(PUBENT);
      whoin();
      usrptr->substt=21;
      return(1);
      }

   else if (sameas(margv[0],"?")) {
      emp_prfmsg(MAIN);
      usrptr->substt=1;
      return(1);
      }

   else if (sameas(margv[0],"menu") && chkpower()) {
      prfmsg(SYSMENU,(acttog==0 ? "OFF" : "ON"),
      (tlktog==0 ? "OFF" : "ON"),
      (atttog==0 ? "OFF" : "ON"),
      (enttog==0 ? "OFF" : "ON"),
      (exitog==0 ? "OFF" : "ON"),
      (rnktog==0 ? "OFF" : "ON"),
      (wsptog==0 ? "OFF" : "ON"),
      (chatog==0 ? "OFF" : "ON"),
      (pubtog==0 ? "OFF" : "ON"),
      (nlvemp==0 ? "OFF" : "ON"));
      usrptr->substt=27;
      return(1);
      }

   usrptr->substt=1;
   emp_prfmsg(MAINSHT);
   return(1);
   }

/**************************************************************************/
/*                 temporary "press enter" routine                        */
/**************************************************************************/

VOID
rou2(VOID)
   {
   usrptr->substt=3;
   emp_prfmsg(ENTER);
   }

/**************************************************************************/
/*                    routine for reprompting user                        */
/**************************************************************************/

VOID
rou3(SHORT unum)
   {
   setmbk(empmb);
   switch(temp[unum].tempsub)
      {
   case 1: 
      emp_prfmsg(MAINSHT);
      break;
   case 5: 
      emptype[unum].last=(ULONG)8523+(emptype[unum].count*376)+(emptype[unum].land/8);
      emptype[unum].last-=(ULONG)(emptype[unum].taxrate*2)/2;
      prfmsg(CONT,spr("%ld",emptype[unum].last));
      break;
   case 6: 
      prfmsg(NUMSELL,spr("%ld",emptype[unum].land));
      break;
   case 7: 
      prfmsg(NUMLA,spr("%ld",emptype[unum].land),spr("%ld",emptype[unum].money/75));
      break;
   case 8:
      prfmsg(BSMENU,spr("%ld",emptype[unum].money),
      spr("%ld",emptype[unum].money/75),
      spr("%ld",emptype[unum].grain),
      spr("%ld",emptype[unum].money/12));
      break;
   case 9: 
      prfmsg(GRANUM,spr("%ld",emptype[unum].grain));
      break;
   case 10: 
      prfmsg(GABUY,spr("%ld",emptype[unum].money),spr("%ld",emptype[unum].money/12));
      break;
   case 11: 
      prfmsg(SHRTMAR,spr("%ld",emptype[unum].money));
      break;
   case 12: 
      prfmsg(ATTMENU,spr("%ld",emptype[usrnum].nobles),
         spr("%ld",emptype[usrnum].soldiers),emptype[usrnum].spies);
      break;
   case 13:
      prfmsg(STATS,spr("%ld",temp[usrnum].x1),spr("%ld",temp[usrnum].x2),
      spr("%ld",temp[usrnum].x3),spr("%ld",temp[usrnum].x4),emptype[unum].taxrate);
      break;
   case 14:
      emp_prfmsg(SHRTBAT);
      break;
   case 15:
      emp_prfmsg(ENTER);
      break;
   case 17:
      prfmsg(GASERFS,spr("%ld",emptype[unum].last),spr("%ld",emptype[unum].last));
      break;
   case 18:
      emptype[usrnum].last=(ULONG)emptype[usrnum].soldiers*11;
      emptype[usrnum].last+=(ULONG)emptype[usrnum].count*6;
      prfmsg(GASOLDI,spr("%ld",emptype[unum].last),spr("%ld",emptype[unum].last));
      break;
   case 19:
      prfmsg(TAXPMPT,emptype[unum].taxrate);
      break;
   case 22:
      emp_prfmsg(ENTIN);
      btumil(unum,73);
      break;
   case 23:
      emp_prfmsg(EXIOUT);
      btumil(unum,73);
      break;
   case 24:
      emp_prfmsg(ENTOWNER);
      btumil(unum,9);
      break;
   case 25:
      emp_prfmsg(ENTORIG);
      btumil(unum,73);
      break;
   case 26:
      emp_prfmsg(ENTALL);
      btumil(unum,73);
      break;
   case 27:
      prfmsg(SYSMENU,(acttog==0 ? "OFF" : "ON"),
      (tlktog==0 ? "OFF" : "ON"),
      (atttog==0 ? "OFF" : "ON"),
      (enttog==0 ? "OFF" : "ON"),
      (exitog==0 ? "OFF" : "ON"),
      (rnktog==0 ? "OFF" : "ON"),
      (wsptog==0 ? "OFF" : "ON"),
      (chatog==0 ? "OFF" : "ON"),
      (pubtog==0 ? "OFF" : "ON"),
      (nlvemp==0 ? "OFF" : "ON"));
      break;
   case 33:
      emp_prfmsg(MSGSHRT);
      break;
   case 34:
      emp_prfmsg(SENDWHO);
      break;
   case 35:
      btupmt(unum,'>');
      btumil(unum,73);
      emp_prfmsg(ENNMSG);
      break;
   case 36:
      emp_prfmsg(SENDACC);
      }

   usroff(unum)->substt=temp[unum].tempsub;
   outprf(unum);
   prf("");
   }

/**************************************************************************/
/*                   enter routine for "other" list                       */
/**************************************************************************/

VOID
rou4(VOID)
   {
   usrptr->substt=1;
   emp_prfmsg(MAINSHT);
   }

/**************************************************************************/
/*                        Buy/Sell land options                           */
/**************************************************************************/

VOID
rou5(VOID)
   {

   setmbk(empmb);
   if (sameto(margv[0],"yes")) {
      prfmsg(BSMENU,spr("%ld",emptype[usrnum].money),
      spr("%ld",emptype[usrnum].money/75),
      spr("%ld",emptype[usrnum].grain),
      spr("%ld",emptype[usrnum].money/12));
      usrptr->substt=8;
      return;
      }

   if (sameto(margv[0],"no")) {
      calgrain();
      prfmsg(GASERFS,spr("%ld",emptype[usrnum].last),spr("%ld",emptype[usrnum].last));
      usrptr->substt=17;
      return;
      }

   prfmsg(CONT,spr("%ld",emptype[usrnum].last));
   usrptr->substt=5;
   return;
   }

/**************************************************************************/
/*                         Sell land routines                             */
/**************************************************************************/

VOID
rou6(VOID)
   {
   LONG i;

   setmbk(empmb);
   i=atol(margv[0]);

   if ((LONG)i < 1 || (LONG)emptype[usrnum].land-(LONG)i <1000 || (LONG)i > (LONG)emptype[usrnum].land ||
       (LONG)i > 2000000) {
      emp_prfmsg(BADNUM);
      temp[usrnum].tempsub=8;
      rou3((SHORT)usrnum);
      return;
      }

   if ( ((LONG)emptype[usrnum].land - i) >= 0) emptype[usrnum].land -= i;  /*RH:  he casted unsigned; unsigned-x is never <0 */
   emptype[usrnum].money+=(ULONG)i*20;
   emptype[usrnum].last=(ULONG)i*20;
   if ((emptype[usrnum].serfs - emptype[usrnum].serfs/5) > 500 && i > 1000) {
      emptype[usrnum].serfs-=emptype[usrnum].serfs/5;
   }
   prfmsg(LASOLD,spr("%ld",emptype[usrnum].last),spr("%ld",i));
   temp[usrnum].tempsub=8;
   rou3((SHORT)usrnum);
   }

/**************************************************************************/
/*                       Buy land routines                                */
/**************************************************************************/

VOID
rou7(VOID)
   {
   LONG i;

   setmbk(empmb);
   i=atol(margv[0]);

   if ((LONG)i < 1 || (LONG)i>1000000) {
      emp_prfmsg(BADNUM);
      temp[usrnum].tempsub=8;
      rou3((SHORT)usrnum);
      return;
      }

   emptype[usrnum].last=(ULONG)i*75;

   if ((ULONG)emptype[usrnum].land+(LONG)i > (ULONG)emptype[usrnum].serfs*10) {
      prfmsg(MSERF,spr("%ld",emptype[usrnum].serfs),
      spr("%ld",emptype[usrnum].land));
      temp[usrnum].tempsub=8;
      rou3((SHORT)usrnum);
      return;
      }

   else if (emptype[usrnum].last>emptype[usrnum].money) {
      prfmsg(BROKE,spr("%ld",emptype[usrnum].last),spr("%ld",emptype[usrnum].money));
      temp[usrnum].tempsub=8;
      rou3((SHORT)usrnum);
      return;
      }

   emptype[usrnum].land+=(ULONG)i;
   if ( ( (LONG)emptype[usrnum].money - (i*75) ) >= 0) emptype[usrnum].money -= i*75; /* RH: Again, unsigned issues */
   if (i > 1000) {
      emptype[usrnum].serfs+=(ULONG)emptype[usrnum].count*24;
   }
   prfmsg(LABUY,spr("%ld",emptype[usrnum].last),spr("%ld",(LONG)i));
   temp[usrnum].tempsub=8;
   rou3((SHORT)usrnum);
   }

/**************************************************************************/
/*                      Buy/Sell menu options                             */
/**************************************************************************/

VOID
rou8(VOID)
   {

   setmbk(empmb);

   if (sameas(margv[0],"1")) {
      usrptr->substt=7;
      prfmsg(NUMLA,spr("%ld",emptype[usrnum].money),spr("%ld",emptype[usrnum].money/75));
      return;
      }

   else if (sameas(margv[0],"2")) {
      usrptr->substt=6;
      prfmsg(NUMSELL,spr("%ld",emptype[usrnum].land));
      return;
      }

   if (sameas(margv[0],"3")) {
      prfmsg(GABUY,spr("%ld",emptype[usrnum].money),spr("%ld",emptype[usrnum].money/12));
      usrptr->substt=10;
      return;
      }

   if (sameas(margv[0],"4")) {
      prfmsg(GRANUM,spr("%ld",emptype[usrnum].grain));
      usrptr->substt=9;
      return;
      }

   else if (sameas(margv[0],"c") || sameas(margv[0],"continue")) {
      calgrain();
      prfmsg(GASERFS,spr("%ld",emptype[usrnum].last),spr("%ld",emptype[usrnum].last));
      usrptr->substt=17;
      return;
      }
   rou3((SHORT)usrnum);
   usrptr->substt=8;
   return;
   }

/**************************************************************************/
/*                        Sell grain routine                              */
/**************************************************************************/

VOID
rou9(VOID)
   {
   LONG i;

   setmbk(empmb);

   i=atol(margv[0]);

   if ( (i < 1) || ( i > (LONG)emptype[usrnum].grain) || ( i > 1500000000L) ) {   /* RH: more unsigned nonsense */
      emp_prfmsg(BADG);
      temp[usrnum].tempsub=8;
      rou3((SHORT)usrnum);
      return;
      }

   if ( ((LONG)emptype[usrnum].grain - i) >= 0 ) emptype[usrnum].grain -= i; /* RH: more unsigned nonsense */
   emptype[usrnum].money+=(ULONG)i;
   emptype[usrnum].last=(ULONG)i;
   prfmsg(GASOLD,spr("%ld",emptype[usrnum].last),spr("%ld",(LONG)i));
   temp[usrnum].tempsub=8;
   rou3((SHORT)usrnum);
   return;
   }

/**************************************************************************/
/*                        Buy grain routine                               */
/**************************************************************************/

VOID
rou10(VOID)
   {
   LONG i;

   setmbk(empmb);
   i=atol(margv[0]);

   emptype[usrnum].last=(ULONG)i*12;

   if ( (i < 1) || ( i > 2000000L) ) {  /* RH: Cleanup */
      emp_prfmsg(BADG);
      temp[usrnum].tempsub=8;
      rou3((SHORT)usrnum);
      return;
      }

   else if (emptype[usrnum].last>emptype[usrnum].money) {
      prfmsg(BROKE,spr("%ld",emptype[usrnum].last),spr("%ld",emptype[usrnum].money));
      temp[usrnum].tempsub=8;
      rou3((SHORT)usrnum);
      return;
      }

   emptype[usrnum].grain+=(ULONG)i;
   if ( ( (LONG)emptype[usrnum].money - (i*12) ) >= 0) emptype[usrnum].money -= i*12; /* RH: unsigned nonsense */
   prfmsg(GABOUT,spr("%ld",emptype[usrnum].last),spr("%ld",i));
   temp[usrnum].tempsub=8;
   rou3((SHORT)usrnum);
   return;
   }

/**************************************************************************/
/*                              Market menu                               */
/**************************************************************************/

SHORT
rou11(VOID)
   {

   ULONG i;

   setmbk(empmb);
   if (sameas(margv[0],"?") || sameas(margv[0],"menu")) {
      prfmsg(MARKET, spr("%-7ld",(LONG)price1),spr("%ld",emptype[usrnum].money/(LONG)price1),
      spr("%-7ld",(LONG)price2),spr("%ld",emptype[usrnum].money/(LONG)price2));
      prfmsg(MARKET2,spr("%-7ld",(LONG)price3),spr("%ld",emptype[usrnum].money/(LONG)price3),
      spr("%-7ld",(LONG)price4),spr("%ld",emptype[usrnum].money/(LONG)price4));
      prfmsg(MARKET3,spr("%-7ld",(LONG)price5),spr("%ld",emptype[usrnum].money/(LONG)price5),
      spr("%-7ld",(LONG)price6),spr("%ld",emptype[usrnum].money/(LONG)price6));
      prfmsg(MARKET4,spr("%-7ld",(LONG)price7),spr("%ld",emptype[usrnum].money/(LONG)price7),
      spr("%-7ld",(LONG)price8),spr("%ld",emptype[usrnum].money/(LONG)price8));
      prfmsg(MARKET5,spr("%ld",emptype[usrnum].money));
      usrptr->substt=11;
      return(1);
      }

   if (sameas(margv[0],"c") || sameas(margv[0],"continue")) {

      if (usaptr->creds < 1 && atttog==0) {
         emp_prfmsg(NOATT);
         if (empcyc()==0) return(0);
         return(1);
         }

      if (temp[usrnum].nofight ||
          emptype[usrnum].soldiers==0 || emptype[usrnum].nobles==0) {
         emp_prfmsg(SKIPPED);
         if (empcyc()==0) return(0);
         return(1);
         }
      else
          prfmsg(ATTMENU,spr("%ld",emptype[usrnum].nobles),
      spr("%ld",emptype[usrnum].soldiers),emptype[usrnum].spies);
      usrptr->substt=12;
      return(1);
      }

    if (sameto(margv[0],"buy") && margc==3) {
      i=atol(margv[1]);

      if (i<1) {
         prfmsg(SHRTMAR,spr("%ld",emptype[usrnum].money));
         usrptr->substt=11;
         return(1);
      }

      else if (i>250000) {
         emp_prfmsg(WONT);
         prfmsg(SHRTMAR,spr("%ld",emptype[usrnum].money));
         usrptr->substt=11;
         return(1);
         }

   switch(check())
      {
   case -1:
      emp_prfmsg(BADITEM);
      prfmsg(SHRTMAR,spr("%ld",emptype[usrnum].money));
      usrptr->substt=11;
      return(1);

   case 0:
      temp[usrnum].tmp=price1;

      if (emptype[usrnum].soldiers+i>
          emptype[usrnum].nobles*20) {
         emp_prfmsg(XNOBLES);
         temp[usrnum].tmp=-1;
         }

      break;
   case 1: 
      temp[usrnum].tmp=price2;
      if (emptype[usrnum].markets+i>
          emptype[usrnum].land) {
         emp_prfmsg(MMLAND);
         temp[usrnum].tmp=-1;
         }
      break;
   case 2:
      temp[usrnum].tmp=price3;
      if (emptype[usrnum].mills+i>
          emptype[usrnum].markets*3) {
         emp_prfmsg(MMAR);
         temp[usrnum].tmp=-1;
         }
      break;
   case 3: 
      temp[usrnum].tmp=price4;
      break;
   case 4: 
      temp[usrnum].tmp=price5;
      break;
   case 5: 
      temp[usrnum].tmp=price6;

      if (emptype[usrnum].palace+i>10) {
         emp_prfmsg(MAXPAL);
         temp[usrnum].tmp=-1;
         }

      break;
   case 6: 
      temp[usrnum].tmp=price7;
      break;

   case 7:
      temp[usrnum].tmp=price8;

      if ( ((emptype[usrnum].spies + i) > 10) || ( (emptype[usrnum].spies + (LONG)i) < 0) ) { /* RH: unsigned / casting thing again */
         emp_prfmsg(BADSPY);
         temp[usrnum].tmp=-1;
         }
      }

   if (temp[usrnum].tmp==-1) {
      prfmsg(SHRTMAR,spr("%ld",emptype[usrnum].money));
      usrptr->substt=11;
      return(1);
      }

   if ((LONG)temp[usrnum].tmp*(ULONG)i>(ULONG)emptype[usrnum].money) {
      emptype[usrnum].last=(ULONG)i*temp[usrnum].tmp;
      prfmsg(BROKE,spr("%ld",emptype[usrnum].last),
      spr("%ld",emptype[usrnum].money));
      prfmsg(SHRTMAR,spr("%ld",emptype[usrnum].money));
      usrptr->substt=11;
      return(1);
      }

   emptype[usrnum].last=(ULONG)i*temp[usrnum].tmp;
   prfmsg(COST,spr("%ld",(ULONG)emptype[usrnum].last),spr("%ld",(LONG)temp[usrnum].tmp));

   if (((LONG)emptype[usrnum].money - ((LONG)i * (LONG)temp[usrnum].tmp)) >= 0)  /* RH: unsigned / casting thing again */
   		emptype[usrnum].money-=(ULONG)i*temp[usrnum].tmp;

   switch(check())
      {
   case 0: 
      emptype[usrnum].soldiers+=i;
      break;
   case 1: 
      emptype[usrnum].markets+=i;
      break;
   case 2: 
      emptype[usrnum].mills+=i;
      break;
   case 3:
      emptype[usrnum].foundries+=i;
      break;
   case 4: 
      emptype[usrnum].shipyards+=i;
      break;
   case 5:
      emptype[usrnum].palace+=(SHORT)i;
      emptype[usrnum].nobles+=i;
      break;
   case 6: 
      emptype[usrnum].nobles+=i;
      break;
   case 7:
      emptype[usrnum].spies+=(SHORT)i;
      }
   }
   prfmsg(SHRTMAR,spr("%ld",emptype[usrnum].money));
   usrptr->substt=11;
   return(1);
   }

/**************************************************************************/
/*                       Attack menu for battle                           */
/**************************************************************************/

SHORT
rou12(VOID)
   {
   setmbk(empmb);
   if (sameas(margv[0],"c") ||
       sameas(margv[0],"continue")) {
      emp_prfmsg(NOFIGHT);
      if (empcyc()==0) return(0);
      return(1);
      }

   else if (sameas(margv[0],"?")) {
      others();
      prfmsg(ATTMENU,spr("%ld",emptype[usrnum].nobles),
      spr("%ld",emptype[usrnum].soldiers),emptype[usrnum].spies);
      usrptr->substt=12;
      return(1);
      }

   else if (sameas(margv[0],usaptr->userid)) {
      emp_prfmsg(IDIOT);
      prfmsg(ATTMENU,spr("%ld",emptype[usrnum].nobles),
      spr("%ld",emptype[usrnum].soldiers),emptype[usrnum].spies);
      usrptr->substt=12;
      return(1);
      }

   if (margc==0) {
      prfmsg(ATTMENU,spr("%ld",emptype[usrnum].nobles),
      spr("%ld",emptype[usrnum].soldiers),emptype[usrnum].spies);
      usrptr->substt=12;
      return(1);
      }

   cnv(margv[0]);
   return(1);
   }

/**************************************************************************/
/*                      Prompt (Play again y/n)                           */
/**************************************************************************/

SHORT
rou13(VOID)
   {
   setmbk(empmb);
   if (sameas(margv[0],"y") ||
       sameas(margv[0],"yes") || margc==0) {
      prfmsg(NEXT,emptype[usrnum].userid);
      emp_prfmsg(MAINSHT);
      usrptr->substt=1;
      return(1);
      }
   empexit();
   return(0);
   }

/**************************************************************************/
/*           Battle mode menu (Attack, conquer, retreat,spy)             */
/**************************************************************************/

SHORT
rou14(VOID)
   {

   SHORT tmprnd;

   setmbk(empmb);
   if (sameas(margv[0],"?")) {
      prfmsg(BATHELP,temp[usrnum].attid);
      emp_prfmsg(SHRTBAT);
      usrptr->substt=14;
      return(1);
      }

   if (sameto(margv[0],"attack")) {
      temp[usrnum].x1=emptype[usrnum].nobles*3;
      temp[usrnum].x1+=emptype[usrnum].soldiers*2;
      temp[usrnum].x1+=emptype[usrnum].wins;

      temp[usrnum].x2=empother[usrnum].palace*75;
      temp[usrnum].x2+=empother[usrnum].nobles*3;
      temp[usrnum].x2+=empother[usrnum].soldiers*2;
      temp[usrnum].x2+=empother[usrnum].wins;

      if (temp[usrnum].x1>temp[usrnum].x2 || temp[usrnum].x1==temp[usrnum].x2) {
         btupmt(usrnum,0);
         emp_prfmsg(WON);
         outprf(usrnum);
         empother[usrnum].soldiers=(ULONG) rndemp(empother[usrnum].nobles*5)/2;
         emptype[usrnum].soldiers=(ULONG)rndemp(emptype[usrnum].nobles*13)/2;
         emptype[usrnum].wins++;
         emptype[usrnum].land+=(ULONG)(empother[usrnum].land/8)+(emptype[usrnum].wins*5);
         empother[usrnum].land-=(ULONG)(empother[usrnum].land/8)+(emptype[usrnum].wins*5);

         if (empother[usrnum].land<500) {
            if (delemp(empother[usrnum].userid)==1) {
               usrapp("attacked and KILLED ",
               empother[usrnum].userid);
               prfmsg(KILLED,empother[usrnum].userid);
               }
            if (empcyc()==0) return(0);
            return(1);
            }

         if (empother[usrnum].nobles-1>=1) {
            empother[usrnum].nobles-=1;
            }

         usrapp("attacked and DEFEATED ",
         empother[usrnum].userid);
         notcour(empother[usrnum].userid,
         usaptr->userid,"You were no challenge for me in battle! Kneel!");
         notify("attacked and DEFEATED you");
         upother();
         if (empcyc()==0) return(0);
         return(1);
         }

      else if (temp[usrnum].x1<temp[usrnum].x2) {
         btupmt(usrnum,0);
         emp_prfmsg(LOST);
         outprf(usrnum);
         empother[usrnum].soldiers=(ULONG)rndemp(empother[usrnum].nobles*13)/5;
         emptype[usrnum].soldiers=0;
         emptype[usrnum].land-=(ULONG)(emptype[usrnum].land/16)+(empother[usrnum].wins*5);
         empother[usrnum].land+=(ULONG)(emptype[usrnum].land/16)+(emptype[usrnum].wins*5);

         if (emptype[usrnum].nobles-1>=1) {
            emptype[usrnum].nobles-=1;
            }

         usrapp("FAILED at strike on ",
         empother[usrnum].userid);
         notcour(empother[usrnum].userid,
         usaptr->userid,"I will beat you NEXT battle! Until next time...");
         notify("attacked you and LOST");
         upother();
         if (empcyc()==0) return(0);
         return(1);
         }
      }

   if (sameto(margv[0],"retreat")) {
      temp[usrnum].x1=emptype[usrnum].nobles*3;
      temp[usrnum].x1+=emptype[usrnum].soldiers*2;
      temp[usrnum].x1+=emptype[usrnum].wins;

      temp[usrnum].x2=empother[usrnum].palace*75;
      temp[usrnum].x2+=empother[usrnum].nobles*3;
      temp[usrnum].x2+=empother[usrnum].soldiers*2;
      temp[usrnum].x2+=empother[usrnum].wins;

      btupmt(usrnum,0);

      if (temp[usrnum].x2>=temp[usrnum].x1/2) {
         emp_prfmsg(HURT);
         outprf(usrnum);
         emptype[usrnum].soldiers=0;
         usrapp("was wounded during retreat from attack on ",
         empother[usrnum].userid);
         notify("was wounded while retreating");
         if (empcyc()==0) return(0);
         return(1);
         }

      emp_prfmsg(NOTHURT);
      outprf(usrnum);
      usrapp("escaped from attack on ",
      empother[usrnum].userid);
      notcour(usaptr->userid,empother[usrnum].userid,
      "HAR! HAR! And you call yourself a ruler!");
      notcour(empother[usrnum].userid,usaptr->userid,
      "You beat me this time - never again!");
      notify("managed to escape successfully");
      if (empcyc()==0) return(0);
      return(1);
      }

   if (sameto(margv[0],"spy")) {
      if (emptype[usrnum].spies==0) {
         emp_prfmsg(NOSPY);
         emp_prfmsg(SHRTBAT);
         usrptr->substt=14;
         return(1);
         }

      emptype[usrnum].spies-=1;

      dfaSetBlk(empfile);
      if (dfaAcqEQ(&spare,emptype[usrnum].userid,0)) {
         dfaUpdate(&emptype[usrnum]);
         }

      tmprnd=rndint(3);
      if (tmprnd==2 || tmprnd==3) {
         emp_prfmsg(SPYRPT);
         distat(&empother[usrnum]);
         emp_prfmsg(SHRTBAT);
         usrptr->substt=14;
         return(1);
         }

      emp_prfmsg(FAILSP);
      emp_prfmsg(SHRTBAT);
      usrptr->substt=14;
      return(1);
      }

   if (sameto(margv[0],"conquer")) {
      if (emptype[usrnum].soldiers>empother[usrnum].soldiers
          && (LONG)emptype[usrnum].soldiers>(empother[usrnum].palace*157)+
          100+(empother[usrnum].wins*3)) {
         if (empother[usrnum].palace<4) {
            emp_prfmsg(CANTCON);
            emp_prfmsg(SHRTBAT);
            usrptr->substt=14;
            return(1);
            }

         prfmsg(SUCC,(empother[usrnum].palace*157)+(empother[usrnum].wins*2));
         outprf(usrnum);
         empother[usrnum].palace-=1;
         emptype[usrnum].soldiers-=(ULONG)(empother[usrnum].palace*157)+(empother[usrnum].wins*2);
         usrapp("demolished palace belonging to ",
         empother[usrnum].userid);
         notify("destroyed some of your palace");
         prfmsg(BATTLE,empother[usrnum].userid,
         spr("%ld",empother[usrnum].soldiers),spr("%ld",empother[usrnum].nobles),
         empother[usrnum].palace*10);
         upother();
         return(1);
         }
      emp_prfmsg(EPFAILED);
      emp_prfmsg(SHRTBAT);
      usrptr->substt=14;
      return(1);
      }

   emp_prfmsg(SHRTBAT);
   usrptr->substt=14;
   return(1);
   }

/**************************************************************************/
/*                       "Your stats" routines                            */
/**************************************************************************/

VOID
rou15(VOID)
   {
   setmbk(empmb);
   prfmsg(STATS,spr("%ld",temp[usrnum].x1),spr("%ld",temp[usrnum].x2),
   spr("%ld",temp[usrnum].x3),spr("%ld",temp[usrnum].x4),emptype[usrnum].taxrate);

   dfaSetBlk(empfile);
   if (dfaAcqEQ(&spare,emptype[usrnum].userid,0)) {
      dfaUpdate(&emptype[usrnum]);
      }
   usrptr->substt=13;
   }

VOID
rou16(VOID)
   {
   btupmt(usrnum,0);
   prf("\r*** NEWS Aborted ***\r");
   emp_prfmsg(MAINSHT);
   btupmt(usrnum,':');
   usrptr->substt=1;
   }

/**************************************************************************/
/*                  Routines to handle giving serfs grain                 */
/**************************************************************************/

VOID
rou17(VOID)
   {
   LONG i;
   setmbk(empmb);
   i=atol(margv[0]);

   if (margc==0 || (LONG)i > (LONG)emptype[usrnum].last) i=(LONG)emptype[usrnum].last;

   if ((LONG)emptype[usrnum].grain < (LONG)i || (LONG)i < (LONG)emptype[usrnum].last || i < 1) {
      if (emptype[usrnum].money>=4) {
      emptype[usrnum].money-=emptype[usrnum].money/4;
      }
      emptype[usrnum].grain=0;
      emptype[usrnum].soldiers=0;
      emptype[usrnum].land-=emptype[usrnum].land/6;
      if (emptype[usrnum].markets>=10) {
      emptype[usrnum].markets-=emptype[usrnum].markets/10;
      }
      if (emptype[usrnum].mills>=10) {
      emptype[usrnum].mills-=emptype[usrnum].mills/10;
      }
      emptype[usrnum].serfs-=emptype[usrnum].serfs/4;
      temp[usrnum].nofight=1;
      usrapp("was RANSACKED by the empire serfs "," ");
      emp_prfmsg(SACKED);
      emp_prfmsg(STARVED);
      prfmsg(SHRTMAR,spr("%ld",emptype[usrnum].money));
      usrptr->substt=11;
      return;
      }

      else {
      emptype[usrnum].grain-=(ULONG)i;
      emptype[usrnum].serfs+=(ULONG)(emptype[usrnum].count*24);
      temp[usrnum].nofight=0;
      emp_prfmsg(DONE);
      emptype[usrnum].last=(ULONG)(emptype[usrnum].soldiers*11)+(emptype[usrnum].count*6);
      prfmsg(GASOLDI,spr("%ld",emptype[usrnum].last),spr("%ld",
      emptype[usrnum].last));
      usrptr->substt=18;
      }
   }

/**************************************************************************/
/*                   Routines for giving soldiers grain                   */
/**************************************************************************/

VOID
rou18(VOID)
   {
   LONG i;

   setmbk(empmb);
   i=atol(margv[0]);

   emptype[usrnum].last=(ULONG)emptype[usrnum].soldiers*11;
   emptype[usrnum].last+=(ULONG)emptype[usrnum].count*6;

   if (margc==0 || (LONG)i > (LONG)emptype[usrnum].last) i=(LONG)emptype[usrnum].last;

   if ((LONG)emptype[usrnum].grain < (LONG)i || (LONG)i < (LONG)emptype[usrnum].last || i < 1) {
      emptype[usrnum].soldiers=0;
      temp[usrnum].nofight=1;
      usrapp("was caught starving empire soldiers!"," ");
      emp_prfmsg(STARVED);
      }

      else {
      emptype[usrnum].grain-=(ULONG)i;
      emp_prfmsg(DONE);
      }

   prfmsg(MARKET, spr("%-7ld",(LONG)price1),spr("%ld",emptype[usrnum].money/(LONG)price1),
   spr("%-7ld",(LONG)price2),spr("%ld",emptype[usrnum].money/(LONG)price2));
   prfmsg(MARKET2,spr("%-7ld",(LONG)price3),spr("%ld",emptype[usrnum].money/(LONG)price3),
   spr("%-7ld",(LONG)price4),spr("%ld",emptype[usrnum].money/(LONG)price4));
   prfmsg(MARKET3,spr("%-7ld",(LONG)price5),spr("%ld",emptype[usrnum].money/(LONG)price5),
   spr("%-7ld",(LONG)price6),spr("%ld",emptype[usrnum].money/(LONG)price6));
   prfmsg(MARKET4,spr("%-7ld",(LONG)price7),spr("%ld",emptype[usrnum].money/(LONG)price7),
   spr("%-7ld",(LONG)price8),spr("%ld",emptype[usrnum].money/(LONG)price8));
   prfmsg(MARKET5,spr("%ld",emptype[usrnum].money));
   usrptr->substt=11;
   }

/**************************************************************************/
/*                     Tax rate modification routines                     */
/**************************************************************************/

VOID
rou19(VOID)
   {
   SHORT i;

   if (sameas(margv[0],"x") || sameas(margv[0],"exit")) {
      emp_prfmsg(MAINSHT);
      usrptr->substt=1;
      return;
      }

   i= (SHORT)atoi(margv[0]);

   if (i<1 || i>50) {
      emp_prfmsg(BADTAX);
      emp_prfmsg(MAINSHT);
      usrptr->substt=1;
      return;
      }

   emptype[usrnum].taxrate=i;
   emp_prfmsg(TAXSET);
   emp_prfmsg(MAINSHT);
   usrptr->substt=1;
   }

/**************************************************************************/
/*                       "E"xit empire routine                            */
/**************************************************************************/

SHORT
rou20(VOID)
   {
   emp_prfmsg(LATER);
   btupmt(usrnum,0);
   return(0);
   }

/**************************************************************************/
/*                    Pub routines && sysop editors                       */
/**************************************************************************/

VOID
rou21(VOID)
   {
   SHORT i,in,at,loop,r;

   setmbk(empmb);
   if (sameas(margv[0],"x") || sameas(margv[0],"exit")) {
      if (usaptr->creds > 1 || (usaptr->creds <1 && exitog==1)) {

         dfaSetBlk(pubfile);
         if (dfaAcqEQ(&emppub,emptype[usrnum].userid,0) &&
             !sameas(emppub.outmsg,"none")) {
            prfmsg(EXIMSG,emppub.outmsg);
            pubout();
            emp_prfmsg(BYE);
            emp_prfmsg(MAINSHT);
            usrptr->substt=1;
            return;
            }
         }
      prfmsg(LEFT,class[calc((SHORT)usrnum)],emptype[usrnum].userid);
      pubout();
      emp_prfmsg(BYE);
      emp_prfmsg(MAINSHT);
      usrptr->substt=1;
      return;
      }

   else if (sameas(margv[0],"/s") || sameas(margv[0],"scan")) {
      prf("\r  Ruler      ... Table\r");
      prf("==========================\r");
      for (i=0; i < nterms; i++) {
         if (usroff(i)->state==empstt && usroff(i)->substt==21) {
            prf("  %-10s ...   %s\r",emptype[i].userid,spr("%ld",emptype[i].table));
            }
         }
      prf("\r");
      return;
      }

   else if (sameas(margv[0],"/a") || sameas(margv[0],"list")) {
      acts();
      return;
      }

   if (margv[0][0]=='/' && strlen(margv[0])>1) {
      if (usaptr->creds < 1 && wsptog==0) {
         emp_prfmsg(NOWHIS);
         whoin();
         return;
         }

      if (!onsys(margv[0]+1)) {
         prfmsg(NOTPUB,margv[0]+1);
         whoin();
         return;
         }

      else if (emptype[othusn].table !=
          emptype[usrnum].table || usroff(othusn)->state!=empstt  ||
          usroff(othusn)->substt!=21) {
         prfmsg(NOTPUB,margv[0]+1);
         whoin();
         return;
         }
      btupmt(usrnum,0);
      prf("***\r");
      prf("Whispered from %s: ",emptype[usrnum].userid);

      for (i=1; i < margc; i++) {
         prf(margv[i]);
         prf(" ");
         }

      prf("\r");
      outprf(othusn);
      emp_prfmsg(WHISSENT);
      btupmt(usrnum,':');
      return;
      }

   else if (sameas(margv[0],"?") || sameas(margv[0],"help")) {
      emp_prfmsg(HELP);
      return;
      }

   else if (sameto(margv[0],"look")) {
      /* check for other users */

      for (i=0,in=0,at=0;i<nterms;i++) {
         if (usroff(i)->state == empstt && usrnum != i
             && usroff(i)->substt == 21) {
            in++;
            if (emptype[i].table==emptype[usrnum].table) at++;
            }
         }

      if (margc == 1) {
         prfmsg(SITAT,emptype[usrnum].table);

         if (in==0) {
            prf("There are no other rulers in the pub now.\r");
            }
         else {
            emp_prfmsg(INTPUB);
            for (i=0,loop=0;i < nterms;i++) {
               if (usroff(i)->state == empstt && usrnum != i &&
                   usroff(i)->substt == 21) {
                  if (loop > 0) {
                     prf(", ");
                     }
                  prf("%s",emptype[i].userid);
                  loop++;
                  }
               }
            prf("\r");
            }
         if (at==0) {
            emp_prfmsg(NOOTRU);
            }

         emp_prfmsg(LOAYS);

         r=rndint(MAXCHARS);
         for (i=0,loop=0;i < r;i++) {
            if (loop > 0)  prf(",");
            if (loop == 2) prf("\r");
            if (i == r-1 && i>0)  prf(" and");
            prf(" %s the %s",pubchar[i].charname,pubchar[i].chartype);
            loop++;
            }
         prf("\r");
         usrptr->substt=21;
         return;
         }
      else if (margv==0) {
         emp_look();
         usrptr->substt=21;
         return;
         }
      }

   else if (sameas(margv[0],"table") && margc>1) {

      if (usaptr->creds < 1 && chatog==0) {
         emp_prfmsg(NOCHA);
         return;
         }

      if (atol(margv[1])>10 || atol(margv[1])<1) {
         if (usaptr->creds < 1) {
            emp_prfmsg(NOTABLE);
            return;
            }
         }

      if (atol(margv[1])>63999 || atol(margv[1])<1) {
         if (chkpower()==0) {
            emp_prfmsg(NOTABLE);
            return;
            }
         }

      if (atol(margv[1])>65000 || atol(margv[1])<0) {
         emp_prfmsg(NOTABLE);
         return;
         }

      prfmsg(RAN,emptype[usrnum].userid);
      pubout();
      emptype[usrnum].table=atol(margv[1]);
      prfmsg(ETRD,emptype[usrnum].userid);
      pubout();
      emp_prfmsg(MOVED);
      whoin();
      return;
      }

   else if (sameas(margv[0],"/s") || sameas(margv[0],"scan")) {
      prf("  Ruler   ... Table\r");
      for (i=0; i < nterms; i++) {
         if (usroff(i)->state==empstt && usroff(i)->substt==21) {
            prf("%10-s ...   %s\r",emptype[i].userid,spr("%ld",emptype[i].table));
            }
         }
      return;
      }

   else if (sameas(margv[0],"edit") && margc>1 && chkpower()) {

      cnvmod(margv[1]);
      setmem(emppub.userid,10,0);
      setmem(emppub.inmsg,74,0);
      setmem(emppub.outmsg,74,0);

      strcpy(emppub.userid,temp[usrnum].moduserid);
      strcpy(emppub.inmsg,"none");
      strcpy(emppub.outmsg,"none");

      btupmt(usrnum,0);
      dfaSetBlk(pubfile);
      if (dfaAcqEQ(&emppub,temp[usrnum].moduserid,0)) {
         prfmsg(CURRENT,temp[usrnum].moduserid,emppub.inmsg,emppub.outmsg);
         outprf(usrnum);
         }
         else {
         prfmsg(NOT,temp[usrnum].moduserid);
         outprf(usrnum);
         }

      prfmsg(SYSLEFT,emptype[usrnum].userid);
      pubout();
      btupmt(usrnum,':');
      emp_prfmsg(EDITMNU);
      usrptr->substt=45;
      return;
      }

   else if (sameas(margv[0],"delete") && margc>1 && chkpower()) {
      cnvmod(margv[1]);

      dfaSetBlk(wordfile);
      if (dfaAcqEQ(&pubact,temp[usrnum].moduserid,0)) {
         dfaDelete();
         emp_prfmsg(DELETED);
         return;
         }

      prfmsg(NOTDEL,temp[usrnum].moduserid);
      return;
      }

   else if (sameas(margv[0],"change") && margc>1 && chkpower()) {

      cnvmod(margv[1]);
      setmem(pubact.owner,10,0);
      setmem(pubact.orig,74,0);
      setmem(pubact.all,74,0);
      setmem(pubact.word,10,0);

      strcpy(pubact.owner,"all");
      strcpy(pubact.orig,"none");
      strcpy(pubact.all,"none");
      strcpy(pubact.word,temp[usrnum].moduserid);

      btupmt(usrnum,0);
      dfaSetBlk(wordfile);
      if (dfaAcqEQ(&pubact,temp[usrnum].moduserid,0)) {
         prfmsg(CURACT,pubact.word,pubact.owner,pubact.orig,pubact.all);
         outprf(usrnum);
         }
         else {
         prfmsg(NOACT,temp[usrnum].moduserid);
         outprf(usrnum);
         }

      prfmsg(SYSLEFT,emptype[usrnum].userid);
      pubout();
      btupmt(usrnum,':');
      emp_prfmsg(CHAMNU);
      usrptr->substt=46;
      return;
      }

   if (margc==0) {
      whoin();
      return;
      }

   if (usaptr->creds > 1 ||
       acttog==1) {
      if (strlen(margv[0])<11) {
         dfaSetBlk(wordfile);
         if (margc > 1) {
            if (check_act()==1) {
               return;
               }
            }
         cnvmod(margv[0]);

         dfaSetBlk(wordfile);
         if (dfaAcqEQ(&pubact,temp[usrnum].moduserid,0)) {
            if (sameas(pubact.owner,"all") ||
                sameas(pubact.owner,emptype[usrnum].userid) ||
                chkpower()) {

               if (!sameas(pubact.all,"none")) {
                  prfmsg(ACTOUT,emptype[usrnum].userid,pubact.all);
                  pubout();
                  }
               if (!sameas(pubact.orig,"none")) {
                  prfmsg(EPOUT,pubact.orig);
                  }
               return;
               }
            }
         }
      }

   if (usaptr->creds < 1 && tlktog==0) {
      emp_prfmsg(NOTLK);
      usrptr->substt=21;
      return;
      }
   rstrin();
   prfmsg(FROM,class[calc((SHORT)usrnum)],emptype[usrnum].userid,margv[0]);
   pubout();
   emp_prfmsg(SENT);
   usrptr->substt=21;
   return;
   }

VOID
emp_look(VOID)
   {
   SHORT i;
   if (onsys(margv[1])) {
      if (usroff(othusn)->state==empstt && usroff(othusn)->substt==21) {
         prf("\r%s is looking over at %s!\r",usaptr->userid,emptype[othusn].userid);
         pubout();
         prf("\rYou see %s %s slurping some ale and %s\r",
         class[calc((SHORT)othusn)],emptype[othusn].userid,
         (uacoff(othusn)->sex=='M' ? "flirting with the wenches!" : "looking as beautiful as ever!"));
         return;
         }
      }
   for (i=0;i<MAXCHARS;i++) {
      if (sameto(margv[1],pubchar[i].charname) ||
          sameas(margv[1],pubchar[i].chartype)) {
         prf("\r%s %s is eyeing %s %s!\r",class[calc((SHORT)usrnum)],usaptr->userid,
         pubchar[i].chartype,pubchar[i].charname);
         pubout();
         emp_prfmsg(pubchar[i].descript);
         outprf(usrnum);
         clrprf();
         prf("");
         return;
         }
      }
   prf("\rYou look around the crowded room but can't seem to locate %s.\r",
   margv[1]);
   return;
   }

SHORT
check_act(VOID)
   {
   SHORT i,chr=0,hit=-1,r;
   //CHAR gender[10];
   setmbk(empmb);
   for (i=0;i<MAXCHARS;i++) {
      if (sameto(margv[1],pubchar[i].charname) ||
          sameas(margv[1],pubchar[i].chartype)) {
         hit=1;
         chr=i;
         r=rndint(4);
         if (pfnlvl > 2 && (pfnlvl*3 < usrptr->pfnacc)) {
            /* toss user out of pub */
            prfmsg(THROWOT,usaptr->userid);
            pubout();
            prfmsg(FINBCA,usaptr->userid);
            usrptr->substt=1;
            emp_prfmsg(MAINSHT);
            return(1);
            }
         if (pubchar[i].sex==0) {     /* if female */
            if (pfnlvl > 0) {
               prf("***\r%s just slapped %s across the face for being obscene!\r",
               pubchar[i].charname,usaptr->userid);
               pubout();
               prf("***\rFrom %s %s: Better watch it %s!\r",
               pubchar[i].chartype,pubchar[i].charname,usaptr->userid);
               pubcur();
               prf("\r%s just slapped you across the face! <smack!>\r",
               pubchar[i].charname);
               }
               else {
               switch (r) {
               case 1:
                  prf("***\rFrom %s %s: Hey there big %s!  Let's dance!\r",
                  pubchar[i].chartype,pubchar[i].charname,
                  (uacoff(usrnum)->sex == 'M' ? "guy" : "moma"));
                  pubcur();
                  break;
               case 2:
                  prf("***\rFrom %s %s: Ohhh %s, you are such a %s!\r",
                  pubchar[i].chartype,pubchar[i].charname,usaptr->userid,
                  (uacoff(usrnum)->sex == 'M' ? "hunk" : "fox"));
                  pubcur();
                  break;
               case 3:
                  prf("***\rFrom %s %s: Oh really %s?\r",
                  pubchar[i].chartype,pubchar[i].charname,usaptr->userid);
                  pubcur();
                  prf("%s just dumped a pitcher of ale over your head!\r",
                  pubchar[i].charname);
                  break;
               case 4:
                  prf("***\rFrom %s %s: I think I like your style %s!\r",
                  pubchar[i].chartype,pubchar[i].charname,usaptr->userid);
                  pubcur();
                  }
               }
            }
            else {
            if (pfnlvl > 0) {
               prf("***\r%s just bonked %s over the head for being obscene!\r",
               pubchar[i].charname,usaptr->userid);
               pubcur();
               prf("***\rFrom %s %s: Better watch it %s!\r",
               pubchar[i].chartype,pubchar[i].charname,usaptr->userid);
               pubcur();
               prf("\r%s just bonked you over the head!\r",
               pubchar[i].charname);
               }
               else {
               switch (r) {
               case 1:
                  prf("***\rFrom %s %s:  Hey there %s!  What's your sign?\r",
                  pubchar[i].chartype,pubchar[i].charname,
                  (uacoff(usrnum)->sex == 'M' ? "guy" : "moma"));
                  pubcur();
                  break;
               case 2:
                  prf("***\rFrom %s %s:  WOW! %s, you are such a %s!\r",
                  pubchar[i].chartype,pubchar[i].charname,usaptr->userid,
                  (uacoff(usrnum)->sex == 'M' ? "hunk" : "fox"));
                  pubcur();
                  break;
               case 3:
                  prf("***\rFrom %s %s:  Oh yeah?\r",
                  pubchar[i].chartype,pubchar[i].charname);
                  pubcur();
                  prf("%s just dumped a pitcher of ale over your head!\r",
                  pubchar[i].charname);
                  break;
               case 4:
                  prf("***\rFrom %s %s:  I think I'm in love!\r",
                  pubchar[i].chartype,pubchar[i].charname);
                  pubcur();
                  }
               }
            }
         }
      }
   if (hit==1 && pfnlvl != 3) {
      outprf(usrnum);
      clrprf();
      prf("***\r%s is %sing %s the %s!\r",usaptr->userid,margv[0],
      pubchar[chr].charname,pubchar[chr].chartype);
      pubcur();
      }
   prf("");
   return(hit);
   }
/**************************************************************************/
/*                      Edit "in" routine                                 */
/**************************************************************************/

VOID
rou22(VOID)
   {

   if (sameas(margv[0],"x") || sameas(margv[0],"exit") || margc==0) {
      emp_prfmsg(EDITMNU);
      btumil(usrnum,DFTIMX);
      usrptr->substt=45;
      return;
      }

   rstrin();

   setmem(emppub.inmsg,74,0);
   strcpy(emppub.inmsg,margv[0]);
   emp_prfmsg(UPDATED);
   emp_prfmsg(EDITMNU);
   usrptr->substt=45;
   btumil(usrnum,DFTIMX);
   return;
   }

/**************************************************************************/
/*                         Edit "out" routines                            */
/**************************************************************************/

VOID
rou23(VOID)
   {
   if (sameas(margv[0],"x") || sameas(margv[0],"exit") || margc==0) {
      emp_prfmsg(EDITMNU);
      usrptr->substt=45;
      btumil(usrnum,DFTIMX);
      return;
      }

   rstrin();

   setmem(emppub.outmsg,74,0);
   strcpy(emppub.outmsg,margv[0]);
   emp_prfmsg(UPDATED);
   emp_prfmsg(EDITMNU);
   usrptr->substt=45;
   btumil(usrnum,DFTIMX);
   }

/**************************************************************************/
/*                     Change "Change" owner routine                      */
/**************************************************************************/

VOID
rou24(VOID)
   {

   if (sameas(margv[0],"x") || sameas(margv[0],"exit") || margc==0) {
      emp_prfmsg(CHAMNU);
      usrptr->substt=46;
      btumil(usrnum,DFTIMX);
      return;
      }

   rstrin();

   setmem(pubact.owner,10,0);
   strcpy(pubact.owner,margv[0]);
   emp_prfmsg(UPDATED);
   emp_prfmsg(CHAMNU);
   usrptr->substt=46;
   btumil(usrnum,DFTIMX);
   return;
   }

/**************************************************************************/
/*                        Change "self" routine                           */
/**************************************************************************/

VOID
rou25(VOID)
   {

   if (sameas(margv[0],"x") || sameas(margv[0],"exit") || margc==0) {
      emp_prfmsg(CHAMNU);
      usrptr->substt=46;
      btumil(usrnum,DFTIMX);
      return;
      }

   rstrin();
   setmbk(empmb);

   setmem(pubact.orig,74,0);
   strcpy(pubact.orig,margv[0]);

   emp_prfmsg(UPDATED);
   emp_prfmsg(CHAMNU);
   usrptr->substt=46;
   btumil(usrnum,DFTIMX);
   return;
   }

/**************************************************************************/
/*                         Change "all" routine                           */
/**************************************************************************/

VOID
rou26(VOID)
   {

   if (sameas(margv[0],"x") || sameas(margv[0],"exit") || margc==0) {
      emp_prfmsg(CHAMNU);
      usrptr->substt=46;
      btumil(usrnum,DFTIMX);
      return;
      }

   rstrin();

   setmem(pubact.all,74,0);
   strcpy(pubact.all,margv[0]);
   emp_prfmsg(UPDATED);
   emp_prfmsg(CHAMNU);
   usrptr->substt=46;
   btumil(usrnum,DFTIMX);
   }

/* market routine */

VOID
rou27(VOID)
   {

   setmbk(empmb);

   if (sameas(margv[0],"1")) acttog^=1;
   else if (sameas(margv[0],"2")) tlktog^=1;
   else if (sameas(margv[0],"3")) atttog^=1;
   else if (sameas(margv[0],"4")) enttog^=1;
   else if (sameas(margv[0],"5")) exitog^=1;
   else if (sameas(margv[0],"6")) rnktog^=1;
   else if (sameas(margv[0],"7")) wsptog^=1;
   else if (sameas(margv[0],"8")) chatog^=1;
   else if (sameas(margv[0],"9")) pubtog^=1;
   else if (sameas(margv[0],"0")) nlvemp^=1;
   else if (sameas(margv[0],"x")) {
      usrptr->substt=1;
      emp_prfmsg(MAINSHT);
      return;
      }

   usrptr->substt=27;
   prfmsg(SYSMENU,(acttog==0 ? "OFF" : "ON"),
   (tlktog==0 ? "OFF" : "ON"),
   (atttog==0 ? "OFF" : "ON"),
   (enttog==0 ? "OFF" : "ON"),
   (exitog==0 ? "OFF" : "ON"),
   (rnktog==0 ? "OFF" : "ON"),
   (wsptog==0 ? "OFF" : "ON"),
   (chatog==0 ? "OFF" : "ON"),
   (pubtog==0 ? "OFF" : "ON"),
   (nlvemp==0 ? "OFF" : "ON"));
   }

VOID
rou28(VOID)
   {
   }

VOID
rou29(VOID)
   {
   if (sameas(margv[0],"c") || margc==0) {
      btupmt(usrnum,0);
      prf("\r");
      usrptr->substt=16;
      btuinj(usrnum,CYCLE);
      return;
      }

   else if (sameas(margv[0],"n")) {
      btupmt(usrnum,0);
      prf("\r");
      temp[usrnum].pagepause=-1;
      usrptr->substt=16;
      btuinj(usrnum,CYCLE);
      return;
      }

   else if (sameas(margv[0],"q")) {
      btupmt(usrnum,':');
      usrptr->substt=1;
      emp_prfmsg(MAINSHT);
      return;
      }
}

SHORT
rou33(VOID)
   {

   setmbk(empmb);

   if (sameas(margv[0],"x")) {
      emp_prfmsg(MAINSHT);
      usrptr->substt=1;
      return(1);
      }

   if (sameas(margv[0],"s")) {
      emp_prfmsg(SENDWHO);
      usrptr->substt=34;
      return(1);
      }

   else if (sameas(margv[0],"l")) {
      emp_prfmsg(SENDACC);
      temp[usrnum].sendmode=3;
      usrptr->substt=36;
      return(1);
      }
   else if (sameas(margv[0],"?")) {
      emp_prfmsg(MSGMENU);
      usrptr->substt=33;
      return(1);
      }
   else if (sameas(margv[0],"r")) {
      prfmsg(CHECKM,usaptr->userid);

      dfaSetBlk(courfile);
      if (dfaAcqEQ(&ccdata,usaptr->userid,0)) {
         prfmsg(COURMSG,ccdata.cfrom,ccdata.cmessage);
         dfaDelete();
         if (dfaAcqEQ(&ccdata,usaptr->userid,0)) {
            emp_prfmsg(STILMORE);
            emp_prfmsg(MSGSHRT);
            usrptr->substt=33;
            return(1);
            }
         }
         else {
         emp_prfmsg(COURF);
         }

      }
   dfaSetBlk(courfile);
   if (dfaAcqEQ(&ccdata,usaptr->userid,0)) {
      emp_prfmsg(COURWAIT);
      }
   emp_prfmsg(MSGSHRT);
   usrptr->substt=33;
   return(1);
   }

SHORT
rou34(VOID)
   {
   if (sameas(margv[0],"x")) {
      emp_prfmsg(MSGSHRT);
      usrptr->substt=33;
      return(1);
      }

   if (sameas(margv[0],"all")) {
      temp[usrnum].sendmode=2;
      }

   else {
      if (!onsys(margv[0])) {
         emp_prfmsg(BADU);
         emp_prfmsg(MSGSHRT);
         usrptr->substt=33;
         return(1);
         }
      if (usroff(othusn)->state!=empstt) {
         emp_prfmsg(BADU);
         emp_prfmsg(MSGSHRT);
         usrptr->substt=33;
         return(1);
         }
      temp[usrnum].sendusrnum= (SHORT)othusn;
      temp[usrnum].sendmode=1;
      }
   btupmt(usrnum,'>');
   btumil(usrnum,73);
   emp_prfmsg(ENNMSG);
   usrptr->substt=35;
   return(1);
   }

SHORT
rou35(VOID)
   {
   SHORT i;

   setmbk(empmb);
   if (sameas(margv[0],"x")) {
      emp_prfmsg(MSGSHRT);
      btupmt(usrnum,':');
      btumil(usrnum,DFTIMX);
      usrptr->substt=33;
      return(1);
      }

   rstrin();

   if (temp[usrnum].sendmode==1 && margc>0) {
      temp[temp[usrnum].sendusrnum].tempsub= (SHORT)usroff(temp[usrnum].sendusrnum)->substt;
      prfmsg(OUTCOUR,usaptr->userid,margv[0]);
      if (temp[usrnum].sendusrnum!=usrnum) rou3(temp[usrnum].sendusrnum);
      prf("");
      }

   else if (temp[usrnum].sendmode==2) {
      prfmsg(OUTCOUR,usaptr->userid,margv[0]);

      for (i=0; i < nterms ; i++) {
         if (usroff(i)->state==empstt && margc>0 && usrnum!=i) {
            outprf(i);
            }
         }
      clrprf();
      prf("");

      for (i=0; i < nterms; i++) {
         if (usroff(i)->state==empstt && usrnum!=i) {
            temp[i].tempsub= (SHORT)usroff(i)->substt;
            rou3(i);
            }
         }
      clrprf();
      prf("");
      }

   else if (temp[usrnum].sendmode==3 && margc>0) {
      notcour(temp[usrnum].moduserid,usaptr->userid,margv[0]);
      }
   btupmt(usrnum,':');
   btumil(usrnum,DFTIMX);
   emp_prfmsg(COURSNT);
   emp_prfmsg(MSGSHRT);
   usrptr->substt=33;
   return(1);
   }

SHORT
rou36(VOID)
   {

   setmbk(empmb);
   if (sameas(margv[0],"x")) {
      emp_prfmsg(MSGSHRT);
      usrptr->substt=33;
      return(1);
      }

   if (margc>0) {
      cnvmod(margv[0]);
      dfaSetBlk(empfile);
      if (dfaAcqEQ(&empother[usrnum],temp[usrnum].moduserid,0)) {
         emp_prfmsg(LEAVEW);
         btupmt(usrnum,'>');
         btumil(usrnum,73);
         emp_prfmsg(ENNMSG);
         usrptr->substt=35;
         return(1);
         }
      prfmsg(BADUSER,temp[usrnum].moduserid);
      }
   emp_prfmsg(MSGSHRT);
   usrptr->substt=33;
   return(1);
   }

/*        Start of edit command         */

VOID
rou45(VOID)
   {
   setmbk(empmb);
   if (sameas(margv[0],"1")) {
      emp_prfmsg(ENTIN);
      btumil(usrnum,73);
      usrptr->substt=22;
      return;
      }

   else if (sameas(margv[0],"2")) {
      emp_prfmsg(EXIOUT);
      btumil(usrnum,73);
      usrptr->substt=23;
      return;
      }

   else if (sameas(margv[0],"x") || sameas(margv[0],"exit")) {
      dfaSetBlk(pubfile);
      if (dfaAcqEQ(&emptmp,temp[usrnum].moduserid,0)) {
         dfaUpdate(&emppub);
         }
         else {
         dfaSetBlk(pubfile);
         dfaInsert(&emppub);
         }
      prfmsg(REJOINED,emptype[usrnum].userid);
      pubout();
      whoin();
      usrptr->substt=21;
      btumil(usrnum,DFTIMX);
      return;
      }
   prfmsg(BADOP,margv[0]);
   emp_prfmsg(EDITMNU);
   }

VOID
rou46(VOID)
   {
   setmbk(empmb);
   if (sameas(margv[0],"1")) {
      emp_prfmsg(ENTORIG);
      btumil(usrnum,73);
      usrptr->substt=25;
      return;
      }

   else if (sameas(margv[0],"2")) {
      emp_prfmsg(ENTALL);
      btumil(usrnum,73);
      usrptr->substt=26;
      return;
      }

   else if (sameas(margv[0],"3")) {
      emp_prfmsg(ENTOWNER);
      btumil(usrnum,9);
      usrptr->substt=24;
      return;
      }

   else if (sameas(margv[0],"x") || sameas(margv[0],"exit")) {
      dfaSetBlk(wordfile);
      if (dfaAcqEQ(&pubtmp,temp[usrnum].moduserid,0)) {
         dfaUpdate(&pubact);
         }
         else {
         dfaSetBlk(wordfile);
         dfaInsert(&pubact);
         }
      prfmsg(REJOINED,emptype[usrnum].userid);
      pubout();
      whoin();
      usrptr->substt=21;
      return;
      }
   prfmsg(BADACT,margv[2]);
   emp_prfmsg(CHAMNU);
   }

/*************************************************************************/
/*                    News "cycle" routine for empire                     */
/**************************************************************************/

VOID
shownws(VOID)
   {

   if ((btuoba(usrnum))>=500) {
      dfaSetBlk(newsfile);
      dfaGetAbs(&news,emptype[usrnum].line,0);
      if (!dfaQueryNX() || !sameas(news.datestamp,emptype[usrnum].lastd)) {
         emp_prfmsg(ENDNEWS);
         btupmt(usrnum,':');
         emp_prfmsg(MAINSHT);
         outprf(usrnum);
         usrptr->substt=1;
         return;
         }

         else {
         dfaSetBlk(newsfile);
         dfaAbsRec(&news,0);
         if (sameas(news.datestamp,emptype[usrnum].lastd)) {
         prf("%s %s\r",news.datestamp,news.info);
         outprf(usrnum);
         if (temp[usrnum].pagepause!=-1) temp[usrnum].pagepause++;
            }
         }
      emptype[usrnum].line=dfaAbs();
      }
   btuinj(usrnum,CYCLE);
   }

VOID
showact(VOID)
   {
   dfaSetBlk(wordfile);

   if ((btuoba(usrnum))>=500) {
      dfaGetAbs(&pubact,emptype[usrnum].line,0);
      if (!dfaQueryNX()) {
         prf("\r");
         whoin();
         outprf(usrnum);
         btupmt(usrnum,':');
         prf("");
         usrptr->substt=21;
         return;
         }
      dfaAbsRec(&pubact,0);

      if (temp[usrnum].empcount+1>5) {
         prf("\r");
         outprf(usrnum);
         temp[usrnum].empcount=0;
         }

      if (sameas(emptype[usrnum].userid,pubact.owner) ||
          sameas(pubact.owner,"all") || chkpower()) {
         prf("  %-10s",pubact.word);
         outprf(usrnum);
         temp[usrnum].empcount++;
         }
      emptype[usrnum].line=dfaAbs();
      }
   btuinj(usrnum,CYCLE);
   }

/**************************************************************************/
/*                     Notify opponent of attack routine                  */
/**************************************************************************/

VOID
notify(CHAR *text)
   {

   setmbk(empmb);
   if (onsys(empother[usrnum].userid)) {
      if (usroff(othusn)->state==empstt) {
         prfmsg(UPD,emptype[usrnum].userid,text);
         temp[usrnum].tempsub= (SHORT)usroff(othusn)->substt;
         rou3((SHORT)othusn);
         }
      }
   }

VOID
notcour(CHAR *coto,CHAR *cofrom,CHAR *comes)
   {
   setmbk(empmb);
   setmem(ccdata.cto,10,0);
   setmem(ccdata.cfrom,10,0);
   setmem(ccdata.cmessage,76,0);
   strcpy(ccdata.cmessage,comes);
   strcpy(ccdata.cto,coto);
   strcpy(ccdata.cfrom,cofrom);
   dfaSetBlk(courfile);
   if (!(dfaAcqEQ(&cctmp,"Abcdefghij",0))) {
   dfaInsert(&ccdata);
   }
   if (onsys(coto)) {
      if (usroff(othusn)->state==empstt) {
         temp[othusn].tempsub= (SHORT)usroff(othusn)->substt;
         prfmsg(MSGALERT,cofrom);
         outprf(othusn);
         if (othusn!=usrnum) rou3((SHORT)othusn);
         }
      }
   }

/**************************************************************************/
/*    Converts userid to Btrieve useable style and sets up for battle     */
/**************************************************************************/

SHORT
cnv(CHAR* uid)
{
	//SHORT i;
	CHAR bff[UIDSIZ];

	setmbk(empmb);
	setmem(bff, UIDSIZ, 0);
	/*bff[0] = toupper(*uid);

	for (uid++, i = 1; *uid != '\0'; uid++, i++) {
		bff[i] = tolower(*uid);
	}*/
    strncpy(bff, uid, strlen(uid));

	if (strstr(temp[usrnum].attlist, bff) != NULL) {
		emp_prfmsg(ALATT);
		prfmsg(ATTMENU, spr("%ld", emptype[usrnum].nobles),
			spr("%ld", emptype[usrnum].soldiers), emptype[usrnum].spies);
		usrptr->substt = 12;
		return(1);
	}

	else if (onsys(bff)) {
		if (usroff(othusn)->state == empstt) {
			if (usroff(othusn)->substt == 16 ||
				usroff(othusn)->substt == 14) {
				emp_prfmsg(BUSY);
				prfmsg(ATTMENU, spr("%ld", emptype[usrnum].nobles),
					spr("%ld", emptype[usrnum].soldiers), emptype[usrnum].spies);
				usrptr->substt = 12;
				return(1);
			}
			memcpy(&empother[usrnum], &emptype[othusn], sizeof(struct emptype));
			if (emptype[usrnum].land > emptype[othusn].land * 2) {
				emp_prfmsg(OUTRNG);
				prfmsg(ATTMENU, spr("%ld", emptype[usrnum].nobles),
					spr("%ld", emptype[usrnum].soldiers), emptype[usrnum].spies);
				usrptr->substt = 12;
				return(1);
			}

			prfmsg(UNDATT, emptype[usrnum].userid);
			temp[usrnum].tempsub = (SHORT)usroff(othusn)->substt;
			rou3((SHORT)othusn);
			prfmsg(BATTLE, empother[usrnum].userid,
				spr("%ld", empother[usrnum].soldiers), spr("%ld", empother[usrnum].nobles),
				empother[usrnum].palace * 10);
			setmem(temp[usrnum].attid, UIDSIZ, 0);
			strcpy(temp[usrnum].attid, bff);
			strcat(temp[usrnum].attlist, " ");
			strcat(temp[usrnum].attlist, bff);
			usrptr->substt = 14;
			return(1);
		}
	}

	dfaSetBlk(empfile);
	if (dfaAcqEQ(&empother[usrnum], bff, 0)) {
		if (empother[usrnum].valid == 2) {
			if (emptype[usrnum].land > empother[usrnum].land * 2) {
				emp_prfmsg(OUTRNG);
				prfmsg(ATTMENU, spr("%ld", emptype[usrnum].nobles),
					spr("%ld", emptype[usrnum].soldiers), emptype[usrnum].spies);
				usrptr->substt = 12;
				return(1);
			}

			prfmsg(BATTLE, empother[usrnum].userid,
				spr("%ld", empother[usrnum].soldiers), spr("%ld", empother[usrnum].nobles),
				empother[usrnum].palace * 10);
			setmem(temp[usrnum].attid, UIDSIZ, 0);
			strcpy(temp[usrnum].attid, bff);
			strcat(temp[usrnum].attlist, " ");
			strcat(temp[usrnum].attlist, bff);
			usrptr->substt = 14;
			return(1);
		}
	}
	prfmsg(BADUSER, bff);
	prfmsg(ATTMENU, spr("%ld", emptype[usrnum].nobles),
		spr("%ld", emptype[usrnum].soldiers), emptype[usrnum].spies);
	usrptr->substt = 12;
	return(1);
}

/**************************************************************************/
/*                   Leave empire and return to BBS routines              */
/**************************************************************************/

VOID
empexit(VOID)
   {
   SHORT sub;


   sub= (SHORT)usrptr->substt;

   if (sub <5 || sub>10 && sub!=17 && sub!=18 && sub!=30) {
      dfaSetBlk(empfile);
      if (dfaAcqEQ(&spare,emptype[usrnum].userid,0)) {
         dfaUpdate(&emptype[usrnum]);
         }
      }
   emp_prfmsg(LATER);
   usrptr->substt=0;
   btupmt(usrnum,0);
   }

/**************************************************************************/
/*          Display all the users in the game to online users             */
/**************************************************************************/

VOID
others(VOID)
   {
   SHORT i;
   dfaSetBlk(empfile);

   emp_prfmsg(EMPLAND);
   btupmt(usrnum,0);

   if (dfaAcqHI(&spare,1) == 1) {
      if (spare.valid==2 || chkpower()) {
         prf("     %-10s            %-2s  %s %s\r",spare.userid,
         spr("%d",spare.phase),spr("%ld",spare.land),
         (spare.valid==0 ? "(*)" : " "));
         }
      for (i=0;i<100;i++) {
         if (dfaQueryPR()) {
            dfaAbsRec(&spare,1);
            if (spare.valid==2 || chkpower()) {
               prf("     %-10s            %-2s  %s %s\r",spare.userid,
               spr("%d",spare.phase),spr("%ld",spare.land),
               (spare.valid==0 ? "(*)" : " "));
               outprf(usrnum);
               }
            }
         }
      emp_prfmsg(MAYBE);
      btupmt(usrnum,':');
      }
   }

/**************************************************************************/
/*                emp_prfmsg routines for "Y"our stats                        */
/**************************************************************************/

VOID
distat(struct emptype *ptr)
   {

   setmbk(empmb);

   prfmsg(STATUS,class[calc((SHORT)usrnum)],&ptr->userid,spr("%ld",ptr->land),spr("%ld",ptr->money),
   spr("%ld",ptr->grain),ptr->taxrate,spr("%ld",ptr->serfs));

   prfmsg(STATUS2,spr("%ld",ptr->soldiers),spr("%ld",ptr->nobles),
   ptr->palace*10,spr("%ld",ptr->markets),spr("%ld",ptr->mills));

   prfmsg(STATUS3,spr("%ld",ptr->foundries),spr("%ld",ptr->shipyards),
   ptr->spies,ptr->count);
   }

/**************************************************************************/
/*           Checks to see if item entered is valid market item           */
/**************************************************************************/

SHORT
check(VOID)
   {
   SHORT num;

   for (num=0;num<8;num++) {
      if (sameto(margv[2],items[num])) {
         return(num);
         }
      }

   return(-1);
   }

/**************************************************************************/
/*                    "End of turn" routine for empire                    */
/**************************************************************************/

SHORT
empcyc(VOID)
   {
   ULONG tempmill;

   setmbk(empmb);

   if ( (emptype[usrnum].land < 500) || (emptype[usrnum].serfs < 1000)
       || ((LONG)emptype[usrnum].money < 0) ) { /* RH: unsigned stuff again */
      emp_prfmsg(DEAD);
      died();
      usrapp("was caught neglecting the empire and was beheaded"," ");
      btupmt(usrnum,0);
      return(0);
      }

   if (emptype[usrnum].serfs/2>emptype[usrnum].land && emptype[usrnum].mills>=10) {
      tempmill=(ULONG)rndemp(emptype[usrnum].mills/5);
      prfmsg(MILLSAK,spr("%ld",tempmill));
      emptype[usrnum].mills-=tempmill;
      }

   temp[usrnum].x1=(ULONG)emptype[usrnum].markets*(10+(rndint(20)));
   temp[usrnum].x2=(ULONG)emptype[usrnum].mills*(45+(rndint(50))+(emptype[usrnum].serfs/120));
   temp[usrnum].x3=(ULONG)emptype[usrnum].foundries*(110+(rndint(40)));
   temp[usrnum].x4=(ULONG)emptype[usrnum].shipyards*(145+(rndint(60)));
   temp[usrnum].x5=(ULONG)(emptype[usrnum].serfs/emptype[usrnum].taxrate)*rndint(2);
   temp[usrnum].x5/=100;

   chkx();
   if (emptype[usrnum].markets) temp[usrnum].x1+=(ULONG)(emptype[usrnum].land/rndint(50));
   if (emptype[usrnum].mills) temp[usrnum].x2+=(ULONG)(emptype[usrnum].land/rndint(50));
   if (emptype[usrnum].foundries) temp[usrnum].x3+=(ULONG)(emptype[usrnum].land/rndint(50));
   if (emptype[usrnum].shipyards) temp[usrnum].x4+=(ULONG)(emptype[usrnum].land/rndint(50));
   emptype[usrnum].money+=temp[usrnum].x1;
   emptype[usrnum].money+=temp[usrnum].x3;
   emptype[usrnum].money+=temp[usrnum].x4;
   emptype[usrnum].grain+=temp[usrnum].x2;
   emptype[usrnum].money+=temp[usrnum].x5;
   dfaSetBlk(empfile);
   if (dfaAcqEQ(&spare,emptype[usrnum].userid,0)) {
      dfaUpdate(&emptype[usrnum]);
      }
   btupmt(usrnum,':');
   emp_prfmsg(ENTER);
   usrptr->substt=15;
   return(1);
   }

/**************************************************************************/
/*                     Update routines for another user                   */
/**************************************************************************/

VOID
upother(VOID)
   {

   if (onsys(empother[usrnum].userid)) {
      if (usroff(othusn)->state==empstt) {
         memcpy(&emptype[othusn],&empother[usrnum],sizeof(struct emptype));
         return; //return(1);
         }
   }

   dfaSetBlk(empfile);
   if (dfaAcqEQ(&spare,empother[usrnum].userid,0)) {
    	dfaUpdate(&empother[usrnum]);
   }
   }

/**************************************************************************/
/*                    Delete routines for another player                  */
/**************************************************************************/

SHORT
delemp(CHAR *uid)
{

   if (onsys(uid)) {
      if (usroff(othusn)->state==empstt) {
         emp_prfmsg(GONE);
         emp_prfmsg(ENTER);
         outprf(othusn);
         prf("");
         usroff(othusn)->substt=20;
         }
      }

   dfaSetBlk(empfile);
   if (dfaAcqEQ(&spare,uid,0)) {
      dfaDelete();
      return(1);
   }
      return(0);
}

/**************************************************************************/
/*                  "Beheaded" routines for current user                  */
/**************************************************************************/

VOID
died(VOID)
   {
   dfaSetBlk(empfile);
   if (dfaAcqEQ(&spare,emptype[usrnum].userid,0)) {
      dfaDelete();
      }
   }

/**************************************************************************/
/*             Routine to start the "display news" process                */
/**************************************************************************/

VOID
viewnews(VOID)
   {
   dfaSetBlk(newsfile);
   setmbk(empmb);

   if (dfaAcqLO(&news,0)==0) {
      usrapp("******** Empire of the Peasants Initialized"," ");
      }

   prfmsg(TDYNEWS,emptype[usrnum].lastd);
   outprf(usrnum);
   prf("");

   dfaGetLO(&news,0);
   if (sameas(news.datestamp,emptype[usrnum].lastd)) {
      prf("%s %s\r",news.datestamp,news.info);
      }
   emptype[usrnum].line=dfaAbs();

   if (!dfaQueryNX()) {
      emp_prfmsg(ENDNEWS);
      btupmt(usrnum,':');
      emp_prfmsg(MAINSHT);
      usrptr->substt=1;
      return; //return(1);
      }

   usrptr->substt=16;
   temp[usrnum].pagepause=1;
   btuinj(usrnum,CYCLE);
   }

VOID
acts(VOID)
   {
   dfaSetBlk(wordfile);

   if (dfaAcqLO(&pubact,0)==0) {
      emp_prfmsg(NOWORDS);
      usrptr->substt=21;
      whoin();
      return;
      }

   btupmt(usrnum,0);
   emp_prfmsg(WORDS);

   dfaGetLO(&pubact,0);
   if (sameas(emptype[usrnum].userid,pubact.owner) ||
       sameas(pubact.owner,"all") || chkpower()) {
      prf("  %-10s",pubact.word);
      temp[usrnum].empcount=1;
      }
   emptype[usrnum].line=dfaAbs();
   usrptr->substt=28;
   btuinj(usrnum,CYCLE);
   }

/**************************************************************************/
/*                 Append news to the empire news file                    */
/**************************************************************************/

VOID
usrapp(CHAR *app,CHAR *uid)
   {

   SHORT i;
   CHAR text[80];

   setmem(text,80,0);
   strcpy(text,emptype[usrnum].userid);

   for (i=0;i<10-(SHORT)strlen(emptype[usrnum].userid);i++) {
      strcat(text," ");
      }

   strcat(text," -> ");
   strcat(text,app);
   strcat(text,uid);
   setmem(news.info,80,0);
   setmem(news.datestamp,10,0);
   strcpy(news.info,text);
   strcpy(news.datestamp,emptype[usrnum].lastd);
   dfaSetBlk(newsfile);
   if (!(dfaAcqEQ(&newstmp,"99/99/99",0))) {
      dfaInsert(&news);
   }
}

/**************************************************************************/
/*                  Send message to all users in pub                      */
/**************************************************************************/

VOID
pubout(VOID)
   {
   SHORT i;

   for (i=0;i<nterms;i++)
      {
      if (usroff(i)->state==empstt &&
          usroff(i)->substt==21 && i != usrnum &&
          (emptype[i].table==emptype[usrnum].table)) {
         outprf(i);
         }
      }

   clrprf();
   prf("");
   }

VOID
puball(VOID)
   {

   SHORT i;

   for (i=0;i<nterms;i++) {
      if (usroff(i)->state==empstt && usroff(i)->substt==21) {
         outprf(i);
         }
      }

   clrprf();
   prf("");
   }


VOID
pubcur(VOID)
   {

   SHORT i;

   for (i=0;i<nterms;i++) {
      if (usroff(i)->state==empstt && usroff(i)->substt==21 &&
          emptype[usrnum].table==emptype[i].table) {
         outprf(i);
         }
      }

   clrprf();
   prf("");
   }

/**************************************************************************/
/*                   Displays list of all players in pub                  */
/**************************************************************************/

VOID
whoin(VOID)
   {

   SHORT i,cnt=0;
   CHAR whotext[255];
   setmbk(empmb);

   strcpy(whotext," ");

   for (i=0;i<nterms;i++)
      {
      if (usroff(i)->state==empstt && usrnum != i &&
          usroff(i)->substt==21 &&
          (emptype[i].table==emptype[usrnum].table)) {
         strcat(whotext,&uacoff(i)->userid[0]);
         strcat(whotext," ");
         cnt++;
         }
      }

   if (cnt==0) strcat(whotext,"** Pub is Empty **");

   prfmsg(WHO,whotext);
   }

/**************************************************************************/
/*           Converts userid of "Edit" user to Btrieve style              */
/**************************************************************************/

VOID
cnvmod(CHAR *uid)
   {
   SHORT i;

   setmem(temp[usrnum].moduserid,UIDSIZ,0);
   temp[usrnum].moduserid[0]= (CHAR)toupper(*uid);

   for (uid++,i=1; *uid != '\0' ; uid++,i++) {
      temp[usrnum].moduserid[i]=(CHAR)tolower(*uid);
      }
   }

/**************************************************************************/
/*              Routines to determine what "rank" a player is             */
/**************************************************************************/

SHORT
calc(SHORT lnum)
   {
   if (usaptr->creds < 1 && rnktog==0) {   /* RICK: CHANGE THIS BECAUSE CREDITS AREN'T USED ARE THEY? */
      return(0);
      }

   else if (emptype[lnum].land>=7500000   &&
       emptype[lnum].nobles>=100000  &&
       emptype[lnum].markets>=100000 &&
       emptype[lnum].mills>=75000    &&
       emptype[lnum].count>=350) {
      return(5);
      }

   else if (emptype[lnum].land>=2000000  &&
       emptype[lnum].nobles>=50000  &&
       emptype[lnum].markets>=50000 &&
       emptype[lnum].mills>=75000   &&
       emptype[lnum].count>=200) {
      return(4);
      }

   else if (emptype[lnum].land>=100000  &&
       emptype[lnum].nobles>=1500  &&
       emptype[lnum].markets>=2200 &&
       emptype[lnum].mills>=3500   &&
       emptype[lnum].count>=100) {
      return(3);
      }

   else if (emptype[lnum].land>=15000  &&
       emptype[lnum].nobles>=60    &&
       emptype[lnum].markets>=60  &&
       emptype[lnum].mills>=75    &&
       emptype[lnum].count>=50) {
      return(2);
      }

   else if (emptype[lnum].land>=3500   &&
       emptype[lnum].nobles>=15   &&
       emptype[lnum].markets>=15  &&
       emptype[lnum].mills>=20    &&
       emptype[lnum].count>=20) {
      return(1);
      }

   return(0);
   }

VOID
calgrain(VOID)
   {
   SHORT y1;
   ULONG y2;
   y1=(SHORT)(6+rndint(3));
   y2=(ULONG)((emptype[usrnum].serfs/65)+(rndemp(emptype[usrnum].serfs/35)));
   emptype[usrnum].last=(ULONG)(emptype[usrnum].serfs*y1)+(emptype[usrnum].count*y2);
   }

VOID
chkcap(VOID)
{
      if (emptype[usrnum].land < 1) {
         emptype[usrnum].land=1;
      }
      if (emptype[usrnum].money < 1) {
         emptype[usrnum].money=1;
      }
      if (emptype[usrnum].grain < 1) {
         emptype[usrnum].grain=1;
      }
      if (emptype[usrnum].nobles < 1) {
         emptype[usrnum].nobles=1;
      }
      if (emptype[usrnum].serfs < 1) {
         emptype[usrnum].serfs=1;
      }
      if (emptype[usrnum].markets < 1) {
         emptype[usrnum].markets=1;
      }
      if (emptype[usrnum].mills < 1) {
         emptype[usrnum].mills=1;
      }
      if (emptype[usrnum].foundries < 1) {
         emptype[usrnum].foundries=1;
      }
      if (emptype[usrnum].shipyards < 1) {
         emptype[usrnum].shipyards=1;
      }
      if (emptype[usrnum].soldiers < 1) {
         emptype[usrnum].soldiers=1;
      }

      if (emptype[usrnum].phase==0) {
         emptype[usrnum].phase=1;
      }

   if (emptype[usrnum].land > 10000000) {
      emptype[usrnum].land = 8000000+rndemp(2000000);
      }
   if (emptype[usrnum].money > 1500000000) {
      emptype[usrnum].money =  1000000000+rndemp(300000000);
      }
   if (emptype[usrnum].soldiers > 10000000) {
      emptype[usrnum].soldiers = 8000000+rndemp(2000000);
      }
   if (emptype[usrnum].spies > 10) {
      emptype[usrnum].spies = 7+rndint(2);
      }
   if (emptype[usrnum].grain > 1500000000) {
      emptype[usrnum].grain = 1000000000+rndemp(300000000);
      }
   if (emptype[usrnum].nobles > 200000000) {
      emptype[usrnum].nobles = 150000000+rndemp(5000000);
      }
   if (emptype[usrnum].serfs > 10000000) {
      emptype[usrnum].serfs = 8000000+rndemp(2000000);
      }
   if (emptype[usrnum].markets > 1500000000) {
      emptype[usrnum].markets = 1000000000+rndemp(300000000);
      }
   if (emptype[usrnum].mills > 1500000000) {
      emptype[usrnum].mills = 1000000000+rndemp(300000000);
      }
   if (emptype[usrnum].foundries > 1500000000) {
      emptype[usrnum].foundries = 1000000000+rndemp(300000000);
      }
   if (emptype[usrnum].shipyards > 1500000000) {
      emptype[usrnum].shipyards = 1000000000+rndemp(300000000);
      }
}

ULONG
rndemp(ULONG num)
{
   /*union REGS regs;
   static SHORT numy = 3569;
   num=abs(num);
   regs.h.ah=0x2c;
   int86(0x21,&regs,&regs);
   numy = numy + (numy*(regs.h.dh+1)*(regs.h.dl+1)) + regs.h.dl;
   return((ULONG)abs(numy)%num + 1); */
   return((ULONG)elw_random(num) + 1);
   }

SHORT
rndint(SHORT num)
{
/*   union REGS regs;
   static SHORT numy = 3569;
   num=abs(num);
   regs.h.ah=0x2c;
   int86(0x21,&regs,&regs);
   numy = numy + (numy*(regs.h.dh+1)*(regs.h.dl+1)) + regs.h.dl;
   return(abs(numy)%num + 1); */
   return((SHORT)elw_random((ULONG)num)+1);
   }

SHORT
emplogon(VOID)
   {
   setmbk(empmb);
   dfaSetBlk(empfile);
   if (dfaAcqEQ(&emptype[usrnum],usaptr->userid,0)) {
      strcpy(emptype[usrnum].lastd,ncdate(today()));

      prfmsg(WELCOME,usaptr->userid);
      switch(emptype[usrnum].valid) {

      case 0:
         emp_prfmsg(STILLNO);
         return(0);

      case 1:
         emptype[usrnum].valid=2;
         if (dfaAcqEQ(&spare,emptype[usrnum].userid,0)) {
            dfaUpdate(&emptype[usrnum]);
            }
         usrapp("New Player (Fresh blood)"," ");
         prfmsg(NEW,emptype[usrnum].userid);
         emp_prfmsg(MAINSHT);
         btupmt(usrnum,':');
         usrptr->substt=1;
         break;

      case 2:
         prfmsg(WELBACK,emptype[usrnum].userid);
         emp_prfmsg(MAINSHT);
         btupmt(usrnum,':');
         usrptr->substt=1;
         break;
         }
      return(1);
      }
   if (acctog==0) {
      emp_prfmsg(NOTACC);
      return(0);
      }

   prfmsg(WELCOME,usaptr->userid);
   setmem(emptype[usrnum].userid,UIDSIZ,0);
   strcpy(emptype[usrnum].userid,usaptr->userid);
   emptype[usrnum].land=lanemk;
   emptype[usrnum].money=monemk;
   emptype[usrnum].grain=graemk;
   emptype[usrnum].last=0;
   emptype[usrnum].taxrate=taxemk;
   emptype[usrnum].soldiers=solemk;
   emptype[usrnum].serfs=seremk;
   emptype[usrnum].nobles=nobemk;
   emptype[usrnum].palace=palemk;
   emptype[usrnum].markets=maremk;
   emptype[usrnum].mills=milemk;
   emptype[usrnum].foundries=fouemk;
   emptype[usrnum].shipyards=shiemk;
   emptype[usrnum].line=0;
   emptype[usrnum].count=couemk;
   temp[usrnum].nofight=0;
   emptype[usrnum].wins=0;
   emptype[usrnum].play=0;
   emptype[usrnum].table=1;
   emptype[usrnum].valid=0;
   emptype[usrnum].phase=1;
   strcpy(emptype[usrnum].lastd,ncdate(today()));
   emptype[usrnum].lastt=now();

   if (valtog==1 || chkpower()) {
      emptype[usrnum].valid=2;
      dfaInsert(&emptype[usrnum]);
      usrapp("New Player (Fresh blood)"," ");
      prfmsg(NEW,emptype[usrnum].userid);
      emp_prfmsg(MAINSHT);
      btupmt(usrnum,':');
      usrptr->substt=1;
      return(1);
      }

   dfaInsert(&emptype[usrnum]);
   prfmsg(UNVAL,emptype[usrnum].userid);
   emp_prfmsg(LATER);
   outprf(usrnum);
   prf("");
   return(0);
   }

SHORT
chkpower(VOID)
   {
   if (haskey("MASTER") || sameas(usaptr->userid,"Sysop") ||
       sameas(usaptr->userid,gamop1) || sameas(usaptr->userid,gamop2) ||
       sameas(usaptr->userid,gamop3)) return(1);
   return(0);
   }

VOID
chkx(VOID)
   {
   if (temp[usrnum].x1>1800000000) temp[usrnum].x1 = 1000000000+rndemp(300000000);
   if (temp[usrnum].x2>1800000000) temp[usrnum].x2 = 1000000000+rndemp(300000000);
   if (temp[usrnum].x3>1800000000) temp[usrnum].x3 = 1000000000+rndemp(300000000);
   if (temp[usrnum].x4>1800000000) temp[usrnum].x4 = 1000000000+rndemp(300000000);
   if (temp[usrnum].x5>1800000000) temp[usrnum].x5 = 1000000000+rndemp(300000000);
   }

VOID
emprompt(VOID)
{
     rou3((SHORT)usrnum);
     outprf(usrnum);
}

VOID
changemp(VOID)
{
   emptype[usrnum].land=lanemk;
   emptype[usrnum].money=monemk+100000;
   emptype[usrnum].grain=graemk+50000;
   emptype[usrnum].last=0;
   emptype[usrnum].taxrate=taxemk;
   emptype[usrnum].soldiers=solemk;
   emptype[usrnum].serfs=seremk;
   emptype[usrnum].nobles=nobemk;
   emptype[usrnum].palace=palemk;
   emptype[usrnum].markets=maremk+100;
   emptype[usrnum].mills=milemk+100;
   emptype[usrnum].foundries=fouemk+100;
   emptype[usrnum].shipyards=shiemk+100;
   emptype[usrnum].line=0;
   emptype[usrnum].count=couemk;
   temp[usrnum].nofight=0;
   emptype[usrnum].wins=0;
   emptype[usrnum].play=0;
   emptype[usrnum].valid=1;
}

VOID
emp_prfmsg(SHORT msgn)
{
   setmbk(empmb);
   prfmsg(msgn);
}

ULONG elw_random(ULONG high) /* Returns a random number from 0 to high */
{
    return((ULONG)elw_rand(0, high));
}

ULONG elw_rand(ULONG low, ULONG high)    /* Returns a random number from low through high       */
{
    return((ULONG)(elw_rnd() * (DOUBLE)((high + 1) - low) + low));
}

DOUBLE elw_rnd(VOID)       /* Returns a random number from 0.000000 thru 0.999999 */
{
    if (rand() / 32767.0 > 0.5) {
        return(elw__rnd(1));
    }
    return(elw__rnd(0));
}

DOUBLE elw__rnd(SHORT rn)    /* Returns a random number from 0.000000 thru 0.999999 */
{
    static LONG rndtbl[][3] = {
         {125,2796203,0},      {32719,32749,3}
    };
    static LONG seed[] = {
         100001,1
    };

    seed[rn] = (seed[rn] * rndtbl[rn][0] + rndtbl[rn][2]) % rndtbl[rn][1];
    return((DOUBLE)seed[rn] / rndtbl[rn][1]);
}

