#pragma once

#include "ICompositionList.h"

class Playlist : public ICompositionList {
public:
    Playlist(const QString &name = "");
};
