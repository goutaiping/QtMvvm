#ifndef QTMVVM_LOGGING_P_H
#define QTMVVM_LOGGING_P_H

#include <QtCore/QLoggingCategory>

#include "qtmvvmcore_global.h"

namespace QtMvvm {

Q_MVVMCORE_EXPORT Q_DECLARE_LOGGING_CATEGORY(mvvmcore)

}

#define logDebug(...) qCDebug(mvvmcore, __VA_ARGS__)
#define logInfo(...) qCInfo(mvvmcore, __VA_ARGS__)
#define logWarning(...) qCWarning(mvvmcore, __VA_ARGS__)
#define logCritical(...) qCCritical(mvvmcore, __VA_ARGS__)

#endif // QTMVVM_LOGGING_P_H