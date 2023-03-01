﻿#pragma once
#include "../simple_core_minimal.h"
#include "../../../simple_library_macro.h"

_CRT_BEGIN_C_HEADER
void SIMPLE_LIBRARY_API remove_string_start(char *str, char const* sub_str);

//从后往前找
int SIMPLE_LIBRARY_API find_string_from_end(const char* str, char const* sub_str, int start_pos);

//从前往后找
int SIMPLE_LIBRARY_API find_string(const char *str, char const* sub_str,int start_pos);

void SIMPLE_LIBRARY_API remove_char_start(char *str, char sub_str);

void SIMPLE_LIBRARY_API remove_char_end(char *str, char sub_str);

//判定字符串是否包含
bool SIMPLE_LIBRARY_API c_str_contain(const char* buff_str,const char *sub_str);

//前后空格都修掉
void SIMPLE_LIBRARY_API trim_start_and_end_inline(char* buff);

//去除前面的空格
void SIMPLE_LIBRARY_API trim_start_inline(char *buff);
//去除后面的空格
void SIMPLE_LIBRARY_API trim_end_inline(char *buff);

//拆分
bool SIMPLE_LIBRARY_API split(const char *buf,const char* str_split,char *l,char *r, bool bcontain_str_split);

void SIMPLE_LIBRARY_API remove_all_char_end(char *str, char sub_str);

void SIMPLE_LIBRARY_API replace_string_inline(char* str,const char* sub_char_a,const char* sub_char_b);
void SIMPLE_LIBRARY_API replace_char_inline(char *str, const char sub_char_a, const char sub_char_b);

int SIMPLE_LIBRARY_API get_printf(char *buf, const char *format, ...);

int SIMPLE_LIBRARY_API get_printf_s(char *out_buf, const char *format, ...);

int SIMPLE_LIBRARY_API get_printf_s_s(int buffer_size,char *out_buf, const char *format, ...);

char SIMPLE_LIBRARY_API*string_mid(const char *int_buf ,char *out_buf,int start,int count);

int SIMPLE_LIBRARY_API char_to_tchar(const char *str, wchar_t *tc);

int SIMPLE_LIBRARY_API tchar_to_char(const wchar_t *tc, char *str);

//注意 ：str 必须是足够大的空间 不要传一个自动匹配内存的指针
void SIMPLE_LIBRARY_API wremove_string_start(wchar_t *str, wchar_t const* sub_str);

int SIMPLE_LIBRARY_API wfind_string(wchar_t *str, wchar_t const* sub_str);

void SIMPLE_LIBRARY_API wremove_wchar_start(wchar_t *str, wchar_t sub_str);

void SIMPLE_LIBRARY_API wremove_wchar_end(wchar_t *str, wchar_t sub_str);

void SIMPLE_LIBRARY_API wremove_all_wchar_end(wchar_t *str, wchar_t sub_str);

void SIMPLE_LIBRARY_API wreplace_wchar_inline(wchar_t *str, const wchar_t sub_char_a, const wchar_t sub_char_b);
void SIMPLE_LIBRARY_API wreplace_string_inline(wchar_t* str, const wchar_t* sub_char_a, const wchar_t* sub_char_b);

int SIMPLE_LIBRARY_API wget_printf(wchar_t *buf, const wchar_t *format, ...);

int SIMPLE_LIBRARY_API wget_printf_s(wchar_t *out_buf, const wchar_t *format, ...);

int SIMPLE_LIBRARY_API wget_printf_s_s(int buffer_size, wchar_t *out_buf,const wchar_t *format, ...);

wchar_t SIMPLE_LIBRARY_API*wstring_mid(const wchar_t *int_buf, wchar_t *out_buf, int start, int count);

_CRT_END_C_HEADER