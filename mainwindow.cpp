#include "mainwindow.h"
#include "ui_mainwindow.h"

void test(char s) {
    qInfo("test() %c", s);
}

QString MainWindow::openCMD(const QString &command)  //getCmdOutput
{
    QProcess *process = new QProcess();
    QString out_err;
    process->start("cmd /v /c " + command);
    process->waitForFinished();
    out_err = process->readAll();
    delete process;
//    QMessageBox::information(this, "CMD output", "*" + out + "*" + err + "*");
    return out_err;
}

void MainWindow::openGUI(const QString &command = "xed")
{
    QProcess *process = new QProcess(/*this*/);
    process->start(command);
    process->waitForStarted();
    if(process->state()!=QProcess::Running)
        QMessageBox::critical(this, "Błąd uruchomienia zewnętrznego komponentu", "Nie udało się uruchomić " + command);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
    this->resize(960, 600);
    this->setWindowTitle("WiNew");

    actionAbout = new QAction("&O Programie", this);
    actionLicense = new QAction("&Licencje", this);
    actionAdmin = new QAction("Sprawdż &uprawnienia");

    menuBar = new QMenuBar(this);
    menuHelp = new QMenu("&Pomoc", menuBar);
    this->setMenuBar(menuBar);

    menuBar->addMenu(menuHelp);
    menuHelp->addAction(actionAdmin);
    menuHelp->addAction(actionLicense);
    menuHelp->addAction(actionAbout);

    // centralWidget + ↓
    centralWidget = new QWidget(this);
    gridCentralWidget = new QGridLayout(centralWidget);
    // tabWidget + ↓
    tabWidget = new QTabWidget(centralWidget);
    tabWidget->setTabPosition(QTabWidget::North);
    buttonTabWidget = new QPushButton(tabWidget);
    buttonTabWidget->setText("Odśwież");
    buttonTabWidget->setIcon(QIcon(":/icons/icons/sync-alt-solid.svg"));
    buttonTabWidget->setIconSize(QSize(12, 12));
    buttonTabWidget->setObjectName("buttonTabWidget");
    tabWidget->setCornerWidget(buttonTabWidget);

    // tab0 + ↓
    tab0 = new QWidget();
    gridTab0 = new QGridLayout(tab0);
    // scrollAreaTab0 + ↓
    scrollAreaTab0 = new QScrollArea(tab0);
    scrollAreaTab0->setWidgetResizable(true);
    scrollAreaTab0->setFrameShape(QFrame::NoFrame);
    // scrollAreaContentTab0 + ↓
    scrollAreaContentTab0 = new QWidget();
    scrollAreaContentTab0->setObjectName("scrollAreaContentTab0");
    gridScrollAreaContentTab0 = new QGridLayout(scrollAreaContentTab0);
        for(int i=0, l=0; i<RowsTab0; i++)
        {
            if(i==rowLine1Tab0 || i==rowLine2Tab0 || i==rowLine3Tab0)
            {
                linesTab0[l] = new QFrame(scrollAreaTab0);
                linesTab0[l]->setFrameShape(QFrame::HLine);
                linesTab0[l]->setFrameShadow(QFrame::Sunken);
                gridScrollAreaContentTab0->addWidget(linesTab0[l], i, 0, 1, 2);
                l++;
                continue;
            }
            labels1Tab0[i] = new QLabel(scrollAreaContentTab0);
            labels2Tab0[i] = new QLabel(scrollAreaContentTab0);
            labels1Tab0[i]->setAlignment(Qt::AlignTop);
            labels2Tab0[i]->setAlignment(Qt::AlignTop);
            gridScrollAreaContentTab0->addWidget(labels1Tab0[i], i, 0);
            gridScrollAreaContentTab0->addWidget(labels2Tab0[i], i, 1);
        }
//        labelTab0 = new QLabel(scrollAreaContentTab0);
//        gridScrollAreaContentTab0->addWidget(labelTab0);
        threadpool1 = new QThreadPool(this);
        QtConcurrent::run(threadpool1, this, &MainWindow::get_aboutSystem);
        spacerTab0 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        gridScrollAreaContentTab0->addItem(spacerTab0, RowsTab0+1, 0);
    scrollAreaTab0->setWidget(scrollAreaContentTab0);  //↓ scrollAreaContentTab0
    gridTab0->addWidget(scrollAreaTab0);  //↓ scrollAreaTab0
    tabWidget->addTab(tab0, "&O systemie");  //↓ tab0

    // tab1
    tab1 = new QWidget();
    gridTab1 = new QGridLayout(tab1);
    // scrollAreaTab1 + ↓
    scrollAreaTab1 = new QScrollArea(tab1);
    scrollAreaTab1->setWidgetResizable(true);
    scrollAreaTab1->setFrameShape(QFrame::NoFrame);
    // scrollAreaContentTab1 + ↓
    scrollAreaContentTab1 = new QWidget();
    scrollAreaContentTab1->setObjectName("scrollAreaContentTab1");
    gridScrollAreaContentTab1 = new QGridLayout(scrollAreaContentTab1);
        for(int i=0; i<RowsTab1; i++)
        {
            linkTab1[i] = new QCommandLinkButton(scrollAreaContentTab1);
//            buttons1Tab1[i] = new QPushButton(scrollAreaContentTab1);
            gridScrollAreaContentTab1->addWidget(linkTab1[i], i, 0);
//            gridScrollAreaContentTab1->addWidget(buttons1Tab1[i], i, 2);
        }
        linkTab1[rowAdminTools]->setText("Narzędzia administracyjne");
        linkTab1[rowAdminTools]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab1[rowTroubleshoot]->setText("Rozwiązywanie problemów");
        linkTab1[rowTroubleshoot]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab1[rowOptionalFeatures]->setText("Włącz lub wyłącz funkcje systemu Windows");
        linkTab1[rowOptionalFeatures]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
//        linkTab1[rowFeedback]->setText("Dane diagnostyczne");
//        linkTab1[rowAdId]->setText("Używanie identyfikatora reklamowego");
        spacerTab1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        gridScrollAreaContentTab1->addItem(spacerTab1, RowsTab1+1, 0);
    scrollAreaTab1->setWidget(scrollAreaContentTab1);  //↓ scrollAreaContentTab1
    gridTab1->addWidget(scrollAreaTab1);  //↓ scrollAreaTab1
    tabWidget->addTab(tab1, "&Narzędzia");


    // tab2 + ↓
    tab2 = new QWidget();
    gridTab2 = new QGridLayout(tab2);
    // scrollAreaTab2 + ↓
    scrollAreaTab2 = new QScrollArea(tab2);
    scrollAreaTab2->setWidgetResizable(true);
    scrollAreaTab2->setFrameShape(QFrame::NoFrame);
    // scrollAreaContentTab2 + ↓
    scrollAreaContentTab2 = new QWidget();
    scrollAreaContentTab2->setObjectName("scrollAreaContentTab2");
    gridScrollAreaContentTab2 = new QGridLayout(scrollAreaContentTab2);
        for(int i=0, l=0; i<RowsTab2; i++)
        {
            if(i==rowLine1Tab2)
            {
                linesTab2[l] = new QFrame(scrollAreaTab2);
                linesTab2[l]->setFrameShape(QFrame::HLine);
                linesTab2[l]->setFrameShadow(QFrame::Sunken);
                gridScrollAreaContentTab2->addWidget(linesTab2[l], i, 0, 1, 2);
                l++;
                continue;
            }
            linkTab2[i] = new QCommandLinkButton(scrollAreaContentTab2);
            if (i<rowLine1Tab2)
                buttons1Tab2[i] = new QPushButton(scrollAreaContentTab2);
            gridScrollAreaContentTab2->addWidget(linkTab2[i], i, 0);
            if (i<rowLine1Tab2)
                gridScrollAreaContentTab2->addWidget(buttons1Tab2[i], i, 1);
        }
//        labelsTab2[rowUAC]->setText("UAC");
        linkTab2[rowUAC]->setText("Kontrola konta użytkownika (UAC)");
        linkTab2[rowFirewall]->setText("Zapora Windows Defender");
        linkTab2[rowAutoPlay]->setText("Autoodtwarzanie");
        linkTab2[rowUpdateFrom]->setText("Pobieranie aktualizacji z innych komputerów");
        linkTab2[rowWindowsSecurity]->setText("Zabezpieczenia Windows");
        linkTab2[rowWindowsSecurity]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab2[rowSystemRestore]->setText("Przywracanie systemu");
        linkTab2[rowSystemRestore]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab2[rowInstalledUpdates]->setText("Historia aktualizacji");
        linkTab2[rowInstalledUpdates]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab2[rowUserPasswords]->setText("Konta użytkowników (Panel Sterowania)");
        linkTab2[rowUserPasswords]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab2[rowUserPasswords2]->setText("Konta użytkowników (zaawansowane)");
        linkTab2[rowUserPasswords2]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        spacerTab2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        gridScrollAreaContentTab2->addItem(spacerTab2, RowsTab2+1, 0);
    scrollAreaTab2->setWidget(scrollAreaContentTab2);  //↓ scrollAreaContentTab2
    gridTab2->addWidget(scrollAreaTab2);  //↓ scrollAreaTab2
    tabWidget->addTab(tab2, "&Zabezpieczenia");  //↓ tab2


    // tab3 + ↓
    tab3 = new QWidget();
    gridTab3 = new QGridLayout(tab3);
    // scrollAreaTab3 + ↓
    scrollAreaTab3 = new QScrollArea(tab3);
    scrollAreaTab3->setWidgetResizable(true);
    scrollAreaTab3->setFrameShape(QFrame::NoFrame);
    // scrollAreaContentTab3 + ↓
    scrollAreaContentTab3 = new QWidget();
    scrollAreaContentTab3->setObjectName("scrollAreaContentTab3");
    gridScrollAreaContentTab3 = new QGridLayout(scrollAreaContentTab3);
        for(int i=0, l=0; i<RowsTab3; i++)
        {
            if(i==rowLine1Tab3)
            {
                linesTab3[l] = new QFrame(scrollAreaTab3);
                linesTab3[l]->setFrameShape(QFrame::HLine);
                linesTab3[l]->setFrameShadow(QFrame::Sunken);
                gridScrollAreaContentTab3->addWidget(linesTab3[l], i, 0, 1, 2);
                l++;
                continue;
            }
            linkTab3[i] = new QCommandLinkButton(scrollAreaContentTab3);
            if (i<rowLine1Tab3)
                buttons1Tab3[i] = new QPushButton(scrollAreaContentTab3);
            gridScrollAreaContentTab3->addWidget(linkTab3[i], i, 0);
            if (i<rowLine1Tab3)
                gridScrollAreaContentTab3->addWidget(buttons1Tab3[i], i, 1);
        }
        linkTab3[rowFeedback]->setText("Dane diagnostyczne");
        linkTab3[rowAdId]->setText("Używanie identyfikatora reklamowego");
        linkTab3[rowSuggestionTimeline]->setText("Sugestie na osi czasu");

        linkTab3[rowPrivacyOptions]->setText("Opcje prywatności");
        linkTab3[rowPrivacyOptions]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab3[rowAppPermissions]->setText("Uprawnienia aplikacji");
        linkTab3[rowAppPermissions]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab3[rowSearchPrivacy]->setText("Wyszukiwanie");
        linkTab3[rowSearchPrivacy]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        spacerTab3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        gridScrollAreaContentTab3->addItem(spacerTab3, RowsTab3+1, 0);
    scrollAreaTab3->setWidget(scrollAreaContentTab3);  //↓ scrollAreaContentTab3
    gridTab3->addWidget(scrollAreaTab3);  //↓ scrollAreaTab3
    tabWidget->addTab(tab3, "&Prywatność");


    // tab4
    tab4 = new QWidget();
    gridTab4 = new QGridLayout(tab4);
    // scrollAreaTab4 + ↓
    scrollAreaTab4 = new QScrollArea(tab4);
    scrollAreaTab4->setWidgetResizable(true);
    scrollAreaTab4->setFrameShape(QFrame::NoFrame);
    // scrollAreaContentTab4 + ↓
    scrollAreaContentTab4 = new QWidget();
    scrollAreaContentTab4->setObjectName("scrollAreaContentTab4");
    gridScrollAreaContentTab4 = new QGridLayout(scrollAreaContentTab4);
        for(int i=0, l=0; i<RowsTab4; i++)
        {
            if(i==rowLine1Tab4)
            {
                linesTab4[l] = new QFrame(scrollAreaTab4);
                linesTab4[l]->setFrameShape(QFrame::HLine);
                linesTab4[l]->setFrameShadow(QFrame::Sunken);
                gridScrollAreaContentTab4->addWidget(linesTab4[l], i, 0, 1, 2);
                l++;
                continue;
            }
            linkTab4[i] = new QCommandLinkButton(scrollAreaContentTab4);
            if (i<rowLine1Tab4)
                buttons1Tab4[i] = new QPushButton(scrollAreaContentTab4);
            gridScrollAreaContentTab4->addWidget(linkTab4[i], i, 0);
            if (i<rowLine1Tab4)
                gridScrollAreaContentTab4->addWidget(buttons1Tab4[i], i, 1);
        }
        linkTab4[rowDefaultApps]->setText("Aplikacje domyślne");
        linkTab4[rowDefaultApps]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab4[rowAutostart]->setText("Autostart");
        linkTab4[rowAutostart]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab4[rowInstalledApps]->setText("Zainstalowane aplikacje");
        linkTab4[rowInstalledApps]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        linkTab4[rowCleanMgr]->setText("Oczyszczanie dysku");
        linkTab4[rowCleanMgr]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
        spacerTab4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        gridScrollAreaContentTab4->addItem(spacerTab4, RowsTab4+1, 0);
    scrollAreaTab4->setWidget(scrollAreaContentTab4);  //↓ scrollAreaContentTab4
    gridTab4->addWidget(scrollAreaTab4);  //↓ scrollAreaTab4
    tabWidget->addTab(tab4, "&Optymalizacja");


    // tab5
    tab5 = new QWidget();
    gridTab5 = new QGridLayout(tab5);
    // scrollAreaTab5 + ↓
    scrollAreaTab5 = new QScrollArea(tab5);
    scrollAreaTab5->setWidgetResizable(true);
    scrollAreaTab5->setFrameShape(QFrame::NoFrame);
    // scrollAreaContentTab5 + ↓
    scrollAreaContentTab5 = new QWidget();
    scrollAreaContentTab5->setObjectName("scrollAreaContentTab5");
    gridScrollAreaContentTab5 = new QGridLayout(scrollAreaContentTab5);
        for(int i=0, l=0; i<RowsTab5; i++)
        {
            if(i==rowLine1Tab5)
            {
                linesTab5[l] = new QFrame(scrollAreaTab5);
                linesTab5[l]->setFrameShape(QFrame::HLine);
                linesTab5[l]->setFrameShadow(QFrame::Sunken);
                gridScrollAreaContentTab5->addWidget(linesTab5[l], i, 0, 1, 2);
                l++;
                continue;
            }
            linkTab5[i] = new QCommandLinkButton(scrollAreaContentTab5);
            if (i<rowLine1Tab5)
                buttons1Tab5[i] = new QPushButton(scrollAreaContentTab5);
            gridScrollAreaContentTab5->addWidget(linkTab5[i], i, 0);
            if (i<rowLine1Tab5)
                gridScrollAreaContentTab5->addWidget(buttons1Tab5[i], i, 1);
        }
        linkTab5[rowStartExplorer]->setText("Domyślna strona eksploratora plików");
        linkTab5[rowNotifications]->setText("Powiadomienia");
        linkTab5[rowNotifications]->setIcon(QIcon(":/icons/icons/external-link-square-alt-solid.svg"));
//        linkTab5[rowFeedback]->setText("Dane diagnostyczne");
//        linkTab5[rowAdId]->setText("Używanie identyfikatora reklamowego");
        spacerTab5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        gridScrollAreaContentTab5->addItem(spacerTab5, RowsTab5+1, 0);
    scrollAreaTab5->setWidget(scrollAreaContentTab5);  //↓ scrollAreaContentTab5
    gridTab5->addWidget(scrollAreaTab5);  //↓ scrollAreaTab5
    tabWidget->addTab(tab5, "&Personalizacja");


    // tab6
    tab6 = new QWidget();
    gridTab6 = new QGridLayout(tab6);
    // scrollAreaTab6 + ↓
    scrollAreaTab6 = new QScrollArea(tab6);
    scrollAreaTab6->setWidgetResizable(true);
    scrollAreaTab6->setFrameShape(QFrame::NoFrame);
    // scrollAreaContentTab6 + ↓
    scrollAreaContentTab6 = new QWidget();
    scrollAreaContentTab6->setObjectName("scrollAreaContentTab6");
    gridScrollAreaContentTab6 = new QGridLayout(scrollAreaContentTab6);
        for(int i=0; i<RowsTab6; i++)
        {
            linkTab6[i] = new QCommandLinkButton(scrollAreaContentTab6);
            buttons1Tab6[i] = new QPushButton(scrollAreaContentTab6);
            gridScrollAreaContentTab6->addWidget(linkTab6[i], i, 0);
            gridScrollAreaContentTab6->addWidget(buttons1Tab6[i], i, 2);
        }
        linkTab6[rowUAC]->setText("Kontrola konta użytkownika (UAC)");
//        linkTab6[rowFeedback]->setText("Dane diagnostyczne");
//        linkTab6[rowAdId]->setText("Używanie identyfikatora reklamowego");
        spacerTab6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        gridScrollAreaContentTab6->addItem(spacerTab6, RowsTab6+1, 0);
    scrollAreaTab6->setWidget(scrollAreaContentTab6);  //↓ scrollAreaContentTab6
    gridTab6->addWidget(scrollAreaTab6);  //↓ scrollAreaTab6
    tabWidget->addTab(tab6, "&Pobieranie");

    gridCentralWidget->addWidget(tabWidget);  //↓ tabWidget
    this->setCentralWidget(centralWidget);  //↓ centralWidget

    // statusBar
    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
    labelStatusBar = new QLabel(statusBar);
    statusBar->addWidget(labelStatusBar);

    // stylesheet
    this->setStyleSheet("#scrollAreaContentTab0, #scrollAreaContentTab1, #scrollAreaContentTab2, #scrollAreaContentTab3, #scrollAreaContentTab4, #scrollAreaContentTab5, #scrollAreaContentTab6"
                        "    {background-color: rgba(255, 255, 255, 255);}"
//                        "QPushButton {background-color: #adadad; color: #111111; border: 1px solid #e1e1e1; border-radius: 0px; padding: 5px;}"
//                        "QPushButton:hover, QPushButton:focus {background-color: #e5f1fb; border-color: #0078d7;}"
                        "QCommandLinkButton {font-weight: 600; padding: 0px; border-color: white;}"
//                        "#buttonTabWidget {border: #111111;}"
                        );

    // functions
//    threadpool2 = new QThreadPool(this);
//    QtConcurrent::run(threadpool2, this, &MainWindow::startAdmin);
    start_admin();
    get_all();

    // connect
    connect(actionAbout, &QAction::triggered, this, &MainWindow::menu_about);
    connect(actionLicense, &QAction::triggered, this, &MainWindow::menu_license);
    connect(actionAdmin, &QAction::triggered, this, &MainWindow::menu_admin);
    connect(buttonTabWidget, &QPushButton::clicked, this, &MainWindow::get_all);

    connect(linkTab2[rowUAC], &QCommandLinkButton::clicked, this, &MainWindow::open_UAC);
    connect(buttons1Tab2[rowUAC], &QPushButton::clicked, this, &MainWindow::set_UAC);
    connect(linkTab2[rowUpdateFrom], &QCommandLinkButton::clicked, this, &MainWindow::open_UpdateFrom);
    connect(buttons1Tab2[rowUpdateFrom], &QPushButton::clicked, this, &MainWindow::set_UpdateFrom);


    connect(linkTab3[rowFeedback], &QCommandLinkButton::clicked, this, &MainWindow::open_Feedback);
    connect(buttons1Tab3[rowFeedback], &QPushButton::clicked, this, &MainWindow::set_Feedback);
    connect(linkTab2[rowFirewall], &QCommandLinkButton::clicked, this, &MainWindow::open_Firewall);
    connect(buttons1Tab2[rowFirewall], &QPushButton::clicked, this, &MainWindow::set_Firewall);
    connect(linkTab2[rowAutoPlay], &QCommandLinkButton::clicked, this, &MainWindow::open_AutoPlay);
    connect(buttons1Tab2[rowAutoPlay], &QPushButton::clicked, this, &MainWindow::set_AutoPlay);
    connect(linkTab3[rowAdId], &QCommandLinkButton::clicked, this, &MainWindow::open_AdId);
    connect(buttons1Tab3[rowAdId], &QPushButton::clicked, this, &MainWindow::set_AdId);
    connect(linkTab3[rowSuggestionTimeline], &QCommandLinkButton::clicked, this, &MainWindow::open_SuggestionTimeline);
    connect(buttons1Tab3[rowSuggestionTimeline], &QPushButton::clicked, this, &MainWindow::set_SuggestionTimeline);
    connect(linkTab5[rowStartExplorer], &QCommandLinkButton::clicked, this, &MainWindow::open_StartExplorer);
    connect(buttons1Tab5[rowStartExplorer], &QPushButton::clicked, this, &MainWindow::set_StartExplorer);

    connect(linkTab1[rowAdminTools], &QCommandLinkButton::clicked, this, &MainWindow::open_AdminTools);
    connect(linkTab1[rowTroubleshoot], &QCommandLinkButton::clicked, this, &MainWindow::open_Troubleshoot);
    connect(linkTab1[rowOptionalFeatures], &QCommandLinkButton::clicked, this, &MainWindow::open_OptionalFeatures);
    connect(linkTab3[rowPrivacyOptions], &QCommandLinkButton::clicked, this, &MainWindow::open_PrivacyOptions);
    connect(linkTab3[rowAppPermissions], &QCommandLinkButton::clicked, this, &MainWindow::open_AppPermissions);
    connect(linkTab3[rowSearchPrivacy], &QCommandLinkButton::clicked, this, &MainWindow::open_SearchPrivacy);
    connect(linkTab2[rowWindowsSecurity], &QCommandLinkButton::clicked, this, &MainWindow::open_WindowsSecurity);
    connect(linkTab2[rowSystemRestore], &QCommandLinkButton::clicked, this, &MainWindow::open_SystemRestore);
    connect(linkTab2[rowInstalledUpdates], &QCommandLinkButton::clicked, this, &MainWindow::open_InstalledUpdates);
    connect(linkTab2[rowUserPasswords], &QCommandLinkButton::clicked, this, &MainWindow::open_UserPasswords);
    connect(linkTab2[rowUserPasswords2], &QCommandLinkButton::clicked, this, &MainWindow::open_UserPasswords2);
    connect(linkTab4[rowDefaultApps], &QCommandLinkButton::clicked, this, &MainWindow::open_DefaultApps);
    connect(linkTab4[rowAutostart], &QCommandLinkButton::clicked, this, &MainWindow::open_Autostart);
    connect(linkTab4[rowInstalledApps], &QCommandLinkButton::clicked, this, &MainWindow::open_InstalledApps);
    connect(linkTab4[rowCleanMgr], &QCommandLinkButton::clicked, this, &MainWindow::open_CleanMgr);
    connect(linkTab5[rowNotifications], &QCommandLinkButton::clicked, this, &MainWindow::open_Notifications);

}

