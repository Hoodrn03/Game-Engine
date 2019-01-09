/*! \file This will be used to give a model within the game a texture. */

#pragma once

#include <glad/glad.h> 

#include <assimp/Importer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <string>
#include <vector>
using namespace std;

/*! \struct This will be used to hold all of the positional data requred for the texture. */
struct Vertex
{
	/*! \var The positioning for the texture. */
	glm::vec3 position;

	/*! \var The normal for the texture, it's facing direction. */
	glm::vec3 normal;

	/*! \var The coordinates for the texture (X, Y). */
	glm::vec2 textureCoords;
};

/*! \struct The texture's main data. */
struct Texture {

	/*! \var A unique identifier for the texture. */
	unsigned int id;

	/*! \var The type of texture. */
	string type;

	/*! \var The location to find that texture. */
	aiString filepath;
};

/*! \class This will allow for a model to have a texture assigned to it. */
class Mesh
{
	// Data Members 

public:
	
	/*! \var The angular points of the model. */
	vector<Vertex> vertices;

	/*! \var The number of elements to draw. */
	vector<unsigned int> indices;

	/*! \var A list of textures for the shape. */
	vector<Texture> textures;

	/*! \var Used to supply vertex data. */
	unsigned int VAO;

private:

	/*! \var Buffer Object. */
	unsigned int VBO, EBO;

	// Member Functions. 

public: 

	//-----------------------------------------------------------//
	/*! Constructor 
	*Param One : A list of verices used by the model. 
	*Param Two : A list of indices used by the model. 
	*Param Three : The list of textures for the model. 
	*/
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	//-----------------------------------------------------------//
	/*! Render : Render the mesh with a given shader program
	*Param One : The current shader program being used. 
	*/
	void render(const unsigned int shaderProgram);

private:

	//-----------------------------------------------------------//
	/*! SetUpMesh : Initialises all the buffer arrays
	*
	*/
	void setupMesh();

};
