/*
 *		This Code Was Created By Jeff Molofee 2000
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 *      Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/24
 */

 /* **************************************************************
 *  Project: $(project)
 *  Function : Main program
 ***************************************************************
 *  $Author: Jeff Molofee 2000
 *  $Name:  $
 ***************************************************************
 *
 *  Copyright NeHe Production
 *
 ***************************************************************/

/**         Comments manageable by Doxygen
*
*  Modified smoothly by Thierry DECHAIZE
*
*  Paradigm : obtain one source (only one !) compatible for multiple free C Compilers
*    and provide for all users an development environment on Windows (64 bits compatible),
*    the great Code::Blocks manager (version 20.03), and don't use glaux.lib or glaux.dll.
*
*	a) Mingw 32 bits, version officielle gcc 9.2.0 (old !) : downloadable on http://sourceforge.net/projects/mingw/ (official)
*	b) Mingw 64 bits included in new IDE Red Panda Dev-Cpp, version gcc 10.3.0 : donwloadable on http://sourceforge.net/projects/dev-cpp-2020/
*	c) Mingw 64 bits included in package Code::Blocks (version 20.03), version gcc 8.1.0 (very old !) : downloadable on http://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/
*	d) Mingw 32 and 64 bits packagés, version gcc 11.2.0 : downloadable on  https://winlibs.com/ (and CLANG included in, 32 and 64 bits), two kits :
*			- winlibs-i686-posix-dwarf-gcc-12.2.0-llvm-14.0.6-mingw-w64ucrt-10.0.0-r2.7z (32 bits)
*			- winlibs-x86_64-posix-seh-gcc-12.2.0-llvm-14.0.6-mingw-w64ucrt-10.0.0-r2.7z (64 bits)
*	e) Cygwin64, 32 et 64 bits, version gcc 11.3.0 : downloadable on http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
*	f) TDM GCC, 32 et 64 bits, version 10.3.0 : downloadable on http://sourceforge.net/projects/TDM-GCC
*	g) MSYS2 environnement MINGW32 and MINGW64, 32 et 64 bits, version de 2022 (msys2-x86_64-20220603.exe), version gcc 12.2.0 : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220603.exe
*	h) Visual Studio 2022, 32 et 64 bits, community edition for free : downloadable on https://visualstudio.microsoft.com/fr/thank-you-downloading-visual-studio/?sku=Community&rel=17
*	i) Borland C/C++ 32 bits, version 5.5 : downloadable on https://developerinsider.co/download-and-install-borland-c-compiler-on-windows-10/
*	j) Digital Mars Compiler C/C++ 32 bits version 8.57 : downloadable on http://www.digitalmars.com (the more old compiler, the more bugged, dead branch !)
*	k) OpenWatcom C/C++ 32 et 64 bits, version 2.0 : downloadable on http://openwatcom.mirror.fr/ (only 32 bits version run correctly !)
*	l) Lcc and Lcc64, 32 et 64 bits: downloadable http://www.cs.virginia.edu/~lcc-win32/
*	m) PELLES C (only C) , 32 et 64 bits, version 11.0 : downloadable on http://www.smorgasbordet.com/pellesc/
*	o) CLANG, adossé aux environnements MINGW64 et MINGW32, version 14.0.6 (version gcc 12.0.0) : downloadable on https://winlibs.com/
*	p) CLANG, adossé aux environnements Visual Studio 2022 (+ kits Microsoft), version 15.0.1 : downloadable on https://releases.llvm.org/download.html
*	q) CLANG de la version MSYS2, adossé aux environnements MINGW64 et MINGW32, version 15.0.0 (version gcc 12.2.0) : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220118.exe
*	r) CLANG de la version CYGWIN, adossé aux environnements MINGW64 et MINGW32, version 8.0.0 (very old !) (version gcc 11.3.0) : downloadable http://www.cygwin.com/install.html (tool for install or update : setup-x86_64.exe)
*
*   TDE -> Add resource file and resource header for restitute version + icon OpenGL.ico for fun
*			because versionning is important, same for freeware :-) !
*
*  Date : 2022/02/15
*
* \file            Lesson24.c
* \author          Jeff Molofee (NeHe) originely, Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/24
* \author          After adapted by Thierry Dechaize to verify paradigm : one source for multiple C Compilers
* \version         2.0.1.0
* \date            15 février 2022
* \brief           Ouvre une fenêtre Windows et affiche la liste des extensions OpenGL : Token, Extensions, Scissoring & TGA Loading de la carte graphique (le renderer).
* \details         Ce programme ne gére que trois événements : le clic sur le bouton "Fermé" de la fenêtre, la sortie par la touche ESC et les flêches de déplacement clavier (bas et haut).
*
*
*/

