//
// Created by 檀木筪 on 2024/6/26.
//

#ifndef QT_PRJ_IMAGE_EDITOR_OPERATIONSTACK_H
#define QT_PRJ_IMAGE_EDITOR_OPERATIONSTACK_H

#include "OperationData.h"
#include <QString>

class OperationStack final
{
public:
    inline static SharedPtr<OperationStack> Instance(){
        static  SharedPtr<OperationStack> instance = std::make_shared<OperationStack>();
        return instance;
    }

    OperationStack();

    virtual ~OperationStack() = default;
    void PushStack(OperationPtr operate);
    void Undo();
    void Redo();
    QString GetStack();
private:
    Deque<OperationPtr> m_undoStack;
    Deque<OperationPtr> m_redoStack;
    int m_nMaxStackSize = OPERATION_STACK_DEPTH;
};

#endif //QT_PRJ_IMAGE_EDITOR_OPERATIONSTACK_H
