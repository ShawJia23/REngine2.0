#include"RComponent.h"


RComponent::RComponent()
{
	Parent = nullptr;
}

void RComponent::AddChildren(RComponent* InChildren)
{
	Children.push_back(InChildren);
}