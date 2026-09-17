//práctica 3: Modelado Geométrico y Cámara Sintética.
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include <gtc\random.hpp>
//clases para dar orden y limpieza al còdigo
#include"Mesh.h"
#include"Shader.h"
#include"Sphere.h"
#include"Window.h"
#include"Camera.h"
//tecla E: Rotar sobre el eje X
//tecla R: Rotar sobre el eje Y
//tecla T: Rotar sobre el eje Z


using std::vector;

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
const float PI = 3.14159265f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;
Camera camera;
Window mainWindow;
vector<Mesh*> meshList;
vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
Sphere sp = Sphere(1.0, 20, 20); //recibe radio, slices, stacks




void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

// Pirámide triangular regular
void CrearPiramideTriangular()
{
	unsigned int indices_piramide_triangular[] = {
			0,1,2,
			1,3,2,
			3,0,2,
			1,0,3

	};
	GLfloat vertices_piramide_triangular[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* piramidet = new Mesh();
	piramidet->CreateMesh(vertices_piramide_triangular, indices_piramide_triangular, 12, 12);
	meshList.push_back(piramidet);

}


//función para crear pirámide cuadrangular unitaria
void CrearPiramideCuadrangular()
{
	unsigned int piramidecuadrangular_indices[] = {
		0,3,4,//frontal
		3,2,4,//izquierda
		2,1,4,//trasera
		1,0,4,//derecha
		0,1,2,//abajo1
		0,2,3//abajo2

	};
	GLfloat piramidecuadrangular_vertices[] = {
		0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		0.0f,0.5f,0.0f,
	};
	Mesh* piramidec = new Mesh();
	piramidec->CreateMesh(piramidecuadrangular_vertices, piramidecuadrangular_indices, 15, 18);
	meshList.push_back(piramidec);

	// Base cuadrada
	unsigned int indicesBase[] = {
		0, 1, 2,
		0, 2, 3
	};
	GLfloat verticesBase[] = {
		0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f
	};

	Mesh* basePiramide = new Mesh();
	basePiramide->CreateMesh(verticesBase, indicesBase, 12, 6);
	meshList.push_back(basePiramide);


	// Cara frontal
	unsigned int indicesFrontal[] = {
		0, 1, 2
	};

	GLfloat verticesFrontal[] = {
		0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.0f,0.5f,0.0f
	};

	Mesh* frontalPiramide = new Mesh();
	frontalPiramide->CreateMesh(verticesFrontal, indicesFrontal, 9, 3);
	meshList.push_back(frontalPiramide);


	// Cara izquierda
	unsigned int indicesIzquierda[] = {
		0, 1, 2
	};

	GLfloat verticesIzquierda[] = {
		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.0f,0.5f,0.0f
	};

	Mesh* izquierdaPiramide = new Mesh();
	izquierdaPiramide->CreateMesh(verticesIzquierda, indicesIzquierda, 9, 3);
	meshList.push_back(izquierdaPiramide);


	// Cara trasera
	unsigned int indicesTrasera[] = {
		0, 1, 2
	};

	GLfloat verticesTrasera[] = {
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.5f,0.0f
	};

	Mesh* traseraPiramide = new Mesh();
	traseraPiramide->CreateMesh(verticesTrasera, indicesTrasera, 9, 3);
	meshList.push_back(traseraPiramide);


	// Cara derecha
	unsigned int indicesDerecha[] = {
		0, 1, 2
	};

	GLfloat verticesDerecha[] = {
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		0.0f,0.5f,0.0f
	};

	Mesh* derechaPiramide = new Mesh();
	derechaPiramide->CreateMesh(verticesDerecha, indicesDerecha, 9, 3);
	meshList.push_back(derechaPiramide);
}



/*
Crear cilindro, cono y esferas con arreglos dinámicos vector creados en el Semestre 2023 - 1 : por Sánchez Pérez Omar Alejandro
*/
void CrearCilindro(int res, float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//cálculo del paso interno en la circunferencia y variables que almacenarán cada coordenada de cada vértice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;

	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//ciclo for para crear los vértices de las paredes del cilindro
	for (n = 0; n <= (res); n++) {
		if (n != res) {
			x = R * cos((n)*dt);
			z = R * sin((n)*dt);
		}
		//caso para terminar el círculo
		else {
			x = R * cos((0)*dt);
			z = R * sin((0)*dt);
		}
		for (i = 0; i < 6; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			case 3:
				vertices.push_back(x);
				break;
			case 4:
				vertices.push_back(0.5);
				break;
			case 5:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia inferior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(-0.5f);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia superior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(0.5);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//Se generan los indices de los vértices
	for (i = 0; i < vertices.size(); i++) indices.push_back(i);

	//se genera el mesh del cilindro
	Mesh *cilindro = new Mesh();
	cilindro->CreateMeshGeometry(vertices, indices, vertices.size(), indices.size());
	meshList.push_back(cilindro);
}

//función para crear un cono
void CrearCono(int res,float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//cálculo del paso interno en la circunferencia y variables que almacenarán cada coordenada de cada vértice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;
	
	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//caso inicial para crear el cono
	vertices.push_back(0.0);
	vertices.push_back(0.5);
	vertices.push_back(0.0);
	
	//ciclo for para crear los vértices de la circunferencia del cono
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}
	vertices.push_back(R * cos(0) * dt);
	vertices.push_back(-0.5);
	vertices.push_back(R * sin(0) * dt);


	for (i = 0; i < res+2; i++) indices.push_back(i);

	//se genera el mesh del cono
	Mesh *cono = new Mesh();
	cono->CreateMeshGeometry(vertices, indices, vertices.size(), res + 2);
	meshList.push_back(cono);
}



void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderColor, fShader);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	//Cilindro y cono reciben resolución (slices, rebanadas) y Radio de circunferencia de la base y tapa

	CrearCubo();//índice 0 en MeshList
	CrearPiramideTriangular();//índice 1 en MeshList
	CrearCilindro(5, 1.0f);//índice 2 en MeshList
	CrearCono(25, 2.0f);//índice 3 en MeshList
	CrearPiramideCuadrangular();//índice 4 en MeshList
	CreateShaders();
	
	

	/*Cámara se usa el comando: glm::lookAt(vector de posición, vector de orientación, vector up));
	En la clase Camera se reciben 5 datos:
	glm::vec3 vector de posición,
	glm::vec3 vector up,
	GlFloat yaw rotación para girar hacia la derecha e izquierda
	GlFloat pitch rotación para inclinar hacia arriba y abajo
	GlFloat velocidad de desplazamiento,
	GlFloat velocidad de vuelta o de giro
	Se usa el Mouse y las teclas WASD y su posición inicial está en 0,0,1 y ve hacia 0,0,-1.
	*/

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.3f);

	
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
	
	//Loop mientras no se cierra la ventana
	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader

	glm::mat4 model(1.0);//Inicializar matriz de Modelo 4x4

	glm::vec3 color = glm::vec3(0.0f,0.0f,0.0f); //inicializar Color para enviar a variable Uniform;

	while (!mainWindow.getShouldClose())
	{
		
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		//Cámara
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		model = glm::mat4(1.0);
		//Traslación inicial para posicionar en -Z a los objetos
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//otras transformaciones para el objeto
		//model = glm::scale(model, glm::vec3(0.5f,0.5f,0.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));		
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		
		//Base (Se modificó el color a gris oscuro para contrastar con el fondo negro)
		glm::mat4 base = model;
		base = glm::translate(base, glm::vec3(0.0f, -1.10f, 0.0f));
		base = glm::scale(base, glm::vec3(6.0f, 0.15f, 6.0f)); // Se hizo un poco más ancha
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(base));
		color = glm::vec3(0.2f, 0.2f, 0.2f); // Gris oscuro en lugar de casi negro
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[0]->RenderMesh();


		// =========================================================
		// FIGURA 1 COHETE
		// =========================================================

		glm::mat4 rocketSystem = model;
		rocketSystem = glm::translate(rocketSystem, glm::vec3(-1.2f, -0.2f, 0.0f));
		rocketSystem = glm::scale(rocketSystem, glm::vec3(0.5f, 0.5f, 0.5f));

		// Cuerpo del Cohete
		glm::mat4 cuerpoCohete = rocketSystem;
		cuerpoCohete = glm::translate(cuerpoCohete, glm::vec3(0.0f, 0.5f, 0.0f));
		cuerpoCohete = glm::scale(cuerpoCohete, glm::vec3(1.0f, 3.0f, 1.0f)); // Prisma rectangular
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(cuerpoCohete));
		color = glm::vec3(0.9f, 0.9f, 0.9f); // Blanco / Gris muy claro
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[0]->RenderMesh();

		// Punta del Cohete
		glm::mat4 puntaCohete = rocketSystem;
		puntaCohete = glm::translate(puntaCohete, glm::vec3(0.0f, 2.5f, 0.0f));
		puntaCohete = glm::scale(puntaCohete, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(puntaCohete));
		color = glm::vec3(0.8f, 0.1f, 0.1f); // Rojo
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[4]->RenderMesh();

		// Ventana
		glm::mat4 ventana = rocketSystem;
		ventana = glm::translate(ventana, glm::vec3(0.0f, 1.0f, 0.51f));
		ventana = glm::scale(ventana, glm::vec3(0.4f, 0.4f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ventana));
		color = glm::vec3(0.2f, 0.8f, 1.0f); // Azul claro simulando cristal
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[0]->RenderMesh();

		// Fuego
		glm::mat4 fuego = rocketSystem;
		fuego = glm::translate(fuego, glm::vec3(0.0f, -1.5f, 0.0f)); // Debajo del cohete
		fuego = glm::rotate(fuego, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Apuntando hacia abajo
		fuego = glm::scale(fuego, glm::vec3(0.6f, 1.2f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(fuego));
		color = glm::vec3(1.0f, 0.5f, 0.0f); // Naranja
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[1]->RenderMesh();

		// Alerones
		glm::vec3 colorAleron = glm::vec3(0.1f, 0.3f, 0.8f); // Azul para alerones

		// Alerón Izquierdo
		glm::mat4 aleron1 = rocketSystem;
		aleron1 = glm::translate(aleron1, glm::vec3(-0.5f, -0.5f, 0.0f));
		aleron1 = glm::scale(aleron1, glm::vec3(0.6f, 0.8f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(aleron1));
		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAleron));
		meshList[1]->RenderMesh();

		// Alerón Derecho
		glm::mat4 aleron2 = rocketSystem;
		aleron2 = glm::translate(aleron2, glm::vec3(0.5f, -0.5f, 0.0f));
		aleron2 = glm::scale(aleron2, glm::vec3(0.6f, 0.8f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(aleron2));
		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAleron));
		meshList[1]->RenderMesh();

		// Alerón Frente
		glm::mat4 aleron3 = rocketSystem;
		aleron3 = glm::translate(aleron3, glm::vec3(0.0f, -0.5f, 0.5f));
		aleron3 = glm::scale(aleron3, glm::vec3(0.1f, 0.8f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(aleron3));
		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAleron));
		meshList[1]->RenderMesh();

		// Alerón Atrás
		glm::mat4 aleron4 = rocketSystem;
		aleron4 = glm::translate(aleron4, glm::vec3(0.0f, -0.5f, -0.5f));
		aleron4 = glm::scale(aleron4, glm::vec3(0.1f, 0.8f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(aleron4));
		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAleron));
		meshList[1]->RenderMesh();

		// Base de Lanzamiento
		glm::vec3 colorTorre = glm::vec3(0.4f, 0.4f, 0.4f); // Gris

		glm::mat4 torre1 = rocketSystem;
		torre1 = glm::translate(torre1, glm::vec3(-1.4f, 0.5f, 0.0f)); // Movido un poco a la izquierda
		torre1 = glm::scale(torre1, glm::vec3(0.2f, 3.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(torre1));
		glUniform3fv(uniformColor, 1, glm::value_ptr(colorTorre));
		meshList[0]->RenderMesh();

		glm::mat4 torre2 = rocketSystem;
		torre2 = glm::translate(torre2, glm::vec3(1.4f, 0.5f, 0.0f)); // Movido un poco a la derecha
		torre2 = glm::scale(torre2, glm::vec3(0.2f, 3.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(torre2));
		glUniform3fv(uniformColor, 1, glm::value_ptr(colorTorre));
		meshList[0]->RenderMesh();

		// =========================================================
		// FIGURA 2 CUBO DE 8 PIRÁMIDES
		// =========================================================

		glm::mat4 figura8 = model;
		figura8 = glm::translate(figura8, glm::vec3(1.0f, 0.5f, 0.0f)); // Posición a la derecha
		figura8 = glm::scale(figura8, glm::vec3(0.8f, 0.8f, 0.8f)); // Tamaño general

		glm::vec3 colorBase = glm::vec3(0.0f, 0.0f, 1.0f);       // Azul
		glm::vec3 colorRojo = glm::vec3(1.0f, 0.0f, 0.0f);       // Rojo
		glm::vec3 colorVerde = glm::vec3(0.0f, 1.0f, 0.0f);      // Verde
		glm::vec3 colorAmarillo = glm::vec3(1.0f, 1.0f, 0.0f);   // Amarillo
		glm::vec3 colorMagenta = glm::vec3(1.0f, 0.0f, 1.0f);    // Magenta

		// Pirámide Superior
		glm::mat4 p1 = figura8;
		p1 = glm::translate(p1, glm::vec3(0.0f, 0.26f, 0.0f));
		p1 = glm::rotate(p1, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		p1 = glm::scale(p1, glm::vec3(1.0f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(p1));

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorBase));
		meshList[5]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorRojo));
		meshList[6]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorVerde));
		meshList[7]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAmarillo));
		meshList[8]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorMagenta));
		meshList[9]->RenderMesh();


		// Pirámide Inferior
		glm::mat4 p2 = figura8;
		p2 = glm::translate(p2, glm::vec3(0.0f, -0.26f, 0.0f));
		p2 = glm::scale(p2, glm::vec3(1.0f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(p2));

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorBase));
		meshList[5]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorRojo));
		meshList[6]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorVerde));
		meshList[7]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAmarillo));
		meshList[8]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorMagenta));
		meshList[9]->RenderMesh();


		// Pirámide Derecha
		glm::mat4 p3 = figura8;
		p3 = glm::translate(p3, glm::vec3(0.26f, 0.0f, 0.0f));
		p3 = glm::rotate(p3, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		p3 = glm::scale(p3, glm::vec3(1.0f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(p3));

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorBase));
		meshList[5]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorRojo));
		meshList[6]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorVerde));
		meshList[7]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAmarillo));
		meshList[8]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorMagenta));
		meshList[9]->RenderMesh();


		// Pirámide Izquierda
		glm::mat4 p4 = figura8;
		p4 = glm::translate(p4, glm::vec3(-0.26f, 0.0f, 0.0f));
		p4 = glm::rotate(p4, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		p4 = glm::scale(p4, glm::vec3(1.0f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(p4));

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorBase));
		meshList[5]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorRojo));
		meshList[6]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorVerde));
		meshList[7]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAmarillo));
		meshList[8]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorMagenta));
		meshList[9]->RenderMesh();


		// Pirámide Superior Adicional
		glm::mat4 p7 = figura8;
		p7 = glm::translate(p7, glm::vec3(0.0f, 0.77f, 0.0f));
		p7 = glm::scale(p7, glm::vec3(1.0f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(p7));

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorBase));
		meshList[5]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorRojo));
		meshList[6]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorVerde));
		meshList[7]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAmarillo));
		meshList[8]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorMagenta));
		meshList[9]->RenderMesh();


		// Pirámide Inferior Adicional
		glm::mat4 p8 = figura8;
		p8 = glm::translate(p8, glm::vec3(0.0f, -0.77f, 0.0f));
		p8 = glm::rotate(p8, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		p8 = glm::scale(p8, glm::vec3(1.0f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(p8));

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorBase));
		meshList[5]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorRojo));
		meshList[6]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorVerde));
		meshList[7]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAmarillo));
		meshList[8]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorMagenta));
		meshList[9]->RenderMesh();


		// Pirámide Derecha Adicional
		glm::mat4 p9 = figura8;
		p9 = glm::translate(p9, glm::vec3(0.77f, 0.0f, 0.0f));
		p9 = glm::rotate(p9, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		p9 = glm::scale(p9, glm::vec3(1.0f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(p9));

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorBase));
		meshList[5]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorRojo));
		meshList[6]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorVerde));
		meshList[7]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAmarillo));
		meshList[8]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorMagenta));
		meshList[9]->RenderMesh();


		// Pirámide Izquierda Adicional
		glm::mat4 p10 = figura8;
		p10 = glm::translate(p10, glm::vec3(-0.77f, 0.0f, 0.0f));
		p10 = glm::rotate(p10, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		p10 = glm::scale(p10, glm::vec3(1.0f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(p10));

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorBase));
		meshList[5]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorRojo));
		meshList[6]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorVerde));
		meshList[7]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorAmarillo));
		meshList[8]->RenderMesh();

		glUniform3fv(uniformColor, 1, glm::value_ptr(colorMagenta));
		meshList[9]->RenderMesh();
		

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}		