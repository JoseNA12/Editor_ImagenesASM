
// progra_2Dlg.cpp: archivo de implementación
//

#include "stdafx.h"
#include "progra_2.h"
#include "progra_2Dlg.h"
#include "afxdialogex.h"
#include "atlimage.h"
#include "afxwin.h"
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#define length(x) (sizeof(x)/sizeof(x[0]))
#endif


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cuadro de diálogo de Cprogra_2Dlg



Cprogra_2Dlg::Cprogra_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROGRA_2_DIALOG, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cprogra_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_ImagenActual, m_ImagenOriginal);
	DDX_Control(pDX, ID_imagenModificada, m_imagenModificada);
	DDX_Control(pDX, ID_dirImagen, m_dirImagen);
	DDX_Control(pDX, ID_EfectoEscogido, m_EfectoEscogido);
	DDX_Control(pDX, ID_matrizPrewitEscogida, m_matrizPrewitEscogida);
	DDX_Control(pDX, ID_MatrizEscogida, m_matrizEscogida);
	//DDX_Control(pDX, ID_vistaColores, m_vistaColores);
	DDX_Control(pDX, ID_barraProgreso, m_barraProgreso);
}

BEGIN_MESSAGE_MAP(Cprogra_2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_botonProcesar, &Cprogra_2Dlg::OnBnClicked_botonProcesar)
	ON_BN_CLICKED(ID_botonGuardar, &Cprogra_2Dlg::OnBnClicked_botonGuardar)
	ON_BN_CLICKED(ID_buscarImagen, &Cprogra_2Dlg::OnBnClicked_buscarImagen)
END_MESSAGE_MAP()


// Controladores de mensaje de Cprogra_2Dlg

