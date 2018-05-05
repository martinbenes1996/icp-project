/**
 * @file main.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief main module
 *
 * This module contains main.
 */

#include <iostream>

#include <QApplication>
#include <QPushButton>

#include "config.h"
#include "controller.h"

/**
 * @brief Applies the style to the application.
 * @param app       Application.
 */
void setAppStyle(QApplication& app)
{
    QFile File( QString::fromStdString(Config::getStyleFileName()) );
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
}

/**
 * @brief Main function.
 * @param argc      Count of input parameters.
 * @param argv      Input parameters.
 * @returns Exit code.
 */
int main(int argc, char *argv[])
{
    // init config
    Config::initConfig();

    // init qapp
    QApplication app (argc, argv);
    setAppStyle(app);

    // init model
    Controller c;

    // run
    return app.exec();
}


/*! \mainpage BlockEditor
 *
 * This app allows you to create block schemes, save and load them and do a calculation using them.
 * It is very easy to learn, and great fun to use!
 *
 * \section Controls
 *
 * \subsection Blocks
 * After you start the application, you will see a neat menu on the left side and a play ground on the right side.
 * Use the menu to choose from eleven different blocks by left-clicking the block icon and then left-clicking
 * the free space. Each block type performs a different operation displayed by an intuitive icon.
 * Remember to place your blocks further from each other due to anti-collision detection. Blocks cannot
 * be too close to each other. In order to delete blocks just simply right-click them and they will disappear
 * together with all wires connected to them.
 *
 * \subsection Wires
 * Each block (apart from input blocks, about them later) requires either one or two input wires and allows
 * you to connect one output wire. The whole playground is situated left-to-right, the inputs are the ones on the
 * left of the box. In order to place a wire, choose "wire" in the menu and then left-click
 * two connectors of two different blocks. Wires can only connect output connectors with input ones and
 * do not allow you to use one connector multiple times. If any action violates these rules, nothing will happen.
 * Wires can be deleted, as well as blocks, by right-clicking them or removing any adjacent block.
 *
 * \subsection Inputs
 * To be able to compute anything, input blocks are required. Choose "input" option in menu and left-click
 * empty space. Beware collisions with other blocks. After placing an input block, a dialog window will pop up
 * asking you to enter value and type of the input block. This value will be sent through a connected wire to a
 * normal block. To remove input blocks, right-click them. The value of input blocks can be changed by double-clicking
 * the block and entering updated value. All buttons in menu must be unchecked during this process!
 * 
 * \image html inputdialog.png "Input dialog."
 *
 * \subsection Computation
 * There is not any output block. Every block or wire will tell you its value and type when you hover the cursor
 * over it. Use this method to get the final value of the last block or any other. Wires will automatically display
 * value in the middle (N means not defined value). Do not try to add wire to output connector of the last block.
 *
 * To perform computation choose "run" option from top bar and then "compute". This will compute everything. If you desire
 * to enjoy the computation step by step press "run" -> "debug" option and use your spacebar to move forward. To interrupt
 * debugging press escape. Progress of the debugging will be highlighted with red color.
 * 
 * \image html debug.png "Debug mode"
 *
 * \subsection Saving
 * Your work can be saved by choosing "file" -> "save" and entering file name and later loaded by pressing
 * "file" -> "open". The "new" option resets the play ground and discards all unsaved work.
 *
 * Our program also allows you to enter your own custom types (apart from default "general" type). Press "types"
 * -> "add type"/"remove type" to do that.
 * 
 * \image html addtype.png "Add type dialog."
 * 
 * \image html removetype.png "Remove type dialog"
 *
 * \section Implementation
 * 
 * The program is implemented in C++ (standard C++17) and Qt framework 3.5. We used Git for versioning
 * and cooperation. The documentation is generated using Doxygen.
 * 
 * \subsection Design
 * 
 * The whole design is based on MVC architecture. The Controller instantiates the Model and Window, and
 * connects them with the signals (Qt specific), so they may communicate simply. The Window instantiates
 * the parts, it consists of, Menu and PlayGround. After that, the event loop is executed and whole
 * system waits for user to do his actions.
 * 
 * When A block in Menu is selected, the PlayGround receives signal, and when it is clicked, it already
 * knows, which type of block it should place on the position. The model is asked to generate a ID for
 * the block, and the block is placed to the scene, and saved inside a PlayGround (as GuiBlock) and 
 * inside the Model too (as Block).
 * 
 * When the wire is connected, the specification of the block is done by giving its ID. In model,
 * each IBlock (generalization over Block and Input) knows the Wire objects connected to it,
 * as same as every Wire instance knows the IBlock, it is connected to.
 * 
 * When the Wire is instatiated, it is also connected. The blocks must actualize their level (aka
 * discrete time value, when they are going to have result during evaluation). The distribute it
 * through the wires. During this process, they also detect possible loops in the scheme and prevent it.
 * 
 * When the computation is initialized, the Model provides its results in advance. Every input returns
 * the structure with results, it may provide, and afterwards, they all are merged together.
 * When debugging, the vector is simply iterated on spacebar event.
 * 
 * When saving, the Model and the Window provide its states and the Controller then saves it to the file.
 * When reading, the read information are propagated to the Model and the Window, when the objects are
 * generated.
 * 
 * \image html classes.png "Class diagram."
 */
