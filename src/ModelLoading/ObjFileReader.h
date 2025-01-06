#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include "../Mesh.h"
#include <algorithm>
#include <vector>
#include <cctype>

class ObjFileReader {
public:
	ObjFileReader();
	~ObjFileReader();

	Mesh Read(std::string filePath, bool write = false, bool old = false);

	void AddVertexData(std::vector<glm::fvec3>& vPos, std::vector<glm::fvec3> vNorm, Mesh& mesh);

	void ParseObjectData(std::string& line, unsigned int endOfFirstWord, bool write);
	void ParseVertexData(const std::string& dataType, std::string& line, unsigned int endOfFirstWord, bool write, std::vector<glm::fvec3>& v);
	void ParseVertexData(const std::string & dataType, std::string& line, unsigned int endOfFirstWord, bool write, std::vector<glm::fvec2>& v);
	void ParseFaceData(std::string& line, unsigned int endOfFirstWord, bool write, Mesh& mesh, std::vector<glm::fvec3> vPos, bool old);
	
	void AddFacePos(Mesh& mesh, vector<fvec3> vertex, Face face);

	void Save();

private:
	//std::string m_FilePath;
};