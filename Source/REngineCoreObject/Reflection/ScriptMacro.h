#pragma once
#define FUNCTION_DEFINITION(Func) static void Func(RMinimalObject* Context, RFrame& Stack,void const *RefData)
#define FUNCTION_IMPLEMENTATION(Func) void Func(RMinimalObject* Context, RFrame& Stack,void const *RefData)