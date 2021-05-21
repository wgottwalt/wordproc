#pragma once

#include <QWidget>
#include "ui_TextWindow.h"
#include "Types.hxx"

class TextWindow : public QWidget, public Ui::TextWindow {
    Q_OBJECT
public:
    //--- public constructors ---
    TextWindow(QWidget *parent = nullptr);
    TextWindow(const TextWindow &rhs) = delete;
    TextWindow(TextWindow &&rhs) = delete;
    virtual ~TextWindow();

    //--- public operators ---
    TextWindow &operator=(const TextWindow &rhs) = delete;
    TextWindow &operator=(TextWindow &&rhs) = delete;

    //--- public methods ---
    void formatText(const Types::Format format);
    bool undoAvailable() const;
    bool redoAvailable() const;
    bool copyAvailable() const;
    bool pasteAvailable() const;
    bool textChanged() const;
    QTextCursor textCursor() const;

protected:
    //--- protected methods ---
    virtual void changeEvent(QEvent *event) override final;
    void setupActions();
    void updateWindowTitle();

private:
    //--- private properties ---
    QString _filename;
    QString _search_string;
    quint64 _id;
    bool _undo_available;
    bool _redo_available;
    bool _copy_available;
    bool _text_changed;
};
