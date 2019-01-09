/*! \file This will be the basis for adding a model into the game engine, it will 
*			be expnaded upon with a component to allow for game object to be assigned models 
*			easily. 
*/

#pragma once
#include <string>
#include <vector>
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

/*! \class This will form the basis for creating and assigning a model to game objects. */
class Model
{

	// Data Members

private:

	/*! \var A list of meshes for the model. */
	std::vector<Mesh> v_meshes;

	/*! \var The directory where to find the model. */
	string directory;

	/*! \var A list of textures on the model. */
	vector<Texture> v_textures;

	// Member Functions 

public:

	//-----------------------------------------------------------//
	/*! Constructor 
	*Param One : The file path to find the model. 
	*/
	Model(string filepath);

	//-----------------------------------------------------------//
	/*! Render : This will be usesd to render the model in the scene. 
	*Param One : THe current shader program used by the game engine. 
	*/
	void render(const unsigned int shaderProgram);

	//-----------------------------------------------------------//
	/*! TextureFromFile : This will be used to load a model's texture from a file. 
	*Param One : The name of the file. 
	*Param Two : The location where to find the file.
	*Param Three : The gamma in the texture. 
	*/
	static unsigned int TextureFromFile(const char* filepath, const string& directory, bool gamma = false);

private: 

	//-----------------------------------------------------------//
	/*! LoadModel : This will be used to load the model from a file.
	*Param One : The file path for that model. 
	*/
	void loadModel(string path);

	//-----------------------------------------------------------//
	/*! ProcessNode : This will process a node. 
	*
	*/
	void processNode(aiNode* node, const aiScene* scene);

	//-----------------------------------------------------------//
	/*!	ProcessMesh : This will process a mesh.
	*
	*/
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	//-----------------------------------------------------------//
	/*! LoadMaterialTexture : This will load all of the tectures used by the model. 
	*
	*/
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};
