#include "WinMainCommandParameters.h"

WinMainCommandParameters::WinMainCommandParameters(HINSTANCE InhInstance, HINSTANCE InprevInstance, PSTR IncmdLine, int InshowCmd)
	:HInstance(InhInstance)
	, PrevInstance(InprevInstance)
	, CmdLine(IncmdLine)
	, ShowCmd(InshowCmd)
{

}
