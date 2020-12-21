/*
    SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: MIT
*/
#include "barcodeutil.h"

using namespace Prison;

QList<bool> BarCodeUtil::barSequence(const char* str)
{
    Q_ASSERT(strlen(str)==9); // this is a internal helper tool, only called with fixed strings in here, all 9 chars long
    QList<bool> ret;
    for(int i = 0 ; i < 9 ; i++) {
        ret.append(str[i] == '1');
        Q_ASSERT(str[i] == '0' || str[i] == '1');
    }
    return ret;
}
