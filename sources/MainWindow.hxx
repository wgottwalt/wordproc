#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "Types.hxx"

class QSettings;
class QTranslator;

class MainWindow : public QMainWindow, protected Ui::MainWindow {
    Q_OBJECT
public:
    //--- public constructors ---
    MainWindow(QWidget *parent = nullptr);
    MainWindow(const MainWindow &rhs) = delete;
    MainWindow(MainWindow &&rhs) = delete;
    virtual ~MainWindow();

    //--- public operators ---
    MainWindow &operator=(const MainWindow &rhs) = delete;
    MainWindow &operator=(MainWindow &&rhs) = delete;

protected:
    //--- protected methods ---
    virtual void changeEvent(QEvent *event) override final;

    void setupActions();
    void setLanguage(const Types::Language lang = Types::Language::English);
    void setTheme(const Types::Theme theme = Types::Theme::Fusion);

private:
    //--- private properties ---
    QTranslator *_trans;
    QSettings *_conf;
    Types::Language _lang;
    Types::Theme _theme;
};
