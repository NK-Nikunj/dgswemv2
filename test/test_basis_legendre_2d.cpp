#include "utilities/almost_equal.hpp"
#include "basis/bases_2D.hpp"

const std::vector<Point<2>> points = {{1.0000000000000000e+00, -1.0000000000000000e+00},
                                      {5.0000000000000000e-01, -1.0000000000000000e+00},
                                      {5.0000000000000000e-01, -5.0000000000000000e-01},
                                      {0.0000000000000000e+00, -1.0000000000000000e+00},
                                      {0.0000000000000000e+00, -5.0000000000000000e-01},
                                      {0.0000000000000000e+00, 0.0000000000000000e+00},
                                      {-5.0000000000000000e-01, -1.0000000000000000e+00},
                                      {-5.0000000000000000e-01, -5.0000000000000000e-01},
                                      {-5.0000000000000000e-01, 0.0000000000000000e+00},
                                      {-5.0000000000000000e-01, 5.0000000000000000e-01},
                                      {-1.0000000000000000e+00, -1.0000000000000000e+00},
                                      {-1.0000000000000000e+00, -5.0000000000000000e-01},
                                      {-1.0000000000000000e+00, 0.0000000000000000e+00},
                                      {-1.0000000000000000e+00, 5.0000000000000000e-01},
                                      {-1.0000000000000000e+00, 1.0000000000000000e+00}};

const std::vector<std::vector<double>> true_vals= {
    {1,-1, 1,-1,1,-1,1,-1,1,-1},
{-0.188228607177734,0.267898559570313,-0.0736389160156250,-0.223144531250000,0.323242187500000,-0.0898437500000000,-0.289062500000000,0.437500000000000,-0.125000000000000,-0.500000000000000},
{0.0354300085600699,-0.0717696382198483,0.00542268995195627,-0.0497934818267822,0.104485511779785,-0.00807189941406250,0.0835571289062500,-0.191406250000000,0.0156250000000000,-0.250000000000000},
{-0.246093750000000,0,0.273437500000000,0,-0.312500000000000,0,0.375000000000000,0,-0.500000000000000,0},
{0.0463218837976456,0,-0.0201356410980225,0,-0.101013183593750,0,-0.108398437500000,0,0.0625000000000000,0},
{0.0605621337890625,0,0.0747680664062500,0,0.0976562500000000,0,0.140625000000000,0,0.250000000000000,0},
{-0.188228607177734,-0.267898559570313,-0.0736389160156250,0.223144531250000,0.323242187500000,0.0898437500000000,-0.289062500000000,-0.437500000000000,-0.125000000000000,0.500000000000000},
{0.0354300085600699,0.0717696382198483,0.00542268995195627,0.0497934818267822,0.104485511779785,0.00807189941406250,0.0835571289062500,0.191406250000000,0.0156250000000000,0.250000000000000},
{0.0463218837976456,0,-0.0201356410980225,0,-0.101013183593750,0,-0.108398437500000,0,0.0625000000000000,0},
{0.0354300085600699,-0.0717696382198483,0.00542268995195627,-0.0497934818267822,0.104485511779785,-0.00807189941406250,0.0835571289062500,-0.191406250000000,0.0156250000000000,-0.250000000000000},
{1,1,1,1,1,1,1,1,1,1},
{-0.188228607177734,-0.267898559570313,-0.0736389160156250,0.223144531250000,0.323242187500000,0.0898437500000000,-0.289062500000000,-0.437500000000000,-0.125000000000000,0.500000000000000},
{-0.246093750000000,0,0.273437500000000,0,-0.312500000000000,0,0.375000000000000,0,-0.500000000000000,0},
{-0.188228607177734,0.267898559570313,-0.0736389160156250,-0.223144531250000,0.323242187500000,-0.0898437500000000,-0.289062500000000,0.437500000000000,-0.125000000000000,-0.500000000000000},
{1,-1,1,-1,1,-1,1,-1,1,-1}};

const std::vector<std::vector<double>> true_Dvals;


