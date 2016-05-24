#include "Script.h"
#include "Constants.h"

sel::State Script::m_state{ true };

void Script::Load(const std::string & filename)
{
	m_state.Load(filename);
}

void Script::Eval(const std::string & code)
{
	m_state(code.c_str());
}

void Script::GC()
{
	m_state.ForceGC();
}

sel::Selector Script::Get(const std::string & name)
{
	return m_state[name.c_str()];
}

void Script::Init()
{
	m_state("objects = {} scenes = {}");
}

void Script::Close()
{
	m_state.ForceGC();
}
