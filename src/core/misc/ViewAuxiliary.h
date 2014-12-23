#ifndef QI_VIEW_AUXILIARY_H
#define QI_VIEW_AUXILIARY_H

#include "QiAPI.h"
#include <QWidget>
#include <QStyleOption>

namespace Qi
{

// struct to hold tooltip information
struct QI_EXPORT TooltipInfo
{
    QString text;
    QRect rect;
};

// constants for intended view application
enum ViewApplicationFlag
{
    ViewApplicationNone = 0x0000,
    // view intended to be drawn on the widget
    ViewApplicationDraw = 0x0001,
    // view intended to be drawn for copy
    ViewApplicationCopyDraw = 0x0002,
    // view intended to make text copy
    ViewApplicationCopyText = 0x0004,

    // view intended for user defined operations
    ViewApplicationUser = 0x0100,

    ViewApplicationCopy = ViewApplicationCopyDraw | ViewApplicationCopyText,
    ViewApplicationAll = 0xFFFF,
};

Q_DECLARE_FLAGS(ViewApplicationMask, ViewApplicationFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(ViewApplicationMask)

class QI_EXPORT GuiContext
{
public:
    const QWidget* widget;

    GuiContext(const QWidget* widget)
        : widget(widget)
    {
        Q_ASSERT(widget);
    }

    QStyle* style() const { return widget->style(); }
    void initStyleOption(QStyleOption& option) const
    {
        option.initFrom(widget);
        // State_MouseOver should be set explicitly
        option.state &= ~QStyle::State_MouseOver;
    }

    const QPalette& palette() const { return widget->palette(); }
    QPalette::ColorGroup colorGroup() const
    {
        if (!widget->isEnabled())
            return QPalette::Disabled;
        else if (!widget->hasFocus())
            return QPalette::Inactive;
        else
            return QPalette::Active;
    }
};

} // end namespace Qi

#endif // QI_VIEW_AUXILIARY_H