#if defined __CYGWIN__ || defined __LCC__
#define WIN32_LEAN_AND_MEAN
#endif

#include	<windows.h>										// Header File For Windows
#if defined(__LCC__)
#ifndef WINGDIAPI
#   define WINGDIAPI __stdcall
#endif
#endif

#include	<stdio.h>										// Header File For Standard Input / Output
#include	<stdarg.h>										// Header File For Variable Argument Routines
#include	<string.h>										// Header File For String Management
#include	<gl\gl.h>										// Header File For The OpenGL32 Library
#include	<gl\glu.h>										// Header File For The GLu32 Library

#if defined __GNUC__ || defined __LCC__ || defined _MSC_VER || defined __TURBOC__
#include <stdbool.h>
#endif

#if defined(__SC__) || defined(__DMC__)
#include <wtypes.h>
// typedef BOOLEAN         bool;
#endif

// A user defined ``bool'' type for compilers that don't yet support one.
//
#if defined(__BORLANDC__) && (__BORLANDC__ < 0x500) || defined(__WATCOMC__)
  #define DONT_HAVE_BOOL_TYPE
#endif

// A ``bool'' type for compilers that don't yet support one.
#if defined(DONT_HAVE_BOOL_TYPE)
  typedef char bool;

  #ifdef true
    #warning Better check include file ``mytypes.h''.
    #undef true
  #endif
  #define true 1

  #ifdef false
    #warning Better check include file ``mytypes.h''.
    #undef false
  #endif
  #define false 0
#endif

#if defined __POCC__ || defined __LCC__ || defined __WATCOMC__   // because malloc, free function ... `
#include <stdlib.h>
#endif

HDC			hDC=NULL;										// Private GDI Device Context
HGLRC		hRC=NULL;										// Permanent Rendering Context
HWND		hWnd=NULL;										// Holds Our Window Handle
HINSTANCE	hInstance;										// Holds The Instance Of The Application

BOOL		keys[256];										// Array Used For The Keyboard Routine
BOOL		active=TRUE;									// Window Active Flag Set To TRUE By Default
BOOL		fullscreen=TRUE;								// Fullscreen Flag Set To Fullscreen Mode By Default

int			scroll;											// Used For Scrolling The Screen
int			maxtokens;										// Keeps Track Of The Number Of Extensions Supported
int			swidth;											// Scissor Width
int			sheight;										// Scissor Height

GLuint		base;											// Base Display List For The Font

typedef struct												// Create A Structure
{
	GLubyte	*imageData;										// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
} TextureImage;												// Structure Name

TextureImage textures[1];									// Storage For One Texture

static	PIXELFORMATDESCRIPTOR pfd=							// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),							// Size Of This Pixel Format Descriptor
		1,														// Version Number
		PFD_DRAW_TO_WINDOW |									// Format Must Support Window
		PFD_SUPPORT_OPENGL |									// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,										// Must Support Double Buffering
		PFD_TYPE_RGBA,											// Request An RGBA Format
		0,  													// Select Our Color Depth
		0, 0, 0, 0, 0, 0,										// Color Bits Ignored
		0,														// No Alpha Buffer
		0,														// Shift Bit Ignored
		0,														// No Accumulation Buffer
		0, 0, 0, 0,												// Accumulation Bits Ignored
		16,														// 16Bit Z-Buffer (Depth Buffer)
		0,														// No Stencil Buffer
		0,														// No Auxiliary Buffer
		PFD_MAIN_PLANE,											// Main Drawing Layer
		0,														// Reserved
		0, 0, 0													// Layer Masks Ignored
    };

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);		// Declaration For WndProc

/**	            This Code Creates Texture From a TGA File.
*
* \brief      Fonction NeHeLoadBitmap2 : charge deux fichiers BMP en mémoire pour générer un tableau de six textures
* \details    En entrée le nom du fichier TGA et en sortie un tableau de textures utilisables avec OpenGL
* \param	  texture			    le tableau des textures				                                *
* \param	  filename			    nom du fichier TGA				                                    *
* \return     BOOL                  un booleen, le tableau des textures créé ou non.                    *
*
*/

