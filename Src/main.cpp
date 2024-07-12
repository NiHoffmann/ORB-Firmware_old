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

extern "C"{
    #include <port/micropython_embed.h>
}
//*******************************************************************
Monitor   monitor;

Settings  settings( mem2 );

//*******************************************************************
cISC_UART        ipcBT ( bt );
cISC_USBdevice   ipcUSB( usb, 0/*interfId*/);

//*******************************************************************
AppTask        app      ( rtos                                     );
UserInterface  ui       (              app,      settings          );
Control        ctrl     ( taskManager, ui                          );
Remote         remoteBT ( ipcBT,       ui, ctrl, settings, monitor );
Remote         remoteUSB( ipcUSB,      ui, ctrl, settings, monitor );


// This is example 2 script, which will be compiled and executed.
static const uint8_t program[]  = {
  0x4d, 0x06, 0x00, 0x1f, 0x06, 0x01, 0x81, 0x16, 0x43, 0x3a, 0x2f, 0x55, 0x73, 0x65, 0x72, 0x73,
  0x2f, 0x6e, 0x69, 0x6c, 0x73, 0x39, 0x2f, 0x44, 0x6f, 0x63, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x73,
  0x2f, 0x61, 0x72, 0x62, 0x65, 0x69, 0x74, 0x2f, 0x6f, 0x72, 0x62, 0x2f, 0x6f, 0x72, 0x62, 0x2f,
  0x6d, 0x69, 0x63, 0x72, 0x6f, 0x70, 0x79, 0x74, 0x68, 0x6f, 0x6e, 0x2f, 0x6d, 0x70, 0x79, 0x2d,
  0x63, 0x72, 0x6f, 0x73, 0x73, 0x2f, 0x62, 0x75, 0x69, 0x6c, 0x64, 0x2f, 0x74, 0x65, 0x73, 0x74,
  0x2e, 0x70, 0x79, 0x00, 0x0f, 0x0e, 0x63, 0x5f, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x00, 0x0a, 0x68,
  0x65, 0x6c, 0x6c, 0x6f, 0x00, 0x0c, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x32, 0x00, 0x81, 0x77, 0x08,
  0x03, 0x32, 0x2e, 0x35, 0x82, 0x58, 0x10, 0x08, 0x01, 0x26, 0x2b, 0x2b, 0x80, 0x51, 0x1b, 0x02,
  0x16, 0x02, 0x11, 0x05, 0x11, 0x02, 0x14, 0x03, 0x36, 0x00, 0x34, 0x01, 0x59, 0x11, 0x05, 0x11,
  0x02, 0x14, 0x04, 0x36, 0x00, 0x34, 0x01, 0x59, 0x11, 0x05, 0x23, 0x00, 0x34, 0x01, 0x59, 0x51,
  0x63
};

// This is example 2 script, which will be compiled and executed.
static const char *program_string =
    "from orb import Port\n"
    "from orb import Motor\n"
    "from orb import Led\n"
    "m1 = Motor(Port.M2)\n"
    "m1.run(5)\n"
    "l1 = Led(Led.LED_POWER)\n"
    "l1.blink(1000,90)\n"
    "l2 = Led(Led.LED_1)\n"
    "l2.blink(2000,30)\n"
    "l3 = Led(Led.LED_2)\n"
    "l3.value(1)\n"
    ;

// This array is the MicroPython GC heap.
static char heap[8 * 1024];
//*******************************************************************
int main( void )
{
    int stack_top;
    mp_embed_init(&heap[0], sizeof(heap), &stack_top);
    // Run the example scripts (they will be compiled first).
    mp_embed_exec_str(program_string);
    //mp_embed_exec_mpy(program, 161);
    // Deinitialise MicroPython.
    mp_embed_deinit();

    usb.start();
    System::delayMilliSec(100);
  while(1)
  {
    ui.       update();
    ctrl.     update();
    remoteBT. update();
    remoteUSB.update();
  }
}
