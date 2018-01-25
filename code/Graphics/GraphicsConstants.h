#ifndef GRAPHICSCONSTANTS_H
#define GRAPHICSCONSTANTS_H

#include "../Maths/Math.h"

constexpr float hfov = (90.0f * PI) / 180.0f;
constexpr float tanHalfHFov = (float)tan(hfov / 2.0f);

constexpr float wallHeightScale = 0.2f;

#endif
