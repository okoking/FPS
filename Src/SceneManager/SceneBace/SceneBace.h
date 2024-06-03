#pragma once

class SceneBace
{
public:
	static int g_scene_ID;

	virtual void Init() = 0;
	virtual void Step() = 0;
	virtual void Draw() = 0;
	virtual void Fin() = 0;
};