BOOL Cprogra_2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Inicializar componentes

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional

	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void Cprogra_2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void Cprogra_2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR Cprogra_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cprogra_2Dlg::desplegarImagenBmp(CString DirrecionImagen, int cuadroImagen) {

	// Abre el archivo en sólo lectura. Lee por partes los datos la informacion del archivo BMP
	if (!ArchivoBmp.Open(DirrecionImagen, CFile::modeRead | CFile::typeBinary))
		return;
	if (ArchivoBmp.Read(&HeaderBmp, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (ArchivoBmp.Read(&InformacionBMP, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;

	pInformacionBMP = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];

	// Aplicacion de datos de la imagen
	memcpy(pInformacionBMP, &InformacionBMP, sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = HeaderBmp.bfSize - HeaderBmp.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	ArchivoBmp.Read(pBmpData, dataBytes);
	ArchivoBmp.Close();

	// Visualizar la imagen
	CWnd *pWnd = GetDlgItem(cuadroImagen);							//Obtener el identificador de la ventana(Picture Control)
	CRect rect;
	pWnd->GetClientRect(&rect);										//Obtener el area del Picture Control
	CDC *pDC = pWnd->GetDC();
	pDC->SetStretchBltMode(COLORONCOLOR);
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
		InformacionBMP.biWidth, InformacionBMP.biHeight, pBmpData, pInformacionBMP, DIB_RGB_COLORS, SRCCOPY);	//Amoldar la imagen segun el tamaño del Picture Control

}


void Cprogra_2Dlg::desplegarImagenBmpProcesada() {

	CString dirImagenTemp = DireccionImagenOriginal + "TEMP.bmp";	//Guardar de manera temporal la imagen modificada
	BitMap_Mod.Save(dirImagenTemp);										//..para poder desplegarla en el Picture Control
	desplegarImagenBmp(dirImagenTemp, ID_imagenModificada);			// Desplegar la imagen en el cuadro

	OnDisplayMessage(_T("Listo!. Imagen procesada."));				//Desplegar cuadro de mensaje

	CFile::Remove(dirImagenTemp);									//Una vez desplegada la imagen, borrarla
}

void Cprogra_2Dlg::OnBnClicked_buscarImagen()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, ExtensionImagen, NULL);
 
	if (dlg.DoModal() == IDOK)
	{
		DireccionImagenOriginal = dlg.GetPathName();				//Obtiene el nombre de la imagen
		ExtensionArchivo = dlg.GetFileExt();						//Obtiene la extencion de la imagen
		ExtensionArchivo.MakeLower();								//Pasa a minusculas la extencion en caso de que sea BMP

		desplegarImagenBmp(DireccionImagenOriginal, ID_ImagenActual);

		m_dirImagen.SetWindowText(DireccionImagenOriginal);			//Cuadro de texto con la dirrecion de la imagen seleccionada

		BitMap.Destroy(); BitMap_Mod.Destroy();						//Desprende el mapa de bits del objeto CImage y destruye el mapa de bits
																	//Soluciona un error de runtime cuando se cargan imagenes seguidas.
	}
}


void Cprogra_2Dlg::OnBnClicked_botonProcesar()
{
	BitMap.Destroy();
	BitMap_Mod.Destroy();

	BitMap.Load(DireccionImagenOriginal);
	BitMap_Mod.Load(DireccionImagenOriginal);

	if (DireccionImagenOriginal != "") {

		CString filtroEscogido;
		m_EfectoEscogido.GetWindowTextW(filtroEscogido);			//Obtener lo seleccionado de la caja de texto
		
		if (filtroEscogido != "") {
			COLORREF ValorPixel = 0;								//Informacion del color del pixel
			float R = 0.0f, G = 0.0f, B = 0.0f;						//Valores RGB
			CWaitCursor wait;										//Pone el cursor del mouse en 'espera'
			m_barraProgreso.SetRange(0, BitMap.GetWidth());			//Asignar el rango por el cual la barra se va a desplazar de acuerdo a la imagen

			//==========================================================================================================//
			//												BLANCO Y NEGRO
			//==========================================================================================================//

			if (filtroEscogido == "Escala de grises") {

				for (int i = 0; i < BitMap.GetWidth(); i++)			//Ancho
				{
					m_barraProgreso.SetPos(i);

					for (int j = 0; j < BitMap.GetHeight(); j++)    //Largo
					{
						ValorPixel = BitMap.GetPixel(i, j);
						R = GetRValue(ValorPixel);					//Extrae el valor rojo

						G = GetGValue(ValorPixel);					//Extrae el valor verde

						B = GetBValue(ValorPixel);					//Extrae el valor azul

						//-----------ENSAMBLADOR-----------//
						float valorGris = escalaGrises(R, G, B);
						//-----------ENSAMBLADOR-----------//

						R = valorGris;
						G = valorGris;
						B = valorGris;

						ValorPixel = RGB(R, G, B);
						BitMap_Mod.SetPixel(i, j, ValorPixel);			//Guardar la imagen modificada
					}
				}
				desplegarImagenBmpProcesada();						//Muestra la imagen modificada en el cuadro de vista previa.
				m_barraProgreso.SetPos(0);
			}

			//==========================================================================================================//
			//													IDEAL
			//==========================================================================================================//

			if (filtroEscogido == "Ideal") {
				CString tamañoMatrizEscogida;
				m_matrizEscogida.GetWindowTextW(tamañoMatrizEscogida);

				if (tamañoMatrizEscogida != "") {
					int mitad, i, j, m, n, mm, nn, ii, jj;
					float acumulador_R; float acumulador_G; float acumulador_B;

					if (tamañoMatrizEscogida == "3x3") {
						
						mitad = length(kernel_I_3x3) / 2;

						/* Proceso de convolucion
						* Recorro la imagen en los dos primeros for, al igual que el kernel
						* en la variable mm hallo el indice de la fila del kernel alrevez, al
						* igual que la variable nn, almacena la columna del kernel alrevez,
						* las variables ii,jj son para almacenar la posicion de las imagenes tomando
						* en cuenta su limite exterior es decir i-1, j-1,la variable 'acumulador' almacena el resultado
						* que luego es asignado en la posicion de la imagen resultante
						*/

						for (i = 0; i < BitMap.GetWidth(); ++i) // Filas
						{
							m_barraProgreso.SetPos(i);

							for (j = 0; j < BitMap.GetHeight(); ++j) // Columnas
							{
								// Variable acumuladora

								acumulador_R = 0.0f; acumulador_G = 0.0f; acumulador_B = 0.0f;

								for (m = 0; m < length(kernel_I_3x3); ++m) // Filas del Kernel
								{
									mm = length(kernel_I_3x3) - 1 - m; // Indice de la fila del kernel alrevez

									for (n = 0; n < length(kernel_I_3x3); ++n) // Columnas del kernel
									{
										nn = length(kernel_I_3x3) - 1 - n; // Indice de la columna del kernel alrevez


										ii = i + (m - mitad);
										jj = j + (n - mitad);

										// validar limites de la imagen 00000
										if (ii >= 0 && ii < BitMap.GetWidth() && jj >= 0 && jj < BitMap.GetHeight())
										{

											ValorPixel = BitMap.GetPixel(ii, jj);
											R = GetRValue(ValorPixel);
											G = GetGValue(ValorPixel);
											B = GetBValue(ValorPixel);

											acumulador_R += multiplicar(R, kernel_I_3x3[mm][nn]);
											acumulador_G += multiplicar(G, kernel_I_3x3[mm][nn]);
											acumulador_B += multiplicar(B, kernel_I_3x3[mm][nn]);
										}
									}
								}
								acumulador_R = dividir(acumulador_R, 9);
								acumulador_G = dividir(acumulador_G, 9);
								acumulador_B = dividir(acumulador_B, 9);

								COLORREF nuevoPixel = RGB(acumulador_R, acumulador_G, acumulador_B);
								BitMap_Mod.SetPixel(i, j, nuevoPixel);
							}
						}
						desplegarImagenBmpProcesada();
						m_barraProgreso.SetPos(0);
					}

					if (tamañoMatrizEscogida == "5x5") {
						mitad = length(kernel_I_5x5) / 2;

						for (i = 0; i < BitMap.GetWidth(); ++i) // Filas
						{
							m_barraProgreso.SetPos(i);

							for (j = 0; j < BitMap.GetHeight(); ++j) // Columnas
							{
								acumulador_R = 0.0f; acumulador_G = 0.0f; acumulador_B = 0.0f;

								for (m = 0; m < length(kernel_I_5x5); ++m) // Filas del Kernel
								{
									mm = length(kernel_I_5x5) - 1 - m; // Indice de la fila del kernel alrevez

									for (n = 0; n < length(kernel_I_5x5); ++n) // Columnas del kernel
									{
										nn = length(kernel_I_5x5) - 1 - n; // Indice de la columna del kernel alrevez


										ii = i + (m - mitad);
										jj = j + (n - mitad);

										// validar limites de la imagen 00000
										if (ii >= 0 && ii < BitMap.GetWidth() && jj >= 0 && jj < BitMap.GetHeight())
										{
											ValorPixel = BitMap.GetPixel(ii, jj);
											R = GetRValue(ValorPixel);
											G = GetGValue(ValorPixel);
											B = GetBValue(ValorPixel);

											acumulador_R += multiplicar(R, kernel_I_5x5[mm][nn]);
											acumulador_G += multiplicar(G, kernel_I_5x5[mm][nn]);
											acumulador_B += multiplicar(B, kernel_I_5x5[mm][nn]);
										}
									}
								}
								acumulador_R = dividir(acumulador_R, 25);
								acumulador_G = dividir(acumulador_G, 25);
								acumulador_B = dividir(acumulador_B, 25);

								COLORREF nuevoPixel = RGB(acumulador_R, acumulador_G, acumulador_B);
								BitMap_Mod.SetPixel(i, j, nuevoPixel);

							}
						}
						desplegarImagenBmpProcesada();
					}

					if (tamañoMatrizEscogida == "7x7") {
						mitad = length(kernel_I_7x7) / 2;

						for (i = 0; i < BitMap.GetWidth(); ++i) // Filas
						{
							m_barraProgreso.SetPos(i);

							for (j = 0; j < BitMap.GetHeight(); ++j) // Columnas
							{
								acumulador_R = 0.0f; acumulador_G = 0.0f; acumulador_B = 0.0f;

								for (m = 0; m < length(kernel_I_7x7); ++m) // Filas del Kernel
								{
									mm = length(kernel_I_7x7) - 1 - m; // Indice de la fila del kernel alrevez

									for (n = 0; n < length(kernel_I_7x7); ++n) // Columnas del kernel
									{
										nn = length(kernel_I_7x7) - 1 - n; // Indice de la columna del kernel alrevez


										ii = i + (m - mitad);
										jj = j + (n - mitad);

										// validar limites de la imagen 00000
										if (ii >= 0 && ii < BitMap.GetWidth() && jj >= 0 && jj < BitMap.GetHeight())
										{

											ValorPixel = BitMap.GetPixel(ii, jj);
											R = GetRValue(ValorPixel);
											G = GetGValue(ValorPixel);
											B = GetBValue(ValorPixel);

											acumulador_R += multiplicar(R, kernel_I_7x7[mm][nn]);
											acumulador_G += multiplicar(G, kernel_I_7x7[mm][nn]);
											acumulador_B += multiplicar(B, kernel_I_7x7[mm][nn]);

										}
									}
								}

								acumulador_R = dividir(acumulador_R, 49);
								acumulador_G = dividir(acumulador_G, 49);
								acumulador_B = dividir(acumulador_B, 49);

								COLORREF nuevoPixel = RGB(acumulador_R, acumulador_G, acumulador_B);
								BitMap_Mod.SetPixel(i, j, nuevoPixel);
							}
						}
						desplegarImagenBmpProcesada();
					}
				}

				else {
					OnDisplayMessage(_T("Por favor, selecione el tamaño de la matriz."));
				}
			}

			//==========================================================================================================//
			//												GAUSSEAN BLUR
			//==========================================================================================================//

			if (filtroEscogido == "Gaussean Blur") {
				CString tamañoMatrizEscogida;
				m_matrizEscogida.GetWindowTextW(tamañoMatrizEscogida);

				if (tamañoMatrizEscogida != "") {
					int mitad, i, j, m, n, mm, nn, ii, jj;
					float acumulador_R; float acumulador_G; float acumulador_B; float acumulador; float valorMultiplicar;

					if (tamañoMatrizEscogida == "3x3") {
						mitad = length(kernel_GB_3x3) / 2; int cont = 0;

						for (i = 0; i < BitMap.GetWidth(); ++i) // Filas
						{
							m_barraProgreso.SetPos(i);

							for (j = 0; j < BitMap.GetHeight(); ++j) // Columnas
							{
								acumulador_R = 0; acumulador_G = 0; acumulador_B = 0;  acumulador = 0; valorMultiplicar = 0;

								for (m = 0; m < length(kernel_GB_3x3); ++m) // Filas del Kernel
								{
									mm = length(kernel_GB_3x3) - 1 - m; // Indice de la fila del kernel alrevez

									for (n = 0; n < length(kernel_GB_3x3); ++n) // Columnas del kernel
									{
										nn = length(kernel_GB_3x3) - 1 - n; // Indice de la columna del kernel alrevez

										ii = i + (m - mitad);
										jj = j + (n - mitad);

										// validar limites de la imagen 00000
										if (ii >= 0 && ii < BitMap.GetWidth() && jj >= 0 && jj < BitMap.GetHeight())
										{

											ValorPixel = (BitMap.GetPixel(ii, jj));

											R = GetRValue(ValorPixel);
											G = GetGValue(ValorPixel);
											B = GetBValue(ValorPixel);

											acumulador_R += multiplicar(R, kernel_GB_3x3[mm][nn]);
											acumulador_G += multiplicar(G, kernel_GB_3x3[mm][nn]);
											acumulador_B += multiplicar(B, kernel_GB_3x3[mm][nn]);
										}
									}
								}
								COLORREF nuevoPixel = RGB(acumulador_R, acumulador_G, acumulador_B);
								BitMap_Mod.SetPixel(i, j, nuevoPixel);
							}
						}

						desplegarImagenBmpProcesada();
					}

					if (tamañoMatrizEscogida == "5x5") {
						mitad = length(kernel_GB_5x5) / 2; int cont = 0;

						for (i = 0; i < BitMap.GetWidth(); ++i) // Filas
						{
							m_barraProgreso.SetPos(i);

							for (j = 0; j < BitMap.GetHeight(); ++j) // Columnas
							{
								acumulador_R = 0; acumulador_G = 0; acumulador_B = 0;  acumulador = 0; valorMultiplicar = 0;

								for (m = 0; m < length(kernel_GB_5x5); ++m) // Filas del Kernel
								{
									mm = length(kernel_GB_5x5) - 1 - m; // Indice de la fila del kernel alrevez

									for (n = 0; n < length(kernel_GB_5x5); ++n) // Columnas del kernel
									{
										nn = length(kernel_GB_5x5) - 1 - n; // Indice de la columna del kernel alrevez

										ii = i + (m - mitad);
										jj = j + (n - mitad);

										// validar limites de la imagen 00000
										if (ii >= 0 && ii < BitMap.GetWidth() && jj >= 0 && jj < BitMap.GetHeight())
										{

											ValorPixel = (BitMap.GetPixel(ii, jj));
											R = GetRValue(ValorPixel);
											G = GetGValue(ValorPixel);
											B = GetBValue(ValorPixel);

											acumulador_R += multiplicar(R, kernel_GB_5x5[mm][nn]);
											acumulador_G += multiplicar(G, kernel_GB_5x5[mm][nn]);
											acumulador_B += multiplicar(B, kernel_GB_5x5[mm][nn]);
										}
									}
								}
								COLORREF nuevoPixel = RGB(acumulador_R, acumulador_G, acumulador_B);
								BitMap_Mod.SetPixel(i, j, nuevoPixel);
							}
						}
						desplegarImagenBmpProcesada();
					}

					if (tamañoMatrizEscogida == "7x7") {
						mitad = length(kernel_GB_7x7) / 2; int cont = 0;

						for (i = 0; i < BitMap.GetWidth(); ++i) // Filas
						{
							m_barraProgreso.SetPos(i);

							for (j = 0; j < BitMap.GetHeight(); ++j) // Columnas
							{
								acumulador_R = 0; acumulador_G = 0; acumulador_B = 0;  acumulador = 0; valorMultiplicar = 0;

								for (m = 0; m < length(kernel_GB_7x7); ++m) // Filas del Kernel
								{
									mm = length(kernel_GB_7x7) - 1 - m; // Indice de la fila del kernel alrevez

									for (n = 0; n < length(kernel_GB_7x7); ++n) // Columnas del kernel
									{
										nn = length(kernel_GB_7x7) - 1 - n; // Indice de la columna del kernel alrevez

										ii = i + (m - mitad);
										jj = j + (n - mitad);

										// validar limites de la imagen 00000
										if (ii >= 0 && ii < BitMap.GetWidth() && jj >= 0 && jj < BitMap.GetHeight())
										{

											ValorPixel = (BitMap.GetPixel(ii, jj));

											R = GetRValue(ValorPixel);
											G = GetGValue(ValorPixel);
											B = GetBValue(ValorPixel);

											acumulador_R += multiplicar(R, kernel_GB_7x7[mm][nn]);
											acumulador_G += multiplicar(G, kernel_GB_7x7[mm][nn]);
											acumulador_B += multiplicar(B, kernel_GB_7x7[mm][nn]);
										}
									}
								}
								COLORREF nuevoPixel = RGB(acumulador_R, acumulador_G, acumulador_B);
								BitMap_Mod.SetPixel(i, j, nuevoPixel);
							}
						}
						desplegarImagenBmpProcesada();
					}
				}
				else {
					OnDisplayMessage(_T("Por favor, selecione el tamaño de la matriz."));
				}
			}

			//==========================================================================================================//
			//													PREWIT
			//==========================================================================================================//

			if (filtroEscogido == "Prewit") {
				CString tamañoMatrizPrewitEscogida;
				m_matrizPrewitEscogida.GetWindowTextW(tamañoMatrizPrewitEscogida);

				if (tamañoMatrizPrewitEscogida != "") {
					int mitad, i, j, m, n, ii, jj, mm, nn;
					float acumulador_R; float acumulador_G; float acumulador_B; float acumulador;

					if (tamañoMatrizPrewitEscogida == "Horizontal") {

						mitad = length(kernel_P_Horizontal) / 2;

						for (i = 0; i < BitMap.GetWidth(); ++i) // Filas
						{
							m_barraProgreso.SetPos(i);

							for (j = 0; j < BitMap.GetHeight(); ++j) // Columnas
							{
								// Variable acumuladora
								acumulador_R = 0.0f; acumulador_G = 0.0f; acumulador_B = 0.0f; acumulador = 0;

								for (m = 0; m < length(kernel_P_Horizontal); ++m) // Filas del Kernel
								{
									mm = length(kernel_P_Horizontal) - 1 - m; // Indice de la fila del kernel alrevez

									for (n = 0; n < length(kernel_P_Horizontal); ++n) // Columnas del kernel
									{
										nn = length(kernel_P_Horizontal) - 1 - n; // Indice de la columna del kernel alrevez

										ii = i + (m - mitad);
										jj = j + (n - mitad);

										// validar limites de la imagen 00000
										if (ii >= 0 && ii < BitMap.GetWidth() && jj >= 0 && jj < BitMap.GetHeight())
										{

											ValorPixel = BitMap.GetPixel(ii, jj);

											R = GetRValue(ValorPixel);
											G = GetGValue(ValorPixel);
											B = GetBValue(ValorPixel);

											float valorMultiplicar = (float)(dividir(kernel_P_Horizontal[mm][nn], 3));

											//acumulador += (float)((R+G+B) *kernel_P_Horizontal[m][n]);

											acumulador_R += multiplicar(R, valorMultiplicar);
											acumulador_G += multiplicar(G, valorMultiplicar);
											acumulador_B += multiplicar(B, valorMultiplicar);
										}
									}
								}

								acumulador_R = dividir(acumulador_R, 9);
								acumulador_G = dividir(acumulador_G, 9);
								acumulador_B = dividir(acumulador_B, 9);

								COLORREF nuevoPixel = RGB(acumulador_R, acumulador_G, acumulador_B);
								BitMap_Mod.SetPixel(i, j, nuevoPixel);
							}
						}
						desplegarImagenBmpProcesada();
					}

					if (tamañoMatrizPrewitEscogida == "Vertical") {
						mitad = length(kernel_P_Horizontal) / 2;

						for (i = 0; i < BitMap.GetWidth(); ++i) // Filas
						{
							m_barraProgreso.SetPos(i);

							for (j = 0; j < BitMap.GetHeight(); ++j) // Columnas
							{
								// Variable acumuladora
								acumulador_R = 0.0f; acumulador_G = 0.0f; acumulador_B = 0.0f; acumulador = 0;

								for (m = 0; m < length(kernel_P_Vertical); ++m) // Filas del Kernel
								{
									mm = length(kernel_P_Vertical) - 1 - m; // Indice de la fila del kernel alrevez

									for (n = 0; n < length(kernel_P_Vertical); ++n) // Columnas del kernel
									{
										nn = length(kernel_P_Vertical) - 1 - n; // Indice de la columna del kernel alrevez

										ii = i + (m - mitad);
										jj = j + (n - mitad);

										// validar limites de la imagen 00000
										if (ii >= 0 && ii < BitMap.GetWidth() && jj >= 0 && jj < BitMap.GetHeight())
										{

											ValorPixel = BitMap.GetPixel(ii, jj);

											R = GetRValue(ValorPixel);
											G = GetGValue(ValorPixel);
											B = GetBValue(ValorPixel);

											float valorMultiplicar = (float)(dividir(kernel_P_Vertical[mm][nn], 3));

											//acumulador += (float)((R+G+B) *kernel_P_Horizontal[m][n]);

											acumulador_R += multiplicar(R, valorMultiplicar);
											acumulador_G += multiplicar(G, valorMultiplicar);
											acumulador_B += multiplicar(B, valorMultiplicar);
										}
									}
								}

								acumulador_R = dividir(acumulador_R, 9);
								acumulador_G = dividir(acumulador_G, 9);
								acumulador_B = dividir(acumulador_B, 9);

								COLORREF nuevoPixel = RGB(acumulador_R, acumulador_G, acumulador_B);
								BitMap_Mod.SetPixel(i, j, nuevoPixel);
							}
						}
						desplegarImagenBmpProcesada();
					}

					if (tamañoMatrizPrewitEscogida == "Combinado") {

						mitad = length(kernel_P_Horizontal) / 2; m_barraProgreso.SetRange(0, BitMap.GetWidth() * 2);

						for (i = 0; i < BitMap.GetWidth(); ++i) // Filas
						{
							m_barraProgreso.SetPos(i);

							for (j = 0; j < BitMap.GetHeight(); ++j) // Columnas
							{
								// Variable acumuladora
								acumulador_R = 0.0f; acumulador_G = 0.0f; acumulador_B = 0.0f; acumulador = 0;

								for (m = 0; m < length(kernel_P_Horizontal); ++m) // Filas del Kernel
								{
									mm = length(kernel_P_Horizontal) - 1 - m; // Indice de la fila del kernel alrevez

									for (n = 0; n < length(kernel_P_Horizontal); ++n) // Columnas del kernel
									{
										nn = length(kernel_P_Horizontal) - 1 - n; // Indice de la columna del kernel alrevez

										ii = i + (m - mitad);
										jj = j + (n - mitad);

										// validar limites de la imagen 00000
										if (ii >= 0 && ii < BitMap.GetWidth() && jj >= 0 && jj < BitMap.GetHeight())
										{

											ValorPixel = BitMap.GetPixel(ii, jj);

											R = GetRValue(ValorPixel);
											G = GetGValue(ValorPixel);
											B = GetBValue(ValorPixel);

											float valorMultiplicar = (float)(dividir(kernel_P_Horizontal[mm][nn], 3));

											//acumulador += (float)((R+G+B) *kernel_P_Horizontal[m][n]);

											acumulador_R += multiplicar(R, valorMultiplicar);
											acumulador_G += multiplicar(G, valorMultiplicar);
											acumulador_B += multiplicar(B, valorMultiplicar);
										}
									}
								}

								acumulador_R = dividir(acumulador_R, 9);
								acumulador_G = dividir(acumulador_G, 9);
								acumulador_B = dividir(acumulador_B, 9);

								COLORREF nuevoPixel = RGB(acumulador_R, acumulador_G, acumulador_B);
								BitMap_Mod.SetPixel(i, j, nuevoPixel);
							}
						}

						mitad, i, j, m, n, ii, jj, mm, nn = 0;
						acumulador_R, acumulador_G, acumulador_B, acumulador = 0.0f;

						mitad = length(kernel_P_Horizontal) / 2;
						

						for (i = 0; i < BitMap_Mod.GetWidth(); ++i) // Filas
						{
							m_barraProgreso.SetPos(i + BitMap_Mod.GetWidth());

							for (j = 0; j < BitMap_Mod.GetHeight(); ++j) // Columnas
							{
								// Variable acumuladora
								acumulador_R = 0.0f; acumulador_G = 0.0f; acumulador_B = 0.0f; acumulador = 0;

								for (m = 0; m < length(kernel_P_Vertical); ++m) // Filas del Kernel
								{
									mm = length(kernel_P_Vertical) - 1 - m; // Indice de la fila del kernel alrevez

									for (n = 0; n < length(kernel_P_Vertical); ++n) // Columnas del kernel
									{
										nn = length(kernel_P_Vertical) - 1 - n; // Indice de la columna del kernel alrevez

										ii = i + (m - mitad);
										jj = j + (n - mitad);

										// validar limites de la imagen 00000
										if (ii >= 0 && ii < BitMap_Mod.GetWidth() && jj >= 0 && jj < BitMap_Mod.GetHeight())
										{

											ValorPixel = BitMap_Mod.GetPixel(ii, jj);

											R = GetRValue(ValorPixel);
											G = GetGValue(ValorPixel);
											B = GetBValue(ValorPixel);

											float valorMultiplicar = (float)(dividir(kernel_P_Vertical[mm][nn], 3));

											//acumulador += (float)((R+G+B) *kernel_P_Horizontal[m][n]);

											acumulador_R += multiplicar(R, valorMultiplicar);
											acumulador_G += multiplicar(G, valorMultiplicar);
											acumulador_B += multiplicar(B, valorMultiplicar);
										}
									}
								}

								acumulador_R = dividir(acumulador_R, 9);
								acumulador_G = dividir(acumulador_G, 9);
								acumulador_B = dividir(acumulador_B, 9);

								COLORREF nuevoPixel = RGB(acumulador_R, acumulador_G, acumulador_B);
								BitMap.SetPixel(i, j, nuevoPixel);
							}
						}
						BitMap_Mod = BitMap;
						desplegarImagenBmpProcesada();
					}
				}
				else {
					OnDisplayMessage(_T("Por favor, selecione el tipo de matriz Prewit."));
				}
			}
			wait.Restore();					//Restaura el cursor del mouse
			m_barraProgreso.SetPos(0);		//Restaura la barra de progreso
		}
		else {
			// No hay filtro selecionado
			OnDisplayMessage(_T("Por favor, selecione un filtro para aplicar a la imagen."));
		}
	}
	else {
		// No hay imagen seleccionada
		OnDisplayMessage(_T("Por favor, selecione una imagen (.bmp) de su equipo."));
	}
	
}


void Cprogra_2Dlg::OnBnClicked_botonGuardar()
{

	CFileDialog FileDlg(FALSE, CString(".bmp"), NULL, 0, CString(ExtensionImagen));

	if (FileDlg.DoModal() == IDOK)
	{
		DireccionImagenModificada = FileDlg.GetPathName();
		BitMap_Mod.Save(FileDlg.GetPathName());
	}

}


void Cprogra_2Dlg::OnDisplayMessage(CString msj)
{
	MessageBox(msj, _T("Atención"), MB_ICONINFORMATION | MB_OK);
}


