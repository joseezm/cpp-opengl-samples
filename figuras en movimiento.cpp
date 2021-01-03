
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <string>
using namespace std;

#define M_PI 3.14159265359

const char* vertexShaderSource = "#version 330 core\n"							//  VERTEX SHADER
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"						//  FRAGMENT SHADER
"out vec4 FragColor;\n"
"uniform vec4 myColor;\n"
"void main()\n"
"{\n"
"   FragColor = myColor;\n"
"}\n\0";


double sind(double angle) {
	return sin(angle * M_PI / 180);
}

double cosd(double angle) {
	return cos(angle * M_PI / 180);
}

float t1[] = {						//  VERTICES TRIANGULO
		
		 0.08f,  -0.05f, 0.0f,
		 0.08f, -0.05f, 0.0f,
		 0.0f, 0.5f, 0.0f,
		 0.0f, 0.15f, 0.0f
		 
};
unsigned int i1[] = {				//  INDICES TRIANGULO
	0,1,3
};

float t2[] = {						//  VERTICES CUADRADO
		 0.3f,  0.0f, 0.0f,
		 0.5f, 0.2f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.0f
};
unsigned int i2[] = {				//  INDICES ROMBO
	0, 1, 2,
	0, 1, 3
};

float t3[] = { 						//  VERTICES ROMBO
		 0.7f,  0.0f, 0.0f,
		 0.6f, 0.1f, 0.0f,
		0.7f, 0.2f, 0.0f,
		0.8f, 0.1f, 0.0f
};
unsigned int i3[] = {	 			// INDICES ROMBO
	0, 1, 3,
	1, 2, 3
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




Matrix mat; 						// DECLARACION DE OBJETO MATRIZ

int animacion = 1; 					// FLAG DE ANIMACION
bool rotar = 0; 					// FLAG DE ROTACION
int it = 0; 						// ITERADOR PARA ANIMACION DE TRIANGULO
bool flag1 = true; 					// FLAG PARA AUMENTAR O REDUCIR TAMAÑO DE TRIANGULO

void animacionTriangulo() {			// ANIMACION DE TRIANGULO
	float aux[3] = { 0 };
	for (int i = 0; i < sizeof(t1) / sizeof(t1[0]); i = i + 3) {
		aux[0] = t1[i];
		aux[1] = t1[i + 1];
		aux[2] = t1[i + 2];
		if (flag1)
			mat.scale(aux, 1.01, 1.01, 1.01); 			// AUMENTAR TAMAÑO
		else
			mat.scale(aux, 0.99, 0.99, 0.99);			// REDUCIR TAMAÑO
		t1[i] = aux[0];
		t1[i + 1] = aux[1];
		t1[i + 2] = aux[2];
	}
	if (it == 100) flag1 = false;
	else if (it == 0) { 								// REGULARIZAR TRIANGULO
		t1[0] = -0.08; t1[1] = -0.05;
		t1[3] = 0.1;  t1[4] = -0.05;
		t1[11] = 0.15;
		flag1 = true;
	}

	if (flag1) it++;
	else it--;

}

int cont = 0;
void animacionCuadrado() { 			// ANIMACION DE CUADRADO
	float aux[3] = { 0 };
	for (int i = 0; i < sizeof(t2) / sizeof(t2[0]); i = i + 3) {
		aux[0] = t2[i];
		aux[1] = t2[i + 1];
		aux[2] = t2[i + 2];
		if(animacion==1) rotar ? mat.zRotate(aux, 0.45) : mat.Traslation(aux, -(sind(cont) / 130), cosd(cont) / 120, 0); 					// ANIMACION ANTIHORARIA
		else if(animacion ==2) rotar ? mat.zRotate(aux, -0.45) : mat.Traslation(aux, -(sind(cont) / 130), -(cosd(cont) / 120), 0);			// ANIMACION HORARIA
		 
		t2[i] = aux[0];
		t2[i + 1] = aux[1];
		t2[i + 2] = aux[2];

	}

	cont = (cont + 1) % 360; 		// AUMENTAR VALOR DE SENO Y COSENO 
}

int flag3 = 0;
void animacionRombo() {				// ANIMACION DE ROMBO
	float aux[3] = { 0 };
	for (int i = 0; i < sizeof(t3) / sizeof(t3[0]); i = i + 3) {
		aux[0] = t3[i];
		aux[1] = t3[i + 1];
		aux[2] = t3[i + 2];
		switch (flag3) {
		case 0:
			animacion == 1 ? mat.Traslation(aux, 0, 0.01, 0) : mat.Traslation(aux, 0, -0.01, 0); // ARRIBA - ABAJO
			break;
		case 1:
			animacion == 1 ? mat.Traslation(aux, -0.01, 0, 0) : mat.Traslation(aux, 0.01, 0, 0); // IZQUIERDA - DERECHA
			break;
		case 2:
			animacion == 1 ? mat.Traslation(aux, 0, -0.01, 0) : mat.Traslation(aux, 0, 0.01, 0); // ABAJO - ARRIBA
			break;
		case 3:
			animacion == 1 ? mat.Traslation(aux, 0.01, 0, 0) : mat.Traslation(aux, -0.01, 0, 0); // DERECHA - IZQUIERDA
			break;
		}
		t3[i] = aux[0];
		t3[i + 1] = aux[1];
		t3[i + 2] = aux[2];
	}

	if (animacion == 1) {			// PARAMETROS PARA ANIMACION ANTIHORARIA
		if (t3[4] > 0.8 && flag3 == 0)
			flag3 = 1;
		else if (t3[3] < -0.8 && flag3 == 1)
			flag3 = 2;
		else if (t3[1] < -0.8 && flag3 == 2)
			flag3 = 3;
		else if (t3[6] > 0.8 && flag3 == 3)
			flag3 = 0;
	}
	else if (animacion==2 ){		// PARAMETROS PARA ANIMACION HORARIA
		if (t3[1] < -0.8 && flag3 == 0)
			flag3 = 3;
		else if (t3[3] < -0.8 && flag3 == 3)
			flag3 = 2;
		else if (t3[7] > 0.8 && flag3 == 2)
			flag3 = 1;
		else if (t3[9] > 0.8 && flag3 == 1)
			flag3 = 0;
	}
}


/////////

int cont1 = 0, cont2 = 1;
int auxiliarPause = 0;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	float aux[3] = { 0 };
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) { 					// ANIMACION ANTIHORARIA
		t2[0] = 0.3; t2[1] = 0.0; t2[2] = 0.0;
		t2[3] = 0.5; t2[4] = 0.2; t2[5] = 0.0;
		t2[6] = 0.5; t2[7] = 0.0; t2[8] = 0.0;
		t2[9] = 0.3; t2[10] = 0.2; t2[11] = 0.0;
		cont = 0;
		animacion = 1;
		rotar = 0;
	}
	else if (key == GLFW_KEY_R && action == GLFW_PRESS)					// TRASLACION A ROTACION
		rotar = 1;

	else if (key == GLFW_KEY_2 && action == GLFW_PRESS) { 				// ANIMACION HORARIA
		animacion = 2;
		t2[0] = 0.3; t2[1] = 0.0; t2[2] = 0.0;
		t2[3] = 0.5; t2[4] = 0.2; t2[5] = 0.0;
		t2[6] = 0.5; t2[7] = 0.0; t2[8] = 0.0;
		t2[9] = 0.3; t2[10] = 0.2; t2[11] = 0.0;
		cont = 0;
		rotar = 0;
	}
	else if (key == GLFW_KEY_P && action == GLFW_PRESS) { 				// PAUSA
		auxiliarPause = animacion != 0 ? animacion : auxiliarPause;
		animacion = animacion == 0 ? auxiliarPause : 0;
	}


}

