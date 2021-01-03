
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <string>
using namespace std;

#define M_PI 3.14159265359


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


double red = 0.77, blue = 0.1, green = 0.2, red1 = 0.6, blue1 = 1, green1 = 0.24;
double intensity = 1, intensity1 = 1;

double sind(double angle) {
	return sin(angle * M_PI / 180);
}

double cosd(double angle) {
	return cos(angle * M_PI / 180);
}

float t1[] = {
		 0.5f,  -0.5f, 0.0f,  // top right
		 0.0f, 0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f  // bottom left
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 2  // first Triangle

};

class Matrix {
public:

	void mxm(float m1[4][4], float m2[4][4], float res[4][4]) {				// MULTIPLICACION MATRIX X MATRIX
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					res[i][j] += m1[i][k] * m2[k][j];

	}

	void mxv(float m[4][4], float vert[3]) {
		float v[4][1] = { {vert[0]}, {vert[1]}, {vert[2]}, {1} };			// MULTIPLICACION MATRIX X VECTOR
		float res[4][1] = { 0 };

		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 1; ++j)
				for (int k = 0; k < 4; ++k)
					res[i][j] += m[i][k] * v[k][j];

		vert[0] = res[0][0];
		vert[1] = res[1][0];
		vert[2] = res[2][0];
	}

	void Traslation(float vert[3], float val1, float val2, float val3) {	// TRASLACION EN X
		float m[4][4] = { {1,0,0,val1},{0,1,0,val2},{0,0,1,val3},{0,0,0,1} };
		mxv(m, vert);
	}


	void scale(float vert[3], float val1, float val2, float val3) {			// ESCALA EN TODOS LOS EJES
		float m[4][4] = { {val1,0,0,0},{0,val2,0,0},{0,0,val3,0},{0,0,0,1} };
		mxv(m, vert);
	}

	void mirror(float vert[3]) {											// MIRROR
		float m[4][4] = { {-1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
		mxv(m, vert);
	}

	void zRotate(float vert[3], float ang) {								// ROTACION EN Z
		float m[4][4] = { {cosd(ang),(-(sind(ang))),0,0},{sind(ang),cosd(ang),0,0},{0,0,1,0},{0,0,0,1} };
		mxv(m, vert);
	}

	void yRotate(float vert[3], float ang) {								// ROTACION EN Y
		float m[4][4] = { {cosd(ang),0,sind(ang),0},{0,1,0,0},{(-(sind(ang))),0,cosd(ang),0},{0,0,0,1} };
		mxv(m, vert);
	}

	void xRotate(float vert[3], float ang) {								// ROTACION EN X
		float m[4][4] = { {1,0,0,0},{0,cosd(ang),(-(sind(ang))),0},{0,sind(ang),cosd(ang),0},{0,0,0,1} };
		mxv(m, vert);
	}

	///

	void zRotateInv(float vert[3], float ang) {								// ROTACION EN Z INVERSA
		float m[4][4] = { {cosd(ang),(-(sind(ang))),0,0},{sind(ang),cosd(ang),0,0},{0,0,1,0},{0,0,0,1} };
		float m_2[4][4] = { 0 };
		transpuesta(m, m_2);
		mxv(m_2, vert);
	}

	void yRotateInv(float vert[3], float ang) {								// ROTACION EN Y INVERSA
		float m[4][4] = { {cosd(ang),0,sind(ang),0},{0,1,0,0},{(-(sind(ang))),0,cosd(ang),0},{0,0,0,1} };
		float m_2[4][4] = { 0 };
		transpuesta(m, m_2);
		mxv(m_2, vert);
	}

	void xRotateInv(float vert[3], float ang) {								// ROTACION EN X INVERSA
		float m[4][4] = { {1,0,0,0},{0,cosd(ang),(-(sind(ang))),0},{0,sind(ang),cosd(ang),0},{0,0,0,1} };
		float m_2[4][4] = { 0 };
		transpuesta(m, m_2);
		mxv(m_2, vert);
	}

	void printM(float m[4][4]) {
		cout << endl << endl;
		for (int i = 0; i < 4; i++) {
			cout << endl;
			for (int j = 0; j < 4; j++) {
				cout << m[i][j] << " ";
			}
		}
	}

	void printV(float v[3],string comm) {
		cout << endl;
		cout << " TECLA [1] PARA APLICAR UNA TRANSFORMACION DE LA COLUMNA [L]" << endl;
		cout << " TECLA [2] PARA APLICAR UNA TRANSFORMACION DE LA COLUMNA [R]" << endl;
		cout << " *** LAS TRANSFORMACIONES SE APLICAN UNA A UNA MIENTRAS SE APRETA LA TECLA CORRESPONDIENTE [1 o 2] \n ES NECESARIO RESETEAR LA FIGURA PARA PASAR DE LA TRANSFORMACION 1 A LA 2 ***" << endl;
		cout << endl << " TECLA [A] PARA APLICAR TRANFORMACION DE LA COLUMNA [L] COMPLETA" << endl;
		cout << " TECLA [S] PARA APLICAR TRANFORMACION DE LA COLUMNA [R] COMPLETA" << endl;
		cout << " TECLA [R] PARA RESETEAR A VERTICES ORIGINALES" << endl;

		cout << endl << endl << endl << endl << endl << " ----> "<< comm  << endl;
		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0) cout << endl << " >> ";
			cout << v[i] << ", ";
		}

		cout << endl << endl << endl << endl << endl << endl;
	}

	void transpuesta(float m[4][4], float res[4][4]) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				res[j][i] = m[i][j];
	}
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


