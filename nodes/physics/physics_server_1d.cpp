#include "physics_server_1d.h"

#include "scene/scene_string_names.h"

#define DOES_MOVEMENT_OVERLAP_STILL_BODY                                       \
	real_t still_body_position = still_body->get_position();                   \
	real_t still_body_extents = still_body->get_size() / 2;                    \
	real_t still_body_left_extent = still_body_position - still_body_extents;  \
	real_t still_body_right_extent = still_body_position + still_body_extents; \
	if (left_extent < still_body_right_extent && still_body_left_extent < right_extent)

Set<Area1D *>::Element *PhysicsServer1D::register_area(Area1D *p_area) {
	return _areas.insert(p_area);
}

Set<KinematicBody1D *>::Element *PhysicsServer1D::register_kinematic_body(KinematicBody1D *p_body) {
	return _kinematic_bodies.insert(p_body);
}

Set<StaticBody1D *>::Element *PhysicsServer1D::register_static_body(StaticBody1D *p_body) {
	return _static_bodies.insert(p_body);
}

void PhysicsServer1D::unregister_area(Set<Area1D *>::Element *p_area) {
	_areas.erase(p_area);
}

void PhysicsServer1D::unregister_kinematic_body(Set<KinematicBody1D *>::Element *p_body) {
	_kinematic_bodies.erase(p_body);
}

void PhysicsServer1D::unregister_static_body(Set<StaticBody1D *>::Element *p_body) {
	_static_bodies.erase(p_body);
}

real_t PhysicsServer1D::move_and_collide(KinematicBody1D *p_body, const real_t p_movement) {
	real_t body_position = p_body->get_position();
	real_t body_extents = p_body->get_size() / 2;
	real_t start_left_extent = body_position - body_extents;
	real_t start_right_extent = body_position + body_extents;
	real_t left_extent = start_left_extent;
	real_t right_extent = start_right_extent;
	if (p_movement < 0) {
		left_extent += p_movement;
	} else {
		right_extent += p_movement;
	}
	// Start by assuming we can move the whole way.
	real_t new_body_position = body_position + p_movement;

	// Detect collisions with StaticBody1D nodes and push our movement back.
	for (Set<StaticBody1D *>::Element *E = _static_bodies.front(); E; E = E->next()) {
		StaticBody1D *still_body = E->get();
		DOES_MOVEMENT_OVERLAP_STILL_BODY {
			if (body_position < still_body_position) {
				real_t farthest_possible_position = still_body_left_extent - body_extents;
				if (farthest_possible_position < new_body_position) {
					new_body_position = farthest_possible_position;
				}
			} else {
				real_t farthest_possible_position = still_body_right_extent + body_extents;
				if (farthest_possible_position > new_body_position) {
					new_body_position = farthest_possible_position;
				}
			}
		}
	}
	// Detect collisions with KinematicBody1D nodes and push our movement back.
	for (Set<KinematicBody1D *>::Element *E = _kinematic_bodies.front(); E; E = E->next()) {
		KinematicBody1D *still_body = E->get();
		if (still_body == p_body) {
			// We don't want to collide with ourself!
			continue;
		}
		DOES_MOVEMENT_OVERLAP_STILL_BODY {
			if (body_position < still_body_position) {
				real_t farthest_possible_position = still_body_left_extent - body_extents;
				if (farthest_possible_position < new_body_position) {
					new_body_position = farthest_possible_position;
				}
			} else {
				real_t farthest_possible_position = still_body_right_extent + body_extents;
				if (farthest_possible_position > new_body_position) {
					new_body_position = farthest_possible_position;
				}
			}
		}
	}
	// Now that we are done with everything we can collide with, set the new position.
	p_body->set_position(new_body_position);

	// Check overlapping areas. This is only for detection and not for collision.
	real_t end_left_extent = new_body_position - body_extents;
	real_t end_right_extent = new_body_position + body_extents;
	for (Set<Area1D *>::Element *E = _areas.front(); E; E = E->next()) {
		Area1D *still_body = E->get();
		DOES_MOVEMENT_OVERLAP_STILL_BODY {
			bool start_overlaps = start_left_extent < still_body_right_extent && still_body_left_extent < start_right_extent;
			bool end_overlaps = end_left_extent < still_body_right_extent && still_body_left_extent < end_right_extent;
			Variant body_variant = Variant(p_body);
			if (start_overlaps && end_overlaps) {
				// If both of these are true, we are starting and ending
				// inside the Area1D, therefore we are not entering or exiting.
			} else if (start_overlaps) {
				// If we started overlapping but are not overlapping
				// at the end, we are exiting the Area1D.
				still_body->emit_signal(SceneStringNames::get_singleton()->body_exited, body_variant);
			} else if (end_overlaps) {
				// If we ended overlapping but are not overlapping
				// at the start, we are entering the Area1D.
				still_body->emit_signal(SceneStringNames::get_singleton()->body_entered, body_variant);
			} else {
				// If we did not start overlapping and will not end
				// overlapping, we phased through the Area1D, therefore
				// we will emit both entered and exited signals since
				// this would happen if only the framerate was higher.
				still_body->emit_signal(SceneStringNames::get_singleton()->body_entered, body_variant);
				still_body->emit_signal(SceneStringNames::get_singleton()->body_exited, body_variant);
			}
		}
	}
	// Return the remainder of the movement after collision.
	return body_position + p_movement - new_body_position;
}

PhysicsServer1D *PhysicsServer1D::_singleton = nullptr;

PhysicsServer1D *PhysicsServer1D::get_singleton() {
	if (!_singleton) {
		_singleton = memnew(PhysicsServer1D);
	}
	return _singleton;
}

PhysicsServer1D::PhysicsServer1D() {
	//_areas = *memnew(Set<Area1D *>);
}
