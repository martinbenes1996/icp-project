
/**
 * @file window.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief window interface
 *
 * This module contains window definition.
 */

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
   std::vector<struct wireState> wires; /**< Wires state. */
};

/**
 * @brief Window.
 */
class Window: public QWidget
{
    Q_OBJECT
    public:
        /**
         * @brief Window constructor.
         * @param parent        Parent.
         */
        Window(QWidget *parent = 0);
        /**
         * @brief Window destructor.
         */
        virtual ~Window() {}

        /**
         * @brief PlayGround getter.
         * @returns Playground.
         */
        PlayGround* getPG() const { return mplayground.get(); }

        /**
         * @brief State getter.
         * @returns State of GUI.
         */
        GuiState getState();
        /**
         * @brief State setter.
         * @param s         New state.
         */
        void setState(GuiState);
        /**
         * @brief Reinitializes the window.
         */
        void reinit() { mplayground->reinit(); mmenu->reinit(); }

        /**
         * @brief   Mouse press handler.
         * @param event     Description of event.
         */  
        void keyPressEvent(QKeyEvent *);
        /**
         * @brief Ends computation.
         */
        void endComputation();

        /**
         * @brief Shows alert dialog.
         */
        void showDialog(const char *);

    public slots:
        /**
         * @brief Exit button handler.
         */
        void slotExit() { exit(0); }
        /**
         * @brief New button handler.
         */
        void slotNew() { reinit(); emit sigReset(); }
        /**
         * @brief Open button handler.
         */
        void slotOpen();
        /**
         * @brief Save button handler.
         */
        void slotSave();
        /**
         * @brief Debug button handler.
         */
        void slotDebug();
        /**
         * @brief Calculate button handler.
         */
        void slotCalculate();
        /**
         * @brief Add type button handler.
         */
        void slotAddType();
        /**
         * @brief Remove type button handler.
         */
        void slotRemoveType();
        /**
         * @brief Remove type slot.
         * @param s         Type to be removed.
         */
        void slotRemoveType(const QString&);
    signals:
        /**
         * @brief Emitted, when reset.
         */
        void sigReset();
        /**
         * @brief Emitted, when opening a file.
         * @param s         File name.
         */
        void sigOpen(std::string);
        /**
         * @brief Emitted, when saving to a file.
         * @param s         File name.
         */
        void sigSave(std::string);
        /**
         * @brief Emitted, when running.
         * @param dbg       True if debug. False if compute.
         */
        void sigRun(bool dbg);
        /**
         * @brief Emitted, when previous file is needed.
         */
        void sigPreviousResult();
        /**
         * @brief Emitted, when next file is needed.
         */
        void sigNextResult();
        /**
         * @brief Emitted, when computation ends.
         */
        void sigEndComputation();
    private:
        std::shared_ptr<PlayGround> mplayground; /**< Playground. */
        std::shared_ptr<Menu> mmenu; /**< Menu. */
        bool mcompute = false; /**< Compute mode is on. */
};

#endif // WINDOW_H
