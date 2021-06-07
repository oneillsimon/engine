%module engine
%{
#include <components/camera_component.h>
%};

%include "../src/components/camera_component.h"

%wxtend CameraComponent {
        swig_type_info* stored_swig_info() {
            return SWIG_TypeQuery("CameraComponent *");
        }
};