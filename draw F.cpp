#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.17f, 0.31f, 0.64f, 1.0f);\n"
"}\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.5f, 0.8f, 0.77f, 1.0f);\n"
"}\0";

const char* fragmentShaderSource3 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.1f, 0.8f, 0.6f, 1.0f);\n"
"}\0";


const char* fragmentShaderSource4 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.23f, 0.44f, 0.0f, 1.0f);\n"
"}\0";


const char* fragmentShaderSource5 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.81f, 0.12f, 0.34f, 1.0f);\n"
"}\0";


const char* fragmentShaderSource6 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.9f, 0.0f, 0.4f, 1.0f);\n"
"}\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmentShader3 = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmentShader4 = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmentShader5 = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmentShader6 = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int shaderProgram1 = glCreateProgram();
	unsigned int shaderProgram2 = glCreateProgram();
	unsigned int shaderProgram3 = glCreateProgram();
	unsigned int shaderProgram4 = glCreateProgram();
	unsigned int shaderProgram5 = glCreateProgram();
	unsigned int shaderProgram6 = glCreateProgram();


	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader1, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader1);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	glShaderSource(fragmentShader3, 1, &fragmentShaderSource3, NULL);
	glCompileShader(fragmentShader3);
	glShaderSource(fragmentShader4, 1, &fragmentShaderSource4, NULL);
	glCompileShader(fragmentShader4);
	glShaderSource(fragmentShader5, 1, &fragmentShaderSource5, NULL);
	glCompileShader(fragmentShader5);
	glShaderSource(fragmentShader6, 1, &fragmentShaderSource6, NULL);
	glCompileShader(fragmentShader6);


	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	glAttachShader(shaderProgram3, vertexShader);
	glAttachShader(shaderProgram3, fragmentShader3);
	glLinkProgram(shaderProgram3);

	glAttachShader(shaderProgram4, vertexShader);
	glAttachShader(shaderProgram4, fragmentShader4);
	glLinkProgram(shaderProgram4);

	glAttachShader(shaderProgram5, vertexShader);
	glAttachShader(shaderProgram5, fragmentShader5);
	glLinkProgram(shaderProgram5);

	glAttachShader(shaderProgram6, vertexShader);
	glAttachShader(shaderProgram6, fragmentShader6);
	glLinkProgram(shaderProgram6);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);
	glDeleteShader(fragmentShader3);
	glDeleteShader(fragmentShader4);
	glDeleteShader(fragmentShader5);
	glDeleteShader(fragmentShader6);

	float t1[] = {
	 0.0f,  0.0f, 0.0f,  // top right
	 0.5f,  0.0f, 0.0f,  // bottom right
	 0.5f,  0.2f, 0.0f,  // bottom left
	};

	float t2[] = {
	 0.0f,  0.0f, 0.0f,  // top right
	 0.0f,  0.2f, 0.0f,  // bottom right
	 0.5f,  0.2f, 0.0f,  // bottom left
	};

	float t3[] = {
	 0.0f,  0.4f, 0.0f,  // top right
	 0.0f, -0.4f, 0.0f,  // bottom right
	-0.2f, -0.4f, 0.0f,  // bottom left
	};

	float t4[] = {
	 0.0f,  0.4f, 0.0f,  // top right
	 -0.2f, 0.4f, 0.0f,  // bottom right
	-0.2f, -0.4f, 0.0f,  // bottom left
	};

	float t5[] = {
	 -0.2f,  0.6f, 0.0f,  // top right
	 -0.2f,  0.4f, 0.0f,  // bottom right
	 0.5f,  0.6f, 0.0f,  // bottom left
	};

	float t6[] = {
	 -0.2f,  0.4f, 0.0f,  // top right
	 0.5f, 0.4f, 0.0f,  // bottom right
	 0.5f, 0.6f, 0.0f,  // bottom left
	};

	unsigned int VBO[6], VAO[6];
	glGenVertexArrays(6, VAO);
	glGenBuffers(6, VBO);

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

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t1), t3, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t1), t4, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t1), t5, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[5]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t1), t6, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.61f, 0.98f, 0.185f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram6);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram5);
		glBindVertexArray(VAO[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[3]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram3);
		glBindVertexArray(VAO[4]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram4);
		glBindVertexArray(VAO[5]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(6, VAO);
	glDeleteBuffers(6, VBO);

	glfwTerminate();
	return 0;
}