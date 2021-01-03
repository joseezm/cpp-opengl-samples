#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

int iteraciones = 0;
bool automatico = 0;
int animacion = 0;
int direccion = 0;
bool movimiento = 0;
float movimientoSuma = 0;
bool  invertir = 0;
unsigned int timer = 10000000;

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

class Sierpinski {
public:
	float vertices[30000];
	int indices[30000];
	int indiceV;
	int indiceI;
	int maximo = 8;
	float r, g, b;


	Sierpinski() {
		
		//inicializarVertices();
		vertices[0] = -0.6f;
		vertices[1] = -0.6f;
		vertices[2] = 0.0f;
		vertices[3] = 0.6f;
		vertices[4] = -0.6f;
		vertices[5] = 0.0f;
		vertices[6] = 0.0f;
		vertices[7] = 0.6f;
		vertices[8] = 0.0f;
		indiceV = 3;
		indiceI = 0;
	}

	//void inicializarVertices() {
	//	std::fill(vertices, vertices + sizeof(vertices), -1);
	//	std::fill(indices, indices + sizeof(indices), -1);
	//}


	void crearTriangulo(unsigned int v1, unsigned int v2, unsigned int v3, int lim) {
		if (lim < maximo) {
			int aux1;
			int aux2;
			int aux3;
			aux1 = indiceV;
			aux2 = indiceV + 1;
			aux3 = indiceV + 2;
			v1 = v1*3;
			v2 = v2*3;
			v3 = v3*3;
			indiceV = indiceV*3;
			vertices[indiceV] = (vertices[v1] + vertices[v2]) / 2;					//T1
			vertices[indiceV + 1] = (vertices[v1 + 1] + vertices[v2 + 1]) / 2;  
			vertices[indiceV + 2] = (vertices[v1 + 2] + vertices[v2 + 2]) / 2;
			vertices[indiceV + 3] = (vertices[v1] + vertices[v3]) / 2;				//T2
			vertices[indiceV + 4] = (vertices[v1 + 1] + vertices[v3 + 1]) / 2;
			vertices[indiceV + 5] = (vertices[v1 + 2] + vertices[v3 + 2]) / 2;
			vertices[indiceV + 6] = (vertices[v3] + vertices[v2]) / 2;				//T3
			vertices[indiceV + 7] = (vertices[v3 + 1] + vertices[v2 + 1]) / 2;
			vertices[indiceV + 8] = (vertices[v3 + 2] + vertices[v2 + 2]) / 2;
			//vertices[indiceV] = (vertices[v1] + vertices[v2]) / 2;
			//vertices[indiceV + 1] = (vertices[++v1] + vertices[v2 + 1]) / 2;
			//vertices[indiceV + 2] = (vertices[v1 + 2] + vertices[v2 + 2]) / 2;
			//vertices[indiceV + 3] = (vertices[v1] + vertices[v3]) / 2;
			//vertices[indiceV + 4] = (vertices[++v1] + vertices[v3 + 1]) / 2;
			//vertices[indiceV + 5] = (vertices[v1 + 2] + vertices[v3 + 2]) / 2;
			//vertices[indiceV + 6] = (vertices[v3] + vertices[v2]) / 2;
			//vertices[indiceV + 7] = (vertices[++v3] + vertices[v2 + 1]) / 2;
			//vertices[indiceV + 8] = (vertices[v3 + 2] + vertices[v2 + 2]) / 2;
			v1 = v1/3;
			v2 = v2/3;
			v3 = v3/3;
			indiceV = indiceV / 3;
			indiceV = indiceV + 3;
			//triangulos nuevos
			crearTriangulo( v1, aux1, aux2, lim + 1);	//der
			crearTriangulo( aux1, v2, aux3, lim + 1);	//izq
			crearTriangulo(aux2, aux3, v3, lim + 1);	//arriba
			return;
		}
		indices[indiceI] = v1; 
		indices[++indiceI] = v2;
		indices[++indiceI] = v3;
		indiceI++;
		return;
	}

