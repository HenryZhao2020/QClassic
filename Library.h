#pragma once

#include "ICompositionList.h"

class Library : public ICompositionList {
public:
    ~Library();

    bool removeComposition(Composition *compositoon) override;
};
