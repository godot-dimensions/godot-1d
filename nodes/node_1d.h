#ifndef NODE1D_H
#define NODE1D_H

#include "scene/2d/canvas_item.h"

class Node1D : public CanvasItem {
	GDCLASS(Node1D, CanvasItem);

	// 1x2 transformation matrix plus a Z-index. That's it.
	real_t _position = 0.0;
	real_t _scale = 1.0;
	int _z_index = 0;
	bool _z_relative = true;

	void _update_transform();

protected:
	static void _bind_methods();

public:
#ifdef TOOLS_ENABLED
	virtual Dictionary _edit_get_state() const;
	virtual void _edit_set_state(const Dictionary &p_state);

	virtual void _edit_set_position(const Point2 &p_position);
	virtual Point2 _edit_get_position() const;

	virtual void _edit_set_scale(const Size2 &p_scale);
	virtual Size2 _edit_get_scale() const;

	virtual void _edit_set_rotation(float p_rotation);
	virtual float _edit_get_rotation() const;
	virtual bool _edit_use_rotation() const;

	virtual void _edit_set_rect(const Rect2 &p_edit_rect);
#endif

	real_t get_position() const;
	real_t get_scale() const;
	Transform2D get_transform() const;
	void set_position(const real_t p_position);
	void set_scale(const real_t p_scale);
	void translate(const real_t p_amount);
	void apply_scale(const real_t p_amount);

	real_t get_global_position() const;
	real_t get_global_scale() const;
	void set_global_position(const real_t p_global_position);
	void set_global_scale(const real_t p_global_scale);

	void set_z_index(const int p_z);
	int get_z_index() const;
	void set_z_as_relative(const bool p_enabled);
	bool is_z_relative() const;
};

#endif // NODE1D_H
