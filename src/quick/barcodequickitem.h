/*
    SPDX-FileCopyrightText: 2018 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_BARCODEQUICKITEM_H
#define PRISON_BARCODEQUICKITEM_H

#include <prison/prison.h>

#include <QColor>
#include <QQuickPaintedItem>

#include <memory>

namespace Prison
{
class AbstractBarcode;

class BarcodeQuickItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(BarcodeType barcodeType READ barcodeType WRITE setBarcodeType NOTIFY barcodeTypeChanged)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(Dimensions dimensions READ dimensions NOTIFY dimensionsChanged)
    /**
     * @see Prison::AbstractBarcode::trueMinimumSize()
     * @since 5.69
     */
    Q_PROPERTY(qreal minimumHeight READ minimumHeight NOTIFY implicitHeightChanged)
    /**
     * @see Prison::AbstractBarcode::trueMinimumSize()
     * @since 5.69
     */
    Q_PROPERTY(qreal minimumWidth READ minimumWidth NOTIFY implicitWidthChanged)

public:
    enum BarcodeType {
        Null = Prison::Null,
        QRCode = Prison::QRCode,
        DataMatrix = Prison::DataMatrix,
        Aztec = Prison::Aztec,
        Code39 = Prison::Code39,
        Code93 = Prison::Code93,
        Code128 = Prison::Code128,
    };
    Q_ENUM(BarcodeType)
    explicit BarcodeQuickItem(QQuickItem *parent = nullptr);
    ~BarcodeQuickItem();

    QString content() const;
    void setContent(const QString &data);

    Prison::BarcodeQuickItem::BarcodeType barcodeType() const;
    void setBarcodeType(Prison::BarcodeQuickItem::BarcodeType type);

    QColor foregroundColor() const;
    void setForegroundColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    enum Dimensions {
        NoDimensions,
        OneDimension,
        TwoDimensions,
    };
    Q_ENUM(Dimensions);
    Dimensions dimensions() const;

    void paint(QPainter *painter) override;
    void componentComplete() override;

    qreal minimumHeight() const;
    qreal minimumWidth() const;

Q_SIGNALS:
    void contentChanged();
    void barcodeTypeChanged();
    void foregroundColorChanged();
    void backgroundColorChanged();
    void dimensionsChanged();

private:
    void updateBarcode();

    QString m_content;
    std::unique_ptr<AbstractBarcode> m_barcode;
    QColor m_fgColor = Qt::black;
    QColor m_bgColor = Qt::white;
    Prison::BarcodeType m_type = Prison::Null;
};

}

#endif // PRISON_BARCODEQUICKITEM_H
