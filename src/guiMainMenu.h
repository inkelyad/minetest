/*
Minetest-c55
Copyright (C) 2010-2012 celeron55, Perttu Ahola <celeron55@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef GUIMAINMENU_HEADER
#define GUIMAINMENU_HEADER

#include "common_irrlicht.h"
#include "modalMenu.h"
#include <string>
#include <list>
#include "subgame.h"
class IGameCallback;

struct MainMenuData
{
	// These are in the native format of the gui elements
	// Generic
	int selected_tab;
	// Client options
	std::wstring address;
	std::wstring port;
	std::wstring name;
	std::wstring password;
	bool fancy_trees;
	bool smooth_lighting;
	bool clouds_3d;
	bool opaque_water;
	// Server options
	bool creative_mode;
	bool enable_damage;
	int selected_world;
	bool simple_singleplayer_mode;
	// Actions
	WorldSpec delete_world_spec;
	std::wstring create_world_name;
	std::string create_world_gameid;

	std::vector<WorldSpec> worlds;
	std::vector<SubgameSpec> games;

	MainMenuData():
		// Generic
		selected_tab(0),
		// Client opts
		fancy_trees(false),
		smooth_lighting(false),
		// Server opts
		creative_mode(false),
		enable_damage(false),
		selected_world(0),
		simple_singleplayer_mode(false)
	{}
};

class GUIMainMenu : public GUIModalMenu
{
public:
	GUIMainMenu(gui::IGUIEnvironment* env,
			gui::IGUIElement* parent, s32 id,
			IMenuManager *menumgr,
			MainMenuData *data,
			IGameCallback *gamecallback);
	~GUIMainMenu();
	
	void removeChildren();
	// Remove and re-add (or reposition) stuff
	void regenerateGui(v2u32 screensize);
	void drawMenu();
	void readInput(MainMenuData *dst);
	void acceptInput();
	bool getStatus()
	{ return m_accepted; }
	bool OnEvent(const SEvent& event);
	void createNewWorld(std::wstring name, std::string gameid);
	void deleteWorld(WorldSpec spec);
	int getTab();
	
private:
	MainMenuData *m_data;
	bool m_accepted;
	IGameCallback *m_gamecallback;

	gui::IGUIEnvironment* env;
	gui::IGUIElement* parent;
	s32 id;
	IMenuManager *menumgr;
	
	bool m_is_regenerating;
	v2s32 m_topleft_client;
	v2s32 m_size_client;
	v2s32 m_topleft_server;
	v2s32 m_size_server;
};

#endif

