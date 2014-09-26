/*
#include <QObject>
#include <QString>
#include <QtDeclarative>
#include <QQmlProperty>
#include <QQmlPropertyValueSource>


//Well, this is a complete failure. I *might* pick it up later...
class LennyQmlType : public QObject
{
    Q_OBJECT
    Q_INTERFACES(QQmlPropertyValueSource)
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged)
public:
    LennyQmlType(QObject *parent){

    }
    double scale() const;
    void setScale();

signals:
    void scaleChanged();

public slots:
    void updateScale(double newScale){
        m_targetProperty.write(newScale);
        emit scaleChanged();
    }

private:
    QQmlProperty m_targetProperty;

private slots:
    virtual void setScale(const QQmlProperty &prop) {
        m_targetProperty = prop;
    }

};
*/
