#include "imguiManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>

#include <GL/gl3w.h>    // Initialize with gl3wInit()

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

imguiManager* imguiManager::imgui = nullptr;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

imguiManager::imguiManager()
{
}

imguiManager::~imguiManager()
{
}

void imguiManager::CreateInstance()
{
	if (imgui == nullptr)
	{
		imgui = new imguiManager();
	}
}

void imguiManager::DeleteInstance()
{
	if (imgui != nullptr)
	{
		delete imgui;
		imgui = nullptr;
	}
}

bool imguiManager::Initialize()
{
	return false;
}
