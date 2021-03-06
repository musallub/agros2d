// This file is part of Agros2D.
//
// Agros2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Agros2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Agros2D.  If not, see <http://www.gnu.org/licenses/>.
//
// hp-FEM group (http://hpfem.org/)
// University of Nevada, Reno (UNR) and University of West Bohemia, Pilsen
// Email: agros2d@googlegroups.com, home page: http://hpfem.org/agros2d/

#ifndef SCENESOLUTION_H
#define SCENESOLUTION_H

#include "util.h"
#include "hermes2d.h"

class Scene;
class SceneMaterial;

class ViewScalarFilter;

struct SolutionArray;

class ProgressDialog;
class ProgressItemMesh;
class ProgressItemSolve;
class ProgressItemProcessView;

class SceneSolution : public QObject
{
    Q_OBJECT

public:
    SceneSolution();
    ~SceneSolution();

    void clear();
    void loadMeshInitial(QDomElement *element);
    void saveMeshInitial(QDomDocument *doc, QDomElement *element);
    void loadSolution(QDomElement *element);
    void saveSolution(QDomDocument *doc, QDomElement *element);

    // solve
    void solve(SolverMode solverMode);

    // mesh
    inline Mesh *meshInitial() { return m_meshInitial; }
    void setMeshInitial(Mesh *meshInitial);

    // solution
    Solution *sln(int i = -1);
    void setSolutionArrayList(QList<SolutionArray *> solutionArrayList);
    inline QList<SolutionArray *> solutionArrayList() { return m_solutionArrayList; }

    // time
    void setTimeStep(int timeStep, bool showViewProgress = true);
    inline int timeStep() const { return m_timeStep; }
    int timeStepCount() const;
    double time() const;

    bool isSolved() const { return (m_timeStep != -1); }
    bool isMeshed()  const { return m_meshInitial; }
    bool isSolving() const { return m_isSolving; }

    // mesh
    inline Linearizer &linInitialMeshView() { return m_linInitialMeshView; }
    inline Linearizer &linSolutionMeshView() { return m_linSolutionMeshView; }

    // contour
    inline ViewScalarFilter *slnContourView() { return m_slnContourView; }
    void setSlnContourView(ViewScalarFilter *slnScalarView);
    inline Linearizer &linContourView() { return m_linContourView; }

    // scalar view
    inline ViewScalarFilter *slnScalarView() { return m_slnScalarView; }
    void setSlnScalarView(ViewScalarFilter *slnScalarView);
    inline Linearizer &linScalarView() { return m_linScalarView; }

    // vector view
    void setSlnVectorView(ViewScalarFilter *slnVectorXView, ViewScalarFilter *slnVectorYView);
    inline ViewScalarFilter *slnVectorViewX() { return m_slnVectorXView; }
    inline ViewScalarFilter *slnVectorViewY() { return m_slnVectorYView; }
    inline Vectorizer &vecVectorView() { return m_vecVectorView; }

    // order view
    Orderizer *ordView();

    inline int timeElapsed() const { return m_timeElapsed; }
    double adaptiveError();
    int adaptiveSteps();
    inline void setTimeElapsed(int timeElapsed) { m_timeElapsed = timeElapsed; }

    int findElementInMesh(Mesh *mesh, const Point &point) const;
    int findElementInVectorizer(const Vectorizer &vecVectorView, const Point &point) const;

    // process
    void processView(bool showViewProgress);
    void processSolutionMesh();
    void processRangeContour();
    void processRangeScalar();
    void processRangeVector();

    // progress dialog
    ProgressDialog *progressDialog();

signals:
    void timeStepChanged(bool showViewProgress = true);
    void meshed();
    void solved();

    void processedSolutionMesh();
    void processedRangeContour();
    void processedRangeScalar();
    void processedRangeVector();

private:
    int m_timeElapsed;
    bool m_isSolving;

    // general solution array
    QList<SolutionArray *> m_solutionArrayList;
    int m_timeStep;

    // mesh
    Linearizer m_linInitialMeshView;
    Linearizer m_linSolutionMeshView;

    // contour
    ViewScalarFilter *m_slnContourView; // scalar view solution
    Linearizer m_linContourView;

    // scalar view
    ViewScalarFilter *m_slnScalarView; // scalar view solution
    Linearizer m_linScalarView; // linealizer for scalar view

    // vector view
    ViewScalarFilter *m_slnVectorXView; // vector view solution - x
    ViewScalarFilter *m_slnVectorYView; // vector view solution - y
    Vectorizer m_vecVectorView; // vectorizer for vector view

    Mesh *m_meshInitial; // linearizer only for mesh (on empty solution)

    // progress dialog
    ProgressDialog *m_progressDialog;
    ProgressItemMesh *m_progressItemMesh;
    ProgressItemSolve *m_progressItemSolve;
    ProgressItemProcessView *m_progressItemProcessView;
};

#endif // SCENESOLUTION_H
