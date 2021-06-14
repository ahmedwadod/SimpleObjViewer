#include <iostream>
#include <string>

#include "Utility\glApp.h"
#include "Utility\ShadersProgram.h"
#include "Utility\Camera.h"
#include "Utility\Mesh.h"
#include "Utility\ObjLoader.h"

GLfloat HexToFloat(int hex) {
	return (float)hex / 255.0f;
}
#define _CC HexToFloat

// Usage text
auto usage = "objviewer <filename>";

// Light vertices
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 lightPos(0.5f, 1.0f, 0.0f);

int main(int argc, char* argv[])
{
	// Parsing the command line arguments
	if (argc < 2) {
		std::cout << usage;
		return 1;
	}
	else if (strcmp("--help", argv[1]) == 0) {
		std::cout << usage;
		return 0;
	}

	// Initializing the App
	GLApp app = GLApp();
	app.AllowFullscreen();
	if (!app.CreateWindow(800, 800, "Simple OBJ Viewer", NULL, NULL)) {
		std::cout << "ERROR: Couldn't start the app!";
		app.Destroy();
		return 1;
	};

	// Creating and compiling the shaders program
	ShadersProgram* shader = new ShadersProgram("Shaders\\VertexShader.glsl", "Shaders\\FragmentShader.glsl");
	if (!shader->HasCompiled()) {
		std::cout << "ERROR: Shader compilation error!";
		app.Destroy();
		return 1;
	}
	// Activate the shader to edit the uniform of light
	shader->Activate();
	// Light data
	glUniform3f(shader->GetUniform("lightColor"), lightColor.x, lightColor.y, lightColor.z);
	glUniform3f(shader->GetUniform("lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Loading the OBJ into a mesh
	Mesh model;
	Texture2D texture;
	if (!LoadObjToMesh(argv[1], model, texture, shader)) {
		std::cout << "ERROR: Model loading error!";
		app.Destroy();
		return 1;
	};

	// Creating the camera
	Camera cam = Camera(model.GetOptimalCameraPosition(0));

	float speed = 0.05f;
	// Enable depth
	glEnable(GL_DEPTH_TEST);
	while (!app.WindowShouldClose()) {
		// Background Color
		glClearColor(_CC(0x11), _CC(0x67), _CC(0xb1), 1.0f);
		// Clear bits
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (app.KeyPress(GLFW_KEY_LEFT_SHIFT))
		{
			speed = 0.1f;
		}
		else {
			speed = 0.01f;
		}
		if (app.KeyPress(GLFW_KEY_D))
		{
			model.Rotate(speed * 5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (app.KeyPress(GLFW_KEY_A))
		{
			model.Rotate(speed * 5.0f, glm::vec3(0.0f, -1.0f, 0.0f));
		}
		if (app.KeyPress(GLFW_KEY_UP))
		{
			cam.Position += speed * cam.Orientation;
		}
		if (app.KeyPress(GLFW_KEY_DOWN))
		{
			cam.Position += -speed * cam.Orientation;
		}
		if (app.KeyPress(GLFW_KEY_LEFT))
		{
			cam.Position += -speed * glm::vec3(1.0f, 0.0f, 0.0f);
		}
		if (app.KeyPress(GLFW_KEY_RIGHT))
		{
			cam.Position += speed * glm::vec3(1.0f, 0.0f, 0.0f);
		}
		if (app.KeyPress(GLFW_KEY_W))
		{
			cam.Position += speed * cam.Up;
		}
		if (app.KeyPress(GLFW_KEY_S))
		{
			cam.Position += -speed * cam.Up;
		}

		// Rednering
		model.Draw("modelMat");
		cam.Render(app.GetWindowWidth(), app.GetWindowHeight(), shader, "cameraMat");

		app.SwapBuffers();

		app.PollEvents();
	}

	model.Delete();
	texture.Delete();
	shader->Delete();
	app.Destroy();
	return 0;
}