	void reset(int v) {
		vertices[0] = -0.1 * v;
		vertices[1] = -0.1 * v;
		vertices[2] = 0.0;
		vertices[3] = 0.1 * v;
		vertices[4] = -0.1 * v;
		vertices[5] = 0.0;
		vertices[6] = 0.0;
		vertices[7] = 0.1 * v;
		vertices[8] = 0.0;
		indiceV = 3;
		indiceI = 0;
	}
};

Sierpinski t1[8];

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	srand(time(NULL));
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		iteraciones = 1;
		t1[0].r = ((float)rand() / RAND_MAX) * (1);
		t1[0].g = ((float)rand() / RAND_MAX) * (1);
		t1[0].b = ((float)rand() / RAND_MAX) * (1);
		automatico = 0;
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		iteraciones = 2;
		t1[1].r = 1- ((float)rand() / RAND_MAX) * (1);
		t1[1].g = 1 - ((float)rand() / RAND_MAX) * (1);
		t1[1].b = 1 - ((float)rand() / RAND_MAX) * (1);
		automatico = 0;
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		iteraciones = 3;
		t1[2].r = ((float)rand() / RAND_MAX) * (1);
		t1[2].g = ((float)rand() / RAND_MAX) * (1);
		t1[2].b = ((float)rand() / RAND_MAX) * (1);
		automatico = 0;
	}
	else if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		iteraciones = 4;
		t1[3].r = 1 - ((float)rand() / RAND_MAX) * (1);
		t1[3].g = 1 - ((float)rand() / RAND_MAX) * (1);
		t1[3].b = 1 - ((float)rand() / RAND_MAX) * (1);
		automatico = 0;
	}
	else if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		iteraciones = 5;
		t1[4].r = ((float)rand() / RAND_MAX) * (1);
		t1[4].g = ((float)rand() / RAND_MAX) * (1);
		t1[4].b = ((float)rand() / RAND_MAX) * (1);
		automatico = 0;
	}
	else if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		iteraciones = 6;
		t1[5].r = 1 - ((float)rand() / RAND_MAX) * (1);
		t1[5].g = 1 - ((float)rand() / RAND_MAX) * (1);
		t1[5].b = 1 - ((float)rand() / RAND_MAX) * (1);
		automatico = 0;
	}
	else if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		iteraciones = 7;
		t1[6].r = ((float)rand() / RAND_MAX) * (1);
		t1[6].g = ((float)rand() / RAND_MAX) * (1);
		t1[6].b = ((float)rand() / RAND_MAX) * (1);
		automatico = 0;
	}
	else if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		iteraciones = 8;
		t1[7].r = 1 - ((float)rand() / RAND_MAX) * (1);
		t1[7].g = 1 - ((float)rand() / RAND_MAX) * (1);
		t1[7].b = 1 - ((float)rand() / RAND_MAX) * (1);
		automatico = 0;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		if (automatico == 1) automatico = 0;
		else automatico = 1;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		movimiento = 1;
		direccion = 1;
		movimientoSuma = 0.1;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		movimiento = 1;
		direccion = 0;
		movimientoSuma = 0.1;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		movimiento = 1;
		direccion = 0;
		movimientoSuma = -0.1;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		movimiento = 1;
		direccion = 1;
		movimientoSuma = -0.1;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		movimiento = 0;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		movimiento = 0;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
		movimiento = 0;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
		movimiento = 0;
	}
	else if (key == GLFW_KEY_I && action == GLFW_PRESS) {
	invertir = 1;
	}
	else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
	timer = timer - 5000000;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
	timer = timer + 5000000;
	}
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		exit(0);
	}	
}


