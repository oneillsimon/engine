//
// Created by simon on 14/11/2020.
//

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "entity.h"
#include "input_processor.h"

class Application {
private:
    bool close_requested;
public:
    Application();

    Entity* root{};

    virtual void initialise(const InputProcessor& input);
    virtual void update(const double& delta, const InputProcessor& input);
    virtual void render(const double& delta);
    virtual void stop();

    bool is_close_requested() const;
};

#endif //ENGINE_APPLICATION_H
