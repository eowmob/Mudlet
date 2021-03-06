/***************************************************************************
 *   Copyright (C) 2020 by Gustavo Sousa - gustavocms@gmail.com            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "TMxpFormattingTagsHandler.h"
#include "TMxpClient.h"

bool TMxpFormattingTagsHandler::supports(TMxpContext& ctx, TMxpClient& client, MxpTag* tag)
{
    return tag->isNamed("B") || tag->isNamed("BOLD") || tag->isNamed("STRONG") ||
           tag->isNamed("I") || tag->isNamed("ITALIC") || tag->isNamed("EM") ||
           tag->isNamed("U") || tag->isNamed("UNDERLINE") ||
           tag->isNamed("S") || tag->isNamed("STRIKEOUT");
}

TMxpTagHandlerResult TMxpFormattingTagsHandler::handleStartTag(TMxpContext& ctx, TMxpClient& client, MxpStartTag* tag)
{
    setAttribute(client, tag, true);

    return MXP_TAG_HANDLED;
}
TMxpTagHandlerResult TMxpFormattingTagsHandler::handleEndTag(TMxpContext& ctx, TMxpClient& client, MxpEndTag* tag)
{
    setAttribute(client, tag, false);

    return MXP_TAG_HANDLED;
}
void TMxpFormattingTagsHandler::setAttribute(TMxpClient& client, MxpTag* tag, bool value) const
{
    if (tag->isNamed("B") || tag->isNamed("BOLD") || tag->isNamed("STRONG")) {
        client.setBold(value);
    } else if (tag->isNamed("I") || tag->isNamed("ITALIC") || tag->isNamed("EM")) {
        client.setItalic(value);
    } else if (tag->isNamed("U") || tag->isNamed("UNDERLINE")) {
        client.setUnderline(value);
    } else if (tag->isNamed("S") || tag->isNamed("STRIKEOUT")) {
        client.setStrikeOut(value);
    } else {
        // do nothing
    }
}
