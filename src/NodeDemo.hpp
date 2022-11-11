/**
 * @file NodeImageBase.hpp
 * @author moth (QianMoth@qq.com)
 * @brief 图像基础节点
 * @version 0.0.1
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <iostream>
#include <string>

#include <nodes2/BaseNode>
#include <nodes2/Parameter>

namespace QtNodes
{

    class TestNode : public BaseNode
    {
    public:
        TestNode();

    public Q_SLOTS:
        void onTestButtonClick();

    protected:
        /**
         * @brief initProcess
         *
         * @return true 执行process()
         * @return false 不执行process()
         */
        bool initProcess() override;
        void process(const Parameter &param) override;

    private:
        /**
         * @brief 节点名称(唯一)
         *
         * @return const QString
         */
        const QString Name() const override { return QString("NodeDemo"); }
        bool resizable() const override { return true; }

        std::shared_ptr<NodeData> outData(PortIndex portIndex) override;

        QString _out0; // 节点数据
        QString _out1; // 节点数据
    };

}