BOOL LoadTGA(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
{
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)
    int         i=0;

	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if(	file==NULL ||										// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return FALSE;									// Return FALSE
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return FALSE;									// Return FALSE
		}
	}

	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

 	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return FALSE;										// Return FALSE
	}

	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return FALSE;										// Return FALSE
	}

	for(i=0; i<(int)(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

	if (texture[0].bpp==24)									// Was The TGA 24 Bits
	{
		type=GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return TRUE;											// Texture Building Went Ok, Return True
}

/**	            This Code Create la fonte à afficher.
*
* \brief      Fonction BuildFont : création de la fonte du texte à afficher
* \details    Cette fonction utilise la fonction CreateFont
* \param      GLvoid        un void OpenGL.
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid BuildFont(GLvoid)									// Build Our Font Display List
{
    int loop1=0;

	base=glGenLists(256);									// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, textures[0].texID);		// Select Our Font Texture
	for (loop1=0; loop1<256; loop1++)					    // Loop Through All 256 Lists
	{
		float cx=(float)(loop1%16)/16.0f;						// X Position Of Current Character
		float cy=(float)(loop1/16)/16.0f;						// Y Position Of Current Character

		glNewList(base+loop1,GL_COMPILE);					// Start Building A List
			glBegin(GL_QUADS);								// Use A Quad For Each Character
				glTexCoord2f(cx,1.0f-cy-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2d(0,16);							// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(16,16);							// Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.001f);	// Texture Coord (Top Right)
				glVertex2i(16,0);							// Vertex Coord (Top Right)
				glTexCoord2f(cx,1.0f-cy-0.001f);			// Texture Coord (Top Left)
				glVertex2i(0,0);							// Vertex Coord (Top Left)
			glEnd();										// Done Building Our Quad (Character)
			glTranslated(14,0,0);							// Move To The Right Of The Character
		glEndList();										// Done Building The Display List
	}														// Loop Until All 256 Are Built
}

/**	            This Code destruct la fonte à afficher.
*
* \brief      Fonction KillFont : descruction de la fonte
* \details    Cette fonction détruit l'ensemble des 96 caractères de la fonte
* \param      GLvoid        un void OpenGL.
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid KillFont(GLvoid)										// Delete The Font From Memory
{
	glDeleteLists(base,256);								// Delete All 256 Display Lists
}

/**	            This Code present la fonte à afficher.
*
* \brief      Fonction glPrint : impression à l'écran de la fonte
* \details    Cette fonction affiche l'ensemble des 96 caractères de la fonte
* \param      x             la position d'écriture en abscisse de la chaîne de caractère à imprimer.
* \param      y             la position d'écriture en ordonnée de la chaîne de caractère à imprimer.
* \param      set           un entier
* \param      fmt           la chaîne de caractère à imprimer
* \param      ...           des paramètres supplémentaires possibles ...
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid glPrint(GLint x, GLint y, int set, const char *fmt, ...)	// Where The Printing Happens
{
	char		text[1024];									// Holds Our String
	va_list		ap;											// Pointer To List Of Arguments

	if (fmt == NULL)										// If There's No Text
		return;												// Do Nothing

	va_start(ap, fmt);										// Parses The String For Variables
	    vsprintf(text, fmt, ap);							// And Converts Symbols To Actual Numbers
	va_end(ap);												// Results Are Stored In Text

	if (set>1)												// Did User Choose An Invalid Character Set?
	{
		set=1;												// If So, Select Set 1 (Italic)
	}

	glEnable(GL_TEXTURE_2D);								// Enable Texture Mapping
	glLoadIdentity();										// Reset The Modelview Matrix
	glTranslated(x,y,0);									// Position The Text (0,0 - Top Left)
	glListBase(base-32+(128*set));							// Choose The Font Set (0 or 1)

	glScalef(1.0f,2.0f,1.0f);								// Make The Text 2X Taller

	glCallLists(strlen(text),GL_UNSIGNED_BYTE, text);		// Write The Text To The Screen
	glDisable(GL_TEXTURE_2D);								// Disable Texture Mapping
}

/**	            This Code Resize the main window.
*
* \brief      Fonction ReSizeGLScene : redimensionnement de la fenêtre Windows gérant OpenGL
* \details    En entrée les deux nouvelles dimensions de la fenêtre
* \param	  width			Width of the GL Window Or Fullscreen Mode				*
* \param	  height		Height of the GL Window Or Fullscreen Mode			    *
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)			// Resize And Initialize The GL Window
{
	swidth=width;											// Set Scissor Width To Window Width
	sheight=height;											// Set Scissor Height To Window Height
	if (height==0)											// Prevent A Divide By Zero By
	{
		height=1;											// Making Height Equal One
	}
	glViewport(0,0,width,height);							// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glLoadIdentity();										// Reset The Projection Matrix
	glOrtho(0.0f,640,480,0.0f,-1.0f,1.0f);					// Create Ortho 640x480 View (0,0 At Top Left)
	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();										// Reset The Modelview Matrix
}

/**	            This Code finish the initialization OpenGL of the main window.
*
* \brief      Fonction InitGL : Fin de l'initialisation de la fenêtre Windows gérant OpenGL
* \details    Rien
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int InitGL(GLvoid)											// All Setup For OpenGL Goes Here
{
	if (!LoadTGA(&textures[0],"../../Data/Font.TGA"))				// Load The Font Texture
	{
		return FALSE;										// If Loading Failed, Return FALSE
	}

	BuildFont();											// Build The Font

	glShadeModel(GL_SMOOTH);								// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);					// Black Background
	glClearDepth(1.0f);										// Depth Buffer Setup
	glBindTexture(GL_TEXTURE_2D, textures[0].texID);		// Select Our Font Texture

	return TRUE;											// Initialization Went OK
}

/**	            This Code draw the scene OpenGL in the main window.
*
* \brief      Fonction DrawGLScene : Dessin sous OpenGL dans la fenêtre Windows.
* \details    Rien
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int DrawGLScene(GLvoid)										// Here's Where We Do All The Drawing
{
	char	*token;											// Storage For Our Token
	int		cnt=0;											// Local Counter Variable
	char* text=(char *)malloc(strlen((char *)glGetString(GL_EXTENSIONS))+1);	// Allocate Memory For Our Extension String

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer

	glColor3f(1.0f,0.5f,0.5f);								// Set Color To Bright Red
	glPrint(50,16,1,"Renderer");							// Display Renderer
	glPrint(80,48,1,"Vendor");								// Display Vendor Name
	glPrint(66,80,1,"Version");								// Display Version

	glColor3f(1.0f,0.7f,0.4f);								// Set Color To Orange
	glPrint(200,16,1,(char *)glGetString(GL_RENDERER));		// Display Renderer
	glPrint(200,48,1,(char *)glGetString(GL_VENDOR));		// Display Vendor Name
	glPrint(200,80,1,(char *)glGetString(GL_VERSION));		// Display Version

	glColor3f(0.5f,0.5f,1.0f);								// Set Color To Bright Blue
	glPrint(192,432,1,"NeHe Productions");					// Write NeHe Productions At The Bottom Of The Screen

	glLoadIdentity();										// Reset The ModelView Matrix
	glColor3f(1.0f,1.0f,1.0f);								// Set The Color To White
	glBegin(GL_LINE_STRIP);									// Start Drawing Line Strips (Something New)
		glVertex2d(639,417);								// Top Right Of Bottom Box
		glVertex2d(  0,417);								// Top Left Of Bottom Box
		glVertex2d(  0,480);								// Lower Left Of Bottom Box
		glVertex2d(639,480);								// Lower Right Of Bottom Box
		glVertex2d(639,128);								// Up To Bottom Right Of Top Box
	glEnd();												// Done First Line Strip
	glBegin(GL_LINE_STRIP);									// Start Drawing Another Line Strip
		glVertex2d(  0,128);								// Bottom Left Of Top Box
		glVertex2d(639,128);								// Bottom Right Of Top Box
		glVertex2d(639,  1);								// Top Right Of Top Box
		glVertex2d(  0,  1);								// Top Left Of Top Box
		glVertex2d(  0,417);								// Down To Top Left Of Bottom Box
	glEnd();												// Done Second Line Strip

	glScissor(1	,(int)(0.135416f*sheight),swidth-2,(int)(0.597916f*sheight));	// Define Scissor Region
	glEnable(GL_SCISSOR_TEST);								// Enable Scissor Testing

	strcpy (text,(char *)glGetString(GL_EXTENSIONS));		// Grab The Extension List, Store In Text

	token=strtok(text," ");									// Parse 'text' For Words, Seperated By " " (spaces)
	while(token!=NULL)										// While The Token Isn't NULL
	{
		cnt++;												// Increase The Counter
		if (cnt>maxtokens)									// Is 'maxtokens' Less Than 'cnt'
		{
			maxtokens=cnt;									// If So, Set 'maxtokens' Equal To 'cnt'
		}

		glColor3f(0.5f,1.0f,0.5f);							// Set Color To Bright Green
		glPrint(0,96+(cnt*32)-scroll,0,"%i",cnt);			// Print Current Extension Number
		glColor3f(1.0f,1.0f,0.5f);							// Set Color To Yellow
		glPrint(50,96+(cnt*32)-scroll,0,token);				// Print The Current Token (Parsed Extension Name)
		token=strtok(NULL," ");								// Search For The Next Token
	}

	glDisable(GL_SCISSOR_TEST);								// Disable Scissor Testing

	free(text);												// Free Allocated Memory

	glFlush();												// Flush The Rendering Pipeline
	return TRUE;											// Everything Went OK
}

/**	            This Code destroy all resources of this program.
*
* \brief      Fonction KillGLWindow : Destruction de toutes les ressources du programme.
* \details    Rien
* \param	  GLvoid			un void OpenGL.
* \return     GLvoid        	un void OpenGL.
*
*/

GLvoid KillGLWindow(GLvoid)									// Properly Kill The Window
{
	if (fullscreen)											// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);						// If So Switch Back To The Desktop
		ShowCursor(TRUE);									// Show Mouse Pointer
	}

	if (hRC)												// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))						// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))							// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;											// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))						// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;											// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))						// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;											// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))				// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;										// Set hInstance To NULL
	}

	KillFont();												// Kill The Font
}

