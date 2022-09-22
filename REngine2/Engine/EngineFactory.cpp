#include "EngineFactory.h"
#if defined(_WIN32)
#include "Platform/Windows/WindowsEngine.h"
#endif

REngineFactory::REngineFactory()
{

}

REngine* REngineFactory::CreateEngine()
{
#if defined(_WIN32)
	return new RWindowsEngine();
#elif defined(__linux__)

#endif // DEBUG
}