MainWindow::~MainWindow()
{
//    delete ui;
    delete threadpool1;
//    delete threadpool2;
//    for(int i=0; i<RowsTab1; i++)
//    {
//        delete labelsTab1[i];
//        delete buttons1Tab1[i];
//        delete buttons2Tab1[i];
//    }
//    delete statusBar;
//    delete tab2;
//    delete tab1;
//    delete tabWidget;
//    delete menuHelp;
//    delete menuBar;
//    delete centralWidget;
//    delete actionLicense;
//    delete actionAbout;
}


void MainWindow::menu_about()
{
    QMessageBox::about(this, "About WiNew", "WiNew <b>0.00</b> (8.02.2020)<br>Paweł Mąsior");
}
void MainWindow::menu_license()
{
    QMessageBox::information(this, "License WiNew", "...");
}
void MainWindow::menu_admin()
{
//    int result1 = openCMD("whoami /groups | findstr \"S-1-16-12288\"").indexOf("S-1-16-12288");
    QString result2 = openCMD("net session & ECHO ERRORLEVEL=!ERRORLEVEL!");
//    if(result1!=-1)
    if(result2.indexOf("ERRORLEVEL=0")!=-1)
        QMessageBox::information(this, "Sprawdzanie uprawnień", "Program został uruchomiony z prawami administratora");
//    else if(result1==-1)
    else if(result2.indexOf("ERRORLEVEL=2")!=-1)
    {
        if (QMessageBox::warning(this, "Sprawdzanie uprawnień", "Program NIE został uruchomiony z prawami administratora", QMessageBox::Cancel | QMessageBox::Ok)
                == QMessageBox::Cancel)
            exit(5);
    }
    else
        QMessageBox::critical(this, "Sprawdzanie uprawnień", "Nie można sprawdzić czy program został uruchomiony z prawami administratora");
}
void MainWindow::start_admin()
{
//    int result1 = openCMD("(whoami /groups | findstr \"S-1-16-12288\")").indexOf("S-1-16-12288");
    QString result2 = openCMD("net session & ECHO ERRORLEVEL=!ERRORLEVEL!");
//    if(result1!=-1)
    if(result2.indexOf("ERRORLEVEL=0")!=-1)
        labelStatusBar->setText("Administrator");
//    else if(result1==-1)
    else if(result2.indexOf("ERRORLEVEL=2")!=-1)
    {
        labelStatusBar->setText("Użytkownik standardowy");
        if (QMessageBox::warning(this, "Sprawdzanie uprawnień", "Program NIE został uruchomiony z prawami administratora", QMessageBox::Cancel | QMessageBox::Ok)
                == QMessageBox::Cancel)
            exit(5);
    } else {
        labelStatusBar->setText("Nieznane uprawnienia");
        QMessageBox::critical(this, "Sprawdzanie uprawnień", "Nie można sprawdzić czy program został uruchomiony z prawami administratora");
    }
}
void MainWindow::get_all()
{
    get_UAC();
    get_Feedback();
    get_AdId();
    get_UpdateFrom();
    get_SuggestionTimeline();
    get_Firewall();
    get_AutoPlay();
    get_StartExplorer();
}


