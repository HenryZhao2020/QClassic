#pragma once

#include "IPieceList.h"

class Playlist : public IPieceList {
public:
    Playlist(const QString &name = "");
};
