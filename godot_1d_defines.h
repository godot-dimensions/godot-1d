#pragma once
// This file should be included before any other files.

#if GODOT_MODULE
#include "core/object/class_db.h"
#include "core/string/ustring.h"
#include "core/version.h"

#ifndef GODOT_VERSION_MAJOR
// Prior to Godot 4.5, the Godot version macros were just "VERSION_*" which did not match the godot-cpp API.
// See https://github.com/godotengine/godot/pull/103557
#define GODOT_VERSION_MAJOR VERSION_MAJOR
#define GODOT_VERSION_MINOR VERSION_MINOR
#define GODOT_VERSION_PATCH VERSION_PATCH
#endif

#if GODOT_VERSION_MAJOR == 4 && GODOT_VERSION_MINOR > 4
// In Godot 4.5 and later, Math_TAU was replaced with Math::TAU, and a few other things also moved to the Math namespace.
#define ABS Math::abs
#define Math_E Math::E
#define Math_PI Math::PI
#define Math_SQRT12 Math::SQRT12
#define Math_SQRT2 Math::SQRT2
#define Math_TAU Math::TAU
#endif
#else
#error "Must build as a Godot module."
#endif