void MainWindow::get_aboutSystem()
{
    QString temp;
    labels1Tab0[rowOs]->setText("Nazwa systemu");
    labels2Tab0[rowOs]->setText(openCMD("powershell -Command \"(gcim Win32_OperatingSystem)| Select -Expand Caption\"").remove("\r\n")
                                + " " + openCMD("@FOR /F \"skip=1 tokens=3\" %G IN ('REG QUERY \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\" /v ReleaseId') DO @(echo %G)").remove("\r\n"));
    labels1Tab0[rowOsVersion]->setText("Wersja systemu");
    labels2Tab0[rowOsVersion]->setText(openCMD("ver").remove(QRegExp("[^0-9.]")));
    labels1Tab0[rowOsArchitecture]->setText("Architektura systemu");
    labels2Tab0[rowOsArchitecture]->setText(openCMD("powershell -Command \"(gcim Win32_OperatingSystem).OSArchitecture\"").remove("\r\n"));

    labels1Tab0[rowCpu]->setText("Model procesora");
    labels2Tab0[rowCpu]->setText(openCMD("powershell -Command \"(gcim Win32_Processor).Name\"").remove("\r\n"));
    labels1Tab0[rowCpuArchitecture]->setText("Architektura procesora");
    labels2Tab0[rowCpuArchitecture]->setText(openCMD("echo %PROCESSOR_ARCHITECTURE%").remove("\r\n"));
    labels1Tab0[rowGpu]->setText("Model karty graficznej");
    labels2Tab0[rowGpu]->setText(openCMD("powershell -Command \"(gcim Win32_VideoController).Name\"").remove("\r\n"));

    labels1Tab0[rowRam]->setText("Rozmiar pamięci RAM");
    QString Ram = openCMD("powershell -Command \"(gcim Win32_ComputerSystem).TotalPhysicalMemory\"").remove(QRegExp("[^0-9]"));
    double Ram2 = Ram.toDouble()/1024/1024/1024;
    labels2Tab0[rowRam]->setText(QString::number(Ram2) + " GB");

    labels1Tab0[rowInstallDate]->setText("Data instalacji");
    labels2Tab0[rowInstallDate]->setText(openCMD("powershell -Command \"chcp 65001; ECHO chcp; (gcim Win32_OperatingSystem).InstallDate\"")
                                         .remove(QRegExp(".*chcp")).remove("\r\n"));
    labels1Tab0[rowBootTime]->setText("Data ostatniego uruchomienia");
    labels2Tab0[rowBootTime]->setText(openCMD("powershell -Command \"chcp 65001; ECHO chcp; (gcim Win32_OperatingSystem).LastBootUpTime\"")
                                      .remove(QRegExp(".*chcp")).remove("\r\n"));

    labels1Tab0[rowHotfixDate]->setText("Data ostatniej aktualizacji");
    labels2Tab0[rowHotfixDate]->setText(openCMD("powershell -Command \"(gcim Win32_QuickFixEngineering) | Sort InstalledOn -Desc | Select -ExpandProperty InstalledOn -First 1\"").remove("\r\n").remove(QRegExp("\\d\\d:\\d\\d:\\d\\d")));
    labels1Tab0[rowHotfix]->setText("Lista zainstalowanych aktualizacji");
    labels2Tab0[rowHotfix]->setText(openCMD("powershell -Command \"(Get-Hotfix).HotFixID\""));
}

