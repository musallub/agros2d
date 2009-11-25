#ifndef SCRIPTEDITORCOMMANDPYTHON_H
#define SCRIPTEDITORCOMMANDPYTHON_H

#include "util.h"
#include "sceneview.h"

class PythonEngine : public QObject
{
    Q_OBJECT

signals:
    void printStdout(const QString &);

public:
    PythonEngine();
    ~PythonEngine();

    void setSceneView(SceneView *sceneView);
    inline void showMessage(const QString &message);

    ScriptResult runPythonScript(const QString &script, const QString &fileName);
    ExpressionResult runPythonExpression(const QString &expression);
    QString parseError();

private slots:
    void doPrintStdout(const QString &message);

private:
    QString m_stdOut;

    PyObject *m_dict;
    QString m_functions;
    SceneView *m_sceneView;

    void runPythonHeader();
};

// cython functions
void pythonMessage(char *str);
char *pythonInput(char *str);
char *pythonVersion();
char *pythonMeshFileName();
char *pythonSolutionFileName();
Solution *pythonSolutionObject();
void pythonQuit();

void pythonNewDocument(char *name, char *type, char *physicfield,
                       int numberofrefinements, int polynomialorder, char *adaptivitytype,
                       double adaptivitysteps, double adaptivitytolerance,
                       double frequency,
                       char *analysistype, double timestep, double totaltime, double initialcondition);
void pythonOpenDocument(char *str);
void pythonSaveDocument(char *str);

void pythonAddNode(double x, double y);
void pythonAddEdge(double x1, double y1, double x2, double y2, double angle, char *marker);
void pythonAddLabel(double x, double y, double area, char *marker);

void pythonSelectNone();
void pythonSelectAll();

void pythonSelectNodePoint(double x, double y);
void pythonSelectEdgePoint(double x, double y);
void pythonSelectLabelPoint(double x, double y);

void pythonRotateSelection(double x, double y, double angle, bool copy);
void pythonScaleSelection(double x, double y, double scale, bool copy);
void pythonMoveSelection(double dx, double dy, bool copy);
void pythonDeleteSelection();

void pythonMesh();
void pythonSolve();

void pythonZoomBestFit();
void pythonZoomIn();
void pythonZoomOut();
void pythonZoomRegion(double x1, double y1, double x2, double y2);

void pythonMode(char *str);
void pythonPostprocessorMode(char *str);

void pythonShowScalar(char *type, char *variable, char *component, int rangemin, int rangemax);
void pythonShowGrid(bool show);
void pythonShowGeometry(bool show);
void pythonShowInitialMesh(bool show);
void pythonShowSolutionMesh(bool show);
void pythonShowContours(bool show);
void pythonShowVectors(bool show);

void pythonSetTimeStep(int timestep);
int pythonTimeStepCount();

void pythonSaveImage(char *str, int w, int h);

#endif // SCRIPTEDITORCOMMANDPYTHON_H