#pragma once

#include <QPixmap>
#include <QString>
#include <QtNodes/NodeData>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

template<class T, char const *id>
class TemplateNodeData : public NodeData
{
  public:
    TemplateNodeData() {}

    TemplateNodeData(const QString name) : name(name) {}

    // TemplateNodeData(T const & data) : data(data) {}
    TemplateNodeData(T const &data, const QString name) : name(name), data(data) {}

    virtual NodeDataType type() const override { return NodeDataType{QString(id), name}; }

    T data;
    QString name = QString(id);
};

static char const BOOL_ID[] = "bool";
typedef TemplateNodeData<bool, BOOL_ID> BoolData;

static char const INT_ID[] = "int";
typedef TemplateNodeData<int, INT_ID> IntData;
static char const DOUBLE_ID[] = "double";
typedef TemplateNodeData<double, DOUBLE_ID> DoubleData;

static char const VEC2I_ID[] = "vec2i";
typedef TemplateNodeData<std::vector<std::pair<int, int>>, VEC2I_ID> Vec2iData;
static char const VEC2D_ID[] = "vec2d";
typedef TemplateNodeData<std::vector<std::pair<double, double>>, VEC2D_ID> Vec2dData;

static char const VEC3I_ID[] = "vec3i";
typedef TemplateNodeData<std::vector<std::tuple<int, int, int>>, VEC3I_ID> Vec3iData;
static char const VEC3D_ID[] = "vec3d";
typedef TemplateNodeData<std::vector<std::tuple<double, double, double>>, VEC3D_ID> Vec3dData;

static char const VEC4I_ID[] = "vec4i";
typedef TemplateNodeData<std::vector<std::tuple<int, int, int, int>>, VEC4I_ID> Vec4iData;
static char const VEC4D_ID[] = "vec4d";
typedef TemplateNodeData<std::vector<std::tuple<double, double, double, double>>, VEC4D_ID> Vec4dData;

static char const QSTRING_ID[] = "string";
typedef TemplateNodeData<QString, QSTRING_ID> StringData;
static char const QPIXMAP_ID[] = "pixmap";
typedef TemplateNodeData<QPixmap, QPIXMAP_ID> PixmapData;