void MainWindow::get_UAC()
{
    QString result1 = openCMD("@FOR /F \"skip=1 tokens=3\" %G IN ('REG QUERY HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v EnableLUA') DO @(echo %G)");
    QString result2 = openCMD("@FOR /F \"skip=1 tokens=3\" %G IN ('REG QUERY HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v ConsentPromptBehaviorAdmin') DO @(echo %G)");
    QString result3 = openCMD("@FOR /F \"skip=1 tokens=3\" %G IN ('REG QUERY HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v EnableLUA') DO @(echo %G)");

    if(result1=="0x1\r\n" && result2=="0x2\r\n" && result3=="0x1\r\n") {
        buttons1Tab2[rowUAC]->setText("Aktywne (Zawsze)");
        linkTab2[rowUAC]->setIcon(QIcon(":/icons/icons/check-square-solid.svg"));
    } else if (result1=="0x1\r\n" && result2=="0x5\r\n" && result3=="0x1\r\n") {
        buttons1Tab2[rowUAC]->setText("Aktywne (Tylko aplikacje)");
        linkTab2[rowUAC]->setIcon(QIcon(":/icons/icons/minus-square-solid.svg"));
    } else if (result1=="0x\r\n1" && result2=="0x5\r\n" && result3=="0x0\r\n") {
        buttons1Tab2[rowUAC]->setText("Aktywne (Tylko aplikacje)");
        linkTab2[rowUAC]->setIcon(QIcon(":/icons/icons/minus-square-solid.svg"));
    } else if (result1=="0x1\r\n" && result2=="0x0\r\n" && result3=="0x0\r\n") {
        buttons1Tab2[rowUAC]->setText("Nieaktywne");
        linkTab2[rowUAC]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    } else {
        buttons1Tab2[rowUAC]->setEnabled(false);
        buttons1Tab2[rowUAC]->setText("Nieznany");
        linkTab2[rowUAC]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    }
}
void MainWindow::set_UAC()
{
    if(buttons1Tab2[rowUAC]->text()=="Aktywne (Zawsze)")
    {
        openCMD("REG ADD HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /t REG_DWORD /v EnableLUA /f /d 0x1");
        openCMD("REG ADD HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /t REG_DWORD /v ConsentPromptBehaviorAdmin /f /d 0x5");
        openCMD("REG ADD HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /t REG_DWORD /v EnableLUA /f /d 0x1");
    } else if(buttons1Tab2[rowUAC]->text()=="Aktywne (Tylko aplikacje)" || buttons1Tab2[rowUAC]->text()=="Nieaktywne")
    {
        openCMD("REG ADD HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /t REG_DWORD /v EnableLUA /f /d 0x1");
        openCMD("REG ADD HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /t REG_DWORD /v ConsentPromptBehaviorAdmin /f /d 0x2");
        openCMD("REG ADD HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /t REG_DWORD /v EnableLUA /f /d 0x1");
    }
    get_UAC();
}
void MainWindow::open_UAC()
{
    openGUI("UserAccountControlSettings.exe");
    get_UAC();
}

