#pragma once

#include <nodes/FlowView>

#include "CustomFlowScene.h"
#include "Export.hpp"

namespace QtNodes
{
    class FLOW_EDITOR_PUBLIC CustomFlowView : public FlowView
    {
        Q_OBJECT
    public:
        CustomFlowView(QWidget *parent = Q_NULLPTR);
        CustomFlowView(CustomFlowScene *scene, QWidget *parent = Q_NULLPTR);
    };
} // namespace QtNodes