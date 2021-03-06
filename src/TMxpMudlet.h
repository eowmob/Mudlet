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
#ifndef MUDLET_TMXPMUDLET_H
#define MUDLET_TMXPMUDLET_H

#include "TEntityResolver.h"
#include "TLinkStore.h"
#include "TMxpClient.h"
#include "TMxpEvent.h"

#include "pre_guard.h"
#include <QList>
#include <QQueue>
#include "post_guard.h"

class Host;
class TMediaData;

class TMxpMudlet : public TMxpClient
{
    inline static const QString scmVersion = QStringLiteral(APP_VERSION APP_BUILD);

    Host* mpHost;

    bool mLinkMode;

    QList<QColor> fgColors, bgColors;
    // These are also a kind of stack for parameters as fg/bgColours, but here a
    // simple counter suffices:
    int boldCtr, italicCtr, underlineCtr, strikeOutCtr;
    QString mxpStyle;

public:
    // Shouldn't be here, look for a better solution
    QQueue<TMxpEvent> mMxpEvents;

    TMxpMudlet(Host* pHost);

    QString getVersion() override;

    void sendToServer(QString& str) override;

    void setLinkMode(bool val) override { mLinkMode = val; }

    bool isInLinkMode() const { return mLinkMode; }

    void pushColor(const QString& fgColor, const QString& bgColor) override;

    void popColor() override;

    void pushColor(QList<QColor>& stack, const QString& color);

    void popColor(QList<QColor>& stack);

    bool hasFgColor() const { return !fgColors.isEmpty(); }
    const QColor& getFgColor() { return fgColors.last(); }

    bool hasBgColor() const { return !bgColors.isEmpty(); }

    const QColor& getBgColor() { return bgColors.last(); }

    // TODO: implement support for fonts?
    void pushFont(const QString& fontFace, const QString& fontSize) override {}
    void popFont() override {}

    int setLink(const QStringList& links, const QStringList& hints) override;

    bool getLink(int id, QStringList** links, QStringList** hints) override;

    void playMedia(TMediaData& mediaData) override;
    void stopMedia(TMediaData& mediaData) override;

    void setBold(bool bold) override {boldCtr += bold ? 1 : -1; if(boldCtr <0) boldCtr = 0; }
    void setItalic(bool italic) override { italicCtr += italic ? 1 : -1; if(italicCtr <0) italicCtr = 0;  }
    void setUnderline(bool underline) override { underlineCtr += underline ? 1 : -1; if(underlineCtr <0) underlineCtr = 0;  }
    void setStrikeOut(bool strikeOut) override { strikeOutCtr += strikeOut ? 1 : -1; if(strikeOutCtr <0) strikeOutCtr = 0;  }

    bool isBold() override { return boldCtr > 0; }
    bool isItalic() override { return italicCtr > 0; }
    bool isUnderline() override { return underlineCtr > 0; }
    bool isStrikeOut() override { return strikeOutCtr > 0; }

    void setStyle(const QString& val) override {mxpStyle = val; }
    virtual const QString &getStyle() override {return mxpStyle;}

    void setFlag(const QString& elementName, const QMap<QString, QString>& values, const QString& content) override
    {
        // TODO: raise mxp event
    }

    void publishEntity(const QString& name, const QString& value) override {}

    void setVariable(const QString& name, const QString& value) override {}

    TMxpTagHandlerResult tagHandled(MxpTag* tag, TMxpTagHandlerResult result) override;

    void enqueueMxpEvent(MxpStartTag* tag);
    TLinkStore& getLinkStore();
};

#endif //MUDLET_TMXPMUDLET_H
