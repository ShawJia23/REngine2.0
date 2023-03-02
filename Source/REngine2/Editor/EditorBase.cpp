#include"EditorBase.h"

EditorBase::EditorBase():bOpen(true)
{

}

void EditorBase::RenderEnd()
{
	bOpen = false;
}

void EditorBase::RenderStart()
{
	bOpen = true;
}