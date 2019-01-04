#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <time.h>

#include "graphics\BatchRender.h"
#include "graphics\Shader.h"

#include "Game.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Game game;

float timeElapsed;
int frameCount;

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// Sets version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Changes how VAO works
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "There was an error creating the window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error initializing glew." << '\n';

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetKeyCallback(window, key_callback);

	// TODO: Shader
	Shader shader("src/graphics/shaders/basic.vert", "src/graphics/shaders/basic.frag");
	shader.useShader();

	glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::mat4 projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::lookAt(
		cam_pos,
		cam_pos + cam_front,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 MVP = projection * view * model;

	unsigned int mvp_uniform = glGetUniformLocation(shader.m_shaderProgram, "u_MVP");
	glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, &MVP[0][0]);

	// TODO: MVP
	// TODO: Finish Shader
	// TODO: Camera
	// TODO: Game Struct
	// TODO: Input

	float maxVel = 64.0f;

	float vel = maxVel;
	float vel2 = maxVel;

	double lastTime = glfwGetTime();
	double deltaTime = 0, nowTime = 0;
	timeElapsed = 0;
	frameCount = 0;


	game.init();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		lastTime = nowTime;
		nowTime = glfwGetTime();
		deltaTime = nowTime - lastTime;

		timeElapsed += deltaTime;
		if (timeElapsed >= .016) {
			++frameCount;
			timeElapsed -= .016;
		}

		/* Poll for and process events */
		glfwPollEvents();
		game.update(deltaTime, frameCount);

		// Update everything

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw
		game.draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		game.m_moveKeys.push(key);
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		game.m_moveKeys.push(key);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		game.m_actionKeys.push(key);

	if (action == GLFW_PRESS)
		game.m_pressedKeys[key] = true;
	if (action == GLFW_RELEASE)
		game.m_pressedKeys[key] = false;
}