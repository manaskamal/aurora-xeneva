
#include <QuBase.h>
#include <QuWindow.h>
#include <sys\_ipc.h>
#include <string.h>
#include <stdlib.h>
#include <acrylic.h>
#include <sys\_wait.h>
#include <QuButton.h>
#include <color.h>
#include <QuPanel.h>
#include <QuTextbox.h>

void RegisterObject (QuTextbox *_tb);
void OneClicked (QuWidget *wid, QuWindow *win);
void TwoClicked (QuWidget *wid, QuWindow *win);
void ThreeClicked (QuWidget *wid, QuWindow *win);
void FourClicked (QuWidget *wid, QuWindow *win);
void FiveClicked (QuWidget *wid, QuWindow *win);
void SixClicked (QuWidget *wid, QuWindow *win);
void SevenClicked (QuWidget *wid, QuWindow *win);
void EightClicked (QuWidget *wid, QuWindow *win);
void NineClicked (QuWidget *wid, QuWindow *win);
void ZeroClicked (QuWidget *wid, QuWindow *win);
void AddClicked (QuWidget *wid, QuWindow *win) ;
void MulClicked (QuWidget *wid, QuWindow *win);
void SubClicked (QuWidget *wid, QuWindow *win);
void DivClicked (QuWidget *wid, QuWindow *win);
void EqClicked (QuWidget *wid, QuWindow *win);
void ClearClicked (QuWidget *wid, QuWindow *win);
