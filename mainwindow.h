#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QGridLayout>
#include <QPushButton>


//!!! В данной ЛР нужно использовать QWidget. Лишние файлы QMainWindow нужно удалить.

class MainWindow : public QWidget {
public: \
    QT_WARNING_PUSH \
    Q_OBJECT_NO_OVERRIDE_WARNING \
    static const QMetaObject staticMetaObject; \
    virtual const QMetaObject *metaObject() const; \
    virtual void *qt_metacast(const char *); \
    virtual int qt_metacall(QMetaObject::Call, int, void **); \
    QT_TR_FUNCTIONS \
private: \
    Q_OBJECT_NO_ATTRIBUTES_WARNING \
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **); \
    QT_WARNING_POP \
    struct QPrivateSignal {}; \
    QT_ANNOTATE_CLASS(qt_qobject, "")


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool OnlyDigits();
    void SetDigits(bool);
    bool OneDot(bool);

private:

    QWidget* defaultCalcWidget;
    QWidget* simpleCalcWidget;
    QWidget* complCalcWidget;

    QGridLayout* defaultCalcLayout;
    QGridLayout* simpleCalcLayout;
    QGridLayout* complCalcLayout;
    QGridLayout* mainLayout;

    QPushButton* pushButtonSinh;
    QPushButton* pushButtonSin;
    QPushButton* pushButtonExp;
    QPushButton* pushButtonXSq;
    QPushButton* pushButtonCosh;
    QPushButton* pushButtonCos;
    QPushButton* pushButtonLn;
    QPushButton* pushButtonXCubed;
    QPushButton* pushButtonTanh;
    QPushButton* pushButtonTan;
    QPushButton* pushButtonLog;
    QPushButton* pushButtonXNed;
    QPushButton* pushButtonFact;
    QPushButton* pushButtonPi;
    QPushButton* pushButtonCubeRoot;
    QPushButton* pushButtonNRoot;
    QLineEdit* lineEdit;
    QRadioButton* radioButtonSimple;
    QRadioButton* radioButtonCompl;

    void CreateDefaultCalcWidget();
    void CreateSimpleCalcWidget();
    void CreateComplCalcWidget();

    void SpawnSimpleMode();
    void SpawnComplMode();

    bool digits_only = true;
    bool dot_one = false;
public slots:
    void SwitchMode();

    void NumberClicked();
    void UnFnClicked();
    void BinFnClicked();
    void DotClicked();

    void ClearInput();
    void Equals();
};

#endif // MAINWINDOW_H