void MainWindow::get_UpdateFrom()
{
    QString result1 = openCMD("@FOR /F \"skip=1 tokens=3\" %G IN ('REG QUERY HKU\\S-1-5-20\\Software\\Microsoft\\Windows\\CurrentVersion\\DeliveryOptimization\\Settings /v DownloadMode') DO @(echo %G)");

    if(result1=="0x0\r\n") {
        buttons1Tab2[rowUpdateFrom]->setText("Nie zezwalaj");
        linkTab2[rowUpdateFrom]->setIcon(QIcon(":/icons/icons/check-square-solid.svg"));
    } else if (result1=="0x1\r\n") {
        buttons1Tab2[rowUpdateFrom]->setText("Zezwalaj w sieci lokalnej");
        linkTab2[rowUpdateFrom]->setIcon(QIcon(":/icons/icons/minus-square-solid.svg"));
    }else if (result1=="0x3\r\n") {
        buttons1Tab2[rowUpdateFrom]->setText("Zezwalaj w sieci lokalnej i Internecie");
        linkTab2[rowUpdateFrom]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    } else {
        buttons1Tab2[rowUpdateFrom]->setEnabled(false);
        buttons1Tab2[rowUpdateFrom]->setText("Nieznany (Wymaga administratora)");
        linkTab2[rowUpdateFrom]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    }
}
void MainWindow::set_UpdateFrom()
{
    if(buttons1Tab2[rowUpdateFrom]->text()=="Nie zezwalaj")
    {
        openCMD("REG ADD HKU\\S-1-5-20\\Software\\Microsoft\\Windows\\CurrentVersion\\DeliveryOptimization\\Settings /t REG_DWORD /v DownloadMode /f /d 0x1");
    } else if(buttons1Tab2[rowUpdateFrom]->text()=="Zezwalaj w sieci lokalnej" || buttons1Tab2[rowUpdateFrom]->text()=="Zezwalaj w sieci lokalnej i Internecie")
    {
        openCMD("REG ADD HKU\\S-1-5-20\\Software\\Microsoft\\Windows\\CurrentVersion\\DeliveryOptimization\\Settings /t REG_DWORD /v DownloadMode /f /d 0x0");
    }
    get_UpdateFrom();
}
void MainWindow::open_UpdateFrom()
{
    openCMD("start ms-settings:delivery-optimization");
    get_UpdateFrom();
}


