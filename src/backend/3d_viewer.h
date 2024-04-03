#ifdef __unix__
#define M_PI 3.14159265358979323846
#endif
#define _POSIX_C_SOURCE 200809L
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * \mainpage
 * \author hotamir, truckjyn, toricame.
 * \version 0.1
 * \date 25.12.2023
 * \section intro_sec 3DViewer_v1.0-1 was done with
 *   1. C language \n
 *   2. Qt Creator, Qt
 *   3. Qcustomplot
 *   4. Qmake6
 *   5. Doxygen
 *   6. OpenGL
 */

/// @brief  A structure named points containing fields with vertex coordinates
/// along the x, y, and z axes. It has a points variable.
/// @param x double a field with an x-axis coordinate
/// @param y double a field with an y-axis coordinate
/// @param z double a field with an z-axis coordinate
/// @param points a variable of the points structure type
typedef struct points {
  double x;
  double y;
  double z;
} points;

/// @brief A structure named vertex containing fields: Has a vertex variable of
/// the vertex structure type.
/// @param amount_vert int the variable contains the number of vertices.
/// @param coord accepts coordinates of vertices at points x, y, z located in
/// the points structure
/// @param minMaxX[2] the parameters for centering the shape on the x axis
/// (first min, second max).
/// @param minMaxY[2] the parameters for centering the shape on the y axis
/// (first min, second max).
/// @param minMaxZ[2] the parameters for centering the shape on the z axis
/// (first min, second max).
/// @param vertex A variable of the vertex structure type
typedef struct vertex {
  int amount_vert;
  points *coord;
  double minMaxX[2];
  double minMaxY[2];
  double minMaxZ[2];
} vertex;

/// @brief A structure named polygon contains data with the number of values in
/// one polygon and their values.
/// @param p Polygon values. (Coordinate values)
/// @param amount_p The number of values per polygon (faces in the same plane).
///@param poligon A variable of the poligon structure type
typedef struct polygon {
  int *p;
  int amount_p;
} polygon;

/// @brief A structure named Data contains an array of vertices, an array of
/// polygons, and a number of polygons.
/// @param v array of vertices
/// @param p an array of polygons
/// @param amount_poligon number of polygons
/// @param Data A variable of the Data structure type
typedef struct Data {
  vertex *v;
  polygon *p;
  int amount_polygon;
} Data;

/// \file 3d_viewer.h  It contains definitions of data types, structures, and
/// function prototypes intended for use in multiple source data.

/// @brief Parse the file and count the number of vertices and polygons
/// @param [in] FILE file name
/// @param [out] Data data3d a variable of the structure type
/// @return Returns the number of vertices and the number of polygons
Data parse_counting(const char *filename, Data *data3d);
/// @brief The function takes the x, y, z coordinates of the grid vertices from
/// the file using the read_point_value function, and passes them to data3d.
/// The function also takes polygon data from the file using the
/// read_poligon_value function, and transfers them to data3d.
/// @param [in] filename Coordinates of vertices and polygons are taken from the
/// file.
/// @param [out] data3d The received data is transmitted here.
/// @return The received data is transmitted here.
Data parse_values(const char *filename, Data *data3d);
/// @brief The program collects all the values, finds the min max values,
/// centers and scales the object. Then all the received data is transferred to
/// data3d
/// @param [in] filename  Coordinates of vertices and polygons are taken from
/// the file.
/// @param [out] data3d The received data is transmitted here.
/// @return The received data is transmitted here.
Data parse_file(const char *filename, Data *data3d);
/// @brief The function scans the coordinates of the x, y, z vertices and passes
/// them to data3d
/// @param [out] data3d The received data is transmitted here.
/// @param [in] line A pointer to a string read by the getline() function
/// @param [in] len The size of the memory in bytes of the memory block.
/// @param [in] num_of_coord The vertex number.
/// @return The received data is transmitted here.
Data read_point_value(Data *data3d, char *line, int num_of_coord);
/// @brief
/// @param [out] data3d data3d The received data is transmitted here.
/// @param [in] line A pointer to a string read by the getline() function
/// @param [in] len The size of the memory in bytes of the memory block.
/// @param [in] num_of_polygon The poligon number.
/// @param [in] num_of_vertex The vertex number.
/// @return data3d The received data is transmitted here.
Data read_polygon_value(Data *data3d, char *line, int len, int num_of_polygon,
                        int num_of_vertex);
/// @brief Finds min and max values in coordinates along the x, y, z axes
/// @param[in] data3d coordinates of the vertices along the x, y, z axes
/// @return returns min and max values in coordinates along the x, y, z axes
Data find_minMax_points(Data *data3d);
/// @brief Centering the object relative to the origin
/// @param [in] data3d centered values by x, y, z coordinates
/// @return centered values by x, y, z coordinates
Data center_values(Data *data3d);
/// @brief We limit the shape in the range from -1 to 1
/// @param[in]  data3d we pass the min max coordinate values for x, y, z
/// @param [in] scale  The value we want to increase / reduce the shape.
/// @return coordinates on a scale from 0 to 1
Data scale(Data *data3d, double scale);
/// @brief The function allocates memory and uses the parse_file() function to
/// scan the file
/// @param [in] filename Coordinates of vertices and polygons are taken from the
/// file.
/// @return The program collects all the values, finds the min max values,
/// centers and scales the object. Then all the received data is transferred to
/// data3d
Data data_preparation(const char *filename);
/// @brief The function changes the x-coordinate according to the selected angle
/// @param [out] data3d Data with modified x coordinate
/// @param [in] data3d Data required to change
/// @param [in] angle Angle for translating fugure
/// @return The received data is transmitted here.
Data turnX(Data *data3d, double angle);
/// @brief The function changes the y-coordinate according to the selected angle
/// @param [out] data3d Data with modified y coordinate
/// @param [in] data3d Data required to change
/// @param [in] angle Angle for translating fugure
/// @return The received data is transmitted here.
Data turnY(Data *data3d, double angle);
/// @brief The function changes the z-coordinate according to the selected angle
/// @param [out] data3d Data with modified z coordinate
/// @param [in] data3d Data required to change
/// @param [in] angle Angle for translating fugure
/// @return The received data is transmitted here.
Data turnZ(Data *data3d, double angle);
/// @brief The function changes the all coordinates according to offsets
/// @param [out] data3d Data with modified coordinates
/// @param [in] data3d Data required to change
/// @param [in] offsetX offset of the x coordinate
/// @param [in] offsetY offset of the y coordinate
/// @param [in] offsetZ offset of the z coordinate
/// @return The received data is transmitted here.
Data moveObj(Data *data3d, double offsetX, double offsetY, double offsetZ);
/// @brief The function changes the all coordinates according to scale
/// @param [out] data3d Data with modified coordinates
/// @param [in] data3d Data required to change
/// @param [in] scale In accordance with this value, the size of the figure
/// decreases
/// @return The received data is transmitted here.
Data scaleObj(Data *data3d, double scale);
/// @brief The function free memory
/// @param [in] data3d Data required free
void freeAllData(Data *data3d);