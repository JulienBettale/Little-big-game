/*
 *  EditorMode.cpp
 *
 *      Create on : 30/03/2020
 *             by : bettal_j
 *
 */

#include "stdafx.h"
#include "EditorMode.h"

EditorMode::EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: stateData(state_data), tileMap(tile_map), editorStateData(editor_state_data)
{

}

EditorMode::~EditorMode()
{

}

const bool EditorMode::getKeytime()
{
	if (*this->editorStateData->keytime >= *this->editorStateData->keytimeMax)
	{
		*this->editorStateData->keytime = 0.f;
		return true;
	}

	return false;
}