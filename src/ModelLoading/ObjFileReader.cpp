#include "ObjFileReader.h"

ObjFileReader::ObjFileReader()
{

}

ObjFileReader::~ObjFileReader()
{
}

Mesh* ObjFileReader::Read(std::string filePath, bool write)
{
	VertexArray* va = new VertexArray();
	VertexBuffer* vb;
	IndexBuffer* ib;

	std::fstream fileStream;

	std::vector<glm::fvec3> vPos;
	std::vector<glm::fvec3> vNorm;
	std::vector<glm::fvec2> vUVs;

	std::vector<unsigned int> inds;
	fileStream.exceptions(std::ifstream::badbit);
	try {
		fileStream.open(filePath);
		std::string line;

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
				ParseFaceData(line, endOfFirstWord, write, inds);

		}

		fileStream.close();
		std::cout << vnCount << std::endl;
		std::cout << vCount << std::endl;
	}
	catch (std::ifstream::failure exc)
	{
		std::cout << exc.code() << exc.what() << std::endl;
	}
	std::vector<Vertex> verts = AddVertexData(vPos, vNorm);
	std::cout << verts.size() << " : " << inds.size() << std::endl;
	vb = new VertexBuffer(verts.size() * sizeof(Vertex), &verts[0]);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	ib = new IndexBuffer(&inds[0], inds.size());
	std::cout << "A" << std::endl;

	Mesh* mesh = new Mesh(va, ib);

	return mesh;
}

void ObjFileReader::ParseFaceData(std::string& line, unsigned int endOfFirstWord, bool write, std::vector<unsigned int>& inds)
{
	unsigned int endOfLine = line.find('\n');
	std::string value = line.substr(endOfFirstWord, endOfLine);

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
		unsigned int vertexIndex = std::stoi(vertexString) - 1;
		indices.push_back(vertexIndex);
	}

	if (indices.size() == 3) {
		// Triangle: Add directly
		Face face;
		face.indeces = indices;
		//mesh.AddFace(face);

		inds.insert(
			inds.end(),
			indices.begin(),
			indices.end()
		);
	}
	else if (indices.size() == 4) {
		// Quad: Split into two triangles
		Face triangle1, triangle2;
		triangle1.indeces = { indices[0], indices[1], indices[2] };
		triangle2.indeces = { indices[0], indices[2], indices[3] };

		//mesh.AddFace(triangle1);
		//mesh.AddFace(triangle2);

		inds.insert(
			inds.end(),
			triangle1.indeces.begin(),
			triangle1.indeces.end()
		);
		inds.insert(
			inds.end(),
			triangle2.indeces.begin(),
			triangle2.indeces.end()
		);
	}
	else if (indices.size() > 4) {
		// Polygon: Use fan triangulation
		for (size_t i = 1; i < indices.size() - 1; ++i) {
			Face triangle;
			triangle.indeces = { indices[0], indices[i], indices[i + 1] };

			//mesh.AddFace(triangle);

			inds.insert(
				inds.end(),
				triangle.indeces.begin(),
				triangle.indeces.end()
			);
		}
	}

	if (write) {
		for (const auto& index : indices) {
			std::cout << "Index: " << index << std::endl;
		}
	}
}

void ObjFileReader::AddFacePos(Mesh& mesh, std::vector<glm::fvec3> vertex, Face face)
{
	for (int i = 0; i < face.indeces.size(); i++)
	{
		mesh.AddPos(vertex[i]);
	}
}

std::vector<Vertex> ObjFileReader::AddVertexData(std::vector<glm::fvec3>& vPos, std::vector<glm::fvec3> vNorm)
{
	std::vector<Vertex> verts;
	for (int i = 0; i < vPos.size(); i++) {
		Vertex vert;
		vert.postion = vPos[i];
		if (i >= vNorm.size()) {
			verts.push_back(vert);
			continue;
		}

		vert.normals = vNorm[i];
		//vert.uvs = vUVs[i];
		verts.push_back(vert);
	}
	return verts;
}

void ObjFileReader::ParseObjectData(std::string& line, unsigned int endOfFirstWord, bool write)
{
	unsigned int endOfLine = line.find('\n');
	std::string value = line.substr(endOfFirstWord, endOfLine);
	if (write)
		std::cout << 'o' << value << std::endl;
}

void ObjFileReader::ParseVertexData(
	const std::string& dataType,
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

	v.push_back(glm::vec3(components[0], components[1], components[2]));
}

void ObjFileReader::ParseVertexData(
	const std::string& dataType,
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

	v.push_back(glm::vec2(components[0], components[1]));
}

void ObjFileReader::Save()
{
}
