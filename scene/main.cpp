
#include "pxr/pxr.h"
#include "pxr/usd/sdf/layer.h"
#include "pxr/usd/sdf/path.h"
#include "pxr/usd/usd/stage.h"
#include "pxr/usd/usdGeom/mesh.h"
#include "pxr/base/vt/array.h"
#include "pxr/base/gf/range3f.h"
#include <iostream>

PXR_NAMESPACE_USING_DIRECTIVE

int main(int argc, char *argv[])
{
    // Create the layer to populate.
    SdfLayerRefPtr layer = SdfLayer::CreateNew("assignment1.usda");
    
    // Create a UsdStage with that root layer.
    UsdStageRefPtr stage = UsdStage::Open(layer);
    
    // Now we'll populate the stage with content from the objStream.
    //Generates a cube
    std::vector<GfVec3f> objVerts;
    for(int i = 0; i <= 1; i++)
        for(int j = 0; j <= 1; j++)
            for(int k = 0; k <= 1; k++)
                objVerts.emplace_back((float)i,(float)j,(float)k);
    
    std::cout << "objVerts.size() = " << objVerts.size() << std::endl;
    
    if (objVerts.empty())
        throw std::logic_error("Empty array of input vertices");
    
    // Copy objVerts into VtVec3fArray for Usd.
    VtVec3fArray usdPoints;
    usdPoints.assign(objVerts.begin(), objVerts.end());
    
    // Get the mesh elements (index tuples)
    std::vector<std::array<int, 3>> meshElements;
    meshElements.emplace_back(std::array<int, 3>{0, 1, 2});
    meshElements.emplace_back(std::array<int, 3>{1, 3, 2});
    meshElements.emplace_back(std::array<int, 3>{4, 6, 7});
    meshElements.emplace_back(std::array<int, 3>{4, 7, 5});
    meshElements.emplace_back(std::array<int, 3>{0, 4, 5});
    meshElements.emplace_back(std::array<int, 3>{0, 5, 1});
    meshElements.emplace_back(std::array<int, 3>{2, 6, 3});
    meshElements.emplace_back(std::array<int, 3>{3, 6, 7});
    meshElements.emplace_back(std::array<int, 3>{1, 7, 3});
    meshElements.emplace_back(std::array<int, 3>{1, 5, 7});
    meshElements.emplace_back(std::array<int, 3>{0, 2, 4});
    meshElements.emplace_back(std::array<int, 3>{2, 6, 4});
    
    // Usd currently requires an extent, somewhat unfortunately.
    const int nFrames = 20;
    GfRange3f extent;
    for (const auto& pt : usdPoints) {
        extent.UnionWith(pt);
    }
    VtVec3fArray extentArray(2);
    extentArray[0] = extent.GetMin();
    extentArray[1] = extent.GetMax() + GfVec3f(0.03125,.0625,.125) * (float) nFrames;
    
    // Create a mesh for this surface
    UsdGeomMesh mesh = UsdGeomMesh::Define(stage, SdfPath("/TriangulatedSurface0"));
    
    // Set up the timecode
    stage->SetStartTimeCode(0.);
    stage->SetEndTimeCode((double) nFrames);
    
    // Populate the mesh vertex data
    UsdAttribute pointsAttribute = mesh.GetPointsAttr();
    pointsAttribute.SetVariability(SdfVariabilityVarying);
    
    std::vector<double> timeSamples;
    timeSamples.push_back(0.);
    for(int frame = 1; frame <= nFrames; frame++)
        timeSamples.push_back((double)frame);
    for(const auto sample: timeSamples){
        pointsAttribute.Set(usdPoints, sample);
        
//        objVerts[0] += GfVec3f(-0.03125,-0.0625,-0.125);
//        objVerts[1] += GfVec3f(-0.03125,-0.0625,0.125);
//        objVerts[2] += GfVec3f(-0.03125,0.0625,-0.125);
//        objVerts[3] += GfVec3f(-0.03125,0.0625,0.125);
//        objVerts[4] += GfVec3f(0.03125,-0.0625,-0.125);
//        objVerts[5] += GfVec3f(0.03125,-0.0625,0.125);
//        objVerts[6] += GfVec3f(0.03125,0.0625,-0.125);
//        objVerts[7] += GfVec3f(0.03125,0.0625,0.125);
        
        double theta = 0.3;
        
        objVerts[0] = GfVec3f(((objVerts[0].data()[0] * cos(theta)) - (objVerts[0].data()[1] * sin(theta))),
                              ((objVerts[0].data()[0] * sin(theta)) + (objVerts[0].data()[1] * cos(theta))),
                              objVerts[0].data()[2]);
        objVerts[1] = GfVec3f(((objVerts[1].data()[0] * cos(theta)) - (objVerts[1].data()[1] * sin(theta))),
                              ((objVerts[1].data()[0] * sin(theta)) + (objVerts[1].data()[1] * cos(theta))),
                              objVerts[1].data()[2]);
        objVerts[2] = GfVec3f(((objVerts[2].data()[0] * cos(theta)) - (objVerts[2].data()[1] * sin(theta))),
                              ((objVerts[2].data()[0] * sin(theta)) + (objVerts[2].data()[1] * cos(theta))),
                              objVerts[2].data()[2]);
        objVerts[3] = GfVec3f(((objVerts[3].data()[0] * cos(theta)) - (objVerts[3].data()[1] * sin(theta))),
                              ((objVerts[3].data()[0] * sin(theta)) + (objVerts[3].data()[1] * cos(theta))),
                              objVerts[3].data()[2]);
        objVerts[4] = GfVec3f(((objVerts[4].data()[0] * cos(theta)) - (objVerts[4].data()[1] * sin(theta))),
                              ((objVerts[4].data()[0] * sin(theta)) + (objVerts[4].data()[1] * cos(theta))),
                              objVerts[4].data()[2]);
        objVerts[5] = GfVec3f(((objVerts[5].data()[0] * cos(theta)) - (objVerts[5].data()[1] * sin(theta))),
                              ((objVerts[5].data()[0] * sin(theta)) + (objVerts[5].data()[1] * cos(theta))),
                              objVerts[5].data()[2]);
        objVerts[6] = GfVec3f(((objVerts[6].data()[0] * cos(theta)) - (objVerts[6].data()[1] * sin(theta))),
                              ((objVerts[6].data()[0] * sin(theta)) + (objVerts[6].data()[1] * cos(theta))),
                              objVerts[6].data()[2]);
        objVerts[7] = GfVec3f(((objVerts[7].data()[0] * cos(theta)) - (objVerts[7].data()[1] * sin(theta))),
                              ((objVerts[7].data()[0] * sin(theta)) + (objVerts[7].data()[1] * cos(theta))),
                              objVerts[7].data()[2]);
        
        usdPoints.assign(objVerts.begin(), objVerts.end());
    }
    
    VtIntArray faceVertexCounts, faceVertexIndices;
    for (const auto& element : meshElements) {
        faceVertexCounts.push_back(element.size());
        for (const auto& vertex : element)
            faceVertexIndices.push_back(vertex);
    }
    
    // Now set the attributes.
    mesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
    mesh.GetFaceVertexIndicesAttr().Set(faceVertexIndices);
    
    // Set extent.
    mesh.GetExtentAttr().Set(extentArray);
    
    stage->GetRootLayer()->Save();
    
    std::cout << "USD file saved!" << std::endl;
    
    return 0;
}