/**	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *  \brief          Creation of our OpenGL Window
 *  \param 			title			- Title To Appear At The Top Of The Window				*
 *	\param 			width			- Width Of The GL Window Or Fullscreen Mode				*
 *	\param 			height			- Height Of The GL Window Or Fullscreen Mode			*
 *	\param          bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	\param          fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*
 *  \return         BOOL            - un entier booleen (OK ou non).
 */

BOOL CreateGLWindow(char* title, int width, int height, int bits, BOOL fullscreenflag)
{
	GLuint		PixelFormat;									// Holds The Results After Searching For A Match
	WNDCLASS	wc;												// Windows Class Structure
	DWORD		dwExStyle;										// Window Extended Style
	DWORD		dwStyle;										// Window Style
	RECT		WindowRect;										// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;									// Set Left Value To 0
	WindowRect.right=(long)width;								// Set Right Value To Requested Width
	WindowRect.top=(long)0;										// Set Top Value To 0
	WindowRect.bottom=(long)height;								// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;									// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;								// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else												// Otherwise
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else														// Otherwise
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,						// Extended Style For The Window
								"OpenGL",						// Class Name
								title,							// Window Title
								dwStyle |						// Defined Window Style
								WS_CLIPSIBLINGS |				// Required Window Style
								WS_CLIPCHILDREN,				// Required Window Style
								0, 0,							// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,							// No Parent Window
								NULL,							// No Menu
								hInstance,						// Instance
								NULL)))							// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

    pfd.cColorBits = bits;

    if (!(hDC=GetDC(hWnd)))                         // Did We Get A Device Context?
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))				// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))					// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))							// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))								// Try To Activate The Rendering Context
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);									// Show The Window
	SetForegroundWindow(hWnd);									// Slightly Higher Priority
	SetFocus(hWnd);												// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);								// Set Up Our Perspective GL Screen

	if (!InitGL())												// Initialize Our Newly Created GL Window
	{
		fullscreen=TRUE;
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	return TRUE;												// Success
}

