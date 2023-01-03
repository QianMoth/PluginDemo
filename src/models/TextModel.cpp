#include "TextModel.hpp"

#include <QDebug>

TextModel::TextModel(/* args */) { _out0 = std::make_shared<StringData>(); }

TextModel::~TextModel()
{
    delete _messageBox;
    delete _layout;

    delete widget;
}

QWidget *TextModel::embeddedWidget()
{
    if (!widget)
    {
        widget = new QWidget();
        _layout = new QGridLayout(widget);
        // _layout->setContentsMargins(0, 0, 0, 0);

        _messageBox = new QTextEdit();
        connect(_messageBox,
                &QTextEdit::textChanged,
                this,
                [this]()
                {
                    _out0->data = _messageBox->toPlainText();
                    Q_EMIT dataUpdated(0);
                });

        _layout->addWidget(_messageBox, 1, 0);
    }
    return widget;
}

void TextModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex index)
{
    qDebug();

    if (!nodeData)
    {
        Q_EMIT dataInvalidated(index);
        return;
    }

    try
    {
        switch (index)
        {
            case 0 :
            {
                auto in = std::dynamic_pointer_cast<StringData>(nodeData);
                if (!in || in->data.isNull())
                    return;

                _messageBox->setText(in->data);
                _messageBox->moveCursor(QTextCursor::End);
            }
            break;

            default :
                break;
        }
    }
    catch (std::exception &e)
    {
        qCritical() << e.what();
    }
}

unsigned int TextModel::nPorts(PortType const portType) const
{
    switch (portType)
    {
        case PortType::In :
            return 1u;
            break;

        case PortType::Out :
            return 1u;

        default :
            break;
    }
    return 1u;
}

NodeDataType TextModel::dataType(PortType const, PortIndex const) const
{
    return StringData().type();
}

std::shared_ptr<NodeData> TextModel::outData(PortIndex const index)
{
    if (index > 1u)
    {
        std::shared_ptr<NodeData> ptr;
        return ptr;
    }
    return _out0;
}