void MainWindow::get_Feedback()
{
    QString result1 = openCMD("@FOR /F \"skip=1 tokens=3\" %G IN ('REG QUERY HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\DataCollection /v AllowTelemetry') DO @(echo %G)");

    if(result1=="0x0\r\n") {
        buttons1Tab3[rowFeedback]->setText("Wyłączone");
        linkTab3[rowFeedback]->setIcon(QIcon(":/icons/icons/check-square-solid.svg"));
    } else if (result1=="0x1\r\n") {
        buttons1Tab3[rowFeedback]->setText("Podstawowe");
        linkTab3[rowFeedback]->setIcon(QIcon(":/icons/icons/minus-square-solid.svg"));
    } else if (result1=="0x3\r\n") {
        buttons1Tab3[rowFeedback]->setText("Pełne");
        linkTab3[rowFeedback]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    } else {
        buttons1Tab3[rowFeedback]->setEnabled(false);
        buttons1Tab3[rowFeedback]->setText("Nieznany");
        linkTab2[rowFeedback]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    }

}
void MainWindow::set_Feedback()
{
    if(buttons1Tab3[rowFeedback]->text()=="Wyłączone")
    {
        openCMD("REG ADD HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\DataCollection /t REG_DWORD /v AllowTelemetry /f /d 0x1");
    } else if(buttons1Tab3[rowFeedback]->text()=="Podstawowe" || buttons1Tab3[rowFeedback]->text()=="Pełne")
    {
        openCMD("REG ADD HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\DataCollection /t REG_DWORD /v AllowTelemetry /f /d 0x0");
    }
    get_Feedback();
}
void MainWindow::open_Feedback()
{
    openCMD("start ms-settings:privacy-feedback");
    get_Feedback();
}