int main() {

	cout << "------------------------------------------------- \n ----------------- INSTRUCCIONES ----------------- \n -------------------------------------------------   " << endl << endl;;
	cout << "  CAMBIAR ITERACION --> DEL 1 AL 8" << endl;
	cout << "  ACTIVAR O DESACTIVAR ITERACION AUTOMATICA --> A" << endl;
	cout << "  MOVER TRIANGULO --> FLECHAS DIRECCIONALES" << endl;
	cout << "  INVERTIR TRIANGULO --> I" << endl;
	cout << "  AUMENTAR VELICIDAD DE RENDERIZADO --> F" << endl;
	cout << "  REDUCIR VELICIDAD DE RENDERIZADO --> S" << endl;
	cout << "  CERRAR PROGRAMA --> Q" << endl << endl;
	cout << "------------------------------------------------- \n ------------------------------------------------- \n -------------------------------------------------   " << endl;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1000, 900, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	t1[0].crearTriangulo(0, 1, 2, 8);
	t1[1].crearTriangulo(0, 1, 2, 7);
	t1[2].crearTriangulo(0, 1, 2, 6);
	t1[3].crearTriangulo(0, 1, 2, 5);
	t1[4].crearTriangulo(0, 1, 2, 4);
	t1[5].crearTriangulo(0, 1, 2, 3);
	t1[6].crearTriangulo(0, 1, 2, 2);
	t1[7].crearTriangulo(0, 1, 2, 1);

	unsigned int VBO[8], VAO[8], EBO[8];

	bool flag = 1;

	while (!glfwWindowShouldClose(window)) {
			//////////////// ANIMACION AUTOMATICA //////////////////
			if (automatico) {
				if (flag) {
					t1[iteraciones].r = ((float)rand() / RAND_MAX) * (1);
					t1[iteraciones].g = ((float)rand() / RAND_MAX) * (1);
					t1[iteraciones].b = ((float)rand() / RAND_MAX) * (1);
					iteraciones++;
				}
				else {
					iteraciones--;
				}

				if (iteraciones == 8) flag = 0;
				else if (iteraciones == 0) flag = 1;
			}

			//////////////// FONDO MULTICOLOR //////////////////

			float timeValue = glfwGetTime();
			float ColorValue = sin(timeValue) / 2.0f + 0.5f;
			glClearColor(0.1f, 0.1f, ColorValue, 0.2f);
			glClear(GL_COLOR_BUFFER_BIT);

			//////////////// MOVIMIENTO //////////////////
			if (movimiento ) {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 30000; j++) {
						if (j % 3 == 0)
							t1[i].vertices[j + direccion] = t1[i].vertices[j + direccion] + (movimientoSuma);
					}
				}
			}

			//////////////// INVERTIR TRIANGULO //////////////////
			if (invertir) {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 30000; j++) {
						if(j%3==0)
						t1[i].vertices[j+1] = t1[i].vertices[j+1 ] *(-1);
					}
				}
				invertir = 0;
			}

			/////////////// CREACION DE VAOs y EBOs //////////////////
			for (int i = 0; i < iteraciones; i++) {

				glGenVertexArrays(1, &VAO[i]);
				glGenBuffers(1, &VBO[i]);
				glGenBuffers(1, &EBO[i]);
				glBindVertexArray(VAO[i]);

				glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(t1[i].vertices), t1[i].vertices, GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(t1[i].indices), t1[i].indices, GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
			}

			///////////////////  DIBUJAR  //////////////////////

			for (int i = 0; i < iteraciones; i++) {
				glUseProgram(shaderProgram);
				int vertexColorLocation1 = glGetUniformLocation(shaderProgram, "myColor");
				glUniform4f(vertexColorLocation1, t1[i].r, t1[i].g, t1[i].b, 1.0f);
				//cout << t1[i].r << " " << t1[i].g << " " << t1[i].b << endl;
				glBindVertexArray(VAO[i]);
				glDrawElements(GL_TRIANGLES, t1[i].indiceI, GL_UNSIGNED_INT, 0);
			}

			for (unsigned int i = 0; i < timer; i++); // TIMER

			glfwSwapBuffers(window);
			glfwPollEvents();

		}

	for (int i = 0; i < 8; i++) {
		glDeleteVertexArrays(1, &VAO[i]);
		glDeleteBuffers(1, &VBO[i]);
		glDeleteBuffers(1, &EBO[i]);
	}
	glfwTerminate();
	return 0;
}