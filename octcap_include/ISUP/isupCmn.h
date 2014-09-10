/***********************************************************
*
* 
*
* $Source: /ISUP/code/testAndTut/isupCmn.h $
* $Revision: 2.0 $
* 
* 
***********************************************************/
#include <IsupSMProbe.h>
#include <IsupBPProbe.h>

//-------------------------------------------------------
// Definition of classes used in isupClientXY/ServerXY.C
//-------------------------------------------------------

//--------------------------------------------------------------------------
// Class RecvToDo: store active SM probe and respective pending messages when
//                 there is work to do.....
//
//--------------------------------------------------------------------------
class RecvToDo
{
   IsupSMProbe   *L_activeProbe;
   int           nbOfPendingIndic;
   
public: 
   RecvToDo (IsupSMProbe *probe, int indic) {
      L_activeProbe= probe;
      nbOfPendingIndic= indic;
   }
   ~RecvToDo (void) {};
   IsupSMProbe * probe (void) { return L_activeProbe; };
   int           indic (void) { return nbOfPendingIndic; };
};

//--------------------------------------------------------------------------
// Class RecvToDoBP: store active BP probe and respective pending messages when
//                   there is work to do.....
//
//--------------------------------------------------------------------------
class RecvToDoBP
{
   IsupBPProbe   *L_activeProbe;
   int           nbOfPendingIndic;
   
public: 
   RecvToDoBP (IsupBPProbe *probe, int indic) {
      L_activeProbe= probe;
      nbOfPendingIndic= indic;
   }
   ~RecvToDoBP (void) {};
   IsupBPProbe * probe (void) { return L_activeProbe; };
   int           indic (void) { return nbOfPendingIndic; };
};


