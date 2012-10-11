/**
  @file
  @author Stefan Frings
*/

#include "requestmapper.h"
#include "static.h"
#include "staticfilecontroller.h"
#include "controllers/dumpcontroller.h"
#include "controllers/templatecontroller.h"
#include "controllers/formcontroller.h"
#include "controllers/fileuploadcontroller.h"
#include "controllers/sessioncontroller.h"

#include "controllers/librariescontroller.h"
#include "controllers/foldercontroller.h"
#include "controllers/covercontroller.h"
#include "controllers/comiccontroller.h"
#include "controllers/folderinfocontroller.h"
#include "controllers/pagecontroller.h"
#include "controllers/errorcontroller.h"

#include "library_window.h"

extern LibraryWindow * mw;

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent) {}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
	QByteArray path=request.getPath();
	qDebug("RequestMapper: path=%s",path.data());

	QRegExp folder("/library/.+/folder/[0-9]+/?");//(?page=[0-9]+)?
	QRegExp folderInfo("/library/.+/folder/[0-9]+/info/?");
	QRegExp comic("/library/.+/comic/[0-9]+/?");
	QRegExp comicClose("/library/.+/comic/[0-9]+/close/?");
	QRegExp cover("/library/.+/cover/[0-9a-f]+.jpg");
	QRegExp comicPage("/library/.+/comic/[0-9]+/page/[0-9]+/?");

	QRegExp library("/library/([^/.]+)/.+");

	path = QUrl::fromPercentEncoding(path).toLatin1();

	//primera petici�n, se ha hecho un post, se sirven las bibliotecas si la seguridad mediante login no est� habilitada
	if(path == "/")
	{
		LibrariesController().service(request, response);
	}

	else 
	{
		//se comprueba que la sesi�n sea la correcta con el fin de evitar accesos no autorizados
		HttpSession session=Static::sessionStore->getSession(request,response);
		if(session.contains("ySession"))
		{
			if(library.indexIn(path)!=-1 && mw->getLibraries().contains(library.cap(1)) )
			{
				//listar el contenido del folder
				if(folder.exactMatch(path))
				{
					FolderController().service(request, response);
				}
				else if (folderInfo.exactMatch(path))
				{
					FolderInfoController().service(request, response);
				}
				else if(cover.exactMatch(path))
				{
					CoverController().service(request, response);
				}
				else if(comic.exactMatch(path))
				{
					ComicController().service(request, response);
				}
				else if(comicPage.exactMatch(path))
				{
					PageController().service(request,response);
				}
			}
			else
			{
				response.writeText(library.cap(1));
				Static::staticFileController->service(request, response);
			}
		}
		else //acceso no autorizado, redirecci�n
		{
			ErrorController(300).service(request,response);
		}
	}

}