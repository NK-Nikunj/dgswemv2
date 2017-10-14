#include <mpi.h>
#include <omp.h>

#include "general_definitions.hpp"
#include "swe_definitions.hpp"

#include "swe_initial_condition_functions.hpp"
#include "swe_source_functions.hpp"
#include "swe_true_solution_functions.hpp"

#include "swe_problem.hpp"
#include "swe_kernels_preprocessor.hpp"
#include "swe_kernels_processor.hpp"
#include "swe_kernels_postprocessor.hpp"

#include "simulation/ompi_simulation.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage\n"
                  << "    /path/to/DG_HYPER_SWE input_file\n";
        return 1;
    } else {
        auto t1 = std::chrono::high_resolution_clock::now();
        int provided;
        MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);

        if (provided != MPI_THREAD_MULTIPLE) {
            std::cerr << "MPI_THREAD_MULTIPLE is not provided!\n";

            MPI_Abort(MPI_COMM_WORLD, MPI_ERR_OTHER);

            return 1;
        }

        std::string input_string = std::string(argv[1]);

        OMPISimulation<SWE::Problem> simulation(input_string);

        simulation.Run();

        MPI_Barrier(MPI_COMM_WORLD);
        auto t2 = std::chrono::high_resolution_clock::now();

        int locality_id;
        MPI_Comm_rank(MPI_COMM_WORLD, &locality_id);

        if (locality_id == 0) {
            std::cout << "Time Elapsed (in us): " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1)
                                                         .count() << std::endl;
        }

        MPI_Finalize();

        return 0;
    }
}