void MainWindow::get_SuggestionTimeline()
{
    QString result1 = openCMD("@FOR /F \"skip=1 tokens=3\" %G IN ('REG QUERY HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager /v SubscribedContent-353698Enabled') DO @(echo %G)");

    if(result1=="0x0\r\n") {
        buttons1Tab3[rowSuggestionTimeline]->setText("Wyłączone");
        linkTab3[rowSuggestionTimeline]->setIcon(QIcon(":/icons/icons/check-square-solid.svg"));
    } else if (result1=="0x1\r\n") {
        buttons1Tab3[rowSuggestionTimeline]->setText("Włączone");
        linkTab3[rowSuggestionTimeline]->setIcon(QIcon(":/icons/icons/minus-square-solid.svg"));
    } else {
        buttons1Tab3[rowSuggestionTimeline]->setEnabled(false);
        buttons1Tab3[rowSuggestionTimeline]->setText("Nieznany");
        linkTab2[rowSuggestionTimeline]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    }

}
void MainWindow::set_SuggestionTimeline()
{
    if(buttons1Tab3[rowSuggestionTimeline]->text()=="Wyłączone")
    {
        openCMD("REG ADD HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager /t REG_DWORD /v SubscribedContent-353698Enabled /f /d 0x1");
    } else if(buttons1Tab3[rowSuggestionTimeline]->text()=="Włączone")
    {
        openCMD("REG ADD HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager /t REG_DWORD /v SubscribedContent-353698Enabled /f /d 0x0");
    }
    get_SuggestionTimeline();
}
void MainWindow::open_SuggestionTimeline()
{
    openCMD("start ms-settings:multitasking");
    get_Feedback();
}

void MainWindow::get_AdId()
{
    QString result1 = openCMD("@FOR /F \"skip=1 tokens=3\" %G IN ('REG QUERY HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo /v Enabled') DO @(echo %G)");

    if(result1=="0x0\r\n") {
        buttons1Tab3[rowAdId]->setText("Wyłączone");
        linkTab3[rowAdId]->setIcon(QIcon(":/icons/icons/check-square-solid.svg"));
    } else if (result1=="0x1\r\n") {
        buttons1Tab3[rowAdId]->setText("Włączone");
        linkTab3[rowAdId]->setIcon(QIcon(":/icons/icons/minus-square-solid.svg"));
    } else {
        buttons1Tab3[rowAdId]->setEnabled(false);
        buttons1Tab3[rowAdId]->setText("Nieznany");
    }
}
void MainWindow::set_AdId()
{
    if(buttons1Tab3[rowAdId]->text()=="Wyłączone")
    {
        openCMD("start ms-settings:privacy-general");
    } else if(buttons1Tab3[rowAdId]->text()=="Włączone")
    {
        openCMD("REG ADD HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo /t REG_DWORD /v Enabled /f /d 0x0");
        openCMD("REG DELETE HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo /v Id /f");
    }
    get_AdId();
}
void MainWindow::open_AdId()
{
    openCMD("start ms-settings:privacy-general");
    get_AdId();
}

