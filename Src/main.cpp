//*******************************************************************
/*!
\file   main.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"
#include "Module/ISC.h"
#include "Module/USB/USBdeviceSimpleIO.h"
#include "Module/Download.h"
#include "config.h"

#include "Properties.h"
#include "Settings.h"
#include "Monitor.h"
#include "UserInterface.h"
#include "Remote.h"
#include "PythonTask.h"

//*******************************************************************
Monitor   monitor;

Settings  settings( mem2 );

//*******************************************************************
cISC_UART        ipcBT ( bt );
cISC_USBdevice   ipcUSB( usb, 0/*interfId*/);

//*******************************************************************
AppTask        app      ( rtos                                     );
PythonTask     pythonVm ( rtos                                     );
UserInterface  ui       ( app,         pythonVm,          settings );
Control        ctrl     ( taskManager, ui                          );
Remote         remoteBT ( ipcBT,       ui, ctrl, settings, monitor );
Remote         remoteUSB( ipcUSB,      ui, ctrl, settings, monitor );

//*******************************************************************
int main( void )
{
    usb.start();
    //System::delayMilliSec(100);
    System::delayMilliSec(100);
    pythonVm.Start(0);
  while(1)
  {
    ui.       update();
    //ctrl.     update();
    //remoteBT. update();
    //remoteUSB.update();
  }
}
