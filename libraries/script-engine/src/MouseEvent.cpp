//
//  MouseEvent.cpp
//  script-engine/src
//
//  Created by Stephen Birarda on 2014-10-27.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include "MouseEvent.h"

#include <qscriptengine.h>
#include <qscriptvalue.h>

MouseEvent::MouseEvent() :
    x(0.0f),
    y(0.0f),
    isLeftButton(false),
    isRightButton(false),
    isMiddleButton(false),
    isShifted(false),
    isControl(false),
    isMeta(false),
    isAlt(false)
{
    
}


MouseEvent::MouseEvent(const QMouseEvent& event) :
    x(event.x()),
    y(event.y()),
    isLeftButton(event.buttons().testFlag(Qt::LeftButton)),
    isRightButton(event.buttons().testFlag(Qt::RightButton)),
    isMiddleButton(event.buttons().testFlag(Qt::MiddleButton)),
    isShifted(event.modifiers().testFlag(Qt::ShiftModifier)),
    isControl(event.modifiers().testFlag(Qt::ControlModifier)),
    isMeta(event.modifiers().testFlag(Qt::MetaModifier)),
    isAlt(event.modifiers().testFlag(Qt::AltModifier))
{
    // single button that caused the event
    switch (event.button()) {
        case Qt::LeftButton:
            button = "LEFT";
            isLeftButton = true;
            break;
        case Qt::RightButton:
            button = "RIGHT";
            isRightButton = true;
            break;
        case Qt::MiddleButton:
            button = "MIDDLE";
            isMiddleButton = true;
            break;
        default:
            button = "NONE";
            break;
    }
}

/**jsdoc
 * A controller mouse movement or button event.
 * @typedef {object} MouseEvent
 * @property {number} x - Integer x-coordinate of the event on the Interface window or HMD HUD.
 * @property {number} y - Integer y-coordinate of the event on the Interface window or HMD HUD.
 * @property {string} button - <code>"LEFT"</code>, <code>"MIDDLE"</code>, or <code>"RIGHT"</code> if a button press or release 
 *     caused the event, otherwise <code>"NONE"</code>.
 * @property {boolean} isLeftButton - <code>true</code> if the left button was pressed when the event was generated, otherwise 
 *     <code>false</code>.
 * @property {boolean} isMiddleButton - <code>true</code> if the middle button was pressed when the event was generated, 
 *     otherwise <code>false</code>.
 * @property {boolean} isRightButton - <code>true</code> if the right button was pressed when the event was generated, 
 *     otherwise <code>false</code>.
 * @property {boolean} isShifted - <code>true</code> if the Shift key was pressed when the event was generated, otherwise
 *     <code>false</code>.
 * @property {boolean} isMeta - <code>true</code> if the "meta" key was pressed when the event was generated, otherwise
 *     <code>false</code>. On Windows the "meta" key is the Windows key; on OSX it is the Control (Splat) key.
 * @property {boolean} isControl - <code>true</code> if the "control" key was pressed when the event was generated, otherwise
 *     <code>false</code>. On Windows the "control" key is the Ctrl key; on OSX it is the Command key.
 * @property {boolean} isAlt - <code>true</code> if the Alt key was pressed when the event was generated, otherwise
 *     <code>false</code>.
 * @example <caption>Report the MouseEvent details for each mouse move.</caption>
 * Controller.mouseMoveEvent.connect(function (event) {
 *     print(JSON.stringify(event));
 * });
 */
QScriptValue MouseEvent::toScriptValue(QScriptEngine* engine, const MouseEvent& event) {
    QScriptValue obj = engine->newObject();
    obj.setProperty(QStringLiteral("x"), event.x);
    obj.setProperty(QStringLiteral("y"), event.y);
    obj.setProperty(QStringLiteral("button"), event.button);
    obj.setProperty(QStringLiteral("isLeftButton"), event.isLeftButton);
    obj.setProperty(QStringLiteral("isRightButton"), event.isRightButton);
    obj.setProperty(QStringLiteral("isMiddleButton"), event.isMiddleButton);
    obj.setProperty(QStringLiteral("isShifted"), event.isShifted);
    obj.setProperty(QStringLiteral("isMeta"), event.isMeta);
    obj.setProperty(QStringLiteral("isControl"), event.isControl);
    obj.setProperty(QStringLiteral("isAlt"), event.isAlt);
    
    return obj;
}

void MouseEvent::fromScriptValue(const QScriptValue& object, MouseEvent& event) {
    // nothing for now...
}
