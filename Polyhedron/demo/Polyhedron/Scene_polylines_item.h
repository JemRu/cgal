#ifndef SCENE_POLYLINES_ITEM_H
#define SCENE_POLYLINES_ITEM_H
#include "Scene_polylines_item_config.h"
#include <CGAL/Three/Viewer_interface.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Three/Scene_group_item.h>

#include <QString>
#include <QMenu>

#include <list>
#include <vector>

struct Scene_polylines_item_private;
class Scene_spheres_item;

class SCENE_POLYLINES_ITEM_EXPORT Scene_polylines_item : public CGAL::Three::Scene_group_item
{
    Q_OBJECT
public:
    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef K::Point_3 Point_3;
    typedef std::vector<Point_3> Polyline;
    typedef std::list<Polyline> Polylines_container;

    Scene_polylines_item();
    virtual ~Scene_polylines_item();
    enum STATS {
      NB_VERTICES = 0,
      NB_EDGES,
      MIN_LENGTH,
      MAX_LENGTH,
      MEAN_LENGTH
    };
    bool has_stats()const {return true;}
    QString computeStats(int type);
    CGAL::Three::Scene_item::Header_data header() const;

    bool isFinite() const { return true; }
    bool isEmpty() const;
    void compute_bbox() const;
    Bbox bbox() const;

    Scene_polylines_item* clone() const;

    QString toolTip() const;

    // Indicate if rendering mode is supported
    bool supportsRenderingMode(RenderingMode m) const;

    QMenu* contextMenu();

    // Flat/Gouraud OpenGL drawing
    void draw() const {}
    void draw(CGAL::Three::Viewer_interface*) const;

    // Wireframe OpenGL drawing
    void drawEdges() const{}
    void drawEdges(CGAL::Three::Viewer_interface*) const;

    void drawPoints() const{}
    void drawPoints(CGAL::Three::Viewer_interface*) const;


    void smooth(std::vector<Point_3>& polyline);

public Q_SLOTS:
    virtual void invalidateOpenGLBuffers();
    void change_corner_radii(double);
    void change_corner_radii();
    void split_at_sharp_angles();
    void reset_spheres();

    void merge(Scene_polylines_item*);

    void smooth();
public:
    Polylines_container polylines;
protected:
    // http://en.wikipedia.org/wiki/D-pointer
    friend struct Scene_polylines_item_private;
    Scene_polylines_item_private* d;

}; // end class Scene_polylines_item

#endif
