#include "Node.hpp"

#include <QFile>
#include <QMessageBox>

namespace QtNodes
{

#pragma region /* 测试节点 */

    TestNode::TestNode()
    {
        /* input and output */
        IN_PORT("string", "string")  // in0
        IN_PORT("string", "string")  // in1
        OUT_PORT("string", "string") // out0
        OUT_PORT("string", "string") // out1

        /* widget */
        // PARAM_FILE("load", "a")
        // PARAM_BOOL("bool", true)
        // PARAM_INT("threshold", -255, 255, 2364)
        // PARAM_FLAGS("flag", "a|b|c", 0b101)
        // PARAM_RGBA("color", 12, 24, 77, 255)
        // PARAM_FILESAVE("save", "b.txt")
        // PARAM_ENUM("enum", "A|B|C", 1)
        PARAM_BUTTON("button", "button")
        PARAM_BOOL("a", true)
        // PARAM_FXYZ("f3", -4.5, 24.6, 1.3, -2.55, 34.0)
        // PARAM_IXYZW("i4", -10, 10, 1, 2, 3, 4)
        // PARAM_SLIDER("slider", -10, 10, 6)
        // PARAM_DSLIDER("dslider", -0.8, 10.9, 6.5)
        PARAM_STRING("s", "PARAM_STRING");
        PARAM_STRINGSHOW("ss", "PARAM_STRINGSHOW");
        PARAM_TEXTSHOW("text", "text")
    }

    bool TestNode::initProcess()
    {
        qDebug();
        connect(getParameter("button"), &Parameter::widgetUpdated, this, &TestNode::onTestButtonClick);

        return true;
    }

    void TestNode::process(const Parameter &param)
    {
        qDebug();
        try
        {
            /**
             * 在关联上某个控件的信号槽，可以用&param == getParameter("name")过滤
             */
            if (&param == getParameter("button"))
            {
                setOutData(1);
                return;
            }

            _out0 = getParameter("s")->getValueAsString();

            auto _input = getInput<StringData>(1); // 输入0
            if (_input && !_input->_data.isNull())
            {
                getParameter("ss")->setValue(_input->_data);
            }
            this->setOutData(0);
        }
        catch (...)
        {
            setValidationState(NodeValidationState::Error, this->Name() + "未知错误");
        }
    }

    std::shared_ptr<NodeData> TestNode::outData(PortIndex portIndex)
    {
        // qDebug() << "port(" << portIndex << ") out";

        switch (portIndex)
        {
        case 0:
            return std::make_shared<StringData>(_out0);
        case 1:
            return std::make_shared<StringData>(_out1);
        default:
            /* 不输出 */
            std::shared_ptr<NodeData> ptr;
            return ptr;
        }
    }

    void TestNode::onTestButtonClick()
    {
        qDebug();
        static int a = 1;
        switch (a)
        {
        case 1:
            getParameter("a")->setValue(false);
            setValidationState(NodeValidationState::Error, "错误");
            break;
        case 2:
            getParameter("a")->setValue(true);
            setValidationState(NodeValidationState::Valid);
            break;
        case 3:
            getParameter("a")->setValue(true);
            setValidationState(NodeValidationState::Warning, "警告");
            break;
        default:
            a = 0;
            break;
        }
        a++;
        if (a >= 4)
        {
            a = 1;
        }
    }
#pragma endregion

}