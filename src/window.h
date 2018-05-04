// window.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <memory>

#include <QWidget>

#include "menu.h"
#include "playground.h"

/**
 * @brief State of the view.
 */
struct GuiState {
   std::map<long, GuiBlockDescriptor> blocks; /**< Block state <id,GuiBlockDescriptor>. */
   // wires
   std::vector<struct wireState> wires;
};

class Window: public QWidget
{
    Q_OBJECT
    public:
        Window(QWidget *parent = 0);
        virtual ~Window() {}

        PlayGround* getPG() const { return mplayground.get(); }

        GuiState getState();
        void setState(GuiState);
        void reinit() { mplayground->reinit(); mmenu->reinit(); }

        void keyPressEvent(QKeyEvent *);
        void endComputation();

        void showDialog(const char *);

    public slots:
        void slotExit() { exit(0); }
        void slotNew() { reinit(); emit sigReset(); }
        void slotOpen();
        void slotSave();
        void slotDebug();
        void slotCalculate();
        void slotAddType();
        void slotRemoveType();
        void slotRemoveType(const QString&);
    signals:
        void sigReset();
        void sigOpen(std::string);
        void sigSave(std::string);
        void sigRun(bool dbg);
        void sigPreviousResult();
        void sigNextResult();
    private:
        std::shared_ptr<PlayGround> mplayground;
        std::shared_ptr<Menu> mmenu;
        bool mcompute = false;
};

#endif // WINDOW_H
