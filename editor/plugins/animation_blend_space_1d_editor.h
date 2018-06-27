#ifndef ANIMATION_BLEND_SPACE_1D_EDITOR_H
#define ANIMATION_BLEND_SPACE_1D_EDITOR_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "editor/property_editor.h"
#include "scene/animation/animation_blend_space_1d.h"
#include "scene/gui/button.h"
#include "scene/gui/graph_edit.h"
#include "scene/gui/popup.h"
#include "scene/gui/tree.h"

class AnimationNodeBlendSpace1DEditor : public VBoxContainer {

	GDCLASS(AnimationNodeBlendSpace1DEditor, VBoxContainer)

	Ref<AnimationNodeBlendSpace1D> blend_space;

	HBoxContainer *goto_parent_hb;
	ToolButton *goto_parent;

	PanelContainer *panel;
	ToolButton *tool_blend;
	ToolButton *tool_select;
	ToolButton *tool_create;
	VSeparator *tool_erase_sep;
	ToolButton *tool_erase;
	ToolButton *snap;
	SpinBox *snap_value;

	LineEdit *label_value;
	SpinBox *max_value;
	SpinBox *min_value;

	HBoxContainer *edit_hb;
	SpinBox *edit_value;
	Button *open_editor;

	int selected_point;

	Control *blend_space_draw;

	PanelContainer *error_panel;
	Label *error_label;

	bool updating;

	UndoRedo *undo_redo;

	static AnimationNodeBlendSpace1DEditor *singleton;

	void _blend_space_gui_input(const Ref<InputEvent> &p_event);
	void _blend_space_draw();

	void _update_space();

	void _config_changed(double);
	void _labels_changed(String);
	void _snap_toggled();

	PopupMenu *menu;
	PopupMenu *animations_menu;
	Vector<String> animations_to_add;
	float add_point_pos;
	Vector<float> points;

	bool dragging_selected_attempt;
	bool dragging_selected;
	Vector2 drag_from;
	Vector2 drag_ofs;

	void _add_menu_type(int p_index);
	void _add_animation_type(int p_index);

	void _tool_switch(int p_tool);
	void _update_edited_point_pos();
	void _update_tool_erase();
	void _erase_selected();
	void _edit_point_pos(double);
	void _open_editor();

	void _goto_parent();

	void _removed_from_graph();

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	static AnimationNodeBlendSpace1DEditor *get_singleton() { return singleton; }
	void edit(AnimationNodeBlendSpace1D *p_blend_space);
	AnimationNodeBlendSpace1DEditor();
};

class AnimationNodeBlendSpace1DEditorPlugin : public EditorPlugin {

	GDCLASS(AnimationNodeBlendSpace1DEditorPlugin, EditorPlugin)

	AnimationNodeBlendSpace1DEditor *anim_tree_editor;
	EditorNode *editor;
	Button *button;

public:
	virtual String get_name() const { return "BlendSpace1D"; }

	bool has_main_screen() const { return false; }

	virtual void edit(Object *p_object);
	virtual bool handles(Object *p_object) const;
	virtual void make_visible(bool p_visible);

	AnimationNodeBlendSpace1DEditorPlugin(EditorNode *p_node);
	~AnimationNodeBlendSpace1DEditorPlugin();
};

#endif // ANIMATION_BLEND_SPACE_1D_EDITOR_H
