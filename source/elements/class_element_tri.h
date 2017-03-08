#ifndef CLASS_ELEMENT_TRI_H
#define CLASS_ELEMENT_TRI_H

#include <vector>

#include "..\class_element.h"
#include "..\class_interface.h"
#include "..\class_basis.h"
#include "..\class_basis_geometry.h"

class ELEMENT_TRI : public ELEMENT {
private:
    double* nodal_coordinates_x;
    double* nodal_coordinates_y;

    BASIS_2D* basis;
    BASIS_GEOM_2D* basis_geom = nullptr;
    double** M_inv = nullptr;

    INTERFACE_2D** interfaces;

    double*** J_inv_t_area;
    double* det_J_area;

    double** surface_J_edge;
    double** normal_edge_x;
    double** normal_edge_y;

    double** area_int_fac_phi;
    double** area_int_fac_dphidx;
    double** area_int_fac_dphidy;
    double*** edge_int_fac_x;
    double*** edge_int_fac_y;

    double** U; 
    std::vector<double**> U_substep;

    double** U_area;
    double*** U_edge;

public:
    ELEMENT_TRI(int, double[], double[], BASIS_2D*, BASIS_GEOM_2D* basis_geom = nullptr);
    ~ELEMENT_TRI();

    void CreateInterfaces();
    void ComputeInternalU(int);
    void ComputeBoundaryU(int);

    //todo: implement inherited functions
    double* get_f_at_gp(double f_bf_coeffs[]){ return nullptr;};
  
    double test_against_phi(double f_at_gp[]){return 0;};
    double test_against_dphidx(double f_at_gp[]){return 0;};
    double test_against_dphidy(double f_at_gp[]){return 0;};

    double* invert_mass_matrix(double f_bf[]){ return nullptr;};

private:
    void ComputeGeometry();
    void ComputeIntegrationFactors();

    double PerformNumericalIntegration(int, double[], double[]);
};

#endif