#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 myColor;\n"
"void main()\n"
"{\n"
"   FragColor = myColor;\n"
"}\n\0";



double red, blue, green, red1, blue1,green1 = 0;
double intensity=1, intensity1 = 1;
double rojo=1, azul, verde, intensidad = 1;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
			if (red == 0) red = 1;
			else red = 0;
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		if (green == 0) green = 1;
		else green = 0;
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		if (blue == 0) blue = 1;
		else blue = 0;
	}
	else if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		if (intensity >= 0.1) intensity = intensity - 0.1;
	}
	else if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		if (intensity < 1) intensity = intensity + 0.1;
	}



	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		if (red1 == 0) red1 = 1;
		else red1 = 0;
	}
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (green1 == 0) green1 = 1;
		else green1 = 0;
	}
	else if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		if (blue1 == 0) blue1 = 1;
		else blue1 = 0;
	}
	else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		if (intensity1 >= 0.1) intensity1 = intensity1 - 0.1;
	}
	else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		if (intensity1 < 1) intensity1 = intensity1 + 0.1;
	}


	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		if (rojo == 0) rojo = 1;
		else rojo = 0;
	}
	else if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		if (verde == 0) verde = 1;
		else verde = 0;
	}
	else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		if (azul == 0) azul = 1;
		else azul = 0;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		if (intensidad >= 0.1) intensidad = intensidad - 0.1;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		if (intensidad < 1) intensidad = intensidad + 0.1;
	}



}

int main() {

	cout << "TRIANGULO 1 ----->  ROJO: 1, VERDE: 2, AZUL: 3, BAJAR INTENSIDAD: 4, SUBIR INTENSIDAD: 5" << endl;
	cout << "TRIANGULO 2 ----->  ROJO: Q, VERDE: W, AZUL: E, BAJAR INTENSIDAD: R, SUBIR INTENSIDAD: T" << endl;
	cout << "FONDO ----->  ROJO: R, VERDE: G, AZUL: B, BAJAR INTENSIDAD: ABAJO, SUBIR INTENSIDAD: SUBIR" << endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);


		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	

	unsigned int shaderProgram1 = glCreateProgram();


	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader1, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader1);

	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);

	float t1[] = {
	 0.0f,  0.0f, 0.0f,  // top right
	 -0.3f,  0.6f, 0.0f,  // bottom right
	 -0.6f,  0.0f, 0.0f,  // bottom left
	};

	float t2[] = {
	 0.0f,  0.0f, 0.0f,  // top right
	 0.3f,  0.6f, 0.0f,  // bottom right
	 0.6f,  0.0f, 0.0f,  // bottom left
	};


	unsigned int VBO[2], VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t1), t1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t1), t2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(rojo * intensidad, verde * intensidad, azul * intensidad, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shaderProgram1);
		int vertexColorLocation = glGetUniformLocation(shaderProgram1, "myColor");
		glUniform4f(vertexColorLocation, red * intensity , green * intensity , blue * intensity, 1.0f);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram1);
		int vertexColorLocation1 = glGetUniformLocation(shaderProgram1, "myColor");
		glUniform4f(vertexColorLocation1, red1 * intensity1, green1 * intensity1, blue1 * intensity1, 1.0f);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(6, VAO);
	glDeleteBuffers(6, VBO);

	glfwTerminate();
	return 0;
}