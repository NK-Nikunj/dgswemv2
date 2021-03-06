#ifndef EHDG_SWE_POST_WRITE_VTK_HPP
#define EHDG_SWE_POST_WRITE_VTK_HPP

#include "general_definitions.hpp"

namespace SWE {
namespace EHDG {
void Problem::write_VTK_data_kernel(ProblemMeshType& mesh, std::ofstream& raw_data_file) {
    Array2D<double> cell_data;
    Array2D<double> point_data;

    cell_data.resize(4);
    point_data.resize(4);

    mesh.CallForEachElement([&cell_data, &point_data](auto& elt) {
        elt.WriteCellDataVTK(elt.data.state[0].ze, cell_data[0]);
        elt.WriteCellDataVTK(elt.data.state[0].qx, cell_data[1]);
        elt.WriteCellDataVTK(elt.data.state[0].qy, cell_data[2]);
        elt.WriteCellDataVTK(elt.data.state[0].bath, cell_data[3]);

        elt.WritePointDataVTK(elt.data.state[0].ze, point_data[0]);
        elt.WritePointDataVTK(elt.data.state[0].qx, point_data[1]);
        elt.WritePointDataVTK(elt.data.state[0].qy, point_data[2]);
        elt.WritePointDataVTK(elt.data.state[0].bath, point_data[3]);
    });

    std::vector<uint> elt_id_data;

    mesh.CallForEachElement([&elt_id_data](auto& elt) {
        for (uint cell = 0; cell < N_DIV * N_DIV; cell++) {
            elt_id_data.push_back(elt.GetID());
        }
    });

    raw_data_file << "CELL_DATA " << (*cell_data.begin()).size() << std::endl;

    raw_data_file << "SCALARS ze_cell double 1" << std::endl;
    raw_data_file << "LOOKUP_TABLE default" << std::endl;
    for (auto it = cell_data[0].begin(); it != cell_data[0].end(); it++)
        raw_data_file << *it << std::endl;

    raw_data_file << "SCALARS qx_cell double 1" << std::endl;
    raw_data_file << "LOOKUP_TABLE default" << std::endl;
    for (auto it = cell_data[1].begin(); it != cell_data[1].end(); it++)
        raw_data_file << *it << std::endl;

    raw_data_file << "SCALARS qy_cell double 1" << std::endl;
    raw_data_file << "LOOKUP_TABLE default" << std::endl;
    for (auto it = cell_data[2].begin(); it != cell_data[2].end(); it++)
        raw_data_file << *it << std::endl;

    raw_data_file << "SCALARS bath_cell double 1" << std::endl;
    raw_data_file << "LOOKUP_TABLE default" << std::endl;
    for (auto it = cell_data[3].begin(); it != cell_data[3].end(); it++)
        raw_data_file << *it << std::endl;

    raw_data_file << "SCALARS ID unsigned_int 1" << std::endl;
    raw_data_file << "LOOKUP_TABLE default" << std::endl;
    for (auto it = elt_id_data.begin(); it != elt_id_data.end(); it++)
        raw_data_file << *it << std::endl;

    raw_data_file << "POINT_DATA " << (*point_data.begin()).size() << std::endl;

    raw_data_file << "SCALARS ze_point double 1" << std::endl;
    raw_data_file << "LOOKUP_TABLE default" << std::endl;
    for (auto it = point_data[0].begin(); it != point_data[0].end(); it++)
        raw_data_file << *it << std::endl;

    raw_data_file << "SCALARS qx_point double 1" << std::endl;
    raw_data_file << "LOOKUP_TABLE default" << std::endl;
    for (auto it = point_data[1].begin(); it != point_data[1].end(); it++)
        raw_data_file << *it << std::endl;

    raw_data_file << "SCALARS qy_point double 1" << std::endl;
    raw_data_file << "LOOKUP_TABLE default" << std::endl;
    for (auto it = point_data[2].begin(); it != point_data[2].end(); it++)
        raw_data_file << *it << std::endl;

    raw_data_file << "SCALARS bath_point double 1" << std::endl;
    raw_data_file << "LOOKUP_TABLE default" << std::endl;
    for (auto it = point_data[3].begin(); it != point_data[3].end(); it++)
        raw_data_file << *it << std::endl;
}
}
}

#endif