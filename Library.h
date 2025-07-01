#pragma once

#include "ICompositionList.h"

class Library : public ICompositionList {
public:
    ~Library();

    void addComposition(Composition *composition) override;
    bool removeComposition(Composition *compositoon) override;
};
