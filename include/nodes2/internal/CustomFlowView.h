#pragma once

#include <nodes/FlowView>

#include "Export.hpp"

namespace QtNodes
{
    class CustomFlowScene;

    class FLOW_EDITOR_PUBLIC CustomFlowView : public FlowView
    {
        Q_OBJECT

    public:
        CustomFlowView(CustomFlowScene *scene, QWidget *parent = Q_NULLPTR);
        CustomFlowView(QWidget *parent = Q_NULLPTR);
        ~CustomFlowView();
    };
} // namespace QtNodes