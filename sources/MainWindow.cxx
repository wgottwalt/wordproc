#include <QApplication>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QPrintDialog>
#include <QPrinter>
#include <QSettings>
#include <QStyleFactory>
#include <QTranslator>
#include "MainWindow.hxx"
#include "SearchWindow.hxx"
#include "TextWindow.hxx"

//--- public constructors ---

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), Ui::MainWindow(), _trans(new QTranslator(this)),
  _conf(new QSettings(qApp->organizationName(), qApp->applicationName(), this)),
  _search(new SearchWindow), _opalette(qApp->palette()), _lang(Types::Language::English),
  _theme(Types::Theme::Fusion), _darkmode(false)
{
    setupUi(this);
    setupActions();
    _search->setWindowFlags(Qt::WindowStaysOnTopHint);

    if (_conf)
    {
        move(_conf->value("mainwindow_position", QPoint(40, 40)).toPoint());
        resize(_conf->value("mainwindow_size", QSize(800, 600)).toSize());
        _lang = stringToLanguage(_conf->value("language", "English").toString());
        _theme = stringToTheme(_conf->value("theme", "Fusion").toString());
        _darkmode = _conf->value("darkmode", "false").toBool();
    }
    else
    {
        move(40, 40);
        resize(800, 600);
    }
    setLanguage(_lang);
    setTheme(_theme);
    setDarkmode(_darkmode);

    me_theme_fusion->setVisible(false);
    me_theme_macos->setVisible(false);
    me_theme_qtcurve->setVisible(false);
    me_theme_windows->setVisible(false);

    for (auto &stylename : QStyleFactory::keys())
    {
        if (stylename == "Fusion")
            me_theme_fusion->setVisible(true);

        if (stylename == "MacOS")
            me_theme_macos->setVisible(true);

        if (stylename == "QtCurve")
            me_theme_qtcurve->setVisible(true);

        if (stylename == "Windows")
            me_theme_windows->setVisible(true);
    }
}

MainWindow::~MainWindow()
{
    if (_conf)
    {
        _conf->setValue("mainwindow_position", pos());
        _conf->setValue("mainwindow_size", size());
        _conf->setValue("language", languageToString(_lang));
        _conf->setValue("theme", themeToString(_theme));
        _conf->setValue("darkmode", _darkmode);
        _conf->sync();
    }

    delete _search;
    delete _conf;
    delete _trans;
}

//--- protected methods ---

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi(this);

    QMainWindow::changeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    _search->close();

    QMainWindow::closeEvent(event);
}

void MainWindow::setupActions()
{
    // app menu
    connect(mm_app, &QMenu::aboutToShow, [&]()
    {
        auto *subwindow = currentTextWindow();

        me_app_save->setEnabled(subwindow ? true : false);
        me_app_saveas->setEnabled(subwindow ? true : false);
        me_app_close->setEnabled(subwindow ? true : false);
        me_app_print->setEnabled(subwindow ? true : false);
    });
    connect(me_app_new, &QAction::triggered, [&](){ createTextWindow(); });
    connect(me_app_open, &QAction::triggered, [&]()
    {
        if (const auto filenames = QFileDialog::getOpenFileNames(this, tr("I18N_DOCOPEN"), "./",
            tr("I18N_DOCOPEN_FILTER")); filenames.size())
        {
            for (auto &filename : filenames)
                createTextWindow(filename);
        }
    });
    connect(me_app_close, &QAction::triggered, [&](){ wid_mdi->closeActiveSubWindow(); });
    connect(me_app_print, &QAction::triggered, [&]()
    {
        QPrinter printer;
        QPrintDialog dialog(&printer, this);

        dialog.exec();
    });
    connect(me_app_quit, &QAction::triggered, this, &MainWindow::close);

    // edit menu

    // format menu

    // search menu
    connect(mm_search, &QMenu::aboutToShow, [&]()
    {
        auto *subwin = currentTextWindow();

        me_search_find->setEnabled(subwin ? true : false);
        me_search_find_next->setEnabled(subwin ? true : false);
        me_search_find_prev->setEnabled(subwin ? true : false);
        me_search_replace->setEnabled(subwin ? true : false);
        me_search_goto->setEnabled(subwin ? true : false);
    });
    connect(me_search_find, &QAction::triggered, [&](){ _search->show(); });

    // window menu

    // config menu
    connect(me_lang_english, &QAction::triggered, [&](){ setLanguage(); });
    connect(me_lang_dutch, &QAction::triggered, [&](){ setLanguage(Types::Language::Dutch); });
    connect(me_lang_french, &QAction::triggered, [&](){ setLanguage(Types::Language::French); });
    connect(me_lang_german, &QAction::triggered, [&](){ setLanguage(Types::Language::German); });
    connect(me_lang_italian, &QAction::triggered, [&](){ setLanguage(Types::Language::Italian); });
    connect(me_lang_spanish, &QAction::triggered, [&](){ setLanguage(Types::Language::Spanish); });

    connect(me_theme_fusion, &QAction::triggered, [&](){ setTheme(); });
    connect(me_theme_macos, &QAction::triggered, [&](){ setTheme(Types::Theme::Macos); });
    connect(me_theme_qtcurve, &QAction::triggered, [&](){ setTheme(Types::Theme::QtCurve); });
    connect(me_theme_windows, &QAction::triggered, [&](){ setTheme(Types::Theme::Windows); });
    connect(me_theme_darkmode, &QAction::toggled, [&](const bool on){ setDarkmode(on); });

    // help menu
}

