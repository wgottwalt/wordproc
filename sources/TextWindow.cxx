#include "TextWindow.hxx"

//--- internal stuff ---

static quint64 __counter = 0;

//--- public constructors ---

TextWindow::TextWindow(QWidget *parent)
: QWidget(parent), Ui::TextWindow(), _filename(""), _search_string(""), _id(__counter++),
  _text_changed(false)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setupUi(this);
    setupActions();

    wid_text->setFontFamily(btn_font->currentFont().family());
    wid_text->setFontPointSize(btn_fontsize->value());
    wid_text->setFocus();

    updateWindowTitle();
}

TextWindow::~TextWindow()
{
}

//--- public methods ---

void TextWindow::formatText(const Types::Format format)
{
    switch (format)
    {
        case Types::Format::Undo:
            wid_text->undo();
            return;

        case Types::Format::Redo:
            wid_text->redo();
            return;

        case Types::Format::Cut:
            wid_text->cut();
            return;

        case Types::Format::Copy:
            wid_text->copy();
            return;

        case Types::Format::Paste:
            wid_text->paste();
            return;

        case Types::Format::Clear:
            wid_text->textCursor().clearSelection();
            return;

        case Types::Format::SelectAll:
            wid_text->selectAll();
            return;

        case Types::Format::Bold:
            return;

        case Types::Format::Italic:
            wid_text->setFontItalic(!wid_text->fontItalic());
            return;

        case Types::Format::Underline:
            wid_text->setFontUnderline(!wid_text->fontUnderline());
            return;

        case Types::Format::Left:
            return;
        case Types::Format::Center:
            return;
        case Types::Format::Right:
            return;
        case Types::Format::Fill:
            return;
    }
}

//--- protected methods ---

void TextWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi(this);

    QWidget::changeEvent(event);
}

void TextWindow::setupActions()
{
    // toolbar buttons
    connect(btn_font, &QFontComboBox::currentFontChanged, [this](const QFont &font)
    {
        wid_text->setFontFamily(font.family());
        wid_text->setFocus();
    });
    connect(btn_fontsize, QOverload<qint32>::of(&QSpinBox::valueChanged), [this](const qint32 val)
    {
        wid_text->setFontPointSize(val);
        wid_text->setFocus();
    });

    connect(btn_font_italic, &QPushButton::clicked, [this]()
    {
        formatText(Types::Format::Italic);
        wid_text->setFocus();
    });
    connect(btn_font_underline, &QPushButton::clicked, [this]()
    {
        formatText(Types::Format::Underline);
        wid_text->setFocus();
    });

    // text area
    connect(wid_text, &QTextEdit::cursorPositionChanged, [this]()
    {
        btn_font->setCurrentFont(wid_text->currentFont());
        btn_fontsize->setValue(wid_text->fontPointSize());

        btn_font_italic->setChecked(wid_text->fontItalic());
        btn_font_underline->setChecked(wid_text->fontUnderline());
    });
    connect(wid_text, &QTextEdit::textChanged, [&]()
    {
        _text_changed = true;
        updateWindowTitle();
    });
}

void TextWindow::updateWindowTitle()
{
    setWindowTitle("(" + QString::number(_id) + ") " + (_filename.size() ? _filename :
                   tr("I18N_UNKNOWN_FILE")) + (_text_changed ? "*" : ""));
}