void MainWindow::get_Firewall()
{
    QString result1 = openCMD("netsh advfirewall show all | findstr \"State\"");

    if(result1.count("ON")==3) {
        buttons1Tab2[rowFirewall]->setText("Włączone");
        linkTab2[rowFirewall]->setIcon(QIcon(":/icons/icons/check-square-solid.svg"));
    } else if (result1.count("ON")<3 && result1.count("ON")>0) {
        buttons1Tab2[rowFirewall]->setText("Częściowo wyłączone");
        linkTab2[rowFirewall]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    } else if (result1.count("ON")==0) {
        buttons1Tab2[rowFirewall]->setText("Wyłączone");
        linkTab2[rowFirewall]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    } else {
        buttons1Tab2[rowFirewall]->setEnabled(false);
        buttons1Tab2[rowFirewall]->setText("Nieznany");
    }
}
void MainWindow::set_Firewall()
{
    if(buttons1Tab2[rowFirewall]->text()=="Częściowo wyłączone" || buttons1Tab2[rowFirewall]->text()=="Wyłączone")
    {
        openCMD("netsh advfirewall set all state on");
    } else if(buttons1Tab2[rowFirewall]->text()=="Włączone")
    {
        openCMD("netsh advfirewall set all state off");
    }
    get_Firewall();
}
void MainWindow::open_Firewall()
{
    openCMD("start firewall.cpl");
    get_Firewall();
}

void MainWindow::get_AutoPlay()
{
    QString result1 = openCMD("@FOR /F \"skip=1 tokens=3\" %G IN ('REG QUERY HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\AutoplayHandlers /v DisableAutoplay') DO @(echo %G)");

    if(result1=="0x1\r\n") {
        buttons1Tab2[rowAutoPlay]->setText("Wyłączone");
        linkTab2[rowAutoPlay]->setIcon(QIcon(":/icons/icons/check-square-solid.svg"));
    } else if (result1=="") {
        buttons1Tab2[rowAutoPlay]->setText("Włączone");
        linkTab2[rowAutoPlay]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    } else {
        buttons1Tab2[rowAutoPlay]->setEnabled(false);
        buttons1Tab2[rowAutoPlay]->setText("Nieznany");
    }
}
void MainWindow::set_AutoPlay()
{
    if(buttons1Tab2[rowAutoPlay]->text()=="Włączone")
    {
        openCMD("REG ADD HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\AutoplayHandlers /t REG_DWORD /v DisableAutoplay /f /d 0x1");
    } else if(buttons1Tab2[rowAutoPlay]->text()=="Wyłączone")
    {
        openCMD("REG DELETE HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\AutoplayHandlers /v DisableAutoplay /f");
    }
    get_AutoPlay();
}
void MainWindow::open_AutoPlay()
{
    openCMD("start ms-settings:autoplay");
    get_AutoPlay();
}
void MainWindow::get_StartExplorer()
{
    QString result1 = openCMD("@FOR /F \"skip=1 tokens=3\" %G IN ('REG QUERY HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced /v LaunchTo') DO @(echo %G)");

    if(result1=="0x1\r\n") {
        buttons1Tab5[rowStartExplorer]->setText("Ten komputer");
        linkTab5[rowStartExplorer]->setIcon(QIcon(":/icons/icons/check-square-solid.svg"));
    } else if (result1=="0x2\r\n") {
        buttons1Tab5[rowStartExplorer]->setText("Szybki dostęp");
        linkTab5[rowStartExplorer]->setIcon(QIcon(":/icons/icons/minus-square-solid.svg"));
    } else {
        buttons1Tab5[rowStartExplorer]->setEnabled(false);
        buttons1Tab5[rowStartExplorer]->setText("Nieznany (Wymaga administratora)");
        linkTab5[rowStartExplorer]->setIcon(QIcon(":/icons/icons/bug-solid.svg"));
    }
}
void MainWindow::set_StartExplorer()
{
    if(buttons1Tab5[rowStartExplorer]->text()=="Szybki dostęp")
    {
        openCMD("REG ADD HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced /t REG_DWORD /v LaunchTo /f /d 0x1");
    } else if(buttons1Tab5[rowStartExplorer]->text()=="Ten komputer")
    {
        openCMD("REG ADD HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced /t REG_DWORD /v LaunchTo /f /d 0x2");
    }
    get_StartExplorer();
}
void MainWindow::open_StartExplorer()
{
    openCMD("explorer.exe");
    get_StartExplorer();
}


void MainWindow::open_AdminTools()
{
    openCMD("control admintools");
}
void MainWindow::open_Troubleshoot()
{
    openCMD("start ms-settings:troubleshoot");
}
void MainWindow::open_OptionalFeatures()
{
    openCMD("optionalfeatures");
}
void MainWindow::open_PrivacyOptions()
{
    openCMD("start ms-settings:privacy-general");
}
void MainWindow::open_AppPermissions()
{
    openCMD("start ms-settings:privacy-location");
}
void MainWindow::open_WindowsSecurity()
{
    openCMD("start windowsdefender:");
}
void MainWindow::open_InstalledUpdates()
{
    openCMD("start ms-settings:windowsupdate-history");
}
void MainWindow::open_UserPasswords()
{
    openCMD("control userpasswords");
}
void MainWindow::open_UserPasswords2()
{
    openCMD("control userpasswords2");
}
void MainWindow::open_SystemRestore()
{
    openCMD("rstrui.exe");
}
void MainWindow::open_SearchPrivacy()
{
    openCMD("start ms-settings:cortana-permissions");
}
void MainWindow::open_DefaultApps()
{
    openCMD("start ms-settings:defaultapps");
}
void MainWindow::open_Autostart()
{
    openCMD("start ms-settings:startupapps");
    openCMD("taskmgr.exe /0 /startup");
}
void MainWindow::open_InstalledApps()
{
    openCMD("control appwiz.cpl");
}
void MainWindow::open_CleanMgr()
{
    openCMD("cleanmgr");
}
void MainWindow::open_Notifications()
{
    openCMD("start ms-settings:privacy-notifications");
}
