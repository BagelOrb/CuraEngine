/** Copyright (C) 2017 Tim Kuipers - Released under terms of the AGPLv3 License */
#ifndef TEXTURE_PROCESSING_FLAT_PICTURE_H
#define TEXTURE_PROCESSING_FLAT_PICTURE_H

#include "../gcodeExport.h"
#include "../utils/intpoint.h"

namespace cura
{

class FlatPicture
{
public:
    struct PointWidth
    {
        Point location;
        coord_t width;
    };

    FlatPicture(const char* filename, const MeshGroup& meshgroup, GCodeExport& gcode);
    
    Material mat;
    GCodeExport& gcode;
    RetractionConfig retraction_config;
    
    Point size = Point(MM2INT(35), MM2INT(35));
    Point offset = Point(MM2INT(50), MM2INT(50));
    coord_t line_dist = 700;
    coord_t sample_dist = 400; // lower than 300 can already cause flooding in the firmware!!!
    
    coord_t nominal_extrusion_width = 350;
    double nominal_speed = 20;
    
    double max_speed = 150;
    double min_speed = 5;
    
    
    double normal_speed = 40;
    coord_t dense_fill_line_width = 350;
    
    double flow = 0.9;
    
    double travel_speed = nominal_speed;
    
    void generateLines(std::vector<std::vector<PointWidth>>& black_lines);
    /*!
     * 
     * \param starting_direction 1 or 0: whether to start going up the first line and going down the second etc., or going down the first and up the second
     */
    void drawLines(const std::vector<std::vector<PointWidth>>& lines, coord_t layer_height, bool transposed);

    void drawDenseFill(coord_t layer_height, float speed, bool transposed);
    
    void drawPoly(Polygons& perimeter, float speed, coord_t layer_height, coord_t width);
};

} // namespace cura

#endif // TEXTURE_PROCESSING_FLAT_PICTURE_H