void MainWindow::setLanguage(const Types::Language lang)
{
    QTranslator *translator = new QTranslator(this);

    if (translator)
    {
        switch (lang)
        {
            case Types::Language::Dutch:
                translator->load(":/Language/Dutch");
                break;

            case Types::Language::French:
                translator->load(":/Language/French");
                break;

            case Types::Language::German:
                translator->load(":/Language/German");
                break;

            case Types::Language::Italian:
                translator->load(":/Language/Italian");
                break;

            case Types::Language::Spanish:
                translator->load(":/Language/Spanish");
                break;

            case Types::Language::English:
            default:
                translator->load(":/Language/English");
        }

        if (!translator->isEmpty())
        {
            _lang = lang;
            me_lang_dutch->setEnabled(true);
            me_lang_english->setEnabled(true);
            me_lang_french->setEnabled(true);
            me_lang_german->setEnabled(true);
            me_lang_italian->setEnabled(true);
            me_lang_spanish->setEnabled(true);

            switch (lang)
            {
                case Types::Language::Dutch:
                    me_lang_dutch->setEnabled(false);
                    break;

                case Types::Language::French:
                    me_lang_french->setEnabled(false);
                    break;

                case Types::Language::German:
                    me_lang_german->setEnabled(false);
                    break;

                case Types::Language::Italian:
                    me_lang_italian->setEnabled(false);
                    break;

                case Types::Language::Spanish:
                    me_lang_spanish->setEnabled(false);
                    break;

                case Types::Language::English:
                default:
                    me_lang_english->setEnabled(false);
                    break;
            }

            qApp->removeTranslator(_trans);
            delete _trans;
            _trans = translator;
            qApp->installTranslator(translator);
        }
        else
            delete translator;
    }
}

void MainWindow::setTheme(const Types::Theme theme)
{
    me_theme_fusion->setEnabled(true);
    me_theme_macos->setEnabled(true);
    me_theme_qtcurve->setEnabled(true);
    me_theme_windows->setEnabled(true);
    _theme = theme;

    switch (theme)
    {
        case Types::Theme::Macos:
            qApp->setStyle(QStyleFactory::create("MacOS"));
            me_theme_macos->setEnabled(false);
            break;

        case Types::Theme::QtCurve:
            qApp->setStyle(QStyleFactory::create("QtCurve"));
            me_theme_qtcurve->setEnabled(false);
            break;

        case Types::Theme::Windows:
            qApp->setStyle(QStyleFactory::create("Windows"));
            me_theme_windows->setEnabled(false);
            break;

        case Types::Theme::Fusion:
        default:
            qApp->setStyle(QStyleFactory::create("Fusion"));
            me_theme_fusion->setEnabled(false);
    }
}

void MainWindow::setDarkmode(const bool mode)
{
    if (mode)
    {
        QPalette dark;

        dark.setColor(QPalette::Window, QColor(53, 53, 53));
        dark.setColor(QPalette::WindowText, Qt::white);
        dark.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127, 127, 127));
        dark.setColor(QPalette::Base, QColor(42, 42, 42));
        dark.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
        dark.setColor(QPalette::ToolTipBase, Qt::white);
        dark.setColor(QPalette::ToolTipText, QColor(53, 53, 53));
        dark.setColor(QPalette::Text, Qt::white);
        dark.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
        dark.setColor(QPalette::Dark, QColor(30, 30, 30));
        dark.setColor(QPalette::Shadow, QColor(10, 10, 10));
        dark.setColor(QPalette::Button, QColor(53, 53, 53));
        dark.setColor(QPalette::ButtonText, Qt::white);
        dark.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));
        dark.setColor(QPalette::BrightText, Qt::red);
        dark.setColor(QPalette::Link, QColor(42, 130, 218));
        dark.setColor(QPalette::Highlight, QColor(42, 130, 218));
        dark.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
        dark.setColor(QPalette::HighlightedText, Qt::white);
        dark.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));

        qApp->setPalette(dark);
    }
    else
        qApp->setPalette(_opalette);

    _darkmode = mode;
    me_theme_darkmode->setChecked(mode);
}

TextWindow *MainWindow::createTextWindow(const QString &filename)
{
    QMdiSubWindow *subwin = wid_mdi->addSubWindow(new TextWindow);
    TextWindow *textwin = qobject_cast<TextWindow *>(subwin->widget());
    QAction *action = mm_window->addAction(textwin->windowTitle(), subwin, [this,subwin]()
        { wid_mdi->setActiveSubWindow(subwin); });

    connect(textwin, &TextWindow::windowTitleChanged, action, &QAction::setText);
    connect(textwin, &TextWindow::destroyed, [this,action](){ mm_window->removeAction(action); });

#if 0
    if (!filename.isEmpty() && !textwin->openFile(filename))
    {
        wid_mdi->removeSubWindow(subwin);
        return nullptr;
    }
#endif
    subwin->setGeometry(subwin->x(), subwin->y(), width() / 2, height() * 2 / 3);
    textwin->show();

    return textwin;
}

TextWindow *MainWindow::currentTextWindow()
{
    if (QMdiSubWindow *subwin = wid_mdi->activeSubWindow(); subwin)
        return qobject_cast<TextWindow *>(subwin->widget());

    return nullptr;
}