///////////

Matrix mat;
int trans1 = 0, trans2 = 0;


void resetTriangle() {
	t1[0] = 0.5f;
	t1[1] = -0.5f;
	t1[2] = 0.0f;
	t1[3] = 0.0f;
	t1[4] = 0.5f;
	t1[5] = 0.0f;
	t1[6] = -0.5f;
	t1[7] = -0.5f;
	t1[8] = 0.0f;
	trans1 = 0;
	trans2 = 0;

	mat.printV(t1, "Vertices Figura ORIGINAL:  ");
}


//////////


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_I && action == GLFW_PRESS)
		red1 = red1 == 0 ? 1 : 0;
	else if (key == GLFW_KEY_J && action == GLFW_PRESS)
		green1 = green1 == 0 ? 1 : 0;
	else if (key == GLFW_KEY_L && action == GLFW_PRESS)
		blue1 = blue1 == 0 ? 1 : 0;
	else if (key == GLFW_KEY_U && action == GLFW_PRESS && intensity >= 0.1)
		intensity1 = intensity1 - 0.1;
	else if (key == GLFW_KEY_O && action == GLFW_PRESS && intensity < 1)
		intensity1 = intensity1 + 0.1;

	else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		resetTriangle();
	}

	else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		float aux[3] = { 0 };

		switch (trans1)
		{
		case 0:
			resetTriangle();
			for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
				aux[0] = t1[i];
				aux[1] = t1[i + 1];
				aux[2] = t1[i + 2];
				mat.Traslation(aux, 0.34, 0.63, 0.525);
				t1[i] = aux[0];
				t1[i + 1] = aux[1];
				t1[i + 2] = aux[2];
			}
			mat.printV(t1, "Vertices de Transformacion 1 [T] :  ");
			trans1++;
			break;
		case 1:
			for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
				aux[0] = t1[i];
				aux[1] = t1[i + 1];
				aux[2] = t1[i + 2];
				mat.xRotateInv(aux, 66);
				t1[i] = aux[0];
				t1[i + 1] = aux[1];
				t1[i + 2] = aux[2];
			}
			mat.printV(t1, "Vertices de Transformacion 1 [T Rx-1 ] :  ");
			trans1++;
			break;
		case 2:
			for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
				aux[0] = t1[i];
				aux[1] = t1[i + 1];
				aux[2] = t1[i + 2];
				mat.scale(aux, 1, 1.25, 1.25);
				t1[i] = aux[0];
				t1[i + 1] = aux[1];
				t1[i + 2] = aux[2];
			}
			mat.printV(t1, "Vertices de Transformacion 1 [T Rx-1 S] :  ");
			trans1++;
			break;
		case 3:
			for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
				aux[0] = t1[i];
				aux[1] = t1[i + 1];
				aux[2] = t1[i + 2];
				mat.yRotate(aux, 53);
				t1[i] = aux[0];
				t1[i + 1] = aux[1];
				t1[i + 2] = aux[2];
			}
			mat.printV(t1, "Vertices de Transformacion 1 [T Rx-1 S Ry] -- FINAL -- :  ");
			trans1++;
			break;
		case 4:
			resetTriangle();
			break;
		default:
			break;
		}
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		float aux[3] = { 0 };

		switch (trans2)
		{
		case 0:
			resetTriangle();
			for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
				aux[0] = t1[i];
				aux[1] = t1[i + 1];
				aux[2] = t1[i + 2];
				mat.scale(aux, 1, 1.25, 1.25);
				t1[i] = aux[0];
				t1[i + 1] = aux[1];
				t1[i + 2] = aux[2];
			}
			mat.printV(t1, "Vertices de Transformacion 2 [S]:  ");
			trans2++;
			break;
		case 1:
			for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
				aux[0] = t1[i];
				aux[1] = t1[i + 1];
				aux[2] = t1[i + 2];
				mat.xRotate(aux, 66);
				t1[i] = aux[0];
				t1[i + 1] = aux[1];
				t1[i + 2] = aux[2];
			}
			mat.printV(t1, "Vertices de Transformacion 2 [S Rx]:  ");
			trans2++;
			break;
		case 2:
			for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
				aux[0] = t1[i];
				aux[1] = t1[i + 1];
				aux[2] = t1[i + 2];
				mat.zRotateInv(aux, 91);
				t1[i] = aux[0];
				t1[i + 1] = aux[1];
				t1[i + 2] = aux[2];
			}
			mat.printV(t1, "Vertices de Transformacion 2 [S Rx Rz-1]:  ");
			trans2++;
			break;
		case 3:
			for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
				aux[0] = t1[i];
				aux[1] = t1[i + 1];
				aux[2] = t1[i + 2];
				mat.Traslation(aux, 0.34, 0.63, 0.525);
				t1[i] = aux[0];
				t1[i + 1] = aux[1];
				t1[i + 2] = aux[2];
			}
			mat.printV(t1, "Vertices de Transformacion 2 [S Rx Rz-1 T]:  ");
			trans2++;
			break;
		case 4:
			for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
				aux[0] = t1[i];
				aux[1] = t1[i + 1];
				aux[2] = t1[i + 2];
				mat.zRotate(aux, 91);
				t1[i] = aux[0];
				t1[i + 1] = aux[1];
				t1[i + 2] = aux[2];
			}
			mat.printV(t1, "Vertices de Transformacion 2 [S Rx Rz-1 T Rz]:  ");
			trans2++;
			break;
		case 5:
			for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
				aux[0] = t1[i];
				aux[1] = t1[i + 1];
				aux[2] = t1[i + 2];
				mat.Traslation(aux, 0.34, 0.63, 0.525);
				t1[i] = aux[0];
				t1[i + 1] = aux[1];
				t1[i + 2] = aux[2];
			}
			mat.printV(t1, "Vertices de Transformacion 2 [S Rx Rz-1 T Rz T] -- FINAL -- :  ");
			trans2++;
			break;
		case 6:
			resetTriangle();
			break;

		default:
			break;
		}
	}

	else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		resetTriangle();
		float aux[3] = { 0 };
		for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
			aux[0] = t1[i];
			aux[1] = t1[i + 1];
			aux[2] = t1[i + 2];
			mat.Traslation(aux, 0.34, 0.63, 0.525);
			mat.xRotateInv(aux, 66);
			mat.scale(aux, 1, 1.25, 1.25);
			mat.yRotate(aux, 53);
			t1[i] = aux[0];
			t1[i + 1] = aux[1];
			t1[i + 2] = aux[2];
		}
		mat.printV(t1, "Vertices de Transformacion 1 [T  Rx-1  S  Ry]  -- FINAL -- :    ");
	}

	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		resetTriangle();
		float aux[3] = { 0 };
		for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
			aux[0] = t1[i];
			aux[1] = t1[i + 1];
			aux[2] = t1[i + 2];
			mat.scale(aux, 1, 1.25, 1.25);
			mat.xRotate(aux, 66);
			mat.zRotateInv(aux, 91);
			mat.Traslation(aux, 0.34, 0.63, 0.525);
			mat.zRotate(aux, 91);
			mat.Traslation(aux, 0.34, 0.63, 0.525);
			t1[i] = aux[0];
			t1[i + 1] = aux[1];
			t1[i + 2] = aux[2];
		}
		mat.printV(t1, "Vertices de Transformacion 2 [S   Rx  Rz-1  T  Rz  T]  -- FINAL -- :    ");
	}

}

