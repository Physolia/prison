/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "abstractbarcode.h"
#include "abstractbarcode_p.h"

#include <QColor>
#include <QPainter>
#include <QVariant>

using namespace Prison;

AbstractBarcode::AbstractBarcode(AbstractBarcodePrivate *dd)
    : d(dd)
{
}

QString AbstractBarcode::data() const
{
    return d->m_data.userType() == QMetaType::QString ? d->m_data.toString() : QString();
}

QByteArray AbstractBarcode::byteArrayData() const
{
    return d->m_data.userType() == QMetaType::QByteArray ? d->m_data.toByteArray() : QByteArray();
}

QImage AbstractBarcode::toImage(const QSizeF &size)
{
    d->recompute();
    if (d->m_cache.isNull() || d->sizeTooSmall(size)) {
        return QImage();
    }

    // scale to the requested size, using only full integer factors to keep the code readable
    int scaleX = std::max<int>(1, size.width() / d->m_cache.width());
    int scaleY = std::max<int>(1, size.height() / d->m_cache.height());
    if (dimensions() == TwoDimensions) {
        scaleX = scaleY = std::min(scaleX, scaleY);
    }

    QImage out(d->m_cache.width() * scaleX, d->m_cache.height() * scaleY, d->m_cache.format());
    QPainter p(&out);
    p.setRenderHint(QPainter::SmoothPixmapTransform, false);
    p.drawImage(out.rect(), d->m_cache, d->m_cache.rect());
    return out;
}

void AbstractBarcode::setData(const QString &data)
{
    d->m_data = data;
    d->m_cache = QImage();
}

void AbstractBarcode::setData(const QByteArray &data)
{
    d->m_data = data;
    d->m_cache = QImage();
}

QSizeF AbstractBarcode::trueMinimumSize() const
{
    d->recompute();
    return d->m_cache.size();
}

QSizeF AbstractBarcode::preferredSize(qreal devicePixelRatio) const
{
    d->recompute();
    return d->preferredSize(devicePixelRatio);
}

const QColor &AbstractBarcode::backgroundColor() const
{
    return d->m_background;
}

const QColor &AbstractBarcode::foregroundColor() const
{
    return d->m_foreground;
}

void AbstractBarcode::setBackgroundColor(const QColor &backgroundcolor)
{
    if (backgroundcolor != backgroundColor()) {
        d->m_background = backgroundcolor;
        d->m_cache = QImage();
    }
}

void AbstractBarcode::setForegroundColor(const QColor &foregroundcolor)
{
    if (foregroundcolor != foregroundColor()) {
        d->m_foreground = foregroundcolor;
        d->m_cache = QImage();
    }
}

AbstractBarcode::Dimensions AbstractBarcode::dimensions() const
{
    return d->m_dimension;
}

AbstractBarcode::~AbstractBarcode() = default;
