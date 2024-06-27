//
// Created by 檀木筪 on 2024/6/26.
//

#include "OperationStack.h"

OperationStack::OperationStack()
{
    m_redoStack ={};
    m_undoStack ={};
}

void OperationStack::PushStack(OperationPtr operate)
{
    if(m_undoStack.size()>=m_nMaxStackSize){
        m_undoStack.pop_front();
    }
    m_undoStack.push_back(operate);
    if(!m_redoStack.empty())
    {
        m_redoStack.clear();
    }
}

void OperationStack::Undo()
{
    if(m_undoStack.empty())
    {
        return;
    }
    auto func = m_undoStack.back();
    m_undoStack.pop_back();
    func->m_funcUndo();
    m_redoStack.push_back(func);
}

void OperationStack::Redo()
{
    if(m_redoStack.empty())
    {
        return;
    }
    auto func = m_redoStack.back();
    m_redoStack.pop_back();
    func->m_funcRedo();
    m_undoStack.push_back(func);
}

QString OperationStack::GetStack()
{
    QString string = {};
    for(auto operate : m_undoStack){
        string.append(operate->m_strName + "\n");
    }
    return string;
}
