#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include "MainWindow.hxx"

//--- public constructors ---

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), Ui::MainWindow(), _trans(new QTranslator(this)),
  _conf(new QSettings(qApp->organizationName(), qApp->applicationName(), this)),
  _lang(Types::Language::English)
{
    setupUi(this);
    setupActions();

    if (_conf)
    {
        move(_conf->value("mainwindow_position", QPoint(40, 40)).toPoint());
        resize(_conf->value("mainwindow_size", QSize(800, 600)).toSize());
        _lang = stringToLanguage(_conf->value("language", "English").toString());
    }
    else
    {
        move(40, 40);
        resize(800, 600);
    }
    setLanguage(_lang);
}

MainWindow::~MainWindow()
{
    if (_conf)
    {
        _conf->setValue("mainwindow_position", pos());
        _conf->setValue("mainwindow_size", size());
        _conf->setValue("language", languageToString(_lang));
        _conf->sync();
    }

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

void MainWindow::setupActions()
{
    // app menu

    // edit menu

    // format menu

    // search menu

    // window menu

    // config menu
    connect(me_lang_english, &QAction::triggered, [&](){ setLanguage(); });
    connect(me_lang_dutch, &QAction::triggered, [&](){ setLanguage(Types::Language::Dutch); });
    connect(me_lang_french, &QAction::triggered, [&](){ setLanguage(Types::Language::French); });
    connect(me_lang_german, &QAction::triggered, [&](){ setLanguage(Types::Language::German); });
    connect(me_lang_italian, &QAction::triggered, [&](){ setLanguage(Types::Language::Italian); });
    connect(me_lang_spanish, &QAction::triggered, [&](){ setLanguage(Types::Language::Spanish); });
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
