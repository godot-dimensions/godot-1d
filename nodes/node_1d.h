#pragma once

#include "../godot_1d_defines.h"

#include "scene/main/canvas_item.h"

class Node1D : public CanvasItem {
	GDCLASS(Node1D, CanvasItem);

	// 1x2 transformation matrix. That's it.
	real_t _position = 0.0;
	real_t _scale = 1.0;

	void _update_transform();

protected:
	static void _bind_methods();

public:
#ifdef CANVAS_ITEM_EDIT_ENABLED
	virtual Dictionary _edit_get_state() const MODULE_OVERRIDE;
	virtual void _edit_set_state(const Dictionary &p_state) MODULE_OVERRIDE;

	virtual void _edit_set_position(const Point2 &p_position) MODULE_OVERRIDE;
	virtual Point2 _edit_get_position() const MODULE_OVERRIDE;

	virtual void _edit_set_scale(const Size2 &p_scale) MODULE_OVERRIDE;
	virtual Size2 _edit_get_scale() const MODULE_OVERRIDE;

	virtual void _edit_set_rotation(real_t p_rotation) MODULE_OVERRIDE;
	virtual real_t _edit_get_rotation() const MODULE_OVERRIDE;
	virtual bool _edit_use_rotation() const MODULE_OVERRIDE;

	virtual void _edit_set_rect(const Rect2 &p_edit_rect) MODULE_OVERRIDE;
#endif // CANVAS_ITEM_EDIT_ENABLED

	real_t get_position() const;
	real_t get_scale() const;
	Transform2D get_transform() const MODULE_OVERRIDE;
	void set_position(const real_t p_position);
	void set_scale(const real_t p_scale);
	void translate(const real_t p_amount);
	void apply_scale(const real_t p_amount);

	real_t get_global_position() const;
	real_t get_global_scale() const;
	void set_global_position(const real_t p_global_position);
	void set_global_scale(const real_t p_global_scale);
};
