#ifndef __MAIN_WINDOW_VIEWER_H
#define __MAIN_WINDOW_VIEWER_H
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>
#include <QAction>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QSettings>

class Comic;
class Viewer;
class OptionsDialog;
class HelpAboutDialog;
class HttpVersionChecker;
class ShortcutsDialog;


	class MainWindowViewer : public QMainWindow
	{
	Q_OBJECT

	public slots:
		void open();
		void openFolder();
		void saveImage();
		void toggleToolBars();
		void hideToolBars();
		void showToolBars();
		void changeFit();
		void enableActions();
		void disableActions();
		void toggleFullScreen();
		void toFullScreen();
		void toNormal();
		void loadConfiguration();
		void newVersion();
		void openPreviousComic();
		void openNextComic();
		void openComicFromPath(QString pathFile);
		void openFolderFromPath(QString pathDir);
		void alwaysOnTopSwitch();
		void adjustToFullSizeSwitch();
		void reloadOptions();
		/*void viewComic();
		void prev();
		void next();
		void updatePage();*/

	private:
		//!State
		bool fullscreen;
		bool toolbars;
		bool alwaysOnTop;
		
		QString currentDirectory;
		QString currentDirectoryImgDest;
		//!Widgets
		Viewer * viewer;
		//GoToDialog * goToDialog;
		OptionsDialog * optionsDialog;
		HelpAboutDialog * had;
		ShortcutsDialog * shortcutsDialog;

		//! ToolBars
		QToolBar *comicToolBar;

		//! Actions
		QAction *openAction;
		QAction *openFolderAction;
		QAction *saveImageAction;
		QAction *openPreviousComicAction;
		QAction *openNextComicAction;
		QAction *nextAction;
		QAction *prevAction;
		QAction *adjustWidth;
		QAction *adjustHeight;
		QAction *goToPage;
		QAction *optionsAction;
		QAction *helpAboutAction;
		QAction *showMagnifyingGlass;
		QAction *setBookmark;
		QAction *showBookmarks;
		QAction *leftRotationAction;
		QAction *rightRotationAction;
		QAction *showInfo;
		QAction *closeAction;
		QAction *doublePageAction;
		QAction *showShorcutsAction;
		QAction *showDictionaryAction;
		QAction *alwaysOnTopAction;
		QAction *adjustToFullSizeAction;

		HttpVersionChecker * versionChecker;
		QString previousComicPath;
		QString nextComicPath;
		//! M�todo que inicializa el interfaz.
		void setupUI();
		void createActions();
		void createToolBars();
		void getSiblingComics(QString path,QString currentComic);

		//! Manejadores de evento:
		void keyPressEvent(QKeyEvent *event);
		//void resizeEvent(QResizeEvent * event);
		void mouseDoubleClickEvent ( QMouseEvent * event );
		void dropEvent(QDropEvent *event);
		void dragEnterEvent(QDragEnterEvent *event);

		QSettings * settings;
		
	protected:
		virtual void closeEvent ( QCloseEvent * event );
	public:
		MainWindowViewer();

	};
#endif