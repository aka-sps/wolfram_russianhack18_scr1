#include "test.h"
#include "scr1_wrapper.h"

static SCR1::processor* p_proc;

mint
WolframLibrary_getVersion()
{
    return WolframLibraryVersion;
}

DLLEXPORT
int
WolframLibrary_initialize(WolframLibraryData libData)
{
    p_proc = new SCR1::processor;
    return 0;
}

void
WolframLibrary_uninitialize(WolframLibraryData libData)
{
    delete p_proc;
    return;
}

int
constantzero(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    MArgument_setInteger(Res, 0);
    return LIBRARY_NO_ERROR;
}

int
hello(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    mint I0;
    mint I1;
    mint I2;
    I0 = MArgument_getInteger (Args[0]);
    I1 = MArgument_getInteger (Args[1]);
    // p_proc->step();
    I2 = 0;
    MArgument_setInteger (Res, I2);
    return LIBRARY_NO_ERROR;
}

int
reset(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    const char *string = MArgument_getUTF8String(Args[0]);;
    try {
        p_proc->reset(string);
    } catch (...) {
        res = LIBRARY_FUNCTION_ERROR;
    }
    return res;
}

int
run(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    try {
        p_proc->run();
    } catch (...) {
        res = LIBRARY_FUNCTION_ERROR;
    }
    return res;
}

int
step(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    try {
        p_proc->step();
    } catch (...) {
        res = LIBRARY_FUNCTION_ERROR;
    }
    return res;
}

int
is_finished(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    mbool state = p_proc->is_finished();
    libData->Message("is_finished");
    MArgument_setBoolean(Res, state);
    return res;
}

int
get_pc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    mint pc = p_proc->get_pc();
    MArgument_setInteger(Res, pc);
    return res;
}

int
next_pc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    mint pc = p_proc->next_pc();
    MArgument_setInteger(Res, pc);
    return res;
}
