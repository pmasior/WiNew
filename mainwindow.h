#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QGridLayout>
#include <QtWidgets>
#include <QtConcurrent/QtConcurrentRun>
//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    QAction *actionAbout;
    QAction *actionAdmin;
    QAction *actionLicense;
    QMenuBar *menuBar;
    QMenu *menuHelp;

    QWidget *centralWidget;
    QGridLayout *gridCentralWidget;
    QTabWidget *tabWidget;

    QWidget *tab0;
    QGridLayout *gridTab0;
    QScrollArea *scrollAreaTab0;
    QWidget *scrollAreaContentTab0;
    QGridLayout *gridScrollAreaContentTab0;
    enum { RowsTab0 = 14, ColumnsTab0 = 2, LinesTab0=3,
           rowOs = 0,
           rowOsVersion = 1,
           rowOsArchitecture = 2,
           rowLine1Tab0 = 3,
           rowCpu = 4,
           rowCpuArchitecture = 5,
           rowGpu = 6,
           rowRam = 7,
           rowLine2Tab0 = 8,
           rowInstallDate = 9,
           rowBootTime = 10,
           rowLine3Tab0 = 11,
           rowHotfixDate = 12,
           rowHotfix = 13};
    QLabel *labels1Tab0[RowsTab0];
    QLabel *labels2Tab0[RowsTab0];
    QFrame *linesTab0[LinesTab0];
    QSpacerItem *spacerTab0;

    QWidget *tab1;
    QGridLayout *gridTab1;
    QScrollArea *scrollAreaTab1;
    QWidget *scrollAreaContentTab1;
    QGridLayout *gridScrollAreaContentTab1;
    enum { RowsTab1 = 3, ColumnsTab1 = 3, LinesTab1=3,
           rowAdminTools = 0,
           rowTroubleshoot = 1,
           rowOptionalFeatures = 2};
    QLabel *labelsTab1[RowsTab1];
    QCommandLinkButton *linkTab1[RowsTab1];
    QPushButton *buttons1Tab1[RowsTab1];
//    QPushButton *buttons2Tab1[RowsTab1];
    QFrame *linesTab1[LinesTab1];
    QSpacerItem *spacerTab1;

    QWidget *tab2;
    QGridLayout *gridTab2;
    QScrollArea *scrollAreaTab2;
    QWidget *scrollAreaContentTab2;
    QGridLayout *gridScrollAreaContentTab2;
    enum { RowsTab2 = 10, ColumnsTab2 = 3, LinesTab2=3,
           rowUAC = 0,
           rowFirewall = 1,
           rowAutoPlay = 2,
           rowUpdateFrom = 3,
           rowLine1Tab2 = 4,
           rowWindowsSecurity = rowLine1Tab2+1,
           rowSystemRestore = rowLine1Tab2+2,
           rowInstalledUpdates = rowLine1Tab2+3,
           rowUserPasswords = rowLine1Tab2+4,
           rowUserPasswords2 = rowLine1Tab2+5};
    QLabel *labelsTab2[RowsTab2];
    QCommandLinkButton *linkTab2[RowsTab2];
    QPushButton *buttons1Tab2[RowsTab2];
