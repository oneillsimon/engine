//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

#include "input_processor.h"

class Component {
public:
    Component();

    virtual ~Component();

    virtual void initialise();
    virtual void update(double delta, const InputProcessor& input);
    virtual void render(double delta) const;
};


#endif //ENGINE_COMPONENT_H
