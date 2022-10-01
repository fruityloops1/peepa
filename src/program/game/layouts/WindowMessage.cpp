#include "game/layouts/WindowMessage.h"
#include "al/util/LayoutUtil.h"
#include "al/util/NerveUtil.h"
#include "pe/util/Nerve.h"

namespace {

NERVE_DEF(WindowMessage, Appear);
NERVE_DEF(WindowMessage, Wait);

}

void WindowMessage::appearWithSingleMessage(const char16_t* message)
{
    al::startAction(this, "Appear", "Main");
    LayoutActor::appear();
    mMessage = message;
    mPageAmount = 0;
    mPageIndex = 0;
    al::setPaneString(this, "TxtMessage", this->mMessage);
    al::setNerve(this, &nrvWindowMessageAppear);
}