/**
 * @file NodeImageBase.hpp
 * @author moth (QianMoth@qq.com)
 * @brief 图像基础节点
 * @version 0.1
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <iostream>
#include <string>

#include <nodes2/BaseNode>

namespace QtNodes
{

    class TestNode : public BaseNode
    {
    public:
        TestNode();

        static std::unique_ptr<BaseNode> Create()
        {
            return std::make_unique<TestNode>();
        }

    public Q_SLOTS:
        void onTestButtonClick();

    protected:
        void init() override;
        int process(const Parameter &param = Parameter()) override;

    private:
        const QString Name() const override { return QString("NodeDemo"); }
        std::shared_ptr<NodeData> outData(PortIndex) override
        {
            return std::make_shared<PixmapData>(_value);
        }

        bool resizable() const override { return true; }

        QPixmap _value; // 节点数据
    };

}
