#ifndef PYTHONENGINE_H
#define PYTHONENGINE_H

#include "util.h"
#include <Python.h>

struct Variables
{
    QString name;
    QString type;
    QVariant value;
};

class PythonEngine : public QObject
{
    Q_OBJECT

signals:
    void printStdOut(const QString &);
    void executed();

public:
    PythonEngine() {}
    ~PythonEngine();

    void init();

    void showMessage(const QString &message);

    ScriptResult runPythonScript(const QString &script, const QString &fileName = "");
    ExpressionResult runPythonExpression(const QString &expression, bool returnValue);
    ScriptResult parseError();
    inline bool isRunning() { return m_isRunning; }

    QList<Variables> variableList();

protected:
    PyObject *m_dict;

    virtual void addCustomExtensions() {}
    virtual void runPythonHeader() {}

private slots:
    void stdOut(const QString &message);

private:
    bool m_isRunning;
    QString m_stdOut;

    QString m_functions;    
};

// create custom python engine
void createPythonEngine(PythonEngine *custom = NULL);
// current python engine
PythonEngine *currentPythonEngine();

PyObject* pythonCaptureStdout(PyObject* self, PyObject* pArgs);

#endif // PYTHONENGINE_H