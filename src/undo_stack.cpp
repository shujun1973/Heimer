// This file is part of Heimer.
// Copyright (C) 2018 Jussi Lind <jussi.lind@iki.fi>
//
// Heimer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Heimer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Heimer. If not, see <http://www.gnu.org/licenses/>.

#include "undo_stack.hpp"

UndoStack::UndoStack(int maxHistorySize)
  : m_maxHistorySize(maxHistorySize)
{
}

void UndoStack::pushUndoPoint(MindMapDataPtr mindMapData)
{
    auto copyData = new MindMapData(*mindMapData);
    m_undoStack.push_back(MindMapDataPtr(copyData));

    if (static_cast<int>(m_undoStack.size()) > m_maxHistorySize && m_maxHistorySize != -1) {
        m_undoStack.pop_front();
    }
}

void UndoStack::pushRedoPoint(MindMapDataPtr mindMapData)
{
    auto copyData = new MindMapData(*mindMapData);
    m_redoStack.push_back(MindMapDataPtr(copyData));

    if (static_cast<int>(m_redoStack.size()) > m_maxHistorySize && m_maxHistorySize != -1) {
        m_redoStack.pop_front();
    }
}

void UndoStack::clear()
{
    m_undoStack.clear();
    m_redoStack.clear();
}

bool UndoStack::isUndoable() const
{
    return m_undoStack.size() > 0;
}

MindMapDataPtr UndoStack::undo()
{
    if (isUndoable()) {
        auto head = m_undoStack.back();
        m_undoStack.pop_back();
        return head;
    }

    return MindMapDataPtr();
}

bool UndoStack::isRedoable() const
{
    return m_redoStack.size() > 0;
}

MindMapDataPtr UndoStack::redo()
{
    if (isRedoable()) {
        auto head = m_redoStack.back();
        m_redoStack.pop_back();
        return head;
    }

    return MindMapDataPtr();
}
