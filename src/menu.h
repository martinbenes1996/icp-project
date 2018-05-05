
/**
 * @file menu.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief menu header
 *
 * This module contains menu definition.
 */

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <map>
#include <string>

#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

/**
 * @brief Menu class.
 */
class Menu: public QWidget
{
    Q_OBJECT
    public:
        /**
         * @brief Menu constructor.
         * @param parent    Parent.
         */
        Menu(QWidget* parent = 0);
        /**
         * @brief Constructs image button.
         * @param key       Key to save button at.
         */
        void createImageButton(QString);
        /**
         * @brief Constructs image button.
         * @param key       Key to save button at.
         * @param check     Checkable if true.
         */
        void createTextButton(QString,bool);

        /**
         * @brief Reinitializes menu.
         */
        void reinit();
        /**
         * @brief Activates menu.
         */
        void endComputation();

    public slots:
        /**
         * @brief Received, when choice pressed.
         * @param key       Choice key.
         */
        void slotChoicePressed(QString);
        /**
         * @brief Received, when choice rejected.
         */
        void slotChoiceRejected();
        /**
         * @brief Received, when application runs. Deactivates menu.
         * @param dbg   True, if debug.
         */
        void slotRun(bool);

    signals:    
        /**
         * @brief Emitted, when choice pressed.
         * @param key       Choice key.
         */
        void sigChoiceMode(long);
        /**
         * @brief Emitted, when wire pressed.
         */
        void sigWireMode();
        /**
         * @brief Emitted, when input pressed.
         */
        void sigInput();

    private:
        QSignalMapper mmapper; /**< Signal mapper for buttons. */
        std::map<QString, QPushButton*> mButtons; /**< Button map. */
        QVBoxLayout* mlayout; /**< Menu layout. */
        QGridLayout* mblocklayout; /**< Block layout. */
        int mblockiterator = 0; /**< Block iterator. */
};

#endif // MENU_H
