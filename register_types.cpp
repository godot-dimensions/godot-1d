#include "register_types.h"

#include "nodes/audio_listener_1d.h"
#include "nodes/audio_player_1d.h"
#include "nodes/camera_1d.h"
#include "nodes/physics/area_1d.h"
#include "nodes/physics/kinematic_body_1d.h"
#include "nodes/physics/physics_server_1d.h"
#include "nodes/physics/static_body_1d.h"
#include "nodes/sprite_1d.h"

// The module can use CORE or SERVERS initialization levels. In modules, we want to
// register as early as possible, so that other modules can depend on this module.
#define MODULE_INITIALIZATION_LEVEL_CORE_OR_EARLIEST MODULE_INITIALIZATION_LEVEL_CORE

void initialize_1d_module(ModuleInitializationLevel p_level) {
	// Classes MUST be registered in inheritance order, then dependency order.
	// When the inheritance and dependency doesn't matter, then alphabetical order is used.
	if (p_level == MODULE_INITIALIZATION_LEVEL_CORE_OR_EARLIEST) {
		ClassDB::register_class<Node1D>();
		ClassDB::register_class<AudioListener1D>();
		ClassDB::register_class<AudioPlayer1D>();
		ClassDB::register_class<Camera1D>();
		ClassDB::register_class<Sprite1D>();
		// Physics.
		ClassDB::register_abstract_class<CollisionObject1D>();
		ClassDB::register_class<Area1D>();
		ClassDB::register_class<KinematicBody1D>();
		ClassDB::register_class<StaticBody1D>();
		PhysicsServer1D::initialize_singleton();
	}
}

void uninitialize_1d_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_CORE_OR_EARLIEST) {
		PhysicsServer1D::uninitialize_singleton();
	}
}