int main() {
    
    using Utilities::almost_equal;

    auto is_normal_or_zero = [](double a)->bool {
        return (std::isnormal(a) || (a == 0));
    };

    Basis::Legendre_2D basis;
    bool error_found = false;


    Array2D<double> my_evals = basis.GetPhi(10, points);
    Array3D<double> my_Devals = basis.GetDPhi(10, points);
    
    for (uint dof = 0; dof < 10; ++dof) {
        for (uint pt = 0; pt < 15; ++pt) {
            if (!almost_equal(true_vals[dof][pt], my_evals[dof][pt])) {
                std::cerr << "Error dof(" << dof << "): the true value = " << true_vals[dof][pt]
                          << " your computed value  = " << my_evals[dof][pt] << std::endl;
                error_found = true;
            }
        }
        
        //Check the Gradient evaluations of the Dubiner polynomials
        for (int pt = 0; pt < 15; ++pt) {
            /*The problem is in this if statement:
            if (!is_normal_or_zero(my_Devals[dof][LocalCoordTri::z1][pt]) ||
                !is_normal_or_zero(my_Devals[dof][LocalCoordTri::z2][pt])) {
                std::cerr << "Error in Gradient dof(" << dof << "): the true value = (" << true_Dvals[dof][2 * pt]
                          << ", " << true_Dvals[dof][2 * pt + 1] << ") your computed value  = ("
                          << my_Devals[dof][LocalCoordTri::z1][pt] << ", " << my_Devals[dof][LocalCoordTri::z2][pt]
                          << ")\n";
                error_found = true;*/
            }
        }
    }

/*
    for (uint dof = 0; dof < 10; ++dof) {
        // Check the evaluations of the Legendre polynomials
        for (uint pt = 0; pt < 15; ++pt) {
            if (!is_normal_or_zero(my_evals[dof][pt])) {
                std::cerr << "Error dof(" << dof << "): the true value = " << true_vals[dof][pt]
                          << " your computed value  = " << my_evals[dof][pt] << std::endl;

                error_found = true;
            }
        }
    

        for (uint pt = 0; pt < 15; ++pt) {
            if (!almost_equal(true_vals[dof][pt], my_evals[dof][pt])) {
                std::cerr << "Error dof(" << dof << "): the true value = " << true_vals[dof][pt]
                          << " your computed value  = " << my_evals[dof][pt] << std::endl;

                error_found = true;
            }
        }
        

        //Check the Gradient evaluations of the polynomials
        for (int pt = 0; pt < 15; ++pt) {
            if (!is_normal_or_zero(my_Devals[dof][LocalCoordTri::z1][pt]) ||
                !is_normal_or_zero(my_Devals[dof][LocalCoordTri::z2][pt])) {

                std::cerr << "Error in Gradient dof(" << dof << "): the true value = (" << true_Dvals[dof][2 * pt]
                          << ", " << true_Dvals[dof][2 * pt + 1] << ") your computed value  = ("
                          << my_Devals[dof][LocalCoordTri::z1][pt] << ", " << my_Devals[dof][LocalCoordTri::z2][pt]
                          << ")\n";

                error_found = true;
            }
        }
    

        for (int pt = 0; pt < 15; ++pt) {
            if (!almost_equal(true_Dvals[dof][2 * pt], my_Devals[dof][LocalCoordTri::z1][pt], 1000) ||
                !almost_equal(true_Dvals[dof][2 * pt + 1], my_Devals[dof][LocalCoordTri::z2][pt], 1000)) {

                std::cerr << "Error in Gradient dof(" << dof << pt << "): the true value = (" << std::setprecision(14)
                          << true_Dvals[dof][2 * pt] << ", " << true_Dvals[dof][2 * pt + 1]
                          << ") your computed value  = (" << my_Devals[dof][LocalCoordTri::z1][pt] << ", "
                          << my_Devals[dof][LocalCoordTri::z2][pt] << ")\n";

                error_found = true;
            }
            
        }
        
    }*/
    
    
    if (error_found) {
        return 1;
    }
    return 0;
    
}

