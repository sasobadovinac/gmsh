#include <algorithm>
#include "GModel.h"
#include "GEdge.h"
#include "GmshDefines.h"

void GEdge::addFace(GFace *e)
{ 
  l_faces.push_back(e);  
}

void GEdge::delFace(GFace *e)
{ 
  l_faces.erase(std::find(l_faces.begin(), l_faces.end(), e));
}

GEdge::GEdge(GModel *model, 
	     int tag, 
	     GVertex *_v0, 
	     GVertex *_v1)
  : GEntity(model, tag), v0(_v0), v1(_v1)
{
  if(v0) v0->addEdge(this);
  if(v1) v1->addEdge(this);
  meshAttributes.Method = LIBRE; 
}

GEdge::~GEdge() 
{
  if(v0) v0->delEdge(this);
  if(v1) v1->delEdge(this);

  for(unsigned int i = 0; i < mesh_vertices.size(); i++) 
    delete mesh_vertices[i];
  mesh_vertices.clear();

  for(unsigned int i = 0; i < lines.size(); i++) 
    delete lines[i];
  lines.clear();
}

void GEdge::setVisibility(bool val, bool recursive)
{
  GEntity::setVisibility(val);
  if(recursive){
    if(v0) v0->setVisibility(val);
    if(v1) v1->setVisibility(val);
  }
}

void GEdge::recomputeMeshPartitions()
{
  for(unsigned int i = 0; i < lines.size(); i++) {
    int part = lines[i]->getPartition();
    if(part) model()->getMeshPartitions().insert(part);
  }
}