int main() {
	cout << endl << endl;
	cout << " TECLA [1] PARA ANIMACION EN SENTIDO HORARIO" << endl;
	cout << " TECLA [2] PARA ANIMACION EN SENTIDO ANTIHORARIO" << endl;
	cout << " TECLA [R] PARA CAMBIAR EFECTO DEL CUADRADO -> DE TRASLACION A ROTACION" << endl;
	cout << " TECLA [P] PARA PAUSAR LA ANIMACION" << endl;


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

	unsigned int VBO[3], VAO[3], EBO[3];


	while (!glfwWindowShouldClose(window)) {

		// LLAMADA ANIMACIONES
		if (animacion > 0) {
			animacionTriangulo();
			animacionCuadrado();
			animacionRombo();
		}
		
		// BUFFER FIGURA 1 TRIANGULO
		glGenVertexArrays(1, &VAO[0]);
		glGenBuffers(1, &VBO[0]);
		glGenBuffers(1, &EBO[0]);
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(t1), t1, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i1), i1, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		// BUFFER FIGURA 2 CUADRADO
		glGenVertexArrays(1, &VAO[1]);
		glGenBuffers(1, &VBO[1]);
		glGenBuffers(1, &EBO[1]);
		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(t2), t2, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i2), i2, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		// BUFFER FIGURA 3 ROMBO
		glGenVertexArrays(1, &VAO[2]);
		glGenBuffers(1, &VBO[2]);
		glGenBuffers(1, &EBO[2]);
		glBindVertexArray(VAO[2]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(t3), t3, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i3), i3, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// FONDO
		processInput(window);
		float timeValue = glfwGetTime();
		float bValue = sin(timeValue) / 2.0f + 0.5f;
		glClearColor(0.13, 0.87, bValue, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// DIBUJAR FIGURA 1 TRIANGULO
		glUseProgram(shaderProgram1);
		int vertexColorLocation = glGetUniformLocation(shaderProgram1, "myColor");
		timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		glUniform4f(vertexColorLocation, 0.2, greenValue, 0.2, 1.0f);			// COLOR TRIANGULO
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, sizeof(t1) / sizeof(t1[0]), GL_UNSIGNED_INT, 0);

		// DIBUJAR FIGURA 2 CUADRADO
		glUseProgram(shaderProgram1);
		vertexColorLocation = glGetUniformLocation(shaderProgram1, "myColor");
		timeValue = glfwGetTime();
		float blueValue = sin(timeValue) / 2.0f + 0.5f;
		glUniform4f(vertexColorLocation, 0.1, 0.2, blueValue, 1.0f);			// COLOR CUADRADO
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, sizeof(t2) / sizeof(t2[0]), GL_UNSIGNED_INT, 0);

		// DIBUJAR FIGURA 3 ROMBO
		glUseProgram(shaderProgram1);
		vertexColorLocation = glGetUniformLocation(shaderProgram1, "myColor");
		timeValue = glfwGetTime();
		float redValue = sin(timeValue) / 2.0f + 0.5f;
		glUniform4f(vertexColorLocation, redValue, 0.5, 0.2, 1.0f);				// COLOR ROMBO
		glBindVertexArray(VAO[2]);
		glDrawElements(GL_TRIANGLES, sizeof(t3) / sizeof(t3[0]), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	for (int i = 0; i < 3; i++) {
		glDeleteVertexArrays(1, &VAO[i]);
		glDeleteBuffers(1, &VBO[i]);
		glDeleteBuffers(1, &EBO[i]);
		glDeleteProgram(shaderProgram1);
	}

	glfwTerminate();
	return 0;
}