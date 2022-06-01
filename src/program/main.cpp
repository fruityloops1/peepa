#include "lib.hpp"
#include "pe/ProjectActorFactory.h"

MAKE_HOOK(void, actorFactory, (ProjectActorFactory * factory), { new (factory) pe::ProjectActorFactory(); });

extern "C" void exl_main(void* x0, void* x1) {
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    INJECT_HOOK((uintptr_t)0x003d86b0, actorFactory);
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}