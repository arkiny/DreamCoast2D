#pragma once

#include <map>

enum Skill_Area_Type{AREA_TYPE1, AREA_TYPE_MAX};

static std::pair<float, float> Area_Type1[][4] = {
		{ { 1.0f, 0.0f }, { 2.0f, 0.0f }, { 2.0f, 1.0f }, { 2.0f, -1.0f } }, // ld = 0
		{ { 0.0f, -1.0f }, { 0.0f, -2.0f }, { -1.0f, -2.0f }, { 1.0f, -2.0f } }, // lu = 1
		{ { 0.0f, 1.0f }, { 0.0f, 2.0f }, { 1.0f, 2.0f }, { -1.0f, 2.0f } }, // rd = 2
		{ { -1.0f, 0.0f }, { -2.0f, 0.0f }, { -2.0f, 1.0f }, { -2.0f, -1.0f } } // ru = 3
};

#define SKILLCOMMAND_MAX 16
#define ENDCOMMAND 99
static int skill1[SKILLCOMMAND_MAX] = { DIRECTION::LEFT, DIRECTION::DOWN, DIRECTION::RIGHT, ENDCOMMAND, };
static int skill2[SKILLCOMMAND_MAX] = { DIRECTION::LEFT, DIRECTION::LEFT, ENDCOMMAND, };