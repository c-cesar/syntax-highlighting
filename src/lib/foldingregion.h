/*
    Copyright (C) 2016 Volker Krause <vkrause@kde.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SYNTAXHIGHLIGHTING_FOLDINGREGION_H
#define SYNTAXHIGHLIGHTING_FOLDINGREGION_H

#include "kf5syntaxhighlighting_export.h"

#include <QTypeInfo>

namespace SyntaxHighlighting {

/** Represents a begin or end of a folding region. */
class KF5SYNTAXHIGHLIGHTING_EXPORT FoldingRegion
{
public:
    /**
     * Defines whether a FoldingRegion starts or ends a folding region.
     */
    enum Type {
        //! Used internally as indicator for invalid FoldingRegion%s.
        None,
        //! Indicates the start of a FoldingRegion.
        Begin,
        //! Indicates the end of a FoldingRegion.
        End
    };

    /**
     * Constructs an invalid folding region, meaning that isValid() returns @e false.
     * To obtain valid instances, see AbstractHighlighter::applyFolding().
     */
    FoldingRegion();

    /**
     * Returns @c true if this is a valid folding region.
     * A valid FoldingRegion is defined by a type() other than Type::None.
     *
     * @note The FoldingRegion%s passed in AbstractHighlighter::applyFolding()
     *       are always valid.
     */
    bool isValid() const;

    /**
     * Returns a unique identifier for this folding region.
     *
     * As example, the C/C++ highlighter starts and ends a folding region for
     * scopes, e.g.:
     * \code
     * void foo() {     // '{' starts a folding region
     *     if (bar()) { // '{' starts a (nested) folding region
     *     }            // '}' ends the (nested) folding region
     * }                // '}' ends the outer folding region
     * \endcode
     * In this example, all braces '{' and '}' have the same id(), meaning that
     * if you want to find the matching closing region for the first opening
     * brace, you need to do kind of a reference counting to find the correct
     * closing brace.
     */
    quint16 id() const;

    /**
     * Returns whether this is the begin or end of a region.
     *
     * @note The FoldingRegion%s passed in AbstractHighlighter::applyFolding()
     *       are always valid, i.e. either Type::Begin or Type::End.
     */
    Type type() const;

private:
    friend class Rule;
    FoldingRegion(Type type, quint16 id);

    quint16 m_type : 2;
    quint16 m_id: 14;
};

}

Q_DECLARE_TYPEINFO(SyntaxHighlighting::FoldingRegion, Q_PRIMITIVE_TYPE);

#endif