#include "ObjFileReader.h"

ObjFileReader::ObjFileReader()
{

}

ObjFileReader::~ObjFileReader()
{
}

Mesh ObjFileReader::Read(std::string filePath, bool write, bool old)
{
	Mesh mesh;
	std::fstream fileStream;

	fileStream.exceptions(std::ifstream::badbit);
	try {
		fileStream.open(filePath);
		std::string line;
		std::vector<glm::fvec3> vPos;
		std::vector<glm::fvec3> vNorm;
		std::vector<glm::fvec2> vUVs;
		bool isDone = false;
		
		int vnCount = 0;
		int vCount = 0;
		
		while (std::getline(fileStream, line)) {

			if (line.empty()) 
				continue;

			unsigned int endOfFirstWord = line.find(' ');
			std::string firstWord;
			firstWord = line.substr(0, endOfFirstWord);

			if (firstWord == "o")
				ParseObjectData(line, endOfFirstWord, write);
			
			else if (firstWord == "v") {
				vCount++;
				ParseVertexData("v", line, endOfFirstWord, write, vPos);
			}
			
			else if (firstWord == "vn") {
				vnCount++;
				ParseVertexData("vn", line, endOfFirstWord, write, vNorm);
			}
			
			else if (firstWord == "vt")
				ParseVertexData("vt", line, endOfFirstWord, write, vUVs);
			
			else if (firstWord == "f")
				ParseFaceData(line, endOfFirstWord, write, mesh, vPos, old);
			
		}
		if(!old)
			AddVertexData(vPos, vNorm, mesh);
		fileStream.close();
		std::cout << vnCount << std::endl;
		std::cout << vCount << std::endl;
	}
	catch (std::ifstream::failure exc)
	{
		std::cout << exc.code() << exc.what() << std::endl;
	}
	return mesh;
}

void ObjFileReader::ParseFaceData(std::string& line, unsigned int endOfFirstWord, bool write, Mesh& mesh, std::vector<glm::fvec3> vPos, bool old)
{
	unsigned int endOfLine = line.find('\n');
	string value = line.substr(endOfFirstWord, endOfLine);

	if (write)
		std::cout << 'f' << value << std::endl;
	// TODO add index normal and uv parsing

	std::vector<unsigned int> indices;
	std::string vertexString;
	std::istringstream stream(value);

	while (stream >> vertexString) {
		size_t firstSlash = vertexString.find('/');
		if (firstSlash != std::string::npos) {
			vertexString = vertexString.substr(0, firstSlash);
		}

		// This -1 needs to be here because OBJ uses 1 based indexing instead of 0 based indexing.
		// ~Yannek
		unsigned int vertexIndex = std::stoi(vertexString)-1; 
		indices.push_back(vertexIndex);
	}

	if (indices.size() == 3) {
		// Triangle: Add directly
		Face face;
		face.indeces = indices;
		
			mesh.AddFace(face);
		if(old)
			AddFacePos(mesh, vPos, face);
	}
	else if (indices.size() == 4) {
		// Quad: Split into two triangles
		Face triangle1, triangle2;
		triangle1.indeces = { indices[0], indices[1], indices[2] };
		triangle2.indeces = { indices[0], indices[2], indices[3] };

			mesh.AddFace(triangle1);
			mesh.AddFace(triangle2);
		if (old) {
			AddFacePos(mesh, vPos, triangle1);
			AddFacePos(mesh, vPos, triangle2);
		}
	}
	else if (indices.size() > 4) {
		// Polygon: Use fan triangulation
		for (size_t i = 1; i < indices.size() - 1; ++i) {
			Face triangle;
			triangle.indeces = { indices[0], indices[i], indices[i + 1] };

				mesh.AddFace(triangle);
			if (old)
				AddFacePos(mesh, vPos, triangle);
		}
	}

	if (write) {
		for (const auto& index : indices) {
			std::cout << "Index: " << index << std::endl;
		}
	}
}

void ObjFileReader::AddFacePos(Mesh& mesh, vector<fvec3> vertex, Face face)
{
	for (int i = 0; i < face.indeces.size(); i++)
	{
		mesh.AddPos(vertex[i]);
	}
}

void ObjFileReader::AddVertexData(std::vector<glm::fvec3>& vPos, std::vector<glm::fvec3> vNorm, Mesh& mesh)
{
	for (int i = 0; i < vPos.size(); i++) {
		Vertex vert;
		vert.postion = vPos[i];
		if (i >= vNorm.size()) {
			mesh.AddVertex(vert);
			continue;
		}

		vert.normals = vNorm[i];
		//vert.uvs = vUVs[i];
		mesh.AddVertex(vert);
	}
}

void ObjFileReader::ParseObjectData(std::string& line, unsigned int endOfFirstWord, bool write)
{
	unsigned int endOfLine = line.find('\n');
	std::string value = line.substr(endOfFirstWord, endOfLine);
	if (write)
		std::cout << 'o' << value << std::endl;
}

void ObjFileReader::ParseVertexData(
	const std::string& dataType ,
	std::string& line, 
	unsigned int endOfFirstWord, 
	bool write, 
	std::vector<glm::fvec3>& v)
{
	unsigned int endOfLine = line.find('\n');
	std::string value = line.substr(endOfFirstWord, endOfLine);
	if (write)
		std::cout << dataType;

	unsigned int pos = 0;


	float components[3] = { 0,0,0 };

	int index = 0;

	while ((pos = value.find(' ')) != std::string::npos && index < 3) {
		std::string v = value.substr(0, pos);
		if (!v.empty()) {
			components[index++] = std::stof(v);
			if (write)
				std::cout << std::stof(v);
		}
		value.erase(0, pos + 1);
	}
	if (!value.empty() && index < 3) {
		components[index++] = std::stof(value);
		if (write)
			std::cout << std::stof(value);
	}
	if (write)
		std::cout << endl;

	v.push_back(glm::vec3(components[0], components[1], components[2]));
}

void ObjFileReader::ParseVertexData(
	const std::string& dataType ,
	std::string& line, 
	unsigned int endOfFirstWord, 
	bool write, 
	std::vector<glm::fvec2>& v)
{
	unsigned int endOfLine = line.find('\n');
	std::string value = line.substr(endOfFirstWord, endOfLine);
	if (write)
		std::cout << dataType;

	unsigned int pos = 0;


	float components[2] = { 0,0 };

	int index = 0;

	while ((pos = value.find(' ')) != std::string::npos && index < 2) {
		std::string v = value.substr(0, pos);
		if (!v.empty()) {
			components[index++] = std::stof(v);
			if (write)
				std::cout << std::stof(v);
		}
		value.erase(0, pos + 1);
	}
	if (!value.empty() && index < 2) {
		components[index++] = std::stof(value);
		if (write)
			std::cout << std::stof(value);
	}
	if (write)
		std::cout << endl;

	v.push_back(glm::vec2(components[0], components[1]));
}

void ObjFileReader::Save()
{
}
