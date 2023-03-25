/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "abstractbarcode_p.h"
#include "abstractbarcode.h"

#include <QColor>
#include <QVariant>

using namespace Prison;

AbstractBarcodePrivate::AbstractBarcodePrivate(AbstractBarcode::Dimensions dim)
    : m_dimension(dim)
{
}

AbstractBarcodePrivate::~AbstractBarcodePrivate() = default;

bool AbstractBarcodePrivate::sizeTooSmall(const QSizeF &size) const
{
    return m_cache.width() > size.width() || m_cache.height() > size.height();
}

bool AbstractBarcodePrivate::isEmpty() const
{
    switch (m_data.userType()) {
    case QMetaType::QString:
        return m_data.toString().isEmpty();
    case QMetaType::QByteArray:
        return m_data.toByteArray().isEmpty();
    default:
        break;
    }
    return true;
}

void AbstractBarcodePrivate::recompute()
{
    if (m_cache.isNull() && !isEmpty()) {
        m_cache = paintImage();
    }
}

QSizeF AbstractBarcodePrivate::preferredSize(qreal devicePixelRatio) const
{
    switch (m_dimension) {
    case AbstractBarcode::NoDimensions:
        return {};
    case AbstractBarcode::OneDimension:
        return QSizeF(m_cache.width() * (devicePixelRatio < 2 ? 2 : 1), std::max(m_cache.height(), 50));
    case AbstractBarcode::TwoDimensions:
        return m_cache.size() * (devicePixelRatio < 2 ? 4 : 2);
    }
    return {};
}
