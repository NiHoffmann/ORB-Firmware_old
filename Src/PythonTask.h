//*******************************************************************
#ifndef _PYTHON_TASK_H
#define _PYTHON_TASK_H

#include "py/obj.h"
#include "py/mphal.h"
#include "py/runtime.h"
#include "lib.h"

extern "C"{
    #include <port/micropython_embed.h>
}

extern Memory_Flash  programMem;


class PythonTask : public Rtos::Task
{
  public:
    //---------------------------------------------------------------

    BYTE Parameter;
    // This is example 2 script, which will be compiled and executed.
    BYTE *programData;
    BYTE programLength = 0;
    char *program_string =
    "from orb.devices import led\n"
    "l1 = led(led.LED_POWER)\n"
    "l1.blink(1000,90)\n"
    "l2 = led(led.LED_1)\n"
    "l2.blink(2000,30)\n"
    "l3 = led(led.LED_2)\n"
    "l3.value(1)\n"
    "print(led)"
    ;
    DWORD addr = 0;

    // This array is the MicroPython GC heap.
    char heap[8 * 1024];

  public:
    //---------------------------------------------------------------
    PythonTask(Rtos &rtosIn);

    //---------------------------------------------------------------
    virtual ~PythonTask();

    //---------------------------------------------------------------
    virtual void update( );

//    //---------------------------------------------------------------
//    virtual void OnStop(void);
//
//    //---------------------------------------------------------------
//    virtual void OnStart(void);

    //---------------------------------------------------------------
    void Start( BYTE para );

    void Stop();

  private:
    void run();
    void stopProgram();
    void loadProgram();
};
#endif



