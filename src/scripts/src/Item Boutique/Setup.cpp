#include "StdAfx.h"
#include "Setup.h"
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)
{
	Bon_Maxskills(mgr);
	Bon_Powerlevel_70(mgr);
	Bon_Powerlevel_80(mgr);
	Bon_Powerlevel_Blizz(mgr);
}