/**         Comments manageable by Doxygen
*
* \brief      Fonction CALLBACK de traitement des messages Windows
* \details    Traitement de la boucle infinie des messages Windows
* \param      hWnd         L'header de la fenêtre principale.
* \param      uMsg         Un entier non signé.
* \param      wParam       Les paramétres en entrée.
* \param      lParam       Autres paramétres en entrée.
* \return     LRESULT 	   Un LRESULT donnant le status du traitement du message.
*
*/

LRESULT CALLBACK WndProc(	HWND	hWnd,						// Handle For This Window
							UINT	uMsg,						// Message For This Window
							WPARAM	wParam,						// Additional Message Information
							LPARAM	lParam)						// Additional Message Information
{
	switch (uMsg)												// Check For Windows Messages
	{
		case WM_ACTIVATE:										// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))								// Check Minimization State
			{
				active=TRUE;									// Program Is Active
			}
			else												// Otherwise
			{
				active=FALSE;									// Program Is No Longer Active
			}

			return 0;											// Return To The Message Loop
		}

		case WM_SYSCOMMAND:										// Intercept System Commands
		{
			switch (wParam)										// Check System Calls
			{
				case SC_SCREENSAVE:								// Screensaver Trying To Start?
				case SC_MONITORPOWER:							// Monitor Trying To Enter Powersave?
				return 0;										// Prevent From Happening
			}
			break;												// Exit
		}

		case WM_CLOSE:											// Did We Receive A Close Message?
		{
			PostQuitMessage(0);									// Send A Quit Message
			return 0;											// Jump Back
		}

		case WM_KEYDOWN:										// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;								// If So, Mark It As TRUE
			return 0;											// Jump Back
		}

		case WM_KEYUP:											// Has A Key Been Released?
		{
			keys[wParam] = FALSE;								// If So, Mark It As FALSE
			return 0;											// Jump Back
		}

		case WM_SIZE:											// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));		// LoWord=Width, HiWord=Height
			return 0;											// Jump Back
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);				// Pass All Unhandled Messages To DefWindowProc
}

