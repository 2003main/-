#ifndef __GRAY_GO_H
#define __GRAY_GO_H 
//8右1左
/*********前自排一路灰度*********/

#define F1 PFin(8)   //EDIO8
#define F2 PFin(7)   //EDIO7
#define F3 PFin(6)   //EDIO6
#define F4 PFin(5)   //EDIO5
#define F5 PFin(4)   //EDIO4
#define F6 PFin(2)   //EDIO3
#define F7 PFin(1)   //EDIO2
#define F8 PFin(0)  //EDIO1

///**********后自排一路灰度********/

#define D1 PEin(1)   //EDIO9
#define D2 PEin(0)   //EDIO10
#define D3 PBin(9)   //EDIO11
#define D4 PBin(8)   //EDIO12
#define D5 PBin(7)   //EDIO13
#define D6 PBin(6)   //EDIO14
#define D7 PBin(5)   //EDIO15
#define D8 PBin(4)  //EDIO16

void SearchRun(void);
void anti_SearchRun(void);
void LIAP(void);
void anti_LIAP(void);
#endif