//    QPushButton *buttons2Tab2[RowsTab2];
    QFrame *linesTab2[LinesTab2];
    QSpacerItem *spacerTab2;

    QWidget *tab3;
    QGridLayout *gridTab3;
    QScrollArea *scrollAreaTab3;
    QWidget *scrollAreaContentTab3;
    QGridLayout *gridScrollAreaContentTab3;
    enum { RowsTab3 = 7, ColumnsTab3 = 3, LinesTab3=3,
           rowFeedback = 0,
           rowAdId = 1,
           rowSuggestionTimeline = 2,
           rowLine1Tab3 = 3,
           rowPrivacyOptions = rowLine1Tab3+1,
           rowAppPermissions = rowLine1Tab3+2,
           rowSearchPrivacy = rowLine1Tab3+3};
    QLabel *labelsTab3[RowsTab3];
    QCommandLinkButton *linkTab3[RowsTab3];
    QPushButton *buttons1Tab3[RowsTab3];
    QFrame *linesTab3[LinesTab3];
    QSpacerItem *spacerTab3;

    QWidget *tab4;
    QGridLayout *gridTab4;
    QScrollArea *scrollAreaTab4;
    QWidget *scrollAreaContentTab4;
    QGridLayout *gridScrollAreaContentTab4;
    enum { RowsTab4 = 5, ColumnsTab4 = 3, LinesTab4=3,
           rowLine1Tab4 = 0,
           rowCleanMgr = rowLine1Tab4+1,
           rowDefaultApps = rowLine1Tab4+2,
           rowAutostart = rowLine1Tab4+3,
           rowInstalledApps = rowLine1Tab4+4};
    QLabel *labelsTab4[RowsTab4];
    QCommandLinkButton *linkTab4[RowsTab4];
    QPushButton *buttons1Tab4[RowsTab4];
    QFrame *linesTab4[LinesTab4];
    QSpacerItem *spacerTab4;

    QWidget *tab5;
    QGridLayout *gridTab5;
    QScrollArea *scrollAreaTab5;
    QWidget *scrollAreaContentTab5;
    QGridLayout *gridScrollAreaContentTab5;
    enum { RowsTab5 = 3, ColumnsTab5 = 3, LinesTab5=3,
           rowStartExplorer = 0,
           rowLine1Tab5 = 1,
           rowNotifications = rowLine1Tab5 + 1};
    QLabel *labelsTab5[RowsTab5];
    QCommandLinkButton *linkTab5[RowsTab5];
    QPushButton *buttons1Tab5[RowsTab5];
    QFrame *linesTab5[LinesTab5];
    QSpacerItem *spacerTab5;

    QWidget *tab6;
    QGridLayout *gridTab6;
    QScrollArea *scrollAreaTab6;
    QWidget *scrollAreaContentTab6;
    QGridLayout *gridScrollAreaContentTab6;
    enum { RowsTab6 = 2, ColumnsTab6 = 3, LinesTab6=3,
           row_6 = 0};
    QLabel *labelsTab6[RowsTab6];
    QCommandLinkButton *linkTab6[RowsTab6];
    QPushButton *buttons1Tab6[RowsTab6];
    QFrame *linesTab6[LinesTab6];
    QSpacerItem *spacerTab6;


    QPushButton *buttonTabWidget;

    QStatusBar *statusBar;
    QLabel *labelStatusBar;


private slots:
    // menu
    void menu_about();
    void menu_admin();
    void menu_license();

    // TabWidget connect
    void open_UAC();
    void set_UAC();
    void open_UpdateFrom();
    void set_UpdateFrom();
    void open_Feedback();
    void set_Feedback();
    void open_AdId();
    void set_AdId();
    void open_SuggestionTimeline();
    void set_SuggestionTimeline();
    void open_Firewall();
    void set_Firewall();
    void open_AutoPlay();
    void set_AutoPlay();
    void open_StartExplorer();
    void set_StartExplorer();

    void open_AdminTools();
    void open_Troubleshoot();
    void open_OptionalFeatures();
    void open_PrivacyOptions();
    void open_AppPermissions();
    void open_WindowsSecurity();
    void open_InstalledUpdates();
    void open_UserPasswords();
    void open_UserPasswords2();
    void open_SystemRestore();
    void open_SearchPrivacy();
    void open_DefaultApps();
    void open_Autostart();
    void open_InstalledApps();
    void open_CleanMgr();
    void open_Notifications();


private:
    // główne
    QString openCMD(const QString&);  //getCmdOutput
    void openGUI(const QString&);
    void start_admin();

    // TabWidget wątki
    QThreadPool *threadpool1;
    QThreadPool *threadpool2;

    // TabWidget
    void get_all();
    void get_aboutSystem();
    void get_UAC();
    void get_UpdateFrom();
    void get_Feedback();
    void get_AdId();
    void get_SuggestionTimeline();
    void get_Firewall();
    void get_AutoPlay();
    void get_StartExplorer();

//    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
