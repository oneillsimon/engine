//
// Created by simon on 21/02/2021.
//

#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H

#include <glm/glm.hpp>

class Material {
public:
    glm::vec3 k_a; // Ambient reflectivity.
    glm::vec3 k_d; // Diffuse reflectivity.
    glm::vec3 k_s; // Specular reflectivity.
    float shininess;

public:
    Material(const glm::vec3& k_a, const glm::vec3& k_d, const glm::vec3& k_s, float shininess);
};

namespace Materials {
    static const auto EMERALD        = Material(glm::vec3(0.0215, 0.1745, 0.0215), glm::vec3(0.07568, 0.61424, 0.07568), glm::vec3(0.633, 0.727811, 0.633), 0.6);
    static const auto JADE           = Material(glm::vec3(0.135, 0.2225, 0.1575), glm::vec3(0.54, 0.89, 0.63), glm::vec3(0.316228, 0.316228, 0.316228), 0.1);
    static const auto OBSIDIAN       = Material(glm::vec3(0.05375, 0.05, 0.06625), glm::vec3(0.18275, 0.17, 0.22525), glm::vec3(0.332741, 0.328634, 0.346435), 0.3);
    static const auto PEARL          = Material(glm::vec3(0.25, 0.20725, 0.20725), glm::vec3(1, 0.829, 0.829), glm::vec3(0.296648, 0.296648, 0.296648), 0.088);
    static const auto RUBY           = Material(glm::vec3(0.1745, 0.01175, 0.01175), glm::vec3(0.61424, 0.04136, 0.04136), glm::vec3(0.727811, 0.626959, 0.626959), 0.6);
    static const auto TURQUOISE      = Material(glm::vec3(0.1, 0.18725, 0.1745), glm::vec3(0.396, 0.74151, 0.69102), glm::vec3(0.297254, 0.30829, 0.306678), 0.1);
    static const auto BRASS          = Material(glm::vec3(0.329412, 0.223529, 0.027451), glm::vec3(0.780392, 0.568627, 0.113725), glm::vec3(0.992157, 0.941176, 0.807843), 0.21794872);
    static const auto BRONZE         = Material(glm::vec3(0.2125, 0.1275, 0.054), glm::vec3(0.714, 0.4284, 0.18144), glm::vec3(0.393548, 0.271906, 0.166721), 0.2);
    static const auto CHROME         = Material(glm::vec3(0.25, 0.25, 0.25), glm::vec3(0.4, 0.4, 0.4), glm::vec3(0.774597, 0.774597, 0.774597), 0.6);
    static const auto COPPER         = Material(glm::vec3(0.19125, 0.0735, 0.0225), glm::vec3(0.7038, 0.27048, 0.0828), glm::vec3(0.256777, 0.137622, 0.086014), 0.1);
    static const auto GOLD           = Material(glm::vec3(0.24725, 0.1995, 0.0745), glm::vec3(0.75164, 0.60648, 0.22648), glm::vec3(0.628281, 0.555802, 0.366065), 0.4);
    static const auto SILVER         = Material(glm::vec3(0.19225, 0.19225, 0.19225), glm::vec3(0.50754, 0.50754, 0.50754), glm::vec3(0.508273, 0.508273, 0.508273), 0.4);
    static const auto BLACK_PLASTIC  = Material(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.01, 0.01, 0.01), glm::vec3(0.50, 0.50, 0.50), 0.25);
    static const auto CYAN_PLASTIC   = Material(glm::vec3(0.0, 0.1, 0.06), glm::vec3(0.0, 0.50980392, 0.50980392), glm::vec3(0.50196078, 0.50196078, 0.50196078), 0.25);
    static const auto GREEN_PLASTIC  = Material(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1, 0.35, 0.1), glm::vec3(0.45, 0.55, 0.45), 0.25);
    static const auto RED_PLASTIC    = Material(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.5, 0.0, 0.0), glm::vec3(0.7, 0.6, 0.6), 0.25);
    static const auto WHITE_PLASTIC  = Material(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.55, 0.55, 0.55), glm::vec3(0.70, 0.70, 0.70), 0.25);
    static const auto YELLOW_PLASTIC = Material(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.5, 0.5, 0.0), glm::vec3(0.60, 0.60, 0.50), 0.25);
    static const auto BLACK_RUBBER   = Material(glm::vec3(0.02, 0.02, 0.02), glm::vec3(0.01, 0.01, 0.01), glm::vec3(0.4, 0.4, 0.4), 0.078125);
    static const auto CYAN_RUBBER    = Material(glm::vec3(0.0, 0.05, 0.05), glm::vec3(0.4, 0.5, 0.5), glm::vec3(0.04, 0.7, 0.7), 0.078125);
    static const auto GREEN_RUBBER   = Material(glm::vec3(0.0, 0.05, 0.0), glm::vec3(0.4, 0.5, 0.4), glm::vec3(0.04, 0.7, 0.04), 0.078125);
    static const auto RED_RUBBER     = Material(glm::vec3(0.05, 0.0, 0.0), glm::vec3(0.5, 0.4, 0.4), glm::vec3(0.7, 0.04, 0.04), 0.078125);
    static const auto WHITE_RUBBER   = Material(glm::vec3(0.05, 0.05, 0.05), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.7, 0.7, 0.7), 0.078125);
    static const auto YELLOW_RUBBER  = Material(glm::vec3(0.05, 0.05, 0.0), glm::vec3(0.5, 0.5, 0.4), glm::vec3(0.7, 0.7, 0.04), 0.078125);

};


#endif //ENGINE_MATERIAL_H
