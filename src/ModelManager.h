#pragma once

#include "Model.h"

class ModelManager
{
public:
	static Model Get(const std::string& name);
	static void Clear();
private:
	static Model Load(const std::string& filename);

	static std::map<std::string, Model> m_resourceMap;
};