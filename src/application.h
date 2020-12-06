//
// Created by simon on 14/11/2020.
//

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "entity.h"

class Application {
public:
    Application();

    Entity* root;

    virtual void initialise();
    virtual void input(const double& delta);
    virtual void update(const double& delta);
    virtual void render(const double& delta);
    virtual void stop();
};

#endif //ENGINE_APPLICATION_H
