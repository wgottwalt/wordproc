#include <QTranslator>
#include "MainWindow.hxx"

//--- public constructors ---

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), Ui::MainWindow(), _trans(new QTranslator(this)),
  _lang(Types::Language::English)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{
}

//--- protected methods ---

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi(this);

    QMainWindow::changeEvent(event);
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

            switch (lang)
            {
                case Types::Language::Dutch:
                    break;

                case Types::Language::French:
                    break;

                case Types::Language::German:
                    break;

                case Types::Language::Italian:
                    break;

                case Types::Language::Spanish:
                    break;

                case Types::Language::English:
                default:
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
