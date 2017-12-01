
// progra_2Dlg.h: archivo de encabezado
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


extern "C" {
	float escalaGrises(float R, float G, float B);
	float multiplicar(float a, float b);
	float dividir(float a, float b);
}


// Cuadro de diálogo de Cprogra_2Dlg
class Cprogra_2Dlg : public CDialogEx
{
// Construcción
public:
	Cprogra_2Dlg(CWnd* pParent = NULL);	// Constructor estándar

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRA_2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV

	

// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:

	long size;


	// IDEAL
	
	float kernel_I_3x3[3][3] = { {1,1,1}, {1,1,1}, {1,1,1} };
	float kernel_I_5x5[5][5] = { {1,1,1,1,1}, {1,1,1,1,1}, {1,1,1,1,1}, {1,1,1,1,1}, {1,1,1,1,1} };
	float kernel_I_7x7[7][7] = { {1,1,1,1,1,1,1}, {1,1,1,1,1,1,1}, {1,1,1,1,1,1,1}, {1,1,1,1,1,1,1}, {1,1,1,1,1,1,1}, {1,1,1,1,1,1,1}, {1,1,1,1,1,1,1} };

	// GAUSSEAN BLUR

	float kernel_GB_3x3[3][3] = { { 0.0113437f,0.083819f,0.011343f }, { 0.0838195f,0.619347f,0.083819f }, { 0.0113437f,0.083819f,0.011343f } };
	float kernel_GB_5x5[5][5] = { {0.002969f, 0.01330f, 0.021938f, 0.01330f, 0.00296f},
									{0.013306f, 0.05963f, 0.098320f, 0.05963f, 0.01330f},
									{0.021938f, 0.09832f, 0.163102f, 0.09832f, 0.02193f},
									{0.013306f, 0.05963f, 0.098320f, 0.05963f, 0.01330f},
									{0.002969f, 0.01330f, 0.021938f, 0.01330f, 0.00296f} };
	float kernel_GB_7x7[7][7] = { {0.00134196f, 0.004075f, 0.007939f, 0.009915f, 0.007939f, 0.0040765f, 0.001341f},
									{0.00407653f, 0.012383f, 0.024119f, 0.030121f, 0.024119f, 0.0123834f, 0.004076f},
									{0.00793999f, 0.024119f, 0.046978f, 0.058669f, 0.046978f, 0.0241195f, 0.007939f},
									{0.00991585f, 0.030121f, 0.058669f, 0.073268f, 0.058669f, 0.0301217f, 0.009915f},
									{0.00793999f, 0.024119f, 0.046978f, 0.058669f, 0.046978f, 0.0241195f, 0.007939f},
									{0.00407653f, 0.012383f, 0.024119f, 0.030121f, 0.024119f, 0.0123834f, 0.004076f},
									{0.00134196f, 0.004076f, 0.007939f, 0.009915f, 0.007939f, 0.0040765f, 0.001341f} };


	// PREWIT

	float kernel_P_Horizontal[3][3] = { {1,2,1}, {0,0,0}, {-1,-2,-1} };
	float kernel_P_Vertical[3][3] = { {1,0,-1}, {2,0,-2}, {1,0,-1} };


	CImage BitMap;
	CImage BitMap_Mod;
	BITMAPINFO *pInformacionBMP;									//Almacena los datos de la imagen
	BYTE *pBmpData;													//Cabecera de la imagen 
	CFile ArchivoBmp;
	CEdit m_dirImagen;
	CStatic m_ImagenOriginal;
	CStatic m_imagenModificada;
	CComboBox m_EfectoEscogido;
	CString DireccionImagenOriginal;
	CString ExtensionArchivo;										//Se utiliza a la hora de buscar y abrir una imagen
	CString ExtensionImagen = _T("Archivos BMP (*.bmp)|*.bmp||");	//Extencion de la imagen definida. -> .BMP
	CString DireccionImagenModificada;
	DWORD bytesLeidos;
	BITMAPFILEHEADER HeaderBmp;
	BITMAPINFOHEADER InformacionBMP;

	afx_msg void OnBnClicked_buscarImagen();
	afx_msg void OnBnClicked_botonProcesar();
	afx_msg void OnBnClicked_botonGuardar();

	void OnDisplayMessage(CString msj);
	void desplegarImagenBmp(CString DirrecionImagen, int identificador);
	void desplegarImagenBmpProcesada();
	void Convolucion_3x3(float **kernel, float valorDividir);
	void Convolucion_5x5(float kernel[5][5], float valorDividir);
	void Convolucion_7x7(float kernel[7][7], float valorDividir);

	CComboBox m_matrizPrewitEscogida;
	CComboBox m_matrizEscogida;
	CListBox m_vistaColores;
	CProgressCtrl m_barraProgreso;
	afx_msg void OnLbnSelchangevistacolores();
};
