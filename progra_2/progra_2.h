
// progra_2.h: archivo de encabezado principal para la aplicaci�n PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// S�mbolos principales


// Cprogra_2App:
// Consulte la secci�n progra_2.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class Cprogra_2App : public CWinApp
{
public:
	Cprogra_2App();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementaci�n

	DECLARE_MESSAGE_MAP()
};

extern Cprogra_2App theApp;