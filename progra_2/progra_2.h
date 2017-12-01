
// progra_2.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// Símbolos principales


// Cprogra_2App:
// Consulte la sección progra_2.cpp para obtener información sobre la implementación de esta clase
//

class Cprogra_2App : public CWinApp
{
public:
	Cprogra_2App();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
};

extern Cprogra_2App theApp;