#pragma once

#ifndef RENGINECOREOBJECT_EXPORTS
#define RENGINECOREOBJECT_EXPORTS
#endif

#ifdef RENGINECOREOBJECT_EXPORTS
#define RENGINECOREOBJECT_API __declspec(dllexport)
#else
#define ROBJECT_API __declspec(dllimport)
#endif