/**	This Code is mandatory to create windows application (function WinMain)					*
 *  \brief          Creation of our application on Windows System (not console application) *
 *  \param 			hInstance		- Header de l'instance Windows				            *
 *	\param 			hPrevInstance	- Header de l'instance précédente de Windows 			*
 *	\param 			lpCmdLine		- Un pointeur sur la ligne de commande 			        *
 *	\param          nCmdShow		- Un indicateur d'état			                        *
 *  \return         int             - un entier booleen (OK ou non).                        *
 *	                                                                                        *
 */

int WINAPI WinMain(	HINSTANCE	hInstance,						// Instance
					HINSTANCE	hPrevInstance,					// Previous Instance
					LPSTR		lpCmdLine,						// Command Line Parameters
					int			nCmdShow)						// Window Show State
{
	MSG		msg;												// Windows Message Structure
	BOOL	done=FALSE;											// BOOL Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;										// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe's Token, Extensions, Scissoring & TGA Loading Tutorial",640,480,16,fullscreen))
	{
		return 0;												// Quit If Window Was Not Created
	}

	while(!done)												// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))				// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)							// Have We Received A Quit Message?
			{
				done=TRUE;										// If So done=TRUE
			}
			else												// If Not, Deal With Window Messages
			{
				DispatchMessage(&msg);							// Dispatch The Message
			}
		}
		else													// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;										// ESC or DrawGLScene Signalled A Quit
			}
			else												// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);								// Swap Buffers (Double Buffering)

				if (keys[VK_F1])								// Is F1 Being Pressed?
				{
					keys[VK_F1]=FALSE;							// If So Make Key FALSE
					KillGLWindow();								// Kill Our Current Window
					fullscreen=!fullscreen;						// Toggle Fullscreen / Windowed Mode
					// Recreate Our OpenGL Window
					if (!CreateGLWindow("NeHe's Token, Extensions, Scissoring & TGA Loading Tutorial",640,480,16,fullscreen))
					{
						return 0;								// Quit If Window Was Not Created
					}
				}

				if (keys[VK_UP] && (scroll>0))					// Is Up Arrow Being Pressed?
				{
					scroll-=2;									// If So, Decrease 'scroll' Moving Screen Down
				}

				if (keys[VK_DOWN] && (scroll<32*(maxtokens-9)))	// Is Down Arrow Being Pressed?
				{
					scroll+=2;									// If So, Increase 'scroll' Moving Screen Up
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();												// Kill The Window
	return (msg.wParam);										// Exit The Program
}
