#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <algorithm>
#include <vector>
#include <cctype>
#include "../Mesh.h"

class ObjFileReader {
public:
	ObjFileReader();
	~ObjFileReader();

	Mesh Read(std::string filePath, bool write = false);

	std::vector<Vertex> AddVertexData(std::vector<glm::fvec3>& vPos, std::vector<glm::fvec3> vNorm);

	void ParseObjectData(std::string& line, unsigned int endOfFirstWord, bool write);
	void ParseVertexData(const std::string& dataType, std::string& line, unsigned int endOfFirstWord, bool write, std::vector<glm::fvec3>& v);
	void ParseVertexData(const std::string& dataType, std::string& line, unsigned int endOfFirstWord, bool write, std::vector<glm::fvec2>& v);
	void ParseFaceData(std::string& line, unsigned int endOfFirstWord, bool write, std::vector<unsigned int>& inds);

	void AddFacePos(Mesh& mesh, std::vector<glm::fvec3> vertex, Face face);

	void Save();

private:
	//std::string m_FilePath;
};