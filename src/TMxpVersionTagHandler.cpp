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


#include "TMxpVersionTagHandler.h"
#include "TMxpClient.h"

TMxpTagHandlerResult TMxpVersionTagHandler::handleStartTag(TMxpContext& ctx, TMxpClient& client, MxpStartTag* tag)
{
    const QString& version = client.getVersion();

    if (tag->getAttributesCount() > 0) {
        // Spaces in a quoted arg are unlikely and will not parse
        client.setStyle(tag->getAttrName(0));
        // Don't return the version string, if a style was set!
        return MXP_TAG_HANDLED;
    }

    QString payload = scmVersionString.arg(version);
    if (!client.getStyle().isNull())
        payload.replace(QStringLiteral(">"), QStringLiteral(" STYLE=%1>").arg(client.getStyle()));
    client.sendToServer(payload);

    return MXP_TAG_HANDLED;
}
