#include "PythonTask.h"
#include "lib.h"

PythonTask::PythonTask( Rtos &rtosIn)

: Rtos::Task( rtosIn, 10000/* stack size*/ )
{}

PythonTask::~PythonTask(){

}

extern DigitalIndicator pwrIndicator;
Memory_Flash  programMem(11);

void PythonTask::update( ){
    //pwrIndicator.setBrightness( 20); pwrIndicator.blink(1000, 90);
    loadProgram();
    run();
    stop();
}

void PythonTask::Start( BYTE para ){
    //run();
    //Parameter = para;
    start();
}

void PythonTask::Stop(){
    stopProgram();
    mp_embed_deinit();
    stop();
}

void PythonTask::loadProgram(){
    //addr should always point to the beginning of the program memory, this is where the program length is saved
    programLength = 0;
    programLength |= programMem.read(addr)   << 24;
    programLength |= programMem.read(addr+1) << 16;
    programLength |= programMem.read(addr+2) << 8;
    programLength |= programMem.read(addr+3);

    programData = new uint8_t[programLength];

    //read program
    for( DWORD i=0;i<programLength;i++){
        programData[i] = programMem.read(addr + i + 4);
    }
}

void PythonTask::run(){
    int stack_top;
    mp_embed_init(&heap[0], sizeof(heap), &stack_top);
    mp_embed_exec_mpy(programData, programLength);
    mp_embed_deinit();
}

void PythonTask::stopProgram(){
    static mp_obj_exception_t system_exit;
    system_exit.base.type = &mp_type_SystemExit;
    system_exit.traceback_alloc = 0;
    system_exit.traceback_data = NULL;
    system_exit.args = (mp_obj_tuple_t *)&mp_const_empty_tuple_obj;

    MP_STATE_MAIN_THREAD(mp_pending_exception) = &system_exit;
}

