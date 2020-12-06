//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H


class Component {
public:
    Component();

    virtual ~Component() = 0;

    virtual void initialise() = 0;
    virtual void update(float delta) = 0;
    virtual void render(float delta) const = 0;
};


#endif //ENGINE_COMPONENT_H
