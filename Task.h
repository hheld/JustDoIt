#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QString>

class TaskPrivate;

class Task
{
public:
    Task();
    ~Task();

    const QDateTime& startDate() const;
    void startDate(const QDateTime &startDate);

    const QDateTime& endDate() const;
    void endDate(const QDateTime &endDate);

    const QDateTime& dueDate() const;
    void dueDate(const QDateTime &dueDate);

    const QString& title() const;
    void title(const QString &title);

    const QString& description() const;
    void description(const QString &description);

    const qint32& id() const;
    void id(const qint32 &id);

    const QString& location() const;
    void location(const QString &location);

    const QString& realm() const;
    void realm(const QString &realm);

    const bool& done() const;
    void done(const bool &done);

    //-------------------------------------------------

    static QString DateTimeFormat;

private:
    TaskPrivate *d_ptr;

    Q_DISABLE_COPY(Task)
    Q_DECLARE_PRIVATE(Task)
};

#endif // TASK_H
