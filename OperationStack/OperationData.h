//
// Created by 檀木筪 on 2024/6/27.
//

#ifndef QT_PRJ_IMAGE_EDITOR_OPERATIONDATA_H
#define QT_PRJ_IMAGE_EDITOR_OPERATIONDATA_H

#include "Define.h"
#include <QString>

struct OperationData
{
    QString m_strName;
    std::function<void()> m_funcUndo;
    std::function<void()> m_funcRedo;
    OperationData(QString name, std::function<void()> funcUndo, std::function<void()> funcRedo)
        : m_strName(std::move(name)), m_funcUndo(std::move(funcUndo)), m_funcRedo(std::move(funcRedo)) {}
};
using OperationPtr = SharedPtr<OperationData>;
#endif //QT_PRJ_IMAGE_EDITOR_OPERATIONDATA_H
