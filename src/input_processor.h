//
// Created by simon on 06/12/2020.
//

#ifndef ENGINE_INPUT_PROCESSOR_H
#define ENGINE_INPUT_PROCESSOR_H

class InputProcessor {
protected:
    void* window;
public:
    InputProcessor(void* window);

    virtual bool get_key(int key, int state) const = 0;
};


#endif //ENGINE_INPUT_PROCESSOR_H
