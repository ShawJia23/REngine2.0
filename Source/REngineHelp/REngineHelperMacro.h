#pragma once

#ifndef RENGINECORE_EXPORTS
#define RENGINECORE_EXPORTS
#endif

#ifdef RENGINECORE_EXPORTS
#define RENGINECORE_API __declspec(dllexport)
#else
#define RENGINECORE_API __declspec(dllimport)
#endif // EEE