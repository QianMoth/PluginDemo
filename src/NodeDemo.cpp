#include "NodeDemo.hpp"

#include <QFile>
#include <QMessageBox>

#include <nodes2/CustomWidgets>

namespace QtNodes
{

#pragma region /* 测试节点 */

    TestNode::TestNode()
    {
        /* input and output */
        OUT_PORT("pixmap", "pixmap")

        /* widget */
        PARAM_FILE("load", "a")
        PARAM_BOOL("bool", true)
        PARAM_INT("threshold", -255, 255, 2364)
        PARAM_FLAGS("flag", "a|b|c", 0b101)
        PARAM_RGBA("color", 12, 24, 77, 255)
        PARAM_FILESAVE("save", "b.txt")
        PARAM_ENUM("enum", "A|B|C", 1)
        PARAM_BUTTON("button", "button")
        PARAM_FXYZ("f3", -4.5, 24.6, 1.3, -2.55, 34.0)
        PARAM_IXYZW("i4", -10, 10, 1, 2, 3, 4)
        PARAM_SLIDER("slider", -10, 10, 6)
        PARAM_DSLIDER("dslider", -0.8, 10.9, 6.5)
        PARAM_TEXT("text", "text")
    }

    void TestNode::init()
    {
        eButton *button = getParameter("button")->property("0").value<eButton *>();
        assert(button);
        connect(button, &QPushButton::clicked, this, &TestNode::onTestButtonClick);
        process();
    }

    int TestNode::process(const Parameter &param)
    {
        try
        {
            return -1;
        }
        catch (...)
        {
            setValidationState(NodeValidationState::Error, this->Name() + "未知错误");
        }
    }

    void TestNode::onTestButtonClick()
    {
        static int a = 1;
        QMessageBox::information(nullptr, "注意", "测试 ");
        switch (a)
        {
        case 1:
            setValidationState(NodeValidationState::Error, "错误");
            break;
        case 2:
            setValidationState(NodeValidationState::Valid);
            break;
        case 3:
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