int main() {
	cout << endl;
	cout << " TECLA [1] PARA APLICAR UNA TRANSFORMACION DE LA COLUMNA [L]" << endl;
	cout << " TECLA [2] PARA APLICAR UNA TRANSFORMACION DE LA COLUMNA [R]" << endl;
	cout << " *** LAS TRANSFORMACIONES SE APLICAN UNA A UNA MIENTRAS SE APRETA LA TECLA CORRESPONDIENTE [1 o 2] \n ES NECESARIO RESETEAR LA FIGURA PARA PASAR DE LA TRANSFORMACION 1 A LA 2 ***" << endl;
	cout << endl << " TECLA [A] PARA APLICAR TRANFORMACION DE LA COLUMNA [L] COMPLETA" << endl;
	cout << " TECLA [S] PARA APLICAR TRANFORMACION DE LA COLUMNA [R] COMPLETA" << endl;
	cout << " TECLA [R] PARA RESETEAR A VERTICES ORIGINALES" << endl;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	unsigned int VBO, VAO, EBO;


	while (!glfwWindowShouldClose(window)) {


		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(t1), t1, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		processInput(window);

		glClearColor(0.13, 0.87, 0.3, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram1);
		int vertexColorLocation = glGetUniformLocation(shaderProgram1, "myColor");
		glUniform4f(vertexColorLocation, red * intensity, green * intensity, blue * intensity, 1.0f);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(t1) / sizeof(t1[0]), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram1);

	glfwTerminate();
	